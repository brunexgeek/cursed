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

#include <cursed/Window.hh>
#include <cursed/Component.hh>


namespace cursed {


Component::Component(
	Window &parent,
	int y,
	int x,
	int height,
	int width ) : y(y), x(x), height(height), width(width), parent(parent)
{
	if (y < 0) this->y = 0;
	if (x < 0) this->x = 0;
	if (height < 0) this->height = 0;
	if (width < 0) this->width = 0;

	content = derwin( (WINDOW*) parent.content, this->height, this->width, this->y, this->x);

}


Component::~Component()
{
	delwin((WINDOW*) content );
}


Window &Component::getParent()
{
	return parent;
}


const Window &Component::getParent() const
{
	return parent;
}


const Theme &Component::getTheme() const
{
	return parent.getTheme();
}


int Component::getY() const
{
	return y;
}


int Component::getX() const
{
	return x;
}


bool Component::isActive() const
{
	return parent.getActive() == this;
	//return state;
}


void Component::refresh()
{
	wnoutrefresh( (WINDOW*) content );
}


} // namespace cursed