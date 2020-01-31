#ifndef MEKD_MG_Boosts_CPP
#define MEKD_MG_Boosts_CPP

#include "MEKD_MG_Boosts.h"


double Boost_trigger_gamma=1e-10;	//minimum value of 1-gamma to trigger a boost

bool debug = false;	// debuggin flag


void Boost_2p_2_pT0(double mass0, double *pi0, double mass1, double *pi1)
{
	long double p0[4], p1[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	
	long double totalp[4];
	int count=0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
}


void Boost_3p_2_pT0(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2)
{
	long double p0[4], p1[4], p2[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] = sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	
	long double totalp[4];
	int count=0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
}


void Boost_4p_2_pT0(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3)
{
	long double p0[4], p1[4], p2[4], p3[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] = sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] = sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	
	long double totalp[4];
	int count=0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count] + p3[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
}


void Boost_5p_2_pT0(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3, double mass4, double *pi4)
{
	long double p0[4], p1[4], p2[4], p3[4], p4[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	p4[1]=(long double) pi4[1]; p4[2]=(long double) pi4[2]; p4[3]=(long double) pi4[3];
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] = sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] = sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	p4[0] = sqrt( mass4*mass4 + p4[1]*p4[1] + p4[2]*p4[2] + p4[3]*p4[3] );
	
	long double totalp[4];
	int count = 0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count] + p3[count] + p4[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	Boost_long(p4, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
	pi4[0]=(double) p4[0]; pi4[1]=(double) p4[1]; pi4[2]=(double) p4[2]; pi4[3]=(double) p4[3];
}


void Boost_2p_and_2p_2_pT0(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3)
{
	long double p0[4], p1[4], p2[4], p3[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	
	p0[0] =sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] =sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] =sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] =sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	
	long double totalp[4];
	int count = 0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
}


void Boost_3p_and_2p_2_pT0(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3, double mass4, double *pi4)
{
	long double p0[4], p1[4], p2[4], p3[4], p4[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	p4[1]=(long double) pi4[1]; p4[2]=(long double) pi4[2]; p4[3]=(long double) pi4[3];
	
	p0[0] =sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] =sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] =sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] =sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	p4[0] =sqrt( mass4*mass4 + p4[1]*p4[1] + p4[2]*p4[2] + p4[3]*p4[3] );
	
	long double totalp[4];
	int count = 0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	Boost_long(p4, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
	pi4[0]=(double) p4[0]; pi4[1]=(double) p4[1]; pi4[2]=(double) p4[2]; pi4[3]=(double) p4[3];
}


