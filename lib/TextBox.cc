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


namespace cursed {


TextBox::TextBox(
	Window &parent,
	const std::wstring &text,
	int height,
	int width,
	int y,
	int x ) : Component(parent, 1, width, y, x), text(text)
{
	position = (int)text.length();
}


TextBox::~TextBox()
{
	// nothing to do
}


void TextBox::paint()
{
	std::wstring temp;

	if (isActive())
		wattrset( (WINDOW*) content, getTheme().styles[THEME_INPUTBOX_ACTIVE].style);
	else
		wattrset( (WINDOW*) content, getTheme().styles[THEME_INPUTBOX].style);

	--width;

	if ((int)text.length() > width)
		temp = text.substr(text.length() - width);
	else
	{
		temp = text;
		int fill = width - (int)text.length();
		if (fill > 0) temp.append(fill, ' ');
	}

	temp += ' ';
	width++;

	mvwaddwstr( (WINDOW*) content, 0, 0, temp.c_str());
	wattrset( (WINDOW*) content, getTheme().styles[THEME_WINDOW].style);
	wmove( (WINDOW*) content, 0, std::min(position, width-1));
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


bool TextBox::onKeyPress(
	const KeyEvent &event )
{
	bool handled = false;

	if (event.key == KEY_BACKSPACE)
	{
		if (!text.empty())
		{
			text.pop_back();
			--position;
			handled = true;
		}
	}
	else
	if (event.key == KEY_LEFT)
	{
		--position;
		if (position < 0) position = 0;
		handled = true;
	}
	else
	if (event.key == KEY_RIGHT)
	{
		++position;
		if (position >= (int) text.length()) position = (int) text.length();
		handled = true;
	}
	else
	if (event.key == KEY_END)
	{
		position = (int) text.length();
		handled = true;
	}
	else
	if (event.key == KEY_HOME)
	{
		position = 0;
		handled = true;
	}
	else
	if ((event.key >= '\x20' && event.key <= '\x7E'))
	{
		text.insert(position, 1, event.key);
		++position;
		handled = true;
	}

	if (handled)
		paint();

	return handled;
}


} // namespace cursed