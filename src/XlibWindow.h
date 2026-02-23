#ifdef __linux__
#include "Window.h"
#include <X11/Xlib.h>
class XlibWindow : public BaseWindow
{
private:
	Window mWindowHandle;
	Display* mDisplay;

	inline void setNative(Window window) { mWindowHandle = window; }
	inline Window getNative() const { return mWindowHandle; }
public:
	XlibWindow(const char* name = "NULL", unsigned int width = 720, unsigned int height = 720);
	~XlibWindow();
	void swapBuffers() override;
	void processMessages() override;
	void addConsole() const override;
	void removeConsole() const override;
	bool isOpen() const override { return mWindowHandle; }
};
#endif