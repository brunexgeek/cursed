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
			int y,
			int x,
			int height,
			int width );

		virtual ~Component();

		void setActive(
			bool state );

		bool isActive() const;

		Window &getParent();

		const Window &getParent() const;

		int getY() const;

		int getX() const;

		int getHeight() const;

		int getWidth() const;

		const Theme &getTheme() const;

		virtual bool isStatic() const = 0;

		virtual void onActive(
			bool state ) = 0;

		void refresh();

	protected:
		int y, x, height, width;
		Window &parent;
		void *content;
};


} // namespace cursed


#endif // CURSED_COMPONENT_HH