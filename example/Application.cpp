#include "Game.h"

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