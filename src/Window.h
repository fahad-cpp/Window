#pragma once
#include <iostream>
#include <string>
#include "Input.h"

typedef unsigned int u32;
struct RenderState {
	int width;
	int height;
	void* screenBuffer;
	float* depthBuffer;
};
class BaseWindow{
public:
	RenderState renderState;
	Input input;
	virtual void swapBuffers() = 0;
	virtual void processMessages() = 0;
	virtual void addConsole() const = 0;
	virtual void removeConsole() const = 0;
	virtual bool isOpen() const = 0;
	virtual inline RenderState* getRenderState() { return  &renderState; }
	virtual inline Input* getInput() { return &input; }
};

//User interface Class
class Window {
private:
	BaseWindow* impl;
public:
	Window(const char* name = "NULL", unsigned int width = 720, unsigned int height = 720);
	~Window();
	inline void swapBuffers() { impl->swapBuffers(); }
	inline void processMessages() { impl->processMessages(); }
	inline void addConsole() const { impl->addConsole(); };
	inline void removeConsole() const { impl->removeConsole(); };
	inline bool isOpen() const { return impl->isOpen(); };
	inline RenderState* getRenderState() { return impl->getRenderState(); };
	inline Input* getInput() { return impl->getInput(); }
};