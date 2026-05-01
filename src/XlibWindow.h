#ifdef __linux__
#include "FSWindow.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdint.h>
class XlibWindow : public BaseWindow
{
private:
	Window mWindowHandle;
	Display* mDisplay;
	int	mScreen;
	GC mGc;
	XImage* mBackImage=nullptr;

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