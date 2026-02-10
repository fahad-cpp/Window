#include "Main.h"
#include "Scene.h"
static void handleInput(Input& input,Renderer& renderer) {
	if (isDown(BUTTON_W)) {
		renderer.camera.position.z += 1;
	}
	if (isDown(BUTTON_S)) {
		renderer.camera.position.z -= 1;
	}
	if (isDown(BUTTON_A)) {
		renderer.camera.position.x -= 1;
	}
	if (isDown(BUTTON_D)) {
		renderer.camera.position.x += 1;
	}
	if (isDown(BUTTON_SPACE)) {
		renderer.camera.position.y += 1;
	}
	if (isDown(BUTTON_CTRL)) {
		renderer.camera.position.y -= 1;
	}
	return;
}
void init() {
	return;
}
void update(Input* input, Renderer& renderer) {
	handleInput(*input,renderer);
	Vector p[3] = {
		Vector{1.f,2.f,6.f},
		Vector{-1.f,2.f,6.f },
		Vector{0.f,0.f,6.f} 
	};
	Triangle t(p, Vector{ 0,0,-1 }, Colour{ 255,255,255 }, -1.f, 0.f);

	for (int i = 0; i < 3; i++) {
		t.p[i] = t.p[i] - renderer.camera.position;
	}
	renderer.drawTriangle(t);
	return;
}