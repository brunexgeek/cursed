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

#include <cursed/Button.hh>
#include <ncursesw/curses.h>


namespace cursed {


Button::Button(
	Window &parent,
	const std::wstring &label,
	int y,
	int x,
	ButtonPressed *action ) : Component(parent, y, x, 1, (int)label.length() + 4),
		text(label), action(action)
{
	// nothing to do
}

void Button::paint()
{
	std::wstring temp;

	if (isActive())
		wattrset( (WINDOW*) content, getTheme().styles[THEME_BUTTON_ACTIVE].style);
	else
		wattrset( (WINDOW*) content, getTheme().styles[THEME_BUTTON].style);

	temp = L"[ " + text + L" ]";
	mvwaddwstr( (WINDOW*) content, 0, 0, temp.c_str());
	wattrset( (WINDOW*) content, getTheme().styles[THEME_WINDOW].style);
	touchwin( (WINDOW*) content );
}


void Button::onActive(
	bool state )
{
	(void) state;
	// nothing to do
}


bool Button::onKeyPress(
	const KeyEvent &event )
{
	if ((event.key == KEY_ENTER || event.key == '\x0A' || event.key == '\x20'))
	{
		onPressed();
		return true;
	}

	return false;
}


int Button::scale(
	const std::wstring &label )
{
	return (int) label.length() + 4;
}


bool Button::isStatic() const
{
	return false;
}


void Button::onPressed()
{
	if (action != NULL) action(*this);
}


} // namespace cursed