#pragma once
#include "Vector.h"
#include <vector>
#define infinity 2000000000
typedef unsigned int u32;
typedef unsigned char u8;
#define internal static
#define global_variable static
#define PI 3.14159265359
//Colour
typedef unsigned char u8;
typedef unsigned int u32;
struct Colour {
	u8 R, G, B;
	Colour();
	Colour(unsigned char R, unsigned char G, unsigned char B);

	bool operator==(const Colour& op)const;
	Colour operator*(const float num);
	Colour operator+(const Colour& col);
	float luminance();
};
u32 getHex(const Colour&);
Colour hexToRGB(u32 hex);
u32 rgbtoHex(Colour RGB);

//Objects
enum class Type
{
	ST_BASE = 0,
	ST_SPHERE,
	ST_TRIANGLE
};
struct Object {
	Colour color;
	float specular;
	float reflectiveness;
	virtual Type getType()
	{
		return Type::ST_BASE;
	}
};
struct Sphere : Object{
	Vector center;
	float radius;
	Sphere(Vector center = {}, float radius = 1.f, Colour color = {});
	virtual Type getType() {
		return Type::ST_SPHERE;
	}
};
struct Triangle : Object {
	Vector p[3];
	Vector normal;
	Triangle() {
		p[0] = {};
		p[1] = {};
		p[2] = {};
		color = { 255,0,0 };
		reflectiveness = 0;
		specular = -1;
	}
	Triangle(const Vector p[3],const Vector normal = { 0,0,0 },const Colour color = { 0,0,0 },const float specular = -1,const float reflectiveness = 0) {
		this->p[0] = p[0];
		this->p[1] = p[1];
		this->p[2] = p[2];
		this->color = color;
		this->specular = specular;
		this->reflectiveness = reflectiveness;
	}
	virtual Type getType();
	Vector getNormal();
	Vector getCentroid();
};
struct Transform {
	Vector position;
	float scale;
	Vector rotation;
	Transform() {
		position = { 0,0,0 };
		scale = 0;
		rotation = 0;
	}
	Transform(const Vector& position, const float scale, const Vector& rotation) {
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}
};
//Scene
struct Scene {;

};