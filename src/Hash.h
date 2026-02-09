#pragma once
#include <algorithm>
#include "Scene.h"
template<typename T>
inline void hashCombine(std::size_t& seed, const T& value);
template<>
struct std::hash<Vector> {
	std::size_t operator()(const Vector& vec) const;
};
template<>
struct std::hash<Colour> {
	std::size_t operator()(const Colour& color)const;
};
template<>
struct std::hash<Sphere> {
	std::size_t operator()(const Sphere& sphere) const;
};