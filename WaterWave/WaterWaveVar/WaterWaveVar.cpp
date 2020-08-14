#include"WaterWaveVar.h"
namespace WaterWave
{
	BaseVar::BaseVar(const double h, const  double u, const double v)
	{
		var.resize(dim + 1);
		changeBV(h, u, v);
	}
	void BaseVar::changeBV(const double h, const double u, const double v)
	{
		var[0] = h;
		var[1] = u;
		var[2] = v;
	}
	void BaseVar::updateFromConsVar(const  WaterWave::ConsVar& cv)
	{
		var.resize(dim + 1);
		var[0] = cv.flux(0);
		var[1] = cv.flux(1) / var[0];
		var[2] = cv.flux(2) / var[0];
	}
	ConsVar::ConsVar(const double h, const double u, const double v)
	{
		var.resize(dim + 1);
		updateFromBaseVar(h, u, v);
	}


	void ConsVar::updateFromBaseVar(const WaterWave::BaseVar& bv)
	{
		updateFromBaseVar(bv.h(), bv.u(), bv.v());
	}
	void ConsVar::updateFromBaseVar(const double h, const  double u, const double v)
	{
		var[0] = h;
		var[1] = h * u;
		var[2] = h * v;
	}
	ConsVar ConsVar::operator*(const double dig)
	{
		ConsVar fluxOut;
		for (int i = 0; i < var.size(); i++)
			fluxOut.var[i] = var[i] * dig;
		return fluxOut;
	}
	ConsVar ConsVar::operator/(const double dig)
	{
		ConsVar fluxOut;
		for (int i = 0; i < var.size(); i++)
			fluxOut.var[i] = var[i] / dig;
		return fluxOut;
	}
	ConsVar ConsVar::operator+(const FlowFlux& flux_)
	{
		ConsVar fluxOut;
		for (int i = 0; i < var.size(); i++)
			fluxOut.var[i] = var[i] + flux_.flux(i);
		return fluxOut;
	}
	ConsVar& ConsVar::operator=(const ConsVar& flux_)
	{
		for (int i = 0; i < var.size(); i++)
			this->var[i] = flux_.flux(i);
		return *this;
	}
	FlowFlux::FlowFlux(const FlowFlux& f)
	{
		var = f.var;

	}
	FlowFlux::FlowFlux(double f1, double f2, double f3)
	{
		var.resize(dim + 1);
		changeFF(f1, f2, f3);
	}

	void FlowFlux::changeFF(double f1, double f2, double f3)
	{
		var[0] = f1;
		var[1] = f2;
		var[2] = f3;
	}
	FlowFlux FlowFlux::operator+(const FlowFlux& flux_)
	{
		FlowFlux fluxOut;
		for (int i = 0; i < flux_.var.size(); i++)
			fluxOut.var[i] = var[i] + flux_.var[i];
		return fluxOut;
	}
	FlowFlux FlowFlux::operator-(const FlowFlux& flux_)
	{
		FlowFlux fluxOut;
		for (int i = 0; i < flux_.var.size(); i++)
			fluxOut.var[i] = var[i] - flux_.var[i];
		return fluxOut;
	}
	FlowFlux FlowFlux::operator*(const double dig)
	{
		FlowFlux fluxOut;
		for (int i = 0; i < var.size(); i++)
			fluxOut.var[i] = var[i] * dig;
		return fluxOut;
	}
	FlowFlux FlowFlux::operator/(const double dig)
	{
		FlowFlux fluxOut;
		for (int i = 0; i < var.size(); i++)
			fluxOut.var[i] = var[i] / dig;
		return fluxOut;
	}
	FlowFlux& FlowFlux:: operator=(FluxBase& f)
	{
		for (int i = 0; i < dim + 2; i++)
		{
			var[i] = f.flux(i);
		}
		return *this;
	}
	FlowFlux& FlowFlux:: operator+=(const FluxBase& f)
	{

		for (int i = 0; i < dim + 2; i++)
		{

			var[i] += f.flux(i);
		}
		return *this;
	}

}
