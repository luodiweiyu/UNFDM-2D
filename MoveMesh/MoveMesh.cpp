#include"MoveMesh.h"
void MoveMesh::change(double u , double v , double w )
{
	meshVel[0] = u;
	meshVel[1] = v;
	meshVel[2] = w;
}