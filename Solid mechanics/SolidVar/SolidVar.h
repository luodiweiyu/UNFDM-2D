#pragma once
class SolidVar
{
	//�洢Ӧ����Ӧ��
	//stress[0] = ��xx
	//stress[1] = ��yy
	//stress[2] = ��xy
	//strain[0] = ��xx
	//strain[1] = ��yy
	//strain[2] = ��xy
private:
	double* stress;
	double* strain;
	static double ��, ��;
public:
	SolidVar() { stress = new double[3], strain = new double[3]; };
	SolidVar(double ��xx, double ��yy, double ��xy, double ��xx = 0, double ��yy = 0, double ��xy = 0);
	~SolidVar() { delete[]stress, delete[]strain; };
	void updateStressFromStrain();
	void updateStrainFromStress();
	void changeStress(double ��xx, double ��yy, double ��xy);
	void changeStrain(double ��xx, double ��yy, double ��xy);
	double ��xx() { return stress[0]; };
	double ��yy() { return stress[1]; };
	double ��xy() { return stress[2]; };
	double ��xx() { return strain[0]; };
	double ��yy() { return strain[1]; };
	double ��xy() { return strain[2]; };
};