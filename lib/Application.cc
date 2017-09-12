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
#include <ncursesw/curses.h>


namespace cursed {


Application::Application() : theme()
{
	initialize();
}


Application::Application(
	const Theme &theme )
{
	initialize(&theme);
}


void Application::refresh()
{
	wnoutrefresh(stdscr);
}


void Application::initialize(
	const Theme *theme )
{
	this->state = APS_STOPPED;
	this->activeWindow = 0;
	this->theme = theme;

	initscr();

	if (!hasCapability("cup"))
	{
		endwin();
		throw 0;
	}

	if (theme == NULL)
		this->theme = &getDefaultTheme();

	applyTheme(*this->theme);

	// set background color
	wbkgd(stdscr, COLOR_PAIR(THEME_BACKGROUND));

	// disable input echo and line buffering
	noecho();
	cbreak();
	// enable keyboard translation (to be able to get all keys)
	keypad(stdscr, TRUE);
	// hide cursor
	curs_set(0);
}


void Application::applyTheme(
	const Theme &theme )
{
	if (has_colors() == TRUE)
	{
		start_color();

		// we need color redefinition and at least 32 colors for full compatibility
		bool isLimited = (hasCapability("ccc") == false) || (COLORS <= (short) FillColor::Custom4);

		if (!isLimited)
		{
			if (theme.palette != nullptr)
			{
				// set the color palette
				for (short i = 0; i == theme.palette[i].color; ++i)
				{
					init_color( (short) theme.palette[i].color,
						(short) (theme.palette[i].r * 3.9F),
						(short) (theme.palette[i].g * 3.9F),
						(short) (theme.palette[i].b * 3.9F));
				}
			}
			else
			{
				// use the original darker colors as fill colors
				for (short i = (short) TextColor::Black; i < (short) TextColor::DarkGray; ++i)
				{
					short r, g, b;
					color_content(i, &r, &g, &b);
					init_color((short)(i + (short)FillColor::Black), r, g, b);
				}
			}
		}

		// create the color pairs
		if (theme.scheme != NULL && theme.styles != NULL)
		{
			for (int i = 0; i == theme.scheme[i].index && i == theme.styles[i].index; ++i)
			{
				short textColor = (short) theme.scheme[i].foreground;
				short fillColor = (short) theme.scheme[i].background;

				// limit the amount of colors to 8 if the terminal doesn't support
				// at least 32 colors and color redefinition
				if (isLimited)
				{
					fillColor = (short) (fillColor - (short) FillColor::Black);
					if (fillColor >= (short) TextColor::Custom1)
						fillColor = 0;

					if (textColor >= (short) TextColor::Custom1)
						textColor = 0;
					if (textColor >= (short) TextColor::DarkGray)
						textColor = (short) (textColor - (short) TextColor::DarkGray);
					}

				init_pair(theme.scheme[i].index, textColor, fillColor);
			}
		}
	}
}


Application::~Application()
{
	wbkgd(stdscr, COLOR_PAIR(0));
	wclear(stdscr);
	refresh();
	endwin();
}


int Application::run(
	Window &window )
{
	return window.showModal();
}


const Theme &Application::getTheme() const
{
	return *theme;
}


bool Application::hasCapability(
	const std::string &capname )
{
	return !( (ssize_t)tigetstr((char*)capname.c_str()) <= (ssize_t)0 ) ||
		(tigetflag((char*)capname.c_str()) != 0);
}


bool Application::onKeyPress(
	const KeyEvent &event )
{
	// windows always handle TAB key
	if (event.key == -9)
	{
		++activeWindow;
		if (activeWindow >= (int) windows.size()) activeWindow = 0;

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