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

#ifndef CURSED_BUTTON_HH
#define CURSED_BUTTON_HH


#include <cursed/Window.hh>
#include <cursed/Component.hh>
#include <cursed/KeyEventListener.hh>
#include <string>


namespace cursed {


class Button;


typedef void (ButtonPressed)( Button &object );


class Button : public Component
{
	public:
		Button(
			Window &parent,
			const std::wstring &label,
			int y,
			int x,
			ButtonPressed *action = NULL );

		void paint();

		void onActive(
			bool state );

		bool onKeyPress(
			const KeyEvent &event );

		static int scale(
			const std::wstring &label );

		virtual void onPressed();

	private:
		std::wstring text;
		ButtonPressed *action;
};


} // namespace cursed


#endif // CURSED_BUTTON_HH