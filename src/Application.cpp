#include "FSWindow.h"
#include "Renderer.h"
#include "Main.h"
int main() {
	FSWindow window("Window",720,720);
	Renderer renderer(&window);
	init();
	while (window.isOpen()) {
		renderer.clear(0xFF000000);
		
		window.processMessages();
		
		update(window.getInput(), renderer);
		
		window.swapBuffers();
	}
}