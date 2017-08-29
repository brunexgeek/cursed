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


#include <stdint.h>


namespace cursed {


enum class TextColor
{
	Black        = 0,
	Red          = 1,
	Green        = 2,
	Yellow       = 3,
	Blue         = 4,
	Magenta      = 5,
	Cyan         = 6,
	LightGray    = 7,
	DarkGray     = 8,
	LightRed     = 9,
	LightGreen   = 10,
	LightYellow  = 11,
	LightBlue    = 12,
	LightMagenta = 13,
	LightCyan    = 14,
	White        = 15,
	Custom1      = 16,
	Custom2      = 17,
	Custom3      = 18,
	Custom4      = 19,
};


enum class FillColor
{
	Black        = 20,
	Red          = 21,
	Green        = 22,
	Yellow       = 23,
	Blue         = 24,
	Magenta      = 25,
	Cyan         = 26,
	Gray         = 27,
	Custom1      = 28,
	Custom2      = 29,
	Custom3      = 30,
	Custom4      = 31,
};


struct ThemeColor
{
	uint8_t color;
	uint8_t r, g, b;
};

struct ThemePair
{
	uint8_t index;
	TextColor foreground;
	FillColor background;
};

struct ThemeStyle
{
	int index, color, attribute;
};

struct Theme
{
	const ThemeColor *palette;
	const ThemePair *scheme;
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
#define THEME_TEXTBOX                  0x09
#define THEME_TEXTBOX_ACTIVE           0x0A
#define THEME_TEXTBOX_CURSOR           0x0B
#define THEME_CHECKBOX                 0x0C
#define THEME_CHECKBOX_ACTIVE          0x0D


#define ESCAPER             '\x1B'
#define COMMAND_BOLD        '*'
#define COMMAND_UNDERLINE   '_'
#define COMMAND_ESCAPE      ESCAPER



} // namespace cursed


#endif // CURSED_THEME_HH