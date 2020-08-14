#include"Riemann.h"
#include"../SuperSonic.h"
#include"../FluidVar/FluidFlux.h"
//namespace SuperSonic
//{
//	namespace Riemann
//	{
using namespace SuperSonic;
FlowFlux SuperSonic::Riemann::HLLC_Χ(BaseVar& CL, BaseVar& CR, coordTrans& ct)//半点左侧右侧格点，坐标变换参考点
{
	double ξx = ct.ξx();
	double ξy = ct.ξy();
	double ξt = ct.ξt();
	double J = ct.J();
	double Dξ = sqrt(ξx * ξx + ξy * ξy);
	double ξ1 = ξx / Dξ;
	double ξ2 = ξy / Dξ;
	double ξ3 = ξt / Dξ;
	double ξcL = CL.u() * ξ1 + CL.v() * ξ2 + ξ3;
	double ξcR = CR.u() * ξ1 + CR.v() * ξ2 + ξ3;
	double aL = sqrt(gama * CL.p() / CL.rho());
	double aR = sqrt(gama * CR.p() / CR.rho());
	double a = sqrt(CL.rho());
	double b = sqrt(CR.rho());
	double SL = ξcL - aL;
	double SR = ξcR + aR;

	double EL = CL.p() / (gama - 1) + 0.5 * CL.rho() * CL.u() * CL.u() + 0.5 * CL.rho() * CL.v() * CL.v();
	double ER = CR.p() / (gama - 1) + 0.5 * CR.rho() * CR.u() * CR.u() + 0.5 * CR.rho() * CR.v() * CR.v();
	FlowFlux FL, FR;
	FL.changeFF(CL.rho() * ξcL,
		CL.rho() * CL.u() * ξcL + ξ1 * CL.p(),
		CL.rho() * CL.v() * ξcL + ξ2 * CL.p(),
		ξcL * (EL + CL.p()) - ξ3 * CL.p());
	FR.changeFF(CR.rho() * ξcR,
		CR.rho() * CR.u() * ξcR + ξ1 * CR.p(),
		CR.rho() * CR.v() * ξcR + ξ2 * CR.p(),
		ξcR * (ER + CR.p()) - ξ3 * CR.p());

	double SM = (CL.p() - CR.p() + CL.rho() * ξcL * (ξcL - SL) + CR.rho() * ξcR * (SR - ξcR)) / (CR.rho() * (SR - ξcR) + CL.rho() * (ξcL - SL));
	double pM = 0.5 * (CL.rho() * (ξcL - SL) * (ξcL - SM) + CR.rho() * (ξcR - SR) * (ξcR - SM) + CR.p() + CL.p());
	//Average-State Jacobians and Implicit Methods for Compressible Viscous and Turbulent Flows,(7)(8)
	double ΩL = 1 / (SL - SM);
	double ΩR = 1 / (SR - SM);

	double rhoLM = ΩL * CL.rho() * (SL - ξcL);
	double rhouLS = ΩL * ((SL - ξcL) * (CL.rho() * CL.u()) + (pM - CL.p()) * ξ1);
	double rhovLS = ΩL * ((SL - ξcL) * (CL.rho() * CL.v()) + (pM - CL.p()) * ξ2);
	double eLS = ΩL * ((SL - ξcL) * EL - CL.p() * ξcL + pM * SM - (pM - CL.p()) * ξ3);

	double rhoRM = ΩR * CR.rho() * (SR - ξcR);
	double rhouRS = ΩR * ((SR - ξcR) * (CR.rho() * CR.u()) + (pM - CR.p()) * ξ1);
	double rhovRS = ΩR * ((SR - ξcR) * (CR.rho() * CR.v()) + (pM - CR.p()) * ξ2);
	double eRS = ΩR * ((SR - ξcR) * ER - CR.p() * ξcR + pM * SM - (pM - CR.p()) * ξ3);

	FlowFlux FML, FMR;
	FML.changeFF(SM * rhoLM,
		rhouLS * SM + pM * ξ1,
		rhovLS * SM + pM * ξ2,
		(eLS + pM) * SM - pM * ξ3);
	FMR.changeFF(SM * rhoRM,
		rhouRS * SM + pM * ξ1,
		rhovRS * SM + pM * ξ2,
		(eRS + pM) * SM - pM * ξ3);

	FlowFlux F_HLLC;
	if (SL > 0)
		F_HLLC = FL;
	else if (SL <= 0 && SM > 0)
		F_HLLC = FML;
	else if (SM <= 0 && SR >= 0)
		F_HLLC = FMR;
	else
		F_HLLC = FR;
	F_HLLC = F_HLLC / Dξ;
	return F_HLLC;
}
FlowFlux SuperSonic::Riemann::HLLC_Y(BaseVar& CD, BaseVar& CU, coordTrans& ct)//半点左侧右侧格点，坐标变换参考点
{
	double ηx = ct.ηx();
	double ηy = ct.ηy();
	double ηt = ct.ηt();
	double J = ct.J();

	double Dη = sqrt(ηx * ηx + ηy * ηy);
	double η1 = ηx / Dη;
	double η2 = ηy / Dη;
	double η3 = ηt / Dη;
	double ηcU = CU.u() * η1 + CU.v() * η2;
	double ηcD = CD.u() * η1 + CD.v() * η2;
	double aU = sqrt(gama * CU.p() / CU.rho());
	double aD = sqrt(gama * CD.p() / CD.rho());
	double EU = CU.p() / (gama - 1) + 0.5 * CU.rho() * CU.u() * CU.u() + 0.5 * CU.rho() * CU.v() * CU.v();
	double ED = CD.p() / (gama - 1) + 0.5 * CD.rho() * CD.u() * CD.u() + 0.5 * CD.rho() * CD.v() * CD.v();
	FlowFlux GD, GU;
	GD.changeFF(CD.rho() * ηcD,
		CD.rho() * CD.u() * ηcD + η1 * CD.p(),
		CD.rho() * CD.v() * ηcD + η2 * CD.p(),
		ηcD * (ED + CD.p()) - η3 * CD.p());

	GU.changeFF(CU.rho() * ηcU,
		CU.rho() * CU.u() * ηcU + η1 * CD.p(),
		CU.rho() * CU.v() * ηcU + η2 * CD.p(),
		ηcU * (EU + CU.p()) - η3 * CD.p());

	double SD = ηcD - aD;
	double SU = ηcU + aU;
	double SM = (CD.p() - CU.p() - CD.rho() * ηcD * (SD - ηcD) + CU.rho() * ηcU * (SU - ηcU)) / (CU.rho() * (SU - ηcU) - CD.rho() * (SD - ηcD));
	double pM = 0.5 * (CD.rho() * (ηcD - SD) * (ηcD - SM) + CU.rho() * (ηcU - SU) * (ηcU - SM) + CU.p() + CD.p());
	//Average-State Jacobians and Implicit Methods for Compressible Viscous and Turbulent Flows,(7)(8)
	double ΩD = 1 / (SD - SM);
	double ΩU = 1 / (SU - SM);

	double ρDM = ΩD * CD.rho() * (SD - ηcD);
	double ρuDS = ΩD * ((SD - ηcD) * (CD.rho() * CD.u()) + (pM - CD.p()) * η1);
	double ρvDS = ΩD * ((SD - ηcD) * (CD.rho() * CD.v()) + (pM - CD.p()) * η2);
	double eDS = ΩD * ((SD - ηcD) * ED - CD.p() * ηcD + pM * SM - (pM - CD.p()) * η3);

	double ρUM = ΩU * CU.rho() * (SU - ηcU);
	double ρuUS = ΩU * ((SU - ηcU) * (CU.rho() * CU.u()) + (pM - CU.p()) * η1);
	double ρvUS = ΩU * ((SU - ηcU) * (CU.rho() * CU.v()) + (pM - CU.p()) * η2);
	double eUS = ΩU * ((SU - ηcU) * EU - CU.p() * ηcU + pM * SM - (pM - CU.p()) * η3);

	FlowFlux  FMD, FMU;
	FMD.changeFF(SM * ρDM,
		ρuDS * SM + pM * η1,
		ρvDS * SM + pM * η2,
		(eDS + pM) * SM - pM * η3);
	FMU.changeFF(SM * ρUM,
		ρuUS * SM + pM * η1,
		ρvUS * SM + pM * η2,
		(eUS + pM) * SM - pM * η3);


	FlowFlux G_HLLC;
	if (SD >= 0)
		G_HLLC = GD;
	else if (SD <= 0 && SM >= 0)
		G_HLLC = FMD;
	else if (SM <= 0 && SU >= 0)
		G_HLLC = FMU;
	else
		G_HLLC = GU;

	G_HLLC = G_HLLC * Dη;

	return G_HLLC;

}
//	}
//}
