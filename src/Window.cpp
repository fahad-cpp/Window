#include "Window.h"
#ifdef _WIN32
#include "Win32Window.h"
#endif


FSWindow::FSWindow(const char* name,unsigned int width, unsigned int height){
#ifdef _WIN32
	impl = new Win32Window(name, width, height);
#endif
}

FSWindow::~FSWindow() {
	delete impl;
}