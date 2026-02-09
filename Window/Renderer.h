#pragma once
#include <cmath>
#include "Window.h"
#include "Scene.h"
//CPU renderer
struct Renderer {
	Window* renderWindow;
	Transform camera;
	Vector viewPort;
	Vector canvas;
	RenderState* renderState;
	//distance between camera position and viewport
	float d;
	Renderer(Window* window) {
		renderState = window->getRenderState();
		renderWindow = window;
		d = 1.f;
		camera = { {0,0,-5},1,{0,0,0} };
		canvas = {(float)renderState->width,(float)renderState->height};
		float aspectratio = float(renderState->width) / float(renderState->height);
		viewPort.x = aspectratio;
		viewPort.y = 1;
	}
	void clear(Colour colour);
	void clear(u32 colour);
	void putPixelD(int x, int y, Colour color);
	void putPixel(int x, int y, Colour color);
	void drawLine(Vector a, Vector b, Colour color);
	Vector canvasToViewport(float x, float y);
	std::pair<float, float> viewportToCanvas(float x, float y);
	Vector projectVertex(Vector v);
	void drawTriangle(Triangle& t, bool wireframe = false);
	void interpolate(float x0, float y0, float x1, float y1, std::vector<float>& arr);
};
enum class RotateOrder {
	RO_YXZ = 0,
	RO_XYZ
};
template<typename T>
void swap(T&,T&);
template<typename T>
void clamp(T& num, T min_limit, T max_limit);
template<typename T>
bool isIn(T value, T lower, T higher);
Vector rotate(const Vector& vec, const Vector& rotationP, RotateOrder ro = RotateOrder::RO_YXZ, bool cached = false);
Vector transformVertex(Vector vec, const Transform& tf, RotateOrder ro = RotateOrder::RO_YXZ);