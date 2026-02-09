#include "Scene.h"


//Colour 

Colour::Colour() {
	R = 0;
	G = 0;
	B = 0;
}
Colour::Colour(unsigned char R, unsigned char G, unsigned char B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

bool Colour::operator==(const Colour& op)const{
	return (this->R == op.R && this->G == op.G && this->B == op.B);
}
Colour Colour::operator*(const float num) {
	Vector newcol = { float(this->R * num),float(this->G * num),float(this->B * num) };
	if (newcol.x > 255) {
		newcol.x = 255;
	}
	if (newcol.y > 255) {
		newcol.y = 255;
	}
	if (newcol.z > 255) {
		newcol.z = 255;
	}
	return { u8(newcol.x),u8(newcol.y),u8(newcol.z) };
}
Colour Colour::operator+(const Colour& col) {
	Vector newcol = { float(this->R + col.R),float(this->G + col.G),float(this->B + col.B) };
	if (newcol.x > 255) {
		newcol.x = 255;
	}
	if (newcol.y > 255) {
		newcol.y = 255;
	}
	if (newcol.z > 255) {
		newcol.z = 255;
	}
	return { u8(newcol.x),u8(newcol.y),u8(newcol.z) };
}
float Colour::luminance() {
	return ((0.2126f * float(R)) + (0.7152f * float(G)) + (0.0722f * float(B)));
}

u32 getHex(const Colour& RGB)
{
	return u32((RGB.R << 16) | (RGB.G << 8) | RGB.B);
}
Colour hexToRGB(u32 hex) {
	Colour color;
	color.R = u8((hex >> 16) & 0xff);
	color.G = u8((hex >> 8) & 0xff);
	color.B = u8(hex & 0xff);
	return color;
}
u32 rgbtoHex(Colour RGB) {
	return u32((RGB.R << 16) | (RGB.G << 8) | RGB.B);
}


//Sphere
Sphere::Sphere(Vector center, float radius, Colour color) {
	this->center = center;
	this->radius = radius;
	this->color = color;
}

Type Triangle::getType()
{
	return Type::ST_TRIANGLE;
}
Vector Triangle::getNormal()
{
	//anti clockwise
	if (normal == Vector{ 0, 0, 0 })
	{
		normal = cross((p[1] - p[0]), (p[2] - p[0]));
		return normal;
	}
	return normal;
}
Vector Triangle::getCentroid() {
	return ((p[0] + p[1] + p[2]) / 3);
}