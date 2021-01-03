#include "Raytracer.h"

#if defined __linux__ || defined __APPLE__
// "Compiled for Linux
#else
// Windows doesn't define these values by default, Linux does

#define INFINITY 1e8
#endif


//[comment]
// This variable controls the maximum recursion depth
//[/comment]
#define MAX_RAY_DEPTH 5

Raytracer::Raytracer()
{
	wait = new mutex();
	pool = new MemoryPool(width * height * sizeof(Vec3f), loops);
	// This sample only allows one choice per program execution. Feel free to improve upon this
	srand(13);
	auto start = std::chrono::system_clock::now();
	//Basic();
	MovementShrinking();
	//Scaling();
	delete wait;
	delete pool;
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> time = end - start;
	std::cout << "it took " << time.count() << " seconds to finish" << std::endl;
}

Raytracer::Raytracer(string file)
{
	wait = new mutex();
	auto start = std::chrono::system_clock::now();
	// This sample only allows one choice per program execution. Feel free to improve upon this
	srand(13);
	//BasicRender();
	ProduceImage(file);
	//SmoothScaling();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> time = end - start;
	std::cout << "it took " << time.count() << " seconds to finish" << std::endl;
	delete wait;
}

Raytracer::~Raytracer()
{
	delete wait;
	delete pool;
}



//[comment]
// This is the main trace function. It takes a ray as argument (defined by its origin
// and direction). We test if this ray intersects any of the geometry in the scene.
// If the ray intersects an object, we compute the intersection point, the normal
// at the intersection point, and shade this point using this information.
// Shading depends on the surface property (is it transparent, reflective, diffuse).
// The function returns a color for the ray. If the ray intersects an object that
// is the color of the object at the intersection point, otherwise it returns
// the background color.
//[/comment]
Vec3f Raytracer::trace(
	const Vec3f &rayorig,
	const Vec3f &raydir,
	const std::vector<Sphere*> spheres,
	const int &depth)
{
	//if (raydir.length() != 1) std::cerr << "Error " << raydir << std::endl;
	float tnear = INFINITY;
	const Sphere* sphere = NULL;
	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < spheres.size(); ++i) {
		float t0 = INFINITY, t1 = INFINITY;
		if (spheres.at(i)->intersect(rayorig, raydir, t0, t1)) {
			if (t0 < 0) t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				sphere = spheres[i];
			}
		}
	}
	// if there's no intersection return black or background color
	if (!sphere) return Vec3f(2);
	Vec3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
	Vec3f phit = rayorig + raydir * tnear; // point of intersection
	Vec3f nhit = phit - sphere->center; // normal at the intersection point
	nhit.normalize(); // normalize normal direction
					  // If the normal and the view direction are not opposite to each other
					  // reverse the normal direction. That also means we are inside the sphere so set
					  // the inside bool to true. Finally reverse the sign of IdotN which we want
					  // positive.
	float bias = 1e-4; // add some bias to the point from which we will be tracing
	bool inside = false;
	if (raydir.dot(nhit) > 0) nhit = -nhit, inside = true;
	if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) {
		float facingratio = -raydir.dot(nhit);
		// change the mix value to tweak the effect
		float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
		refldir.normalize();
		Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1);
		Vec3f refraction = 0;
		// if the sphere is also transparent compute refraction ray (transmission)
		if (sphere->transparency) {
			float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
			float cosi = -nhit.dot(raydir);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vec3f refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k));
			refrdir.normalize();
			refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
		}
		// the result is a mix of reflection and refraction (if the sphere is transparent)
		surfaceColor = (
			reflection * fresneleffect +
			refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
	}
	else {
		// it's a diffuse object, no need to raytrace any further
		for (unsigned i = 0; i < spheres.size(); ++i) {
			if (spheres.at(i)->emissionColor.x > 0) {
				// this is a light
				Vec3f transmission = 1;
				Vec3f lightDirection = spheres.at(i)->center - phit;
				lightDirection.normalize();
				for (unsigned j = 0; j < spheres.size(); ++j) {
					if (i != j) {
						float t0, t1;
						if (spheres.at(j)->intersect(phit + nhit * bias, lightDirection, t0, t1)) {
							transmission = 0;
							break;
						}
					}
				}
				surfaceColor += sphere->surfaceColor * transmission *
					std::max(float(0), nhit.dot(lightDirection)) * spheres.at(i)->emissionColor;
			}
		}
	}
	Vec3f emissionColor = sphere->emissionColor;
	return surfaceColor + emissionColor;
}

