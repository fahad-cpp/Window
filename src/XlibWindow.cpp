#ifdef __linux__
#include "XlibWindow.h"
XlibWindow::XlibWindow(const char* name, unsigned int width, unsigned int height){
    std::cout << "Xlib Window Created\n";
    mDisplay = XOpenDisplay(NULL);
    mScreen = DefaultScreen(mDisplay);
    Window rootWindow = XDefaultRootWindow(mDisplay);
    mWindowHandle = XCreateSimpleWindow(mDisplay,rootWindow,0,0,width,height,0,0,0x000000);
    XMapWindow(mDisplay,mWindowHandle);
    mGc = DefaultGC(mDisplay,mScreen);
    XFlush(mDisplay);
    input = {};
    renderState.width = width;
    renderState.height = height;

    int bufferSize = width * height * sizeof(unsigned int);
    if(renderState.screenBuffer)free(renderState.screenBuffer);
    renderState.screenBuffer = (unsigned int*)malloc(bufferSize);

    if(renderState.depthBuffer)free(renderState.depthBuffer);
    renderState.depthBuffer = (float*)malloc(width*height*sizeof(float));

    mBackImage = XCreateImage(mDisplay,
        DefaultVisual(mDisplay,mScreen),
        DefaultDepth(mDisplay,mScreen),
        ZPixmap,
        0,
        NULL,
        renderState.width,
        renderState.height,
        32,
        renderState.width * 4
    );
    mBackImage->data = (char*)malloc(width*height*sizeof(uint32_t));
}
XlibWindow::~XlibWindow(){
    std::cout << "Xlib Window Destroyed\n";
    XDestroyImage(mBackImage);
    XDestroyWindow(mDisplay,mWindowHandle);
    XCloseDisplay(mDisplay);
}
void XlibWindow::swapBuffers(){
    for(int y=0;y<renderState.height;y++){
        for(int x=0;x<renderState.width;x++){
            uint32_t index = ((renderState.width * y) + x);
            uint32_t pixel = (((uint32_t*)renderState.screenBuffer)[index]);
            XPutPixel(mBackImage,x,y,pixel);
        }
    }
    XPutImage(mDisplay,mWindowHandle,mGc,mBackImage,0,0,0,0,renderState.width,renderState.height);
}
void XlibWindow::processMessages(){
    while(XPending(mDisplay) > 0){
        XEvent event;
        XNextEvent(mDisplay,&event);
    }
};
void XlibWindow::addConsole() const {
    std::freopen("CONOUT$", "w", stdout);
};
void XlibWindow::removeConsole() const {
    std::fclose(stdout);
};

#endif