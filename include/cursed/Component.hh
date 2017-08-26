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

#ifndef CURSED_COMPONENT_HH
#define CURSED_COMPONENT_HH


#include <cursed/KeyEventListener.hh>
#include <cursed/Paintable.hh>
#include <cursed/Theme.hh>
#include <string>


namespace cursed {


class Window;


class Component : public Paintable, public KeyEventListener
{
	public:
		Component(
			Window &parent,
			int height,
			int width,
			int y,
			int x,
			bool isInteractive = true );

		virtual ~Component();

		void setActive(
			bool state );

		bool isActive() const;

		Window &getParent();

		const Window &getParent() const;

		int getY() const;

		int getX() const;

		void setY(
			int y );

		void setX(
			int x );

		int getHeight() const;

		int getWidth() const;

		const Theme &getTheme() const;

		bool isStatic() const;

		virtual void onActive(
			bool state ) = 0;

		void refresh();

		bool isInteractive() const;

	protected:
		int y, x, height, width;
		Window &parent;
		void *content;
		bool interactive;

		void setStyle(
			int id );

		void setBackground(
			int id );
};


} // namespace cursed


#endif // CURSED_COMPONENT_HH