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

#include <cursed/Label.hh>
#include <ncursesw/curses.h>


namespace cursed {


void Label::render(
	const std::wstring &text,
	int y,
	int x )
{
	const wchar_t *current, *start;

	current = start = text.c_str();

	wmove( (WINDOW*)content, y, x);
	//wattrset(content, COLOR_PAIR(THEME_LABEL) | A_NORMAL );
	//wbkgd(content, COLOR_PAIR(THEME_LABEL) );

	bool isBold = false;
	bool isUnderline = false;

	while (*current != 0)
	{
		if (*current == '\x1B' || *current == COMMAND_BOLD || *current == COMMAND_UNDERLINE)
		{
			wchar_t command = *current;

			// flush the actual content
			if (current - start > 0)
				waddnwstr((WINDOW*)content, start, (int)(current - start));
			++current;

			switch (command)
			{
				case COMMAND_BOLD:
					isBold = !isBold;
					if (isBold)
						wattron((WINDOW*)content, COLOR_PAIR(THEME_LABEL_HIGHLIGHT));
					else
						wattroff((WINDOW*)content, COLOR_PAIR(THEME_LABEL_HIGHLIGHT));
					break;

				case COMMAND_UNDERLINE:
					isUnderline = !isUnderline;
					if (isUnderline)
						wattron((WINDOW*)content, A_UNDERLINE);
					else
						wattroff((WINDOW*)content, A_UNDERLINE);
					break;

				case COMMAND_ESCAPE:
					waddch((WINDOW*)content, *current);
					++current;
					break;
			}

			start = current;
			continue;
		}

		++current;
	}

	if (current >= start)
		waddnwstr((WINDOW*)content, start, (int)(current - start));
}


Label::Label(
	Window &parent,
	const std::wstring &text,
	int height,
	int width,
	int y,
	int x ) : Component(parent, height, width, y, x, false), text(text)
{

}


Label::~Label()
{
	// nothing to do
}


void Label::paint()
{
	setBackground(THEME_LABEL);
	setStyle(THEME_LABEL);

	render(text, y, x);
	touchwin((WINDOW*) content);
}


void Label::onActive(
	bool state )
{
	(void) state;
	// nothing to do
}

bool Label::onKeyPress(
	const KeyEvent &event )
{
	(void) event;
	return false;
}

const std::wstring &Label::getText() const
{
	return text;
}

} // namespace cursed