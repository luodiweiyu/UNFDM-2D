#include"Flux.h"
Flux::Flux(Flux& f)
{
	var = f.var;
}
Flux Flux:: operator+(const Flux& f)
{
	Flux FluxOut;
	for (int i = 0; i < dim + 2; i++)
	{
		FluxOut.var[i] = var[i] + f.var[i];
	}
	return FluxOut;
}
Flux Flux:: operator-(const Flux& f)
{
	Flux FluxOut;
	for (int i = 0; i < dim + 2; i++)
	{
		FluxOut.var[i] = var[i] - f.var[i];
	}
	return FluxOut;
}
Flux& Flux:: operator=(const Flux& f)
{
	var = f.var;
	return *this;
}
Flux& Flux:: operator+=(const Flux& f)
{
	for (int i = 0; i < dim + 2; i++)
	{
		var[i] += f.var[i];
	}
	return *this;
}
Flux operator*(double number, Flux& f)
{
	Flux FluxOut;
	for (int i = 0; i < f.dim + 2; i++)
	{
		FluxOut.var[i] = number * f.var[i];
	}
	return FluxOut;
}
