#include"Riemann.h"
#include"../SuperSonic.h"
#include"../FluidVar/FluidFlux.h"
//namespace SuperSonic
//{
//	namespace Riemann
//	{
using namespace SuperSonic;
FlowFlux SuperSonic::Riemann::HLLC_��(BaseVar& CL, BaseVar& CR, coordTrans& ct)//�������Ҳ��㣬����任�ο���
{
	double ��x = ct.��x();
	double ��y = ct.��y();
	double ��t = ct.��t();
	double J = ct.J();
	double D�� = sqrt(��x * ��x + ��y * ��y);
	double ��1 = ��x / D��;
	double ��2 = ��y / D��;
	double ��3 = ��t / D��;
	double ��cL = CL.u() * ��1 + CL.v() * ��2 + ��3;
	double ��cR = CR.u() * ��1 + CR.v() * ��2 + ��3;
	double aL = sqrt(gama * CL.p() / CL.rho());
	double aR = sqrt(gama * CR.p() / CR.rho());
	double a = sqrt(CL.rho());
	double b = sqrt(CR.rho());
	double SL = ��cL - aL;
	double SR = ��cR + aR;

	double EL = CL.p() / (gama - 1) + 0.5 * CL.rho() * CL.u() * CL.u() + 0.5 * CL.rho() * CL.v() * CL.v();
	double ER = CR.p() / (gama - 1) + 0.5 * CR.rho() * CR.u() * CR.u() + 0.5 * CR.rho() * CR.v() * CR.v();
	FlowFlux FL, FR;
	FL.changeFF(CL.rho() * ��cL,
		CL.rho() * CL.u() * ��cL + ��1 * CL.p(),
		CL.rho() * CL.v() * ��cL + ��2 * CL.p(),
		��cL * (EL + CL.p()) - ��3 * CL.p());
	FR.changeFF(CR.rho() * ��cR,
		CR.rho() * CR.u() * ��cR + ��1 * CR.p(),
		CR.rho() * CR.v() * ��cR + ��2 * CR.p(),
		��cR * (ER + CR.p()) - ��3 * CR.p());

	double SM = (CL.p() - CR.p() + CL.rho() * ��cL * (��cL - SL) + CR.rho() * ��cR * (SR - ��cR)) / (CR.rho() * (SR - ��cR) + CL.rho() * (��cL - SL));
	double pM = 0.5 * (CL.rho() * (��cL - SL) * (��cL - SM) + CR.rho() * (��cR - SR) * (��cR - SM) + CR.p() + CL.p());
	//Average-State Jacobians and Implicit Methods for Compressible Viscous and Turbulent Flows,(7)(8)
	double ��L = 1 / (SL - SM);
	double ��R = 1 / (SR - SM);

	double rhoLM = ��L * CL.rho() * (SL - ��cL);
	double rhouLS = ��L * ((SL - ��cL) * (CL.rho() * CL.u()) + (pM - CL.p()) * ��1);
	double rhovLS = ��L * ((SL - ��cL) * (CL.rho() * CL.v()) + (pM - CL.p()) * ��2);
	double eLS = ��L * ((SL - ��cL) * EL - CL.p() * ��cL + pM * SM - (pM - CL.p()) * ��3);

	double rhoRM = ��R * CR.rho() * (SR - ��cR);
	double rhouRS = ��R * ((SR - ��cR) * (CR.rho() * CR.u()) + (pM - CR.p()) * ��1);
	double rhovRS = ��R * ((SR - ��cR) * (CR.rho() * CR.v()) + (pM - CR.p()) * ��2);
	double eRS = ��R * ((SR - ��cR) * ER - CR.p() * ��cR + pM * SM - (pM - CR.p()) * ��3);

	FlowFlux FML, FMR;
	FML.changeFF(SM * rhoLM,
		rhouLS * SM + pM * ��1,
		rhovLS * SM + pM * ��2,
		(eLS + pM) * SM - pM * ��3);
	FMR.changeFF(SM * rhoRM,
		rhouRS * SM + pM * ��1,
		rhovRS * SM + pM * ��2,
		(eRS + pM) * SM - pM * ��3);

	FlowFlux F_HLLC;
	if (SL > 0)
		F_HLLC = FL;
	else if (SL <= 0 && SM > 0)
		F_HLLC = FML;
	else if (SM <= 0 && SR >= 0)
		F_HLLC = FMR;
	else
		F_HLLC = FR;
	F_HLLC = F_HLLC / D��;
	return F_HLLC;
}
FlowFlux SuperSonic::Riemann::HLLC_Y(BaseVar& CD, BaseVar& CU, coordTrans& ct)//�������Ҳ��㣬����任�ο���
{
	double ��x = ct.��x();
	double ��y = ct.��y();
	double ��t = ct.��t();
	double J = ct.J();

	double D�� = sqrt(��x * ��x + ��y * ��y);
	double ��1 = ��x / D��;
	double ��2 = ��y / D��;
	double ��3 = ��t / D��;
	double ��cU = CU.u() * ��1 + CU.v() * ��2;
	double ��cD = CD.u() * ��1 + CD.v() * ��2;
	double aU = sqrt(gama * CU.p() / CU.rho());
	double aD = sqrt(gama * CD.p() / CD.rho());
	double EU = CU.p() / (gama - 1) + 0.5 * CU.rho() * CU.u() * CU.u() + 0.5 * CU.rho() * CU.v() * CU.v();
	double ED = CD.p() / (gama - 1) + 0.5 * CD.rho() * CD.u() * CD.u() + 0.5 * CD.rho() * CD.v() * CD.v();
	FlowFlux GD, GU;
	GD.changeFF(CD.rho() * ��cD,
		CD.rho() * CD.u() * ��cD + ��1 * CD.p(),
		CD.rho() * CD.v() * ��cD + ��2 * CD.p(),
		��cD * (ED + CD.p()) - ��3 * CD.p());

	GU.changeFF(CU.rho() * ��cU,
		CU.rho() * CU.u() * ��cU + ��1 * CD.p(),
		CU.rho() * CU.v() * ��cU + ��2 * CD.p(),
		��cU * (EU + CU.p()) - ��3 * CD.p());

	double SD = ��cD - aD;
	double SU = ��cU + aU;
	double SM = (CD.p() - CU.p() - CD.rho() * ��cD * (SD - ��cD) + CU.rho() * ��cU * (SU - ��cU)) / (CU.rho() * (SU - ��cU) - CD.rho() * (SD - ��cD));
	double pM = 0.5 * (CD.rho() * (��cD - SD) * (��cD - SM) + CU.rho() * (��cU - SU) * (��cU - SM) + CU.p() + CD.p());
	//Average-State Jacobians and Implicit Methods for Compressible Viscous and Turbulent Flows,(7)(8)
	double ��D = 1 / (SD - SM);
	double ��U = 1 / (SU - SM);

	double ��DM = ��D * CD.rho() * (SD - ��cD);
	double ��uDS = ��D * ((SD - ��cD) * (CD.rho() * CD.u()) + (pM - CD.p()) * ��1);
	double ��vDS = ��D * ((SD - ��cD) * (CD.rho() * CD.v()) + (pM - CD.p()) * ��2);
	double eDS = ��D * ((SD - ��cD) * ED - CD.p() * ��cD + pM * SM - (pM - CD.p()) * ��3);

	double ��UM = ��U * CU.rho() * (SU - ��cU);
	double ��uUS = ��U * ((SU - ��cU) * (CU.rho() * CU.u()) + (pM - CU.p()) * ��1);
	double ��vUS = ��U * ((SU - ��cU) * (CU.rho() * CU.v()) + (pM - CU.p()) * ��2);
	double eUS = ��U * ((SU - ��cU) * EU - CU.p() * ��cU + pM * SM - (pM - CU.p()) * ��3);

	FlowFlux  FMD, FMU;
	FMD.changeFF(SM * ��DM,
		��uDS * SM + pM * ��1,
		��vDS * SM + pM * ��2,
		(eDS + pM) * SM - pM * ��3);
	FMU.changeFF(SM * ��UM,
		��uUS * SM + pM * ��1,
		��vUS * SM + pM * ��2,
		(eUS + pM) * SM - pM * ��3);


	FlowFlux G_HLLC;
	if (SD >= 0)
		G_HLLC = GD;
	else if (SD <= 0 && SM >= 0)
		G_HLLC = FMD;
	else if (SM <= 0 && SU >= 0)
		G_HLLC = FMU;
	else
		G_HLLC = GU;

	G_HLLC = G_HLLC * D��;

	return G_HLLC;

}
//	}
//}
