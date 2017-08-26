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

#include <cursed/CheckBox.hh>
#include <ncursesw/curses.h>


namespace cursed {


CheckBox::CheckBox(
	Window &parent,
	const std::wstring &label,
	int y,
	int x ) : Component(parent, 1, (int)label.length() + 4, y, x, true),
		text(label), checked(false)
{
	// nothing to do
}

void CheckBox::paint()
{
	std::wstring temp;

	if (isActive())
	{
		setBackground(THEME_CHECKBOX_ACTIVE);
		setStyle(THEME_CHECKBOX_ACTIVE);
	}
	else
	{
		setBackground(THEME_CHECKBOX);
		setStyle(THEME_CHECKBOX);
	}

	temp = (checked) ? L"[x] " : L"[ ] ";
	temp += text;
	mvwaddwstr( (WINDOW*) content, 0, 0, temp.c_str());
	touchwin( (WINDOW*) content );
}


void CheckBox::onActive(
	bool state )
{
	(void) state;
	// nothing to do
}


bool CheckBox::onKeyPress(
	const KeyEvent &event )
{
	if (event.key == '\x20' || event.key == KEY_ENTER || event.key == '\x0A')
	{
		checked = !checked;
		return true;
	}

	return false;
}


void CheckBox::scale(
	const std::wstring &label,
	int &height,
	int &width  )
{
	height = 1;
	width = (int) label.length() + 4;
}


void CheckBox::onChanged()
{
	// nothing to do
}


bool CheckBox::isChecked() const
{
	return checked;
}


} // namespace cursed