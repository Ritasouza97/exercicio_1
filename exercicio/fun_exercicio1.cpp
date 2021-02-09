//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words

EQUATION("X")
	v[0]=V("P");
	v[1]=V("Q");
	v[2]=V("c");
	v[3]=V("e_p");
	v[4]=V("e_q");
	v[5]=pow(v[1],v[4])/pow(v[0],v[3]);
	v[6]=v[5]+v[2];
RESULT(v[6])


EQUATION("P")
	v[0]=VL("P",1);
	v[1]=V("p_adj");
	v[2]=VL("Share",1);
	v[3]=VL("Share",2);
	v[4]=(v[2]-v[3])/v[3];
	v[5]=v[0]*(1+v[1]*v[4]);
RESULT(v[5])


EQUATION("Q")
	v[0]=VL("Q",1);
	v[1]=V("q_sd");
	v[2]=norm(v[0],v[1]);
	v[3]=max(v[0],v[2]);
RESULT(v[3])


EQUATION("c")
	v[0]=V("min");
	v[1]=V("max");
	v[2]=uniform(v[0],v[1]);
RESULT(v[2])

EQUATION("X_Sum")
RESULT(SUM("X"))

EQUATION("X_Ave")
RESULT(AVE("X"))

EQUATION("X_Max")
RESULT(MAX("X"))

EQUATION("Share")
	v[0]=V("X");
	v[1]=V("X_Sum");
	v[2]=v[1]!=0?v[0]/v[1]:0;
RESULT(v[2])

EQUATION("Share_Sum")
RESULT(SUM("Share"))


//EXERC�CIO 4
EQUATION("HHI")
	v[0]=0;
	CYCLE(cur,"FIRM")
	{
		v[1]=VS(cur,"Share");
		v[2]=pow(v[1],2);
		v[0]=v[0]+v[2];
	}
	if(v[0]==0)
		v[3]=0;
	else
		v[3]=1/v[0]
RESULT(v[3])
	



MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
