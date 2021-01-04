#include "Sphere.h"

//Data to be able to render the sphere and perform calculatiosn for the raytracer

Heap* Sphere::pHeap = NULL;
AllocHeader* Sphere::head = NULL;

bool Sphere::intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const
{
	Vec3f l = center - rayorig;
	float tca = l.dot(raydir);
	if (tca < 0) return false;
	float d2 = l.dot(l) - tca * tca;
	if (d2 > radius2) return false;
	float thc = sqrt(radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}

void * Sphere::operator new (size_t size)
{
	if (pHeap == NULL)
	{
		pHeap = HeapFactory::CreateHeap("Sphere");		
	}
	return ::operator new(size, pHeap, &head);
	
}

void  Sphere::operator delete (void * pMem)
{
	return ::operator delete(pMem, 0);
}