//[comment]
// Main rendering function. We compute a camera ray for each pixel of the image
// trace it and return a color. If the ray hits a sphere, we return the color of the
// sphere at the intersection point, else we return the background color.
//[/comment]
void Raytracer::render(const std::vector<Sphere*> spheres, int iteration)
{
	unsigned screen = height * width;

	concurrent_vector<thread> threadpool;

	wait->lock();
	Vec3f * image = new (pool)Vec3f[screen], *passed = image;
	wait->unlock();

	// Trace rays
	for (unsigned y = 0; y < height; y++)
		for (unsigned x = 0; x < width; ++x, ++passed)
		{
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Vec3f raydir(xx, yy, -1);
			raydir.normalize();
			*passed = trace(Vec3f(0), raydir, spheres, 0);
		}


	// Save result to a PPM image (keep these flags if you compile under Windows)
	std::stringstream ss;
	ss << "./spheres" << iteration << ".ppm";
	std::string tempString = ss.str();
	char* filename = (char*)tempString.c_str();


	std::ofstream ofs(filename, std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";

		for (unsigned i = 0; i < screen; i++)
		{
			ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) <<
				(unsigned char)(std::min(float(1), image[i].y) * 255) <<
				(unsigned char)(std::min(float(1), image[i].z) * 255);
		}		
	ofs.close();

	Vec3f::operator delete[](image, pool);
}

void Raytracer::Basic()
{
	concurrent_vector<thread> threads;
	// Vector structure for Sphere (position, radius, surface color, reflectivity, transparency, emission color)
	for (int i = 0; i < loops; i++)
		threads.push_back(thread(&Raytracer::BasicRender, this, i));

	for (auto& th : threads)
		th.join();
	threads.clear();
}

void Raytracer::BasicRender(int i)
{
	std::vector<Sphere*> spheres;
	// Vector structure for Sphere (position, radius, surface color, reflectivity, transparency, emission color)

	spheres.push_back(new Sphere(Vec3f(0.0, -10004, -20), 10000, Vec3f(0.20, 0.20, 0.20), 0, 0.0));
	spheres.push_back(new Sphere(Vec3f(0.0, 0, -20), 4, Vec3f(1.00, 0.32, 0.36), 1, 0.5)); // The radius paramter is the value we will change
	spheres.push_back(new Sphere(Vec3f(5.0, -1, -15), 2, Vec3f(0.90, 0.76, 0.46), 1, 0.0));
	spheres.push_back(new Sphere(Vec3f(5.0, 0, -25), 3, Vec3f(0.65, 0.77, 0.97), 1, 0.0));

	// This creates a file, titled 1.ppm in the current working directory
	render(spheres, i);
	spheres.clear();
}

void Raytracer::MovementShrinkingSpheres(float i)
{
	std::vector<Sphere*> spheres;

	spheres.push_back(new Sphere(Vec3f(0.0, -104, -20), 100, Vec3f(0.20, 0.20, 0.20), 0, 0.0));
	spheres.push_back(new Sphere(Vec3f(0.0, 0, -20), 4.0f - 3.0f * i / (float)loops, Vec3f(1.00, 0.32, 0.36), 1, 0.5)); // The radius paramter is the value we will change
	spheres.push_back(new Sphere(Vec3f(-5.0 + i/divisor, -1, -15), 2, Vec3f(0.90, 0.76, 0.46), 1, 0.2));
	spheres.push_back(new Sphere(Vec3f(5.0, -5.0 + i / divisor, -25), 3, Vec3f(0.65, 0.77, 0.97), 1, 0.3));
	spheres.push_back(new Sphere(Vec3f(-5.0, 1, -25 + i / divisor), 3, Vec3f(0.35, 0.45 + i / ((float)loops), 0.77), 1, 0.4));

	auto start = std::chrono::system_clock::now();
	render(spheres, i);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> time = end - start;

	wait->lock();
	std::cout << "Rendered and saved spheres" << i << ".ppm" << std::endl;
	std::cout << "it took " << time.count() << " seconds to render" << std::endl;
	wait->unlock();
	// Dont forget to clear the Vector holding the spheres.
	spheres.clear();
}

void Raytracer::MovementShrinking()
{	// Vector structure for Sphere (position, radius, surface color, reflectivity, transparency, emission color)

	for (int i = 0; i < loops; i++)
		MovementShrinkingSpheres((float)i);
}

void Raytracer::Scaling()
{
	concurrent_vector<thread> threads;
	// Vector structure for Sphere (position, radius, surface color, reflectivity, transparency, emission color)

	for (int i = 0; i < loops; i++)
		threads.push_back(thread(&Raytracer::SmoothScaling, this, i));

	for (auto& th : threads)
		th.join();
	threads.clear();
}

