#include"FluxBase.h"
FluxBase::FluxBase(FluxBase& f)
{
	var = f.var;
}
FluxBase FluxBase:: operator+(const FluxBase& f)
{
	FluxBase FluxOut;
	for (int i = 0; i < dim + 2; i++)
	{
		FluxOut.var[i] = var[i] + f.var[i];
	}
	return FluxOut;
}
FluxBase FluxBase:: operator-(const FluxBase& f)
{
	FluxBase FluxOut;
	for (int i = 0; i < dim + 2; i++)
	{
		FluxOut.var[i] = var[i] - f.var[i];
	}
	return FluxOut;
}
FluxBase& FluxBase:: operator=(const FluxBase& f)
{
	var = f.var;
	return *this;
}
FluxBase& FluxBase:: operator+=(const FluxBase& f)
{
	for (int i = 0; i < dim + 2; i++)
	{
		var[i] += f.var[i];
	}
	return *this;
}
FluxBase operator*(double number, FluxBase& f)
{
	FluxBase FluxOut;
	for (int i = 0; i < f.dim + 2; i++)
	{
		FluxOut.var[i] = number * f.var[i];
	}
	return FluxOut;
}
