#include"FluidFlux.h"
using namespace FluidFlux;
BaseVar::BaseVar(double rho, double u, double v, double p)
{
	var.resize(dim + 2);
	if (dim == 2)
	{
		var[0] = rho;
		var[1] = u;
		var[2] = v;
		var[3] = p;
	}
	else
		throw "三维还没设置";
}
//BaseVar::BaseVar(ConsVar& cv)
//{
//	if (dim == 2)
//		var = new double[dim + 2];
//	else
//		throw "三维还没设置";
//	updateFromConsVar(cv);
//}
void BaseVar::changeBV(double rho, double u, double v, double p)
{
	var[0] = rho;
	var[1] = u;
	var[2] = v;
	var[3] = p;
}

void BaseVar::updateFromConsVar(ConsVar& cv)
{
	var[0] = cv[0];
	var[1] = cv[1] / cv[0];
	var[2] = cv[2] / cv[0];
	var[3] = (gama - 1) * (cv[3] - 0.5 * var[0] * (var[1] * var[1] + var[2] * var[2]));
}

ConsVar::ConsVar(BaseVar& bv)
{
	if (dim == 2)
		var.resize(dim + 2);
	else
		throw "三维还没设置";
	updateFromBaseVar(bv.rho(), bv.u(), bv.v(), bv.p());
}
ConsVar::ConsVar(double rho, double u, double v, double p)
{
	if (dim == 2)
		var.resize(dim + 2);
	else
		throw "三维还没设置";
	updateFromBaseVar(rho, u, v, p);
}
void ConsVar::updateFromBaseVar(BaseVar& bv)
{
	updateFromBaseVar(bv.rho(), bv.u(), bv.v(), bv.p());
}
void ConsVar::updateFromBaseVar(double rho, double u, double v, double p)
{
	var[0] = rho;
	var[1] = rho * u;
	var[2] = rho * v;
	var[3] = 0.5 * rho * (u * u + v * v) + p / (gama - 1);
}
ConsVar& ConsVar:: operator=(Flux& f)
{
	for (int i = 0; i < dim + 2; i++)
	{
		var[i] = f.flux(i);
	}
	return *this;
}
ConsVar& ConsVar::operator+=(const Flux& f)
{
	for (int i = 0; i < dim + 2; i++)
	{
		var[i] += f.flux(i);
	}
	return *this;

}


FlowFlux::FlowFlux(const FlowFlux& f)
{
	var = f.var;

}
FlowFlux::FlowFlux(double f1, double f2, double f3, double f4)
{
	var.resize(dim + 2);
	changeFF(f1, f2, f3, f4);
}
void FlowFlux::changeFF(double f1, double f2, double f3, double f4)
{
	var[0] = f1;
	var[1] = f2;
	var[2] = f3;
	var[3] = f4;
}

FlowFlux& FlowFlux:: operator=(Flux& f)
{
	for (int i = 0; i < dim + 2; i++)
	{
		var[i] = f.flux(i);
	}
	return *this;
}
FlowFlux& FlowFlux:: operator=(double number)
{
	for (int i = 0; i < dim + 2; i++)
	{
		var[i] = number;
	}
	return *this;
}
FlowFlux& FlowFlux:: operator/=(double number)
{
	for (int i = 0; i < dim + 2; i++)
	{
		var[i] /= number;
	}
	return *this;
}
FlowFlux FlowFlux:: operator*(double number)
{
	FlowFlux fluxout;
	for (int i = 0; i < dim + 2; i++)
	{
		fluxout.var[i] = var[i] * number;
	}
	return fluxout;
}
FlowFlux& FlowFlux:: operator+=(const Flux& f)
{

	for (int i = 0; i < dim + 2; i++)
	{

		var[i] += f.flux(i);
	}
	return *this;
}
FlowFlux FlowFlux:: operator+(const FlowFlux& f)
{
	FlowFlux fluxout;
	for (int i = 0; i < dim + 2; i++)
	{
		fluxout.var[i] = var[i] + f.flux(i);
	}
	return fluxout;
}
FlowFlux FlowFlux:: operator-(const FlowFlux& f)
{
	FlowFlux fluxout;
	for (int i = 0; i < dim + 2; i++)
	{
		fluxout.var[i] = var[i] - f.flux(i);
	}
	return fluxout;
}
//FlowFlux operator*(double number, FlowFlux& f)
//{
//	FlowFlux fluxout;
//	for (int i = 0; i < f.dim + 2; i++)
//	{
//		fluxout.var[i] = number* f.var[i];
//	}
//	return fluxout;
//}
