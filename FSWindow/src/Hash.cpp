#include "Hash.h"
template<typename T>
inline void hashCombine(std::size_t& seed, const T& value) {
	seed ^= (std::hash<T>()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

std::size_t std::hash<Vector>::operator()(const Vector& vec) const {
	std::size_t seed = 0;
	hashCombine(seed, vec.x);
	hashCombine(seed, vec.y);
	hashCombine(seed, vec.z);
	return seed;
}

std::size_t std::hash<Colour>::operator()(const Colour& color)const {
	return std::size_t(getHex(color));
}

//Custom Sphere Hashing
std::size_t std::hash<Sphere>::operator()(const Sphere& sphere) const {
	std::size_t seed = 0;
	hashCombine(seed, sphere.center);
	hashCombine(seed, sphere.radius);
	hashCombine(seed, sphere.color);
	hashCombine(seed, sphere.reflectiveness);
	hashCombine(seed, sphere.specular);
	return seed;
}