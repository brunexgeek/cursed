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

#include <cursed/Theme.hh>
#include <cursed/Application.hh>
#include <ncursesw/curses.h>


namespace cursed {


static const ThemeColor THEME_COLOR_PALETTE[] =
{
	{ (uint8_t) TextColor::Black        , 0x2e, 0x34, 0x36 },
	{ (uint8_t) TextColor::Red          , 0xcc, 0x00, 0x00 },
	{ (uint8_t) TextColor::Green        , 0x4e, 0x9a, 0x06 },
	{ (uint8_t) TextColor::Yellow       , 0xc4, 0xa0, 0x00 },
	{ (uint8_t) TextColor::Blue         , 0x34, 0x65, 0xa4 },
	{ (uint8_t) TextColor::Magenta      , 0x75, 0x50, 0x7b },
	{ (uint8_t) TextColor::Cyan         , 0x06, 0x98, 0x9a },
	{ (uint8_t) TextColor::LightGray    , 0xd3, 0xd7, 0xcf },
	{ (uint8_t) TextColor::DarkGray     , 0x55, 0x57, 0x53 },
	{ (uint8_t) TextColor::LightRed     , 0xef, 0x29, 0x29 },
	{ (uint8_t) TextColor::LightGreen   , 0x8a, 0xe2, 0x34 },
	{ (uint8_t) TextColor::LightYellow  , 0xfc, 0xe9, 0x4f },
	{ (uint8_t) TextColor::LightBlue    , 0x72, 0x9f, 0xcf },
	{ (uint8_t) TextColor::LightMagenta , 0xad, 0x7f, 0xa8 },
	{ (uint8_t) TextColor::LightCyan    , 0xad, 0x7f, 0xa8 },
	{ (uint8_t) TextColor::White        , 0xee, 0xee, 0xec },
	{ (uint8_t) TextColor::Custom1      , 0xe0, 0x65, 0x00 },
	{ (uint8_t) TextColor::Custom2      , 0xff, 0x73, 0x00 },
	{ (uint8_t) TextColor::Custom3      , 0x00, 0xb3, 0x69 },
	{ (uint8_t) TextColor::Custom4      , 0x00, 0xff, 0x96 },

	{ (uint8_t) FillColor::Black        , 0x2e, 0x34, 0x36 },
	{ (uint8_t) FillColor::Red          , 0xcc, 0x00, 0x00 },
	{ (uint8_t) FillColor::Green        , 0x4e, 0x9a, 0x06 },
	{ (uint8_t) FillColor::Yellow       , 0xc4, 0xa0, 0x00 },
	{ (uint8_t) FillColor::Blue         , 0x34, 0x65, 0xa4 },
	{ (uint8_t) FillColor::Magenta      , 0x75, 0x50, 0x7b },
	{ (uint8_t) FillColor::Cyan         , 0x06, 0x98, 0x9a },
	{ (uint8_t) FillColor::Gray         , 0xd3, 0xd7, 0xcf },
	{ (uint8_t) FillColor::Custom1      , 0xe0, 0x65, 0x00 },
	{ (uint8_t) FillColor::Custom2      , 0xff, 0x73, 0x00 },
	{ (uint8_t) FillColor::Custom3      , 0x00, 0xb3, 0x69 },
	{ (uint8_t) FillColor::Custom4      , 0x00, 0xff, 0x96 },

	{ 0                                 , 0x00, 0x00, 0x00 },
};

static const ThemePair THEME_COLOR_SCHEME[] =
{
	{ 0,                        TextColor::Black,     FillColor::Gray },
	{ THEME_BACKGROUND,         TextColor::LightGray, FillColor::Blue  },
	{ THEME_SHADOW,             TextColor::Black,     FillColor::Black },
	{ THEME_WINDOW,             TextColor::Black,     FillColor::Gray },
	{ THEME_WINDOW_TITLE,       TextColor::Black,     FillColor::Gray },
	{ THEME_BUTTON,             TextColor::Black,     FillColor::Gray },
	{ THEME_BUTTON_ACTIVE,      TextColor::LightGray, FillColor::Blue  },
	{ THEME_LABEL,              TextColor::Black,     FillColor::Gray },
	{ THEME_LABEL_HIGHLIGHT,    TextColor::Blue,      FillColor::Gray },
	{ THEME_TEXTBOX,            TextColor::LightGray, FillColor::Black },
	{ THEME_TEXTBOX_ACTIVE,     TextColor::White,     FillColor::Blue  },
	{ THEME_TEXTBOX_CURSOR,     TextColor::Black,     FillColor::Gray },
	{ THEME_CHECKBOX,           TextColor::Black,     FillColor::Gray },
	{ THEME_CHECKBOX_ACTIVE,    TextColor::White,     FillColor::Blue  },
};

static const ThemeStyle THEME_COLOR_STYLES[] =
{
	{ 0,                        0                                    , 0 },
	{ THEME_BACKGROUND,         COLOR_PAIR(THEME_BACKGROUND)         , 0 },
	{ THEME_SHADOW,             COLOR_PAIR(THEME_SHADOW)             , 0 },
	{ THEME_WINDOW,             COLOR_PAIR(THEME_WINDOW)             , 0 },
	{ THEME_WINDOW_TITLE,       COLOR_PAIR(THEME_WINDOW_TITLE)       , 0 },
	{ THEME_BUTTON,             COLOR_PAIR(THEME_BUTTON)             , A_DIM },
	{ THEME_BUTTON_ACTIVE,      COLOR_PAIR(THEME_BUTTON_ACTIVE)      , 0 },
	{ THEME_LABEL,              COLOR_PAIR(THEME_LABEL)              , 0 },
	{ THEME_LABEL_HIGHLIGHT,    COLOR_PAIR(THEME_LABEL_HIGHLIGHT)    , 0 },
	{ THEME_TEXTBOX,            COLOR_PAIR(THEME_TEXTBOX)            , 0 },
	{ THEME_TEXTBOX_ACTIVE,     COLOR_PAIR(THEME_TEXTBOX_ACTIVE)     , 0 },
	{ THEME_TEXTBOX_CURSOR,     COLOR_PAIR(THEME_TEXTBOX_CURSOR)     , 0 },
	{ THEME_CHECKBOX,           COLOR_PAIR(THEME_CHECKBOX)           , 0 },
	{ THEME_CHECKBOX_ACTIVE,    COLOR_PAIR(THEME_CHECKBOX_ACTIVE)    , 0 },
	{ 0,                        0                                    , 0 },
};


static const ThemeStyle THEME_MONO_STYLES[] =
{
	{ 0,                        0                                    , 0 },
	{ THEME_BACKGROUND,         COLOR_PAIR(THEME_BACKGROUND)         , 0 },
	{ THEME_SHADOW,             COLOR_PAIR(THEME_SHADOW)             , 0 },
	{ THEME_WINDOW,             COLOR_PAIR(THEME_WINDOW)             , 0 },
	{ THEME_WINDOW_TITLE,       COLOR_PAIR(THEME_WINDOW_TITLE)       , 0 },
	{ THEME_BUTTON,             COLOR_PAIR(THEME_BUTTON)             , 0 },
	{ THEME_BUTTON_ACTIVE,      COLOR_PAIR(THEME_BUTTON_ACTIVE)      , A_REVERSE },
	{ THEME_LABEL,              COLOR_PAIR(THEME_LABEL)              , 0 },
	{ THEME_LABEL_HIGHLIGHT,    COLOR_PAIR(THEME_LABEL_HIGHLIGHT)    , A_BOLD },
	{ THEME_TEXTBOX,            COLOR_PAIR(THEME_TEXTBOX)            , A_REVERSE },
	{ THEME_TEXTBOX_ACTIVE,     COLOR_PAIR(THEME_TEXTBOX_ACTIVE)     , A_REVERSE },
	{ THEME_TEXTBOX_CURSOR,     COLOR_PAIR(THEME_TEXTBOX_CURSOR)     , 0 },
	{ THEME_CHECKBOX,           COLOR_PAIR(THEME_CHECKBOX)           , 0 },
	{ THEME_CHECKBOX_ACTIVE,    COLOR_PAIR(THEME_CHECKBOX_ACTIVE)    , A_REVERSE },
	{ 0,                        0                                    , 0 },
};


static const Theme THEME_COLOR_DEFAULT =
{
	THEME_COLOR_PALETTE, THEME_COLOR_SCHEME, THEME_COLOR_STYLES,
};

static const Theme THEME_MONO_DEFAULT =
{
	NULL, NULL, THEME_MONO_STYLES,
};


const Theme &Application::getDefaultTheme()
{
	if (has_colors() == TRUE)
		return THEME_COLOR_DEFAULT;
	else
		return THEME_MONO_DEFAULT;
}


} // namespace cursed
