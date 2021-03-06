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

#ifndef CURSED_APPLICATION_HH
#define CURSED_APPLICATION_HH


#include <cursed/KeyEventListener.hh>
#include <cursed/Theme.hh>
#include <string>
#include <vector>


namespace cursed {


class Window;


enum ApplicationState
{
	APS_STOPPED,
	APS_STOPPING,
	APS_RUNNING,
};


class Application : public KeyEventListener
{
	public:
		Application(
			const Theme &theme );

		Application();

		~Application();

		void refresh();

		int run(
			Window &panel );

		const Theme &getTheme() const;

		bool hasCapability(
			const std::string &capname );

		bool onKeyPress(
			const KeyEvent &event );

		int screenWidth() const;

		int screenHeight() const;

		const Theme &getDefaultTheme();

	private:
		ApplicationState state;
		const Theme *theme;
		std::vector<Window*> windows;
		int activeWindow;

		void initialize(
			const Theme *theme = NULL );

		void applyTheme(
			const Theme &theme );
};


} // namespace cursed


#endif // CURSED_APPLICATION_HH