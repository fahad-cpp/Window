#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "Window.h"
//WIN32 window
class Win32Window : public BaseWindow
{
private:
	HWND mWindowHandle;
	HDC mDeviceContextHandle;

	inline void setNative(HWND window) { mWindowHandle = window; }
	inline HWND getNative() const { return mWindowHandle; }
public:
	BITMAPINFO bitmapInfo;
	Win32Window(const char* name = "NULL", unsigned int width = 720, unsigned int height = 720);
	~Win32Window();
	void swapBuffers() override;
	void processMessages() override;
	void addConsole() const override;
	void removeConsole() const override;
	bool isOpen() const override { return IsWindow(mWindowHandle); }
};