#ifdef __linux__
#include "XlibWindow.h"
XlibWindow::XlibWindow(const char* name, unsigned int width, unsigned int height){
    mDisplay = XOpenDisplay(0);
    Window rootWindow = XDefaultRootWindow(mDisplay);
    mWindowHandle = XCreateSimpleWindow(mDisplay,rootWindow,0,0,width,height,0,0,0x000000);
    XMapWindow(mDisplay,mWindowHandle);
    XFlush(mDisplay);
    renderState.width = width;
    renderState.height = height;
}
XlibWindow::~XlibWindow(){
    XDestroyWindow(mDisplay,mWindowHandle);
}
void XlibWindow::swapBuffers(){

}
void XlibWindow::processMessages(){

};
void XlibWindow::addConsole() const {

};
void XlibWindow::removeConsole() const {
    
};

#endif