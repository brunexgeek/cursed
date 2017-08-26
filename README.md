# cursed

``cursed`` is a C++ framework that allows you to build user interfaces for your applications using ``ncursesw``. This framework provides a high-level abstraction for creating windows and components (buttons, labels, text boxes, etc.). You can also extend the existing components or create your own.

This framework is in the early stages of development. For now, you can use ``cursed`` to create windows with the following *themeable* components:

* **Label** to display information with minimal formating capabilities (hightlight and underline);
* **TextBox** to read user input (limited to ASCII letters, numbers and symbols);
* **Button** to perform actions;

The following components/features are in development:

* Checkbox
* Radio button
* Hot keys (using ALT+<letter> to activate/focus components)

## Sample

```cpp
Application app;

const int height = 8;
const int width  = 60;
int y = (app.screenHeight() - height) / 2;
int x = (app.screenWidth() - width) / 2;

Window window(app, L"Sample Application", height, width, y, x);

Label label(window,
	L"This is a sample application using *cursed* framework!",
	window.getClientHeight() - 2,
	window.getClientWidth(),
	0,
	0 );

Button button(window,
	L"Close",
	window.getClientHeight() - 1,
	(window.getClientWidth() - Button::scale(L"Close")) / 2,
	[](Button &button) -> void { button.getParent().close(); } );

window.setActive(button);
window.showModal();
```

![Screenshot from 'simple' program"](https://github.com/brunexgeek/cursed/raw/master/screenshots/simple.png "Screenshot from 'simple' program")

## License

Except where explicitly indicated otherwise, all source codes of this project are provide under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).
