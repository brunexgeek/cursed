# cursed  [![Build Status](https://travis-ci.org/brunexgeek/cursed.svg?branch=master)](https://travis-ci.org/brunexgeek/cursed) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

**cursed** is a minimalist C++ (2011 or above) framework that allows you to build user interfaces for your applications using ``ncursesw``. This framework provides a high-level abstraction for creating windows and components (buttons, labels, text boxes, etc.). You can also extend the existing components or create your own.

Most GNU/Linux distributions out there came with ``ncurses`` and ``ncursesw`` runtime by default. To use ``cursed`` in your applications, you only need to install the ``ncursesw`` development package.

![Demonstration"](https://github.com/brunexgeek/cursed/raw/master/screenshots/demo.gif "Demonstration")

This framework is still in development. For now, you can use ``cursed`` to create windows with the following *themeable* components:

* **Label**: display static information with minimal formating capabilities (hightlight and underline);
* **TextBox**: enable the user to input text information (limited to ASCII letters, numbers and symbols);
* **Button**: perform actions when *pressed* (functions or lambda expressions);
* **Checkbox**: enable the user to make a binary choice.

## Example

```cpp
Application app;

const int height = 8;
const int width  = 60;
int y = (app.screenHeight() - height) / 2;
int x = (app.screenWidth() - width) / 2;

Window window(app, L"Sample Application", height, width, y, x);

Label label(window,
	L"This is a sample application "
	"using *cursed* framework!",   // text
	window.getClientHeight() - 2,  // height
	window.getClientWidth(),       // width
	0,                             // y
	0 );                           // x

Button button(window,
	L"Close",                                                     // text
	window.getClientHeight() - 1,                                 // y
	(window.getClientWidth() - Button::scale(L"Close")) / 2,      // x
	[](Button &button) -> void { button.getParent().close(); } ); // action

window.setActive(button);
window.showModal();
```

![Screenshot from 'simple' program"](https://github.com/brunexgeek/cursed/raw/master/screenshots/simple.png "Screenshot from 'simple' program")

## Building the framework

To build ``cursed`` you need ``cmake`` and ``ncursesw`` headers. If you are using Debian/Ubuntu, you can use the following command to install everything:

```
# sudo apt-get install libncurses5-dev cmake
```

To download, build and install ``cursed``, use the following commands:

```
# git clone https://github.com/brunexgeek/cursed.git
# mkdir cursed/build
# cd cursed/build
# cmake ..
# make
# sudo make install
```

## Building applications

Change your build process to link with both ``cursed`` and ``ncursesw``.

```
# g++ -std=c++11 program.cpp -lcursed -lncursesw
```

## Task list

The following components/features are in development:

- Implement *radio button* component
- Hot keys (ALT+&lt;*letter*&gt; to activate/focus components)

The following components/features are in the roadmap:

- Implement *menu* and *menu bar* components


## License

Except where explicitly indicated otherwise, all source codes of this project are provide under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).
