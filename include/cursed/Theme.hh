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

#ifndef CURSED_THEME_HH
#define CURSED_THEME_HH


#include <ncursesw/curses.h>


namespace cursed {


struct ThemeColor
{
	short index, fgColor, bgColor;
};

struct ThemeStyle
{
	int index, style;
};

struct Theme
{
	const ThemeColor *colors;
	const ThemeStyle *styles;
};


#define THEME_BACKGROUND               0x01
#define THEME_SHADOW                   0x02
#define THEME_WINDOW                   0x03
#define THEME_WINDOW_TITLE             0x04
#define THEME_BUTTON                   0x05
#define THEME_BUTTON_ACTIVE            0x06
#define THEME_LABEL                    0x07
#define THEME_LABEL_HIGHLIGHT          0x08
#define THEME_TEXTBOX                 0x09
#define THEME_TEXTBOX_ACTIVE          0x0A
#define THEME_TEXTBOX_CURSOR          0x0B

#define POSITION_CENTER     (int)(-1)
#define ESCAPER             '\x1B'
#define COMMAND_BOLD        '*'
#define COMMAND_UNDERLINE   '_'
#define COMMAND_ESCAPE      ESCAPER



static const ThemeColor THEME_COLORS[] =
{
	{ 0,                        0,           0 },
	{ THEME_BACKGROUND,         COLOR_WHITE, COLOR_BLUE },
	{ THEME_SHADOW,             COLOR_BLACK, COLOR_BLACK },
	{ THEME_WINDOW,             COLOR_BLACK, COLOR_WHITE },
	{ THEME_WINDOW_TITLE,       COLOR_BLUE,  COLOR_WHITE },
	{ THEME_BUTTON,             COLOR_BLACK, COLOR_WHITE },
	{ THEME_BUTTON_ACTIVE,      COLOR_BLUE,  COLOR_WHITE },
	{ THEME_LABEL,              COLOR_BLACK, COLOR_WHITE },
	{ THEME_LABEL_HIGHLIGHT,    COLOR_BLUE,  COLOR_WHITE },
	{ THEME_TEXTBOX,            COLOR_BLACK, COLOR_WHITE },
	{ THEME_TEXTBOX_ACTIVE,     COLOR_BLACK, COLOR_WHITE },
	{ THEME_TEXTBOX_CURSOR,     COLOR_BLACK, COLOR_WHITE },
	{ 0,                        0,           0 },
};

static const ThemeStyle THEME_STYLES[] =
{
	{ 0,                        0 },
	{ THEME_BACKGROUND,         COLOR_PAIR(THEME_BACKGROUND) },
	{ THEME_SHADOW,             COLOR_PAIR(THEME_SHADOW) },
	{ THEME_WINDOW,             COLOR_PAIR(THEME_WINDOW) },
	{ THEME_WINDOW_TITLE,       COLOR_PAIR(THEME_WINDOW_TITLE) },
	{ THEME_BUTTON,             COLOR_PAIR(THEME_BUTTON) | A_DIM },
	{ THEME_BUTTON_ACTIVE,      COLOR_PAIR(THEME_BUTTON_ACTIVE) | A_REVERSE },
	{ THEME_LABEL,              COLOR_PAIR(THEME_LABEL) },
	{ THEME_LABEL_HIGHLIGHT,    COLOR_PAIR(THEME_LABEL_HIGHLIGHT) },
	{ THEME_TEXTBOX,            COLOR_PAIR(THEME_TEXTBOX) | A_REVERSE },
	{ THEME_TEXTBOX_ACTIVE,     COLOR_PAIR(THEME_TEXTBOX_ACTIVE) | A_REVERSE },
	{ THEME_TEXTBOX_CURSOR,     COLOR_PAIR(THEME_TEXTBOX_CURSOR) },
	{ 0,                        0 },
};

static const Theme THEME_DEFAULT =
{
	THEME_COLORS, THEME_STYLES,
};


} // namespace cursed


#endif // CURSED_THEME_HH