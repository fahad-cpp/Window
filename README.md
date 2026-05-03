# FSWindow
FSWindow (Fairly Simple Window) is a windowing library that supports Linux and Windows

# Usage
```C++
#include <FSWindow.h>
#include <FSRenderer.h>

void init(){
  //initialize your app
}
void update(Input& input){
  //Do something per-frame
}

int main(){
    FSWindow window("MyWindow",720,720);
    FSRenderer renderer(&window);

    while(window.isOpen()){
        renderer.clear(0x000000);

        window.processMessages();

        update(window.getInput(),renderer);
        
        window.swapBuffers();
    }
}
```
