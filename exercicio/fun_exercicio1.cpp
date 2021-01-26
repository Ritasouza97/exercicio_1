//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words


// Equações do exercício 3:


// Preço no nível da firma:
EQUATION("Price")
v[0]=VL("X_FShare", 2);
v[1]=VL("X_FShare", 1);
		if(v[1]>=v[0])
		v[2]=((v[1]-v[0])/v[0])+1; 
		else 
		v[2]=1;
v[3]=VL("Price",1);
v[4]=v[2]*v[3];
RESULT(v[4])


// Qualidade no nível da firma:
EQUATION("Quality")
v[0]=VL("Quality",2);
v[1]=VL("Quality",1);
		if(v[1]>=v[0]) 	
		v[2]=v[1]+RND; 
		else
		v[2]=v[0]+RND;
RESULT(v[2])

// X = Vendas no nível da Firma = Preço x Quantidade
EQUATION("Xvendas") 
v[0]=V("Price"); // Equação do Preço
v[1]=VL("Price",1);
v[2]=V("Quality"); // Equação da Qualidade
v[3]=VL("Quality",1);
v[4]=VL("Xvendas",1);
v[5]=V("pP")*(v[0]-v[1]) + V("pQ")*(v[2]-v[3]) +V("pA")*RND + v[4]; // Equação das Vendas = Preço x Quantidade
RESULT(v[5])



//...........................................

// Equações dos exercícios anteriores abaixo:

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
	SORT("FIRM", "X", "DOWN");
	v[0]=0;
	CYCLE(cur, "FIRM")
		{
		v[0]++;
		WRITES(cur, "firm_rank", v[0]);
		}
RESULT(0)




MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