void Raytracer::SmoothScaling(int r)
{
	std::vector<Sphere*> spheres;
	// Vector structure for Sphere (position, radius, surface color, reflectivity, transparency, emission color)
	spheres.push_back(new Sphere(Vec3f(0.0, -10004, -20), 10000, Vec3f(0.20, 0.20, 0.20), 0, 0.0));
	spheres.push_back(new Sphere(Vec3f(0.0, 0, -20), r / 100, Vec3f(1.00, 0.32, 0.36), 1, 0.5)); // Radius++ change here
	spheres.push_back(new Sphere(Vec3f(5.0, -1, -15), 2, Vec3f(0.90, 0.76, 0.46), 1, 0.0));
	spheres.push_back(new Sphere(Vec3f(5.0, 0, -25), 3, Vec3f(0.65, 0.77, 0.97), 1, 0.0));
	render(spheres, r);
	std::cout << "Rendered and saved spheres" << r << ".ppm" << std::endl;
		// Dont forget to clear the Vector holding the spheres.
	spheres.clear();
}



void Raytracer::ProduceImage(string file)
{
	std::vector<Sphere*> spheres;
	std::vector<Animation*> animations;
	std::ifstream read(file + ".json", std::ios::in);
	if (!read.is_open())
	{
		cout << "File could not be open" << endl;
		cin.get();
		return;
	}
	bool animated;
	int cSpheres, totalLoops = 0, frames;
	read >> animated;
	read >> cSpheres;
	float x, y, z, rad, r, g, b, refl, tra, addX, addY, addZ;
	if (!animated)
	{
		for (unsigned a = 0; a < cSpheres; ++a)
		{
			read >> x >> y >> z >> rad >> r >> g >> b >> refl >> tra >> frames >> addX >> addY >> addZ;

			spheres.push_back(new Sphere(Vec3f(x, y, z), rad, Vec3f(r, g, b), refl, tra));
		}
		read.close();
		render(spheres, 101);
		std::cout << "Rendered and saved spheres as *sphere " << 101 << ".ppm*" << std::endl;
	}
	else
	{
		for (unsigned a = 0; a < cSpheres; ++a)
		{
			read >> x >> y >> z >> rad >> r >> g >> b >> refl >> tra >> frames >> addX >> addY >> addZ;

			spheres.push_back(new Sphere(Vec3f(x, y, z), rad, Vec3f(r, g, b), refl, tra));
			animations.push_back(new Animation(addX, addY, addZ, frames));
		}
		for (int i = 0; i < animations.size(); i++)
		{
			if (totalLoops <= animations.at(i)->frames)
			     totalLoops = animations.at(i)->frames;
		}
		pool = new MemoryPool(width * height * sizeof(Vec3f), totalLoops);
		for (int i = 0; i < totalLoops; i++)
			renderAnimated(spheres, animations, i);

		spheres.clear();
		animations.clear();
		delete pool;
	}

}

void Raytracer::renderAnimated(const std::vector<Sphere*> spheres, const std::vector<Animation*> animations, int loops)
{
	std::vector<Sphere*> animated;
	animated.push_back(spheres.at(0));
	for (unsigned a = 1; a < spheres.size(); ++a)
	{
		
		if (animations.at(a)->frames > loops)
		{
			animated.push_back(new Sphere(Vec3f(spheres.at(a)->center.x + animations.at(a)->addX * loops, spheres.at(a)->center.y + animations.at(a)->addZ * loops,
				spheres.at(a)->center.z + animations.at(a)->addZ * loops), spheres.at(a)->radius, Vec3f(spheres.at(a)->surfaceColor.x, spheres.at(a)->surfaceColor.y, spheres.at(a)->surfaceColor.z),
				spheres.at(a)->reflection, spheres.at(a)->transparency));

		}
		else
		{
			animated.push_back(new Sphere(Vec3f(spheres.at(a)->center.x + animations.at(a)->addX * animations.at(a)->frames, spheres.at(a)->center.y + animations.at(a)->addZ * animations.at(a)->frames,
				spheres.at(a)->center.z + animations.at(a)->addZ * animations.at(a)->frames), spheres.at(a)->radius, Vec3f(spheres.at(a)->surfaceColor.x, spheres.at(a)->surfaceColor.y, spheres.at(a)->surfaceColor.z),
				spheres.at(a)->reflection, spheres.at(a)->transparency));
		}
	}	
	render(animated, loops + 100);
	animated.clear();
	wait->lock();
	std::cout << "Rendered and saved spheres" << loops + 100 << ".ppm" << std::endl;
	wait->unlock();
}