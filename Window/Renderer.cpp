#include "Renderer.h"
template<typename T>
void swap(T& a, T& b) {
	T c;
	c = a;
	a = b;
	b = c;
}
template<typename T>
void clamp(T& num, T min_limit, T max_limit) {
	if (num < min_limit) {
		num = min_limit;
		return;
	}
	else if (num > max_limit) {
		num = max_limit;
		return;
	}
	return;
}
template<typename T>
bool isIn(T value, T lower, T higher) {
	if (value >= higher) {
		return false;
	}
	else if (value <= lower) {
		return false;
	}
	else {
		return true;
	}
}
Vector rotate(const Vector& vec, const Vector& rotationP, RotateOrder ro, bool cached) {

	static float sinx, siny, sinz, cosx, cosy, cosz;
	static Vector lastRot = { 0,0,0 };



	if (rotationP == Vector{ 0,0,0 }) {
		return vec;
	}
	Vector rotation = { float(rotationP.x * (PI * 2)) / 360.f,float(rotationP.y * (PI * 2)) / 360.f,float(rotationP.z * (PI * 2)) / 360.f };

	if ((rotationP != lastRot) || (!cached)) {
		lastRot = rotationP;
		sinx = std::sin(rotation.x);
		siny = std::sin(rotation.y);
		sinz = std::sin(rotation.z);

		cosx = std::cos(rotation.x);
		cosy = std::cos(rotation.y);
		cosz = std::cos(rotation.z);
	}

	Vector result = {};
	if (ro == RotateOrder::RO_YXZ) {
		//Yaw
		Vector yrotated;
		yrotated.y = vec.y;
		yrotated.x = vec.x * cosy + vec.z * (-siny);
		yrotated.z = vec.x * siny + vec.z * cosy;

		//Pitch
		Vector xrotated;
		xrotated.x = yrotated.x;
		xrotated.y = yrotated.y * cosx + yrotated.z * (-sinx);
		xrotated.z = yrotated.y * sinx + yrotated.z * cosx;

		//Roll
		Vector zrotated;
		zrotated.z = xrotated.z;
		zrotated.x = xrotated.x * cosz + xrotated.y * (-sinz);
		zrotated.y = xrotated.x * sinz + xrotated.y * cosz;

		result = zrotated;
	}
	else if (ro == RotateOrder::RO_XYZ) {
		Vector xrotated;
		xrotated.x = vec.x;
		xrotated.y = vec.y * cosx + vec.z * (-sinx);
		xrotated.z = vec.y * sinx + vec.z * cosx;

		Vector yrotated;
		yrotated.y = xrotated.y;
		yrotated.x = xrotated.x * cosy + xrotated.z * (-siny);
		yrotated.z = xrotated.x * siny + xrotated.z * cosy;

		Vector zrotated;
		zrotated.z = yrotated.z;
		zrotated.x = yrotated.x * cosz + yrotated.y * (-sinz);
		zrotated.y = yrotated.x * sinz + yrotated.y * (cosz);

		result = zrotated;
	}
	return result;
}
Vector transformVertex(Vector vec, const Transform& tf, RotateOrder ro) {
	return ((rotate(vec, tf.rotation, ro) * tf.scale) + tf.position);
}
void Renderer::putPixelD(int x, int y, Colour color) {
	u32 hexColor = rgbtoHex(color);
	u32* pixel = (u32*)renderWindow->getRenderState()->screenBuffer + x + (y * renderWindow->getRenderState()->width);
	*pixel = hexColor;
}
void Renderer::putPixel(int x, int y, Colour color) {
	u32 hexColor = rgbtoHex(color);
	x += renderWindow->getRenderState()->width / 2;
	y = (renderWindow->getRenderState()->height / 2) - y;
	u32* pixel = (u32*)renderWindow->getRenderState()->screenBuffer + x + (y * renderWindow->getRenderState()->width);
	*pixel = hexColor;
}
void Renderer::clear(u32 color) {
	u32* buffer = (u32*)renderWindow->getRenderState()->screenBuffer;
	float* dep = renderWindow->getRenderState()->depthBuffer;
	for (int y = 0; y < renderWindow->getRenderState()->height; y++) {
		for (int x = 0; x < renderWindow->getRenderState()->width; x++) {
			*buffer++ = color;
			*dep++ = 0.f;
		}
	}
}
void Renderer::clear(Colour color) {
	u32 hexColor = rgbtoHex(color);
	u32* buffer = (u32*)renderWindow->getRenderState()->screenBuffer;
	float* dep = renderWindow->getRenderState()->depthBuffer;
	for (int y = 0; y < renderWindow->getRenderState()->height; y++) {
		for (int x = 0; x < renderWindow->getRenderState()->width; x++) {
			*buffer++ = hexColor;
			*dep++ = 0.f;
		}
	}
}
void Renderer::drawLine(Vector a, Vector b, Colour color) {
	float dy = b.y - a.y;
	float dx = b.x - a.x;
	if (abs(dx) > abs(dy)) {
		if (a.x > b.x) {
			swap(a, b);
		}
		float aspectRatio = 0;
		if (dx != 0)
			aspectRatio = (dy / dx);
		float y = a.y;
		for (int x = a.x; x <= b.x; x++) {
			if (x >= (canvas.x / 2) || x <= -(canvas.x / 2) || y >= (canvas.y / 2) || y <= -(canvas.y / 2)) {
				y += aspectRatio;
			}
			else {
				putPixel(x, y, color);
				y += aspectRatio;
			}
		}
	}
	else {
		if (a.y > b.y) {
			swap(a, b);
		}
		float aspectRatio = 0;
		if (dy != 0)
			aspectRatio = (dx / dy);
		float x = a.x;
		for (int y = a.y; y <= b.y; y++) {
			if (x >= (canvas.x / 2) || x <= -(canvas.x / 2) || y >= (canvas.y / 2) || y <= -(canvas.y / 2)) {
				x += aspectRatio;
			}
			else {
				putPixel(x, y, color);
				x += aspectRatio;
			}
		}
	}
}
Vector Renderer::canvasToViewport(float x, float y) {
	return { x * (viewPort.x / canvas.x), y * (viewPort.y / canvas.y), d };
}
std::pair<float, float> Renderer::viewportToCanvas(float x, float y) {
	return { x * (canvas.x / viewPort.x) ,y * (canvas.y / viewPort.y) };
}
Vector Renderer::projectVertex(Vector v) {
	//Perspective Projection
	std::pair<float, float> result = viewportToCanvas(float((v.x * d) / v.z), float((v.y * d) / v.z));
	return { result.first,result.second ,d };
}
void Renderer::interpolate(float x0, float y0, float x1, float y1, std::vector<float>& arr) {
	float dx = x1 - x0;
	float dy = y1 - y0;
	float aspectratio = (dy != 0) ? (dx / dy) : 0;
	size_t size = int(y1) - int(y0);

	float x = x0;

	for (int y = int(y0); y < int(y1); y++) {
		arr.push_back(x);
		x += aspectratio;
	}
}

