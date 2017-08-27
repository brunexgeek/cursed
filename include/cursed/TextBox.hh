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

#ifndef CURSED_TEXTBOX_HH
#define CURSED_TEXTBOX_HH


#include <cursed/Component.hh>
#include <string>


namespace cursed {


class TextBox : public Component
{
	public:
		TextBox(
			Window &parent,
			const std::wstring &text,
			int height,
			int width,
			int y,
			int x );

		~TextBox();

		void paint();

		void onActive(
			bool state );

		bool onKeyPress(
			const KeyEvent &event );

		const std::wstring &getText() const;

	protected:
		std::wstring text;
		int position;
		int start, end, cursor;

		void moveCursor(
			int direction );
};


} // namespace cursed


#endif // CURSED_TEXTBOX_HH