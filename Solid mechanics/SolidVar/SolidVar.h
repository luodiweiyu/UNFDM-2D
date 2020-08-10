#pragma once
class SolidVar
{
	//存储应力和应变
	//stress[0] = σxx
	//stress[1] = σyy
	//stress[2] = σxy
	//strain[0] = εxx
	//strain[1] = εyy
	//strain[2] = εxy
private:
	double* stress;
	double* strain;
	static double λ, μ;
public:
	SolidVar() { stress = new double[3], strain = new double[3]; };
	SolidVar(double σxx, double σyy, double σxy, double εxx = 0, double εyy = 0, double εxy = 0);
	~SolidVar() { delete[]stress, delete[]strain; };
	void updateStressFromStrain();
	void updateStrainFromStress();
	void changeStress(double σxx, double σyy, double σxy);
	void changeStrain(double εxx, double εyy, double εxy);
	double σxx() { return stress[0]; };
	double σyy() { return stress[1]; };
	double σxy() { return stress[2]; };
	double εxx() { return strain[0]; };
	double εyy() { return strain[1]; };
	double εxy() { return strain[2]; };
};