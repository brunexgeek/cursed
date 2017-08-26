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

#include <cursed/cursed.hh>


using namespace cursed;


int main( )
{
	Application app;

	const int height = 15;
	const int width  = 60;
	int y = (app.screenHeight() - height) / 2;
	int x = (app.screenWidth() - width) / 2;

	Window window(app, L"Sample Application", height, width, y, x);

	Label label(window,
		L"This is a label. Now, let's see other components:\n\n"
		"Button\n\n"
		"CheckBox\n\n"
		"TextBox",                  // text
		window.getClientHeight(),   // height
		window.getClientWidth(),    // width
		0,                          // y
		0 );                        // x

	Button button(window,
		L"Close",  // text
		2,         // y
		9,         // x
		[](Button &button) -> void { button.getParent().close(); } );

	CheckBox checkbox(window,
		L"Press space here",  // text
		4,                    // y
		9 );                  // x

	TextBox textbox(window,
		L"Write something nice",  // text
		1,                        // height
		30,                       // width
		6,                        // y
		9 );                      // x

	window.setActive(button);
	window.showModal();

	return 0;
}