void Boost_4p_and_2p_2_pT0(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3, double mass4, double *pi4, double mass5, double *pi5)
{
	long double p0[4], p1[4], p2[4], p3[4], p4[4], p5[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	p4[1]=(long double) pi4[1]; p4[2]=(long double) pi4[2]; p4[3]=(long double) pi4[3];
	p5[1]=(long double) pi5[1]; p5[2]=(long double) pi5[2]; p5[3]=(long double) pi5[3];
	
	p0[0] =sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] =sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] =sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] =sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	p4[0] =sqrt( mass4*mass4 + p4[1]*p4[1] + p4[2]*p4[2] + p4[3]*p4[3] );
	p5[0] =sqrt( mass5*mass5 + p5[1]*p5[1] + p5[2]*p5[2] + p5[3]*p5[3] );
	
	long double totalp[4];
	int count = 0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count] + p3[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	Boost_long(p4, boost);
	Boost_long(p5, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
	pi4[0]=(double) p4[0]; pi4[1]=(double) p4[1]; pi4[2]=(double) p4[2]; pi4[3]=(double) p4[3];
	pi5[0]=(double) p5[0]; pi5[1]=(double) p5[1]; pi5[2]=(double) p5[2]; pi5[3]=(double) p5[3];
}


void Boost_5p_and_2p_2_pT0(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3, double mass4, double *pi4, double mass5, double *pi5, double mass6, double *pi6)
{
	long double p0[4], p1[4], p2[4], p3[4], p4[4], p5[4], p6[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	p4[1]=(long double) pi4[1]; p4[2]=(long double) pi4[2]; p4[3]=(long double) pi4[3];
	p5[1]=(long double) pi5[1]; p5[2]=(long double) pi5[2]; p5[3]=(long double) pi5[3];
	p6[1]=(long double) pi6[1]; p6[2]=(long double) pi6[2]; p6[3]=(long double) pi6[3];
	
	p0[0] =sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] =sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] =sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] =sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	p4[0] =sqrt( mass4*mass4 + p4[1]*p4[1] + p4[2]*p4[2] + p4[3]*p4[3] );
	p5[0] =sqrt( mass5*mass5 + p5[1]*p5[1] + p5[2]*p5[2] + p5[3]*p5[3] );
	p6[0] =sqrt( mass6*mass6 + p6[1]*p6[1] + p6[2]*p6[2] + p6[3]*p6[3] );
	
	long double totalp[4];
	int count = 0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count] + p3[count] + p4[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = 0;
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	Boost_long(p4, boost);
	Boost_long(p5, boost);
	Boost_long(p6, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
	pi4[0]=(double) p4[0]; pi4[1]=(double) p4[1]; pi4[2]=(double) p4[2]; pi4[3]=(double) p4[3];
	pi5[0]=(double) p5[0]; pi5[1]=(double) p5[1]; pi5[2]=(double) p5[2]; pi5[3]=(double) p5[3];
	pi6[0]=(double) p6[0]; pi6[1]=(double) p6[1]; pi6[2]=(double) p6[2]; pi6[3]=(double) p6[3];
}


/// Two particles
void Boost2CM(double mass0, double *pi0, double mass1, double *pi1)
{
	long double p0[4], p1[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );

	/// For debugging
	if( debug )
	{
		printf( "m(01) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ) );
	}
	
	long double totalp[4];
	int count=0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = totalp[3]/totalp[0];
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	
	/// For debugging
	if( debug )
	{
		printf( "After the boost: m(01) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ) );
		
		printf( "%LE %LE %LE %LE %LE %LE %LE %LE\n", p0[0], p0[1], p0[2], p0[3], p1[0], p1[1], p1[2], p1[3] );
		
		printf( "sum px=%LE\n", (p0[1]+p1[1]) );
		printf( "sum py=%LE\n", (p0[2]+p1[2]) );
		printf( "sum pz=%LE\n", (p0[3]+p1[3]) );
		printf( "sum p0=%LE\n", (p0[0]+p1[0]) );
	}
}


/// Three particles
void Boost2CM(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2)
{
	long double p0[4], p1[4], p2[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] = sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	
	/// For debugging
	if( debug )
	{
		printf( "m(01) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ) );
	}
	
	long double totalp[4];
	int count=0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = totalp[3]/totalp[0];
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	
	/// For debugging
	if( debug )
	{
		printf( "After the boost: m(01) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ) );
		
		printf( "%LE %LE %LE %LE %LE %LE %LE %LE\n", p0[0], p0[1], p0[2], p0[3], p1[0], p1[1], p1[2], p1[3] );
		printf( "%LE %LE %LE %LE\n", p2[0], p2[1], p2[2], p2[3] );
		
		printf( "sum px=%LE\n", (p0[1]+p1[1]+p2[1]) );
		printf( "sum py=%LE\n", (p0[2]+p1[2]+p2[2]) );
		printf( "sum pz=%LE\n", (p0[3]+p1[3]+p2[3]) );
		printf( "sum p0=%LE\n", (p0[0]+p1[0]+p2[0]) );
	}
}


/// Four particles
void Boost2CM(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3)
{
	long double p0[4], p1[4], p2[4], p3[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] = sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] = sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	
	/// For debugging
	if( debug )
	{
		printf( "m(01) = %.10E; m(23) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ),
			sqrt( (p2[0]+p3[0])*(p2[0]+p3[0]) - (p2[1]+p3[1])*(p2[1]+p3[1]) - (p2[2]+p3[2])*(p2[2]+p3[2]) - (p2[3]+p3[3])*(p2[3]+p3[3]) ) );
	}

	long double totalp[4];
	int count=0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count] + p3[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = totalp[3]/totalp[0];
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
	
	/// For debugging
	if( debug )
	{
		printf( "After the boost: m(01) = %.10E; m(23) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ),
			sqrt( (p2[0]+p3[0])*(p2[0]+p3[0]) - (p2[1]+p3[1])*(p2[1]+p3[1]) - (p2[2]+p3[2])*(p2[2]+p3[2]) - (p2[3]+p3[3])*(p2[3]+p3[3]) ) );
			
		printf( "%LE %LE %LE %LE %LE %LE %LE %LE\n", p0[0], p0[1], p0[2], p0[3], p1[0], p1[1], p1[2], p1[3] );
		printf( "%LE %LE %LE %LE %LE %LE %LE %LE\n", p2[0], p2[1], p2[2], p2[3], p3[0], p3[1], p3[2], p3[3] );
		
		printf( "sum px=%LE\n", (p0[1]+p1[1]+p2[1]+p3[1]) );
		printf( "sum py=%LE\n", (p0[2]+p1[2]+p2[2]+p3[2]) );
		printf( "sum pz=%LE\n", (p0[3]+p1[3]+p2[3]+p3[3]) );
		printf( "sum p0=%LE\n", (p0[0]+p1[0]+p2[0]+p3[0]) );
	}
}


/// Five particles
void Boost2CM(double mass0, double *pi0, double mass1, double *pi1, double mass2, double *pi2, double mass3, double *pi3, double mass4, double *pi4)
{
	long double p0[4], p1[4], p2[4], p3[4], p4[4];
	p0[1]=(long double) pi0[1]; p0[2]=(long double) pi0[2]; p0[3]=(long double) pi0[3];
	p1[1]=(long double) pi1[1]; p1[2]=(long double) pi1[2]; p1[3]=(long double) pi1[3];
	p2[1]=(long double) pi2[1]; p2[2]=(long double) pi2[2]; p2[3]=(long double) pi2[3];
	p3[1]=(long double) pi3[1]; p3[2]=(long double) pi3[2]; p3[3]=(long double) pi3[3];
	p4[1]=(long double) pi4[1]; p4[2]=(long double) pi4[2]; p4[3]=(long double) pi4[3];
	
	p0[0] = sqrt( mass0*mass0 + p0[1]*p0[1] + p0[2]*p0[2] + p0[3]*p0[3] );
	p1[0] = sqrt( mass1*mass1 + p1[1]*p1[1] + p1[2]*p1[2] + p1[3]*p1[3] );
	p2[0] = sqrt( mass2*mass2 + p2[1]*p2[1] + p2[2]*p2[2] + p2[3]*p2[3] );
	p3[0] = sqrt( mass3*mass3 + p3[1]*p3[1] + p3[2]*p3[2] + p3[3]*p3[3] );
	p4[0] = sqrt( mass4*mass4 + p4[1]*p4[1] + p4[2]*p4[2] + p4[3]*p4[3] );
	
	/// For debugging
	if( debug )
	{
		printf( "m(01) = %.10E; m(23) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ),
			sqrt( (p2[0]+p3[0])*(p2[0]+p3[0]) - (p2[1]+p3[1])*(p2[1]+p3[1]) - (p2[2]+p3[2])*(p2[2]+p3[2]) - (p2[3]+p3[3])*(p2[3]+p3[3]) ) );
	}

	long double totalp[4];
	int count=0;
	for( ; count<4; count++ ) {totalp[count]=p0[count] + p1[count] + p2[count] + p3[count] + p4[count]; }
	
	long double boost[3];
	boost[0] = totalp[1]/totalp[0];
	boost[1] = totalp[2]/totalp[0];
	boost[2] = totalp[3]/totalp[0];
	
	Boost_long(p0, boost);
	Boost_long(p1, boost);
	Boost_long(p2, boost);
	Boost_long(p3, boost);
	Boost_long(p4, boost);
	
	pi0[0]=(double) p0[0]; pi0[1]=(double) p0[1]; pi0[2]=(double) p0[2]; pi0[3]=(double) p0[3];
	pi1[0]=(double) p1[0]; pi1[1]=(double) p1[1]; pi1[2]=(double) p1[2]; pi1[3]=(double) p1[3];
	pi2[0]=(double) p2[0]; pi2[1]=(double) p2[1]; pi2[2]=(double) p2[2]; pi2[3]=(double) p2[3];
	pi3[0]=(double) p3[0]; pi3[1]=(double) p3[1]; pi3[2]=(double) p3[2]; pi3[3]=(double) p3[3];
	pi4[0]=(double) p4[0]; pi4[1]=(double) p4[1]; pi4[2]=(double) p4[2]; pi4[3]=(double) p4[3];
	
	/// For debugging
	if( debug )
	{
		printf( "After the boost: m(01) = %.10E; m(23) = %.10E\n",
			sqrt( (p0[0]+p1[0])*(p0[0]+p1[0]) - (p0[1]+p1[1])*(p0[1]+p1[1]) - (p0[2]+p1[2])*(p0[2]+p1[2]) - (p0[3]+p1[3])*(p0[3]+p1[3]) ),
			sqrt( (p2[0]+p3[0])*(p2[0]+p3[0]) - (p2[1]+p3[1])*(p2[1]+p3[1]) - (p2[2]+p3[2])*(p2[2]+p3[2]) - (p2[3]+p3[3])*(p2[3]+p3[3]) ) );
			
		printf( "%LE %LE %LE %LE %LE %LE %LE %LE\n", p0[0], p0[1], p0[2], p0[3], p1[0], p1[1], p1[2], p1[3] );
		printf( "%LE %LE %LE %LE %LE %LE %LE %LE\n", p2[0], p2[1], p2[2], p2[3], p3[0], p3[1], p3[2], p3[3] );
		printf( "%LE %LE %LE %LE\n", p4[0], p4[1], p4[2], p4[3] );
		
		printf( "sum px=%LE\n", (p0[1]+p1[1]+p2[1]+p3[1]+p4[2]) );
		printf( "sum py=%LE\n", (p0[2]+p1[2]+p2[2]+p3[2]+p4[2]) );
		printf( "sum pz=%LE\n", (p0[3]+p1[3]+p2[3]+p3[3]+p4[2]) );
		printf( "sum p0=%LE\n", (p0[0]+p1[0]+p2[0]+p3[0]+p4[2]) );
	}
}


void Boost(double *vector, double *boost)
{
	double ovec[4];
	int count=0;
	for( ; count < 4; count++)
		ovec[count]=vector[count];
	
	double beta2=boost[0]*boost[0]+boost[1]*boost[1]+boost[2]*boost[2];
	double gamma=1/sqrt(1-beta2);
	
	if( (gamma-1) > Boost_trigger_gamma )
	{
		vector[0]=gamma*( ovec[0] - boost[0]*ovec[1] - boost[1]*ovec[2] - boost[2]*ovec[3] );
		vector[1]= - gamma*boost[0]*ovec[0] + (1+(gamma-1)*boost[0]*boost[0]/beta2)*ovec[1] + (gamma-1)*boost[0]/beta2*( boost[1]*ovec[2] + boost[2]*ovec[3] );
		vector[2]= - gamma*boost[1]*ovec[0] + (1+(gamma-1)*boost[1]*boost[1]/beta2)*ovec[2] + (gamma-1)*boost[1]/beta2*( boost[0]*ovec[1] + boost[2]*ovec[3] );
		vector[3]= - gamma*boost[2]*ovec[0] + (1+(gamma-1)*boost[2]*boost[2]/beta2)*ovec[3] + (gamma-1)*boost[2]/beta2*( boost[0]*ovec[1] + boost[1]*ovec[2] );
	}
}


void Boost_long(long double *vector, long double *boost)
{
	long double ovec[4];
	int count=0;
	for( ; count < 4; count++)
		ovec[count]=vector[count];
	
	long double beta2=boost[0]*boost[0]+boost[1]*boost[1]+boost[2]*boost[2];
	long double gamma=1/sqrt(1-beta2);
	
	if( (gamma-1) > Boost_trigger_gamma )
	{
		vector[0]=gamma*( ovec[0] - boost[0]*ovec[1] - boost[1]*ovec[2] - boost[2]*ovec[3] );
		vector[1]= - gamma*boost[0]*ovec[0] + (1+(gamma-1)*boost[0]*boost[0]/beta2)*ovec[1] + (gamma-1)*boost[0]/beta2*( boost[1]*ovec[2] + boost[2]*ovec[3] );
		vector[2]= - gamma*boost[1]*ovec[0] + (1+(gamma-1)*boost[1]*boost[1]/beta2)*ovec[2] + (gamma-1)*boost[1]/beta2*( boost[0]*ovec[1] + boost[2]*ovec[3] );
		vector[3]= - gamma*boost[2]*ovec[0] + (1+(gamma-1)*boost[2]*boost[2]/beta2)*ovec[3] + (gamma-1)*boost[2]/beta2*( boost[0]*ovec[1] + boost[1]*ovec[2] );
	}
}



#endif
