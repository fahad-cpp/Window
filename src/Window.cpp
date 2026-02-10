#include "Window.h"
#ifdef _WIN32
#include "Win32Window.h"
#endif


Window::Window(const char* name,unsigned int width, unsigned int height){
#ifdef _WIN32
	impl = new Win32Window(name, width, height);
#endif
}

Window::~Window() {
	delete impl;
}