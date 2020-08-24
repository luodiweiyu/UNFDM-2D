#include"Riemann.h"
#include<string>
#include"../../eigen-3.3.7/Eigen/Dense"
#include<iostream>
namespace WaterWave
{
	namespace Riemann
	{
		FlowFlux Direct_Χ(BaseVar& CL, BaseVar& CR)
		{
			FlowFlux fl, fr, fluxOut;
			fl.changeFF(CL.h() * CL.u(),
				CL.h() * CL.u() * CL.u() + 0.5 * g * CL.h() * CL.h(),
				CL.h() * CL.u() * CL.v());
			fr.changeFF(CR.h() * CR.u(),
				CR.h() * CR.u() * CR.u() + 0.5 * g * CR.h() * CR.h(),
				CR.h() * CR.u() * CR.v());
			fluxOut = (fl + fr) / 2;
			return fluxOut;
		}
		FlowFlux Direct_Y(BaseVar& CD, BaseVar& CU)
		{
			FlowFlux gd, gu, fluxOut;
			gd.changeFF(CD.h() * CD.v(),
				CD.h() * CD.u() * CD.v(),
				CD.h() * CD.v() * CD.v() + 0.5 * g * CD.h() * CD.h());
			gu.changeFF(CU.h() * CU.v(),
				CU.h() * CU.u() * CU.v(),
				CU.h() * CU.v() * CU.v() + 0.5 * g * CU.h() * CU.h());
			fluxOut = (gd + gu) / 2;
			return fluxOut;
		}
		FlowFlux Direct_ξ(BaseVar& CL, BaseVar& CR, coordTrans& ct)
		{
			ConsVar cvl, cvr;
			cvl.updateFromBaseVar(CL);
			cvr.updateFromBaseVar(CR);
			cvl = cvl * ct.ξt();
			cvr = cvr * ct.ξt();
			FlowFlux fl, fr;
			fl.changeFF(CL.h() * CL.u(),
				CL.h() * CL.u() * CL.u() + 0.5 * g * CL.h() * CL.h(),
				CL.h() * CL.u() * CL.v());
			fr.changeFF(CR.h() * CR.u(),
				CR.h() * CR.u() * CR.u() + 0.5 * g * CR.h() * CR.h(),
				CR.h() * CR.u() * CR.v());
			fl = fl * ct.ξx();
			fr = fr * ct.ξx();
			FlowFlux gl, gr;
			gl.changeFF(CL.h() * CL.v(),
				CL.h() * CL.u() * CL.v(),
				CL.h() * CL.v() * CL.v() + 0.5 * g * CL.h() * CL.h());
			gr.changeFF(CR.h() * CR.v(),
				CR.h() * CR.u() * CR.v(),
				CR.h() * CR.v() * CR.v() + 0.5 * g * CR.h() * CR.h());
			gl = gl * ct.ξy();
			gr = gr * ct.ξy();
			FlowFlux fξl, fξr;
			fξl.changeFF(
				cvl.flux(0) + fl.flux(0) + gl.flux(0),
				cvl.flux(1) + fl.flux(1) + gl.flux(1),
				cvl.flux(2) + fl.flux(2) + gl.flux(2));
			fξr.changeFF(
				cvr.flux(0) + fr.flux(0) + gr.flux(0),
				cvr.flux(1) + fr.flux(1) + gr.flux(1),
				cvr.flux(2) + fr.flux(2) + gr.flux(2));
			FlowFlux fluxOut = (fξl + fξr) / 2;
			return fluxOut;
		}
		FlowFlux Direct_η(BaseVar& CD, BaseVar& CU, coordTrans& ct)
		{
			ConsVar cvd, cvu;
			cvd.updateFromBaseVar(CD);
			cvu.updateFromBaseVar(CU);
			cvd = cvd * ct.ηt();
			cvu = cvu * ct.ηt();
			FlowFlux fd, fu;
			fd.changeFF(CD.h() * CD.u(),
				CD.h() * CD.u() * CD.u() + 0.5 * g * CD.h() * CD.h(),
				CD.h() * CD.u() * CD.v());
			fu.changeFF(CU.h() * CU.u(),
				CU.h() * CU.u() * CU.u() + 0.5 * g * CU.h() * CU.h(),
				CU.h() * CU.u() * CU.v());
			fd = fd * ct.ηx();
			fu = fu * ct.ηx();
			FlowFlux gd, gu;
			gd.changeFF(CD.h() * CD.v(),
				CD.h() * CD.u() * CD.v(),
				CD.h() * CD.v() * CD.v() + 0.5 * g * CD.h() * CD.h());
			gu.changeFF(CU.h() * CU.v(),
				CU.h() * CU.u() * CU.v(),
				CU.h() * CU.v() * CU.v() + 0.5 * g * CU.h() * CU.h());
			gd = gd * ct.ηy();
			gu = gu * ct.ηy();
			FlowFlux fξd, fξu;
			fξd.changeFF(
				cvd.flux(0) + fd.flux(0) + gd.flux(0),
				cvd.flux(1) + fd.flux(1) + gd.flux(1),
				cvd.flux(2) + fd.flux(2) + gd.flux(2));
			fξu.changeFF(
				cvu.flux(0) + fu.flux(0) + gu.flux(0),
				cvu.flux(1) + fu.flux(1) + gu.flux(1),
				cvu.flux(2) + fu.flux(2) + gu.flux(2));
			FlowFlux fluxOut = (fξd + fξu) / 2;
			return fluxOut;
		}
		FlowFlux StegerWarming(BaseVar& BV, coordTrans& ct, std::string axisDirection, std::string FluxDirection)
		{
			using namespace Eigen;
			double phix, phiy, phit;
			/*
			此处决定坐标变换的方向 xi，eta
			*/
			if (axisDirection == "xi")
			{
				phix = ct.ξx();
				phiy = ct.ξy();
				phit = ct.ξt();
			}
			else if (axisDirection == "eta")
			{
				phix = ct.ηx();
				phiy = ct.ηy();
				phit = ct.ηt();
			}
			double u = BV.u();
			double v = BV.v();
			double h = BV.h();
			Matrix<double, 3, 1>U;
			U(0, 0) = h;
			U(1, 0) = h * u;
			U(2, 0) = h * v;

			double phic = phit + u * phix + v * phiy;
			double d = sqrt(phix * phix + phiy * phiy);
			double c = sqrt(g * h);
			double lamda1 = phic;
			double lamda2 = phic + c * d;
			double lamda3 = phic - c * d;
			/*
			此处选择特征值正负即lamda+和lamda-
			*/
			if (FluxDirection == "plus")
			{
				lamda1 = (lamda1 + abs(lamda1)) / 2;
				lamda2 = (lamda2 + abs(lamda2)) / 2;
				lamda3 = (lamda3 + abs(lamda3)) / 2;
			}
			else if (FluxDirection == "minus")
			{
				lamda1 = (lamda1 - abs(lamda1)) / 2;
				lamda2 = (lamda2 - abs(lamda2)) / 2;
				lamda3 = (lamda3 - abs(lamda3)) / 2;
			}
			/*
			L和R为左右特征向量矩阵，且L=R^-1
			*/
			Matrix3d L, R, LAM;
			L(0, 0) = 0;
			L(0, 1) = 1;
			L(0, 2) = 1;
			L(1, 0) = phiy;
			L(1, 1) = u + c * phix / d;
			L(1, 2) = u - c * phix / d;
			L(2, 0) = -phix;
			L(2, 1) = v + c * phiy / d;
			L(2, 2) = v - c * phiy / d;

			R(0, 0) = (-u * phiy + v * phix) / (d * d);
			R(0, 1) = phiy / (d * d);
			R(0, 2) = -phix / (d * d);
			R(1, 0) = (c * d - u * phix - v * phiy) / (2 * c * d);
			R(1, 1) = phix / (2 * c * d);
			R(1, 2) = phiy / (2 * c * d);
			R(2, 0) = (c * d + u * phix + v * phiy) / (2 * c * d);
			R(2, 1) = -phix / (2 * c * d);
			R(2, 2) = -phiy / (2 * c * d);
			LAM.fill(0);
			LAM(0, 0) = lamda1;
			LAM(1, 1) = lamda2;
			LAM(2, 2) = lamda3;
			//std::cout << L << std::endl;
			//std::cout << std::endl;
			//std::cout << R << std::endl;
			//std::cout << std::endl;
			//std::cout << LAM << std::endl;
			//std::cout << std::endl;
			//std::cout << L * R << std::endl;
			//std::cout << std::endl;
			//std::cout << L * LAM * R << std::endl;
			//std::cout << std::endl;

			Matrix<double,3,1> flux ;
			flux = L * LAM * R * U;
			FlowFlux FluxOut;
			FluxOut.changeFF(flux(0, 0)/ct.J(), flux(1, 0) / ct.J(), flux(2, 0) / ct.J());
			return FluxOut;
		}
	}
}
