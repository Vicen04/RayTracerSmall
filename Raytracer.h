#pragma once
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <cassert>
// Windows only
#include <algorithm>
#include <sstream>
#include <string.h>
#include <chrono>
#include "Sphere.h"
#define M_PI 3.141592653589793

struct Animation
{
	Animation(float x, float y, float z, float frame) : addX(x), addY(y), addZ(z), frames(frame) {}
	float frames;
	float addX;
	float addY;
	float addZ;
};

class Raytracer
{
public:
	Raytracer();
	Raytracer(string file);
	~Raytracer();
	void MovementShrinking();
	void ProduceImage(string file);
	void SmoothScaling(int r);
	void Scaling();
	void MovementShrinkingSpheres(float i);
	void Basic();
	void BasicRender(int i);
	void render(const std::vector<Sphere*> spheres, int iteration);
	void renderAnimated(const std::vector<Sphere*> spheres, const std::vector<Animation*> animations, int loops);
	void render2(const std::vector<Sphere*> spheres,Vec3f *passed, unsigned currentloop, unsigned divisor);
	Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir, const std::vector<Sphere*> spheres, const int &depth);
	float mix(const float &a, const float &b, const float &mix)
	{
		return b * mix + a * (1 - mix);
	}
private:
	mutex* wait;
	MemoryPool* pool;
	unsigned width = 640, height = 480, loops = 5, ThreadNumber = 5;
	float divisor = (float)loops / 10.0f;
	float fov = 30;
	float angle = tan(M_PI * 0.5 * fov / 180.);
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float aspectratio = width / float(height);
};