# FSWindow
FSWindow (Fairly Simple Window) is a windowing library that supports Linux and Windows
(In Development)

# Usage
```C++
#include "FSWindow.h"
void init(){
  //initialize your app
}
void update(Input& input){
  //Do something per-frame
}
int main() {
	FSWindow window("Window",720,720); // Name , Width , Height
	init();
	while (window.isOpen()) {
		window.processMessages();
		
		update(window.getInput());
		
		window.swapBuffers();
	}
}
```
