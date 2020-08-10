#include"SolidVar.h"
double SolidVar::¦Ë = 54.71E9;
double SolidVar::¦Ì = 25.746E9;
SolidVar::SolidVar(double ¦Òxx, double ¦Òyy, double ¦Òxy, double ¦Åxx , double ¦Åyy , double ¦Åxy )
{
	stress = new double[3];
	strain = new double[3];
	stress[0] = ¦Òxx;
	stress[1] = ¦Òyy;
	stress[2] = ¦Òxy;
	strain[0] = ¦Åxx;
	strain[1] = ¦Åyy;
	strain[2] = ¦Åxy;
}
void SolidVar::updateStressFromStrain()
{
	stress[0] = (¦Ë + 2 * ¦Ì) * strain[0] + ¦Ë * strain[1];
	stress[1] = (¦Ë + 2 * ¦Ì) * strain[1] + ¦Ë * strain[0];
	stress[2] = 2 * ¦Ì * strain[2];
}
void SolidVar::updateStrainFromStress()
{
	strain[0] = (¦Ë * stress[0] - (¦Ë + 2 * ¦Ì) * stress[1]) 
		/ (¦Ë * ¦Ë - (¦Ë + 2 * ¦Ì) * (¦Ë + 2 * ¦Ì));
	strain[1] = (¦Ë * stress[1] - (¦Ë + 2 * ¦Ì) * stress[0])
		/ (¦Ë * ¦Ë - (¦Ë + 2 * ¦Ì) * (¦Ë + 2 * ¦Ì));
	strain[2] = stress[2] / (2 * ¦Ì);
}

void SolidVar::changeStress(double ¦Òxx, double ¦Òyy, double ¦Òxy)
{
	stress[0] = ¦Òxx;
	stress[1] = ¦Òyy;
	stress[2] = ¦Òxy;
	updateStrainFromStress();
}
void SolidVar::changeStrain(double ¦Åxx , double ¦Åyy , double ¦Åxy )
{
	strain[0] = ¦Åxx;
	strain[1] = ¦Åyy;
	strain[2] = ¦Åxy;
	updateStressFromStrain();
}
