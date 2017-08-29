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

#include <cursed/TextBox.hh>
#include <cursed/Text.hh>
#include <ncursesw/curses.h>


namespace cursed {


TextBox::TextBox(
	Window &parent,
	const std::wstring &text,
	int height,
	int width,
	int y,
	int x ) : Component(parent, 1, width, y, x, true), text(text)
{
	(void) height;

	position = (int) text.length();
	end = position - 1;
	if (end < 0) end = 0;
	start = (end + 1) - (width - 1);
	if (start < 0) start = 0;
	cursor = position - start;
}


TextBox::~TextBox()
{
	// nothing to do
}


void TextBox::paint()
{
	std::wstring temp;

	//mvprintw(0, 0, "s:%02d  e:%02d  c:%02d  p:%02d", start, end, cursor, position);

	if (isActive())
	{
		setBackground(THEME_TEXTBOX_ACTIVE);
		setStyle(THEME_TEXTBOX_ACTIVE);
	}
	else
	{
		setBackground(THEME_TEXTBOX);
		setStyle(THEME_TEXTBOX);
	}
	wclear( (WINDOW*)content );

	temp = text.substr(start, (end - start) + 1);

	mvwaddwstr( (WINDOW*) content, 0, 0, temp.c_str());

	if (isActive())
	{
		wmove( (WINDOW*) content, 0, cursor );
		wcursyncup( (WINDOW*) content );
	}

	touchwin( (WINDOW*) content);
}


const std::wstring &TextBox::getText() const
{
	return text;
}


void TextBox::onActive(
	bool state )
{
	if (state)
		curs_set(2);
	else
		curs_set(0);
}


void TextBox::moveCursor(
	int direction )
{
	cursor += direction;

	if (direction < 0)
	{
		if (cursor < 0)
		{
			cursor = 0;
			if (start > 0) --start;
		}
	}
	else
	if (direction > 0)
	{
		// the cursor cannot exceed the component edge
		if (cursor >= width)
		{
			cursor = std::min( (int) text.length(), width - 1);
			if (end < (int) text.length() - 1)
				++start;
		}
		else
		// if the string don't fill the width, limit the cursor
		if (start + cursor > (int) text.length())
			cursor = (int) text.length() - start;
	}

	end = start + std::min( (int) text.length() - start, width - 2 );
	position = start + cursor;
}


bool TextBox::onKeyPress(
	const KeyEvent &event )
{
	bool handled = false;

	if (event.key == KEY_BACKSPACE)
	{
		if (position > 0)
		{
			text.erase(position - 1, 1);
			moveCursor(-1);
			handled = true;
		}
	}
	else
	if (event.key == KEY_DC)
	{
		if (position < (int) text.length())
		{
			text.erase(position, 1);
			moveCursor(0);
			handled = true;
		}
	}
	else
	if (event.key == KEY_LEFT)
	{
		moveCursor(-1);
		handled = true;
	}
	else
	if (event.key == KEY_RIGHT)
	{
		moveCursor(1);
		handled = true;
	}
	else
	if (event.key == KEY_END)
	{
		start  = (int) text.length() - width + 1;
		if (start < 0) start = 0;
		cursor = std::min( (int) text.length(), width - 1 );
		moveCursor(0);
		handled = true;
	}
	else
	if (event.key == KEY_HOME)
	{
		start = 0;
		cursor = 0;
		moveCursor(0);
		handled = true;
	}
	else
	if ((event.key >= '\x20' && event.key <= '\x7E'))
	{
		text.insert(position, 1, event.key);
		moveCursor(1);
		handled = true;
	}

	return handled;
}


} // namespace cursed