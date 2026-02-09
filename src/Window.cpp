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

void Window::swapBuffers() {
	impl->swapBuffers();
}
void Window::processMessages() {
	impl->processMessages();
}
void Window::addConsole() const {
	impl->addConsole();
}
void Window::removeConsole() const {
	impl->removeConsole();
}
bool Window::isOpen() const {
	return impl->isOpen();
}
RenderState* Window::getRenderState() {
	return impl->getRenderState();
}

Input* Window::getInput() {
	return impl->getInput();
}