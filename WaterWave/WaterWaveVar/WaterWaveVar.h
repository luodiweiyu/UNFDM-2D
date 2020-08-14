#pragma once
#include"../WaterWave.h"
#include"../../FluxBase/FluxBase.h"
namespace WaterWave
{
	class BaseVar :public FluxBase
	{
	public:
		BaseVar() { var.resize(dim + 1); };
		BaseVar(const double h, const double u, const double v);
		void changeBV(const double h, const double u, const double v);
		void updateFromConsVar(const WaterWave::ConsVar& cv);
		double h() const { return var[0]; }
		double u() const { return var[1]; }
		double v() const { return var[2]; }
	};
	class ConsVar :public FluxBase
	{
	public:
		ConsVar() { var.resize(dim + 1); };
		ConsVar(const double h, const double u, const double v);
		ConsVar(const BaseVar& bv);
		void updateFromBaseVar(const WaterWave::BaseVar& bv);
		void updateFromBaseVar(const double h, const double u, const double v);
		ConsVar operator*(const double dig);
		ConsVar operator/(const double dig);
		ConsVar operator+(const FlowFlux& flux_);
		ConsVar& operator=(const ConsVar& flux_);
	};
	class FlowFlux :public FluxBase
	{
	public:
		FlowFlux() { var.resize(dim + 1); };
		FlowFlux(const double f1, const double f2, const double f3);
		FlowFlux(const WaterWave::FlowFlux& f);
		void changeFF(const double f1, const double f2, const double f3);
		FlowFlux operator+(const FlowFlux& flux_);
		FlowFlux operator-(const FlowFlux& flux_);
		FlowFlux operator*(const double dig);
		FlowFlux operator/(const double dig);
		FlowFlux& operator=(FluxBase& f);
		FlowFlux& operator+=(const FluxBase& f);

	};
}
