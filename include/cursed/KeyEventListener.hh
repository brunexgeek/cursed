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

#ifndef CURSED_EVENTS_HH
#define CURSED_EVENTS_HH


namespace cursed {


enum KeyModifier
{
	KMOD_SHIFT = 0x01,
	KMOD_ALT   = 0x02,
	KMOD_CTRL  = 0x04
};


struct KeyEvent
{
	bool modifiers;
	int key;
};


class KeyEventListener
{
	public:
		virtual bool onKeyPress(
			const KeyEvent &event ) = 0;
};


} // namespace cursed


#endif // CURSED_EVENTS_HH