//Expects triangle to be in camera space
void Renderer::drawTriangle(Triangle& t, bool wireframe)
{
	Vector p1 = projectVertex(t.p[0]);
	Vector p2 = projectVertex(t.p[1]);
	Vector p3 = projectVertex(t.p[2]);
	Vector N = t.getNormal();
	N = N / length(N);
	p1.z = t.p[0].z;
	p2.z = t.p[1].z;
	p3.z = t.p[2].z;

	Colour color = t.color;

	if (p1.y > p2.y) {
		swap(p1, p2);
	}
	if (p1.y > p3.y) {
		swap(p1, p3);
	}
	if (p2.y > p3.y) {
		swap(p2, p3);
	}

	if (wireframe) {
		//Drawing wireframe						
		drawLine(p1, p2, color);
		drawLine(p2, p3, color);
		drawLine(p3, p1, color);
		return;
	}

	std::vector<float> x01;
	std::vector<float> x12;
	std::vector<float> x02;

	std::vector<float> z01;
	std::vector<float> z12;
	std::vector<float> z02;

	interpolate(p1.x, p1.y, p2.x, p2.y, x01);
	interpolate(p2.x, p2.y, p3.x, p3.y, x12);
	interpolate(p1.x, p1.y, p3.x, p3.y, x02);

	interpolate(1 / p1.z, p1.y, 1 / p2.z, p2.y, z01);
	interpolate(1 / p2.z, p2.y, 1 / p3.z, p3.y, z12);
	interpolate(1 / p1.z, p1.y, 1 / p3.z, p3.y, z02);



	//concatenate short sides in 0-1
	for (const float& val : x12) {
		x01.push_back(val);
	}

	for (const float& val : z12) {
		z01.push_back(val);
	}

	int m = int(x02.size() / (float)2);
	std::vector<float> xLeft = {};
	std::vector<float> xRight = {};
	std::vector<float> zLeft = {};
	std::vector<float> zRight = {};

	//Finding left and right
	if (x02.size()) {
		if (x02[m] < x01[m]) {
			xLeft = x02;
			xRight = x01;

			zLeft = z02;
			zRight = z01;
		}
		else {
			xLeft = x01;
			xRight = x02;

			zLeft = z01;
			zRight = z02;
		}
	}

	for (int y = int(p1.y); y < int(p3.y); y++) {
		float xL = xLeft[y - int(p1.y)];
		float xR = xRight[y - int(p1.y)];

		std::vector<float> zSegment = {};
		interpolate(zLeft[y - int(p1.y)], xL, zRight[y - int(p1.y)], xR, zSegment);


		for (int x = int(xL); x < int(xR); x++) {
			//Per Fragment
			float z = zSegment[x - int(xL)];
			Vector T = canvasToViewport((x * (1 / z)) / d, (y * (1 / z)) / d);
			T.z = 1 / z;
			if (isIn(float(x), float(-canvas.x / 2.f), float(canvas.x / 2.f)) && isIn(float(y), float(-canvas.y / 2.f), float(canvas.y / 2.f))) {
				int nx = int(x + (renderWindow->getRenderState()->width / 2.0));
				int ny = int((renderWindow->getRenderState()->height / 2.f) - y);
				//Pointer to depth buffer
				float* dep = ((float*)(renderWindow->getRenderState()->depthBuffer)) + (ny * renderWindow->getRenderState()->width) + nx;
				if (z > (*dep)) {
					//Point in camera space
					Vector P = T;
					//Camera space to world space
					P = transformVertex(P, camera, RotateOrder::RO_XYZ);
					Triangle newTri;
					newTri.p[0] = transformVertex(t.p[0], camera, RotateOrder::RO_XYZ);
					newTri.p[1] = transformVertex(t.p[1], camera, RotateOrder::RO_XYZ);
					newTri.p[2] = transformVertex(t.p[2], camera, RotateOrder::RO_XYZ);
					Vector N = newTri.getNormal();
					Vector centroid = newTri.getCentroid();
					N = N / length(N);
					Vector R = P - camera.position;
					R = R / length(R);
					float light = 1.f;//computeLight(P, N, R, t.specular, false);
					putPixel(x, y, (color * light));
					*dep = z;
				}
			}
		}
	}
}

