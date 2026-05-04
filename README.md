# FSWindow
FSWindow (Fairly Simple Window) is a windowing library that supports Linux and Windows

# Usage
Clone the repo as git submodule
```bash
git submodule add https://github.com/fahad-cpp/FSWindow vendor/FSWindow
```
add in cmake as subdirectory and link to project
```cmake
cmake_minimum_required(VERSION 3.30)

project(MyProj)

add_subdirectory(vendor/FSWindow)

add_executable(MyProj Game.cpp Application.cpp)

target_link_libraries(MyProj FSWindow)
```
include in project and use
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
