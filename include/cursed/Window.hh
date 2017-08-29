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

#ifndef CURSED_WINDOW_HH
#define CURSED_WINDOW_HH


#include <cursed/Application.hh>
#include <cursed/Component.hh>
#include <cursed/KeyEventListener.hh>
#include <cursed/Paintable.hh>
#include <string>
#include <vector>


namespace cursed {


class Window : public Paintable, public KeyEventListener
{
	public:
		Window(
			Application &app,
			Window &parent,
			const std::wstring &title,
			int height,
			int width,
			int y = 0,
			int x = 0 );

		Window(
			Application &app,
			const std::wstring &title,
			int height,
			int width,
			int y = 0,
			int x = 0 );

		void initialize(
			Window *parent,
			const std::wstring *title,
			int height,
			int width,
			int y,
			int x );

		~Window();

		const Theme &getTheme() const;

		void paint();

		int getClientWidth() const;

		int getClientHeight() const;

		int getWidth() const;

		int getHeight() const;

		void close(
			int result = 0 );

		int showModal();

		Component *getActive();

		void setActive(
			Component *control );

		void setActive(
			Component &control );

		void setActive(
			int index );

		bool onKeyPress(
			const KeyEvent &event );

		void refresh();

	protected:
		void *window, *content, *shadow;
		int height, width, py, px;
		std::wstring title;
		Window *parent;
		std::vector<Component*> controls;
		int activeComponent;
		int result;
		bool allStatic;
		Application &app;

	private:
		void activateNext(
			int direction );

		void addComponent(
			Component &control,
			const bool *interactive = NULL );

		void setBackground(
			void *target,
			int id );

	friend class Component;
};


} // namespace cursed


#endif // CURSED_WINDOW_HH