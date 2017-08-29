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
#include <ncursesw/curses.h>


namespace cursed {


Component::Component(
	Window &parent,
	int height,
	int width,
	int y,
	int x,
	bool interactive ) : y(y), x(x), height(height), width(width), parent(parent),
		interactive(interactive)
{
	if (y < 0) this->y = 0;
	if (x < 0) this->x = 0;
	if (height < 0) this->height = 0;
	if (width < 0) this->width = 0;

	content = derwin( (WINDOW*) parent.content, this->height, this->width, this->y, this->x);
	//wbkgd( (WINDOW*) content, getTheme().styles[THEME_WINDOW].style );
	setBackground(THEME_WINDOW);
	parent.addComponent(*this, &this->interactive);
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


void Component::setY(
	int y )
{
	if (y < 0) y = 0;
	this->y = y;
}

void Component::setX(
	int x )
{
	if (x < 0) x = 0;
	this->x = x;
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


bool Component::isInteractive() const
{
	return interactive;
}


void Component::setStyle(
	int id )
{
	wattrset( (WINDOW*) content, getTheme().styles[id].color | getTheme().styles[id].attribute);
}


void Component::setBackground(
	int id )
{
	wbkgdset( (WINDOW*) content, getTheme().styles[id].color );
}


} // namespace cursed