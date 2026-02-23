#ifdef __linux__
#include "XlibWindow.h"
XlibWindow::XlibWindow(const char* name, unsigned int width, unsigned int height){
    mDisplay = XOpenDisplay(0);
    Window rootWindow = XDefaultRootWindow(mDisplay);
    mWindowHandle = XCreateSimpleWindow(mDisplay,rootWindow,0,0,width,height,0,0,0x000000);
    XMapWindow(mDisplay,mWindowHandle);
    XFlush(mDisplay);
    input = {};
    renderState.width = width;
    renderState.height = height;

    int bufferSize = width * height * sizeof(unsigned int);
    if(renderState.screenBuffer)free(renderState.screenBuffer);
    renderState.screenBuffer = (unsigned int*)malloc(bufferSize);

    if(renderState.depthBuffer)free(renderState.depthBuffer);
    renderState.depthBuffer = (float*)malloc(width*height*sizeof(float));
}
XlibWindow::~XlibWindow(){
    XDestroyWindow(mDisplay,mWindowHandle);
}
void XlibWindow::swapBuffers(){

}
void XlibWindow::processMessages(){
    XEvent generalEvent = {};
    XNextEvent(mDisplay,&generalEvent);
};
void XlibWindow::addConsole() const {
    std::freopen("CONOUT$", "w", stdout);
};
void XlibWindow::removeConsole() const {
    std::fclose(stdout);
};

#endif