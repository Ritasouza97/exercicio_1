//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words

EQUATION("X")
RESULT(VL("X",1)+V("k"))

EQUATION("k")
v[0]=V("min");
v[1]=V("max");
v[2]=uniform(v[0],v[1]);
RESULT(v[2])


EQUATION("X_Sum")
/*
Soma
*/
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	v[0]=v[0]+v[1];
}
RESULT(v[0])


EQUATION("X_Ave")
/*
Média
*/
v[0]=0;
v[1]=0;
v[2]=0;
CYCLE(cur, "FIRM")
{
	v[3]=VS(cur,"X");
	v[0]=v[0]+v[3];
	v[1]=v[1]+1;
}
if(v[1]==0)	
v[2]=0; 
else 
v[2]=v[0]/v[1]
RESULT(v[2])


EQUATION("X_Max")
/*
Máximo
*/
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	if(v[1]>=v[0]) 	
	v[0]=v[1]; 
	else 
	v[0]=v[0];
}
RESULT(v[0])


EQUATION("X_FShare")
/*
Marketshare da Firma
*/
RESULT((V("X")/V("X_Sum")))


EQUATION("FShare_Sum")
/*
Soma do Marketshare das Firmas
*/
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X_FShare");
	v[0]=v[0]+v[1];
}
RESULT(v[0])


EQUATION("FLider") 
/*
NÚMERO (ou posição) da firma com maior X
*/
v[0]=V("X_Max");
cur1=SEARCH_CND("X", v[0]);			// o cur armazena um objeto especifico enquanto o v[] armazena um valor
v[1]=SEARCH_INST(cur1);					// retorna a posição no objeto especificado
RESULT(v[1])



/*
Exercicio 2.1 
*/

EQUATION("Rank")
v[0]=1;
	CYCLE(cur, "FIRM")
	{
			cur1=SORT("FIRM", "X", "DOWN");
			CYCLE(cur1, "FIRM")
			{
					WRITES(cur, "firm_rank", v[0]);
					v[0]=v[0]+1;	
			}				
	}

RESULT(v[0])




MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
