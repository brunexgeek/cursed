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
#include <cursed/Application.hh>


namespace cursed {


Application::Application() : theme(THEME_DEFAULT)
{
	initialize();
}


Application::Application(
	const Theme &theme ) : theme(theme)
{
	initialize();
}


void Application::refresh()
{
	wnoutrefresh(stdscr);
}


void Application::initialize()
{
	this->state = APS_STOPPED;
	this->activeWindow = 0;

	initscr();

	if (!hasCapability("cup"))
	{
		endwin();
		throw 0;
	}

	if (has_colors() == TRUE)
	{
		start_color();

		// create pairs for every color in the theme
		for (int i = 0; i == theme.colors[i].index && i == theme.styles[i].index; ++i)
			init_pair(theme.colors[i].index, theme.colors[i].fgColor, theme.colors[i].bgColor);

		// set background color
		wbkgd(stdscr, COLOR_PAIR(THEME_BACKGROUND));
	}
	// disable input echo and line buffering
	noecho();
	cbreak();
	// enable keyboard translation (to be able to get all keys)
	keypad(stdscr, TRUE);
	// hide cursor
	curs_set(0);
}


Application::~Application()
{
	bkgd(COLOR_PAIR(THEME_SHADOW));
	clear();
	refresh();
	endwin();
}


void Application::run()
{
	if (windows.size() == 0) return;

	state = APS_RUNNING;

	onStart();

	KeyEvent event;
	while (state != APS_STOPPING)
	{
		event.modifiers = 0;
		event.key = wgetch(stdscr);

		if (event.key == '\x1B')
		{
			event.key = wgetch(stdscr);
			if (event.key == '\x09')
			{
				event.key |= 0x80000000;
			}
			else
				continue;
		}

		if (onKeyPress(event))
		{
			this->refresh();
			windows[activeWindow]->refresh();
			doupdate();
		}
	}

	state = APS_STOPPING;
	onStop();

	state = APS_STOPPED;
}


void Application::run(
	Window &window )
{
	window.showModal();
}


void Application::stop()
{
	state = APS_STOPPING;
}


void Application::onStart()
{

}


void Application::onStop()
{

}


const Theme &Application::getTheme() const
{
	return theme;
}


void Application::add(
	Window &window )
{
	windows.push_back(&window);
}

void Application::remove(
	Window &window )
{
	(void) window;
}


bool Application::isRunning() const
{
	return state == APS_RUNNING;
}


bool Application::hasCapability(
	const std::string &capname )
{
	return !( (ssize_t)tigetstr(capname.c_str()) <= (ssize_t)0 );
}


bool Application::onKeyPress(
	const KeyEvent &event )
{
	// windows always handle TAB key
	if ((uint32_t)event.key == 0x80000009)
	{
		int old = activeWindow;

		// notify the control that it's losing focus
		//windows[activeWindow]->onActive(false);

		// look for the next non-static control
		++activeWindow;
		if (activeWindow >= (int) windows.size()) activeWindow = 0;

		windows[old]->paint();

		// notify the control that it's gaining focus
		//windows[activeWindow]->onActive(true);
		windows[activeWindow]->paint();

		return true;
	}

	// send the key event to the active control
	bool handled = false;
	handled = windows[activeWindow]->onKeyPress(event);

	if (handled == false)
	{
		// do additional key handling
	}

	return handled;
}


int Application::screenWidth() const
{
	int h, w;
	getmaxyx(stdscr, h, w);
	(void) h;
	return w;
}


int Application::screenHeight() const
{
	int h, w;
	getmaxyx(stdscr, h, w);
	return h;
}


} // namespace cursed