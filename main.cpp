// [header]
// A very basic raytracer example.
// [/header]
// [compile]
// c++ -o raytracer -O3 -Wall raytracer.cpp
// [/compile]
// [ignore]
// Copyright (C) 2012  www.scratchapixel.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// [/ignore]

//[comment]
// In the main function, we will create the scene which is composed of 5 spheres
// and 1 light (which is also a sphere). Then, once the scene description is complete
// we render that scene, by calling the render() function.
//[/comment]
#include "Raytracer.h"


int main(int argc, char **argv)
{
	HeapFactory::CreateDefaultHeap();
	char response = 'A';
	while (true)
	{
		cout << "Do you need to read a file? Y/N" << endl;
		cin >> response;
		if (response == 'Y' || response == 'N')
			break;
	}
	if (response == 'Y')
	{
		cout << "Please enter the file name" << endl;
		string file;
		cin >> file;
		Raytracer* tracer = new Raytracer(file);
	}
	if (response == 'N')
	{
		cout << "Executing default program" << endl;
		Raytracer* tracer = new Raytracer();
	}
	


	return 0;
}

