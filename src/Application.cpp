#include "Window.h"
#include "Renderer.h"
#include "Main.h"
int main() {
	FSWindow window("Window",720,720);
	Renderer renderer(((FSWindow*)(&window)));
	init();
	while (window.isOpen()) {
		renderer.clear(0x000000);

		window.processMessages();

		update(window.getInput(), renderer);

		window.swapBuffers();
	}
}