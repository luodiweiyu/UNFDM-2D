#include"Riemann.h"
namespace WaterWave
{
	namespace Riemann
	{
		FlowFlux Direct_��(BaseVar& CL, BaseVar& CR)
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
		FlowFlux Direct_��(BaseVar& CL, BaseVar& CR, coordTrans& ct)
		{
			ConsVar cvl, cvr;
			cvl.updateFromBaseVar(CL);
			cvr.updateFromBaseVar(CR);
			cvl = cvl * ct.��t();
			cvr = cvr * ct.��t();
			FlowFlux fl, fr;
			fl.changeFF(CL.h() * CL.u(),
				CL.h() * CL.u() * CL.u() + 0.5 * g * CL.h() * CL.h(),
				CL.h() * CL.u() * CL.v());
			fr.changeFF(CR.h() * CR.u(),
				CR.h() * CR.u() * CR.u() + 0.5 * g * CR.h() * CR.h(),
				CR.h() * CR.u() * CR.v());
			fl = fl * ct.��x();
			fr = fr * ct.��x();
			FlowFlux gl, gr;
			gl.changeFF(CL.h() * CL.v(),
				CL.h() * CL.u() * CL.v(),
				CL.h() * CL.v() * CL.v() + 0.5 * g * CL.h() * CL.h());
			gr.changeFF(CR.h() * CR.v(),
				CR.h() * CR.u() * CR.v(),
				CR.h() * CR.v() * CR.v() + 0.5 * g * CR.h() * CR.h());
			gl = gl * ct.��y();
			gr = gr * ct.��y();
			FlowFlux f��l, f��r;
			f��l.changeFF(
				cvl.flux(0) + fl.flux(0) + gl.flux(0),
				cvl.flux(1) + fl.flux(1) + gl.flux(1),
				cvl.flux(2) + fl.flux(2) + gl.flux(2));
			f��r.changeFF(
				cvr.flux(0) + fr.flux(0) + gr.flux(0),
				cvr.flux(1) + fr.flux(1) + gr.flux(1),
				cvr.flux(2) + fr.flux(2) + gr.flux(2));
			FlowFlux fluxOut = (f��l + f��r) / 2;
			return fluxOut;
		}
		FlowFlux Direct_��(BaseVar& CD, BaseVar& CU, coordTrans& ct)
		{
			ConsVar cvd, cvu;
			cvd.updateFromBaseVar(CD);
			cvu.updateFromBaseVar(CU);
			cvd = cvd * ct.��t();
			cvu = cvu * ct.��t();
			FlowFlux fd, fu;
			fd.changeFF(CD.h() * CD.u(),
				CD.h() * CD.u() * CD.u() + 0.5 * g * CD.h() * CD.h(),
				CD.h() * CD.u() * CD.v());
			fu.changeFF(CU.h() * CU.u(),
				CU.h() * CU.u() * CU.u() + 0.5 * g * CU.h() * CU.h(),
				CU.h() * CU.u() * CU.v());
			fd = fd * ct.��x();
			fu = fu * ct.��x();
			FlowFlux gd, gu;
			gd.changeFF(CD.h() * CD.v(),
				CD.h() * CD.u() * CD.v(),
				CD.h() * CD.v() * CD.v() + 0.5 * g * CD.h() * CD.h());
			gu.changeFF(CU.h() * CU.v(),
				CU.h() * CU.u() * CU.v(),
				CU.h() * CU.v() * CU.v() + 0.5 * g * CU.h() * CU.h());
			gd = gd * ct.��y();
			gu = gu * ct.��y();
			FlowFlux f��d, f��u;
			f��d.changeFF(
				cvd.flux(0) + fd.flux(0) + gd.flux(0),
				cvd.flux(1) + fd.flux(1) + gd.flux(1),
				cvd.flux(2) + fd.flux(2) + gd.flux(2));
			f��u.changeFF(
				cvu.flux(0) + fu.flux(0) + gu.flux(0),
				cvu.flux(1) + fu.flux(1) + gu.flux(1),
				cvu.flux(2) + fu.flux(2) + gu.flux(2));
			FlowFlux fluxOut = (f��d + f��u) / 2;
			return fluxOut;
		}

	}
}
