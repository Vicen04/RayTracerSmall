#pragma once
#include "MemoryPool.h"

static Heap* pHeap = NULL;
static AllocHeader* head = NULL;

template<typename T>

class Vector3
{
public:
	T x, y, z;
	Vector3() : x(T(0)), y(T(0)), z(T(0)) {}
	Vector3(T xx) : x(xx), y(xx), z(xx) {}
	Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	Vector3& normalize()
	{
		T nor2 = length2();
		if (nor2 > 0) {
			T invNor = 1 / sqrt(nor2);
			x *= invNor, y *= invNor, z *= invNor;
		}
		return *this;
	}
	Vector3<T> operator * (const T &f) const { return Vector3<T>(x * f, y * f, z * f); }
	Vector3<T> operator * (const Vector3<T> &v) const { return Vector3<T>(x * v.x, y * v.y, z * v.z); }
	T dot(const Vector3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
	Vector3<T> operator - (const Vector3<T> &v) const { return Vector3<T>(x - v.x, y - v.y, z - v.z); }
	Vector3<T> operator + (const Vector3<T> &v) const { return Vector3<T>(x + v.x, y + v.y, z + v.z); }
	Vector3<T>& operator += (const Vector3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }
	Vector3<T>& operator *= (const Vector3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
	Vector3<T> operator - () const { return Vector3<T>(-x, -y, -z); }
	static void * operator new (size_t size)
	{
		if (pHeap == NULL)
		{
			pHeap = HeapFactory::CreateHeap("Vector3");
		}
		return ::operator new(size, pHeap, &head);
	}
	static void * operator new[] (size_t size, MemoryPool* pool)
	{
		return pool->Alloc(size);
	}
	static void * operator new[] (size_t size)
	{	
		if (pHeap == NULL)
		{
			pHeap = HeapFactory::CreateHeap("Vector3");
		}
		return ::operator new(size, pHeap, &head);
	}

	static void operator delete (void * pMem)
	{
		return ::operator delete(pMem, 0);
	}
	static void operator delete[] (void * pMem)
	{
		return ::operator delete(pMem, 0);
	}
	static void operator delete[] (void * pMem, MemoryPool* pool)
	{
		return pool->Free(pMem, 0);
	}

	T length2() const { return x * x + y * y + z * z; }
	T length() const { return sqrt(length2()); }
	friend std::ostream & operator << (std::ostream &os, const Vector3<T> &v)
	{
		os << "[" << v.x << " " << v.y << " " << v.z << "]";
		return os;
	}

private:
	//static Heap* pHeap;
	//static mutex locked;
};

