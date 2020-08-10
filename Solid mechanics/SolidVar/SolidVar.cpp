#include"SolidVar.h"
double SolidVar::�� = 54.71E9;
double SolidVar::�� = 25.746E9;
SolidVar::SolidVar(double ��xx, double ��yy, double ��xy, double ��xx , double ��yy , double ��xy )
{
	stress = new double[3];
	strain = new double[3];
	stress[0] = ��xx;
	stress[1] = ��yy;
	stress[2] = ��xy;
	strain[0] = ��xx;
	strain[1] = ��yy;
	strain[2] = ��xy;
}
void SolidVar::updateStressFromStrain()
{
	stress[0] = (�� + 2 * ��) * strain[0] + �� * strain[1];
	stress[1] = (�� + 2 * ��) * strain[1] + �� * strain[0];
	stress[2] = 2 * �� * strain[2];
}
void SolidVar::updateStrainFromStress()
{
	strain[0] = (�� * stress[0] - (�� + 2 * ��) * stress[1]) 
		/ (�� * �� - (�� + 2 * ��) * (�� + 2 * ��));
	strain[1] = (�� * stress[1] - (�� + 2 * ��) * stress[0])
		/ (�� * �� - (�� + 2 * ��) * (�� + 2 * ��));
	strain[2] = stress[2] / (2 * ��);
}

void SolidVar::changeStress(double ��xx, double ��yy, double ��xy)
{
	stress[0] = ��xx;
	stress[1] = ��yy;
	stress[2] = ��xy;
	updateStrainFromStress();
}
void SolidVar::changeStrain(double ��xx , double ��yy , double ��xy )
{
	strain[0] = ��xx;
	strain[1] = ��yy;
	strain[2] = ��xy;
	updateStressFromStrain();
}
