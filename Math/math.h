#pragma once
const double pi = 3.141592653;
const double delta = 1e-10;
template<typename T>
T max(T var1, T var2)
{
	if (var1 > var2)
		return var1;
	else
		return var2;
}