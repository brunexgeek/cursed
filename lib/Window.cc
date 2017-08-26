/*
 *  Copyright 2017 Bruno Ribeiro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cursed/Window.hh>


namespace cursed {


Window::Window(
	Application &app,
	Window &parent,
	const std::wstring &title,
	int height,
	int width,
	int y,
	int x ) : app(app)
{
	initialize(&parent, &title, height, width, y, x);
}

Window::Window(
	Application &app,
	const std::wstring &title,
	int height,
	int width,
	int y,
	int x ) : app(app)
{
	initialize(NULL, &title, height, width, y, x);
}

void Window::initialize(
	Window *parent,
	const std::wstring *title,
	int height,
	int width,
	int y,
	int x )
{
	this->height = height;
	this->width = width;
	this->py = y;
	this->px = x;
	this->result = -1;
	this->activeComponent = 0;
	this->allStatic = true;

	if (title != NULL)
		this->title = *title;
	if (parent != NULL)
		this->parent = parent;

	shadow = window = content = NULL;

	WINDOW *pw = stdscr;
	if (parent != NULL) pw = (WINDOW*) parent->content;

	shadow = subwin(pw, height, width, y + 1, x + 2);
	window = subwin(pw, height, width, y, x);
	content = derwin( (WINDOW*) window, height - 4, width - 4, 2, 2);
}

Window::~Window()
{
	//wborder(window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	//wrefresh(window);
	if (content != NULL) delwin( (WINDOW*) content );
	if (window != NULL) delwin( (WINDOW*) window );
	if (shadow != NULL) delwin( (WINDOW*) shadow );
}


const Theme &Window::getTheme() const
{
	return app.getTheme();
}


void Window::paint()
{
	if (shadow != NULL)
	{
		setBackground(shadow, THEME_SHADOW);
		wclear( (WINDOW*) shadow );
		wborder( (WINDOW*) shadow, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	}

	if (window != NULL)
	{
		setBackground(window, THEME_WINDOW);
		wclear( (WINDOW*) window );
		box( (WINDOW*) window, 0 , 0);
		if (!title.empty())
		{
			std::wstring temp = L" " + title + L" ";
			mvwaddwstr( (WINDOW*) window, 0, 2, temp.c_str());
		}
	}

	if (content != NULL)
	{
		setBackground(content, THEME_WINDOW);
		wclear( (WINDOW*) content );
	}

	touchwin( (WINDOW*) shadow);
	touchwin( (WINDOW*) window);
	touchwin( (WINDOW*) content);

	// paint all controls
	auto it = controls.begin();
	for (; it != controls.end(); ++it) (*it)->paint();
}


int Window::getClientWidth() const
{
	return width - 4;
}

int Window::getClientHeight() const
{
	return height - 4;
}

int Window::getWidth() const
{
	return width;
}

int Window::getHeight() const
{
	return height;
}


/*
void Window::render(
	const std::wstring &text,
	int y,
	int x )
{
	ncurses_render(content, text, y, x);
}*/


void Window::addComponent(
	Component &control,
	const bool *interactive )
{
	// Note: never use fields or functions from 'control' here!
	controls.push_back(&control);
	if (interactive == NULL)
		allStatic &= !control.isInteractive();
	else
		allStatic &= !(*interactive);
}


void Window::close(
	int result )
{
	if (result < 0) result = 0;
	this->result = result;
}


Component *Window::getActive()
{
	if (activeComponent <= (int) controls.size())
		return controls[activeComponent];
	else
		return NULL;
}


void Window::setActive(
	Component *control )
{
	activeComponent = -1;

	if (control != NULL)
	{
		auto it = controls.begin();
		for (; it != controls.end(); ++it)
		{
			if (*it == control)
				activeComponent = (int) (it - controls.begin());
		}
	}
}


void Window::setActive(
	Component &control )
{
	setActive(&control);
}


void Window::setActive(
	int index )
{
	if (index < 0 || index >= (int) controls.size())
		activeComponent = -1;
	else
		activeComponent = index;
}


int Window::showModal()
{
	KeyEvent event;
	result = -1;

	paint();

	// notify the active control that it's gaining focus
	if (activeComponent >= 0 && activeComponent < (int) controls.size())
	{
		controls[activeComponent]->onActive(true);
		controls[activeComponent]->paint();
	}

	this->refresh();
	if (activeComponent >= 0 && activeComponent < (int) controls.size())
		controls[activeComponent]->refresh();
	doupdate();

	while (result < 0)
	{
		event.modifiers = 0;
		event.key = wgetch(stdscr);

		if (onKeyPress(event))
		{
			this->refresh();
			if (activeComponent >= 0 && activeComponent < (int) controls.size())
			{
				controls[activeComponent]->paint();
				controls[activeComponent]->refresh();
			}
			doupdate();
		}
	}

	return result;
}


void Window::refresh()
{
	wnoutrefresh( stdscr);
	wnoutrefresh( (WINDOW*) shadow);
	wnoutrefresh( (WINDOW*) window);
	wnoutrefresh( (WINDOW*) content);

	// refresh all controls
	auto it = controls.begin();
	for (; it != controls.end(); ++it) (*it)->refresh();
}


void Window::activateNext(
	int direction )
{
	if (controls.size() == 0) return;

	int old = activeComponent;

	// notify the control that it's losing focus
	if (activeComponent >= 0 && activeComponent < (int) controls.size())
		controls[activeComponent]->onActive(false);

	// look for the next non-static control
	do {
		activeComponent += direction;
		if (activeComponent >= (int) controls.size())
			activeComponent = 0;
		else
		if (activeComponent < 0)
			activeComponent = (int) controls.size() - 1;
	} while (!controls[activeComponent]->isInteractive());

	controls[old]->paint();

	// notify the control that it's gaining focus
	controls[activeComponent]->onActive(true);
	controls[activeComponent]->paint();
}


bool Window::onKeyPress(
	const KeyEvent &event )
{
	// windows always handle the TAB key
	if (!allStatic && event.key == '\x09' && event.modifiers == 0)
	{
		activateNext(1);
		return true;
	}

	// send the key event to the active control
	bool handled = false;
	if (activeComponent >= 0 && activeComponent <= (int) controls.size())
		handled = controls[activeComponent]->onKeyPress(event);

	if (!handled && !allStatic)
	{
		if (event.key == KEY_LEFT)
		{
			activateNext(-1);
			return true;
		}
		else
		if (event.key == KEY_RIGHT)
		{
			activateNext(1);
			return true;
		}
	}

	return handled;
}


void Window::setBackground(
	void *target,
	int id )
{
	wbkgdset( (WINDOW*) target, getTheme().styles[id].color );
	wattrset( (WINDOW*) target, getTheme().styles[id].color | getTheme().styles[id].attribute);
}


} // namespace cursed