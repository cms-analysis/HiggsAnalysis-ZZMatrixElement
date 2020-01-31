/*************************************************************************
 *  Authors:   MEKD & MELA fans
 *  Contact:   ...
 *  Created:   11.01.2013.
 *************************************************************************/
#ifndef MEMCalc_MEMCalc_cpp
#define MEMCalc_MEMCalc_cpp

/// MEMs header
#include "../interface/MEMCalculators.h"

using namespace std;
using namespace MEMNames;

//////////////////////////////////////////////////////////////////////////
///  MEMs interface class to MELA & MEKD packages.
///
///  Provides interface to the MEKD & MELA packages to
///  computes MEs and KDs for the process specified by the user.
///
//////////////////////////////////////////////////////////////////////////


/// Matrix of supported processes - initialisation (to be updated)
const bool MEMs::isProcSupported[MEMNames::NUM_PROCESSES][MEMNames::NUM_MEMCALCS]={
// kAnalytical   kMEKD       kJHUGen     kMCFM       kMELA_HCP
  {1,            1,          1,          1,          1},	// kSMHiggs
  {0,            1,          0,          0,          0},	// kSMHiggs_prodIndep
  {1,            1,          1,          0,          0},	// k0hplus
  {0,            1,          0,          0,          0},	// k0hplus_prodIndep
  {1,            1,          1,          0,          0},	// k0minus
  {0,            1,          0,          0,          0},	// k0minus_prodIndep
  {1,            1,          1,          0,          0},	// k1plus
  {1,            1,          1,          0,          0},	// k1plus_prodIndep
  {1,            1,          1,          0,          0},	// k1minus
  {1,            1,          1,          0,          0},	// k1minus_prodIndep
  {1,            1,          1,          0,          0},	// k2mplus_gg
  {1,            1,          1,          0,          0},	// k2mplus_qqbar
  {1,            1,          1,          0,          0},	// k2mplus_prodIndep
  {1,            1,          1,          0,          0},	// k2hplus			//TO BE RENAMED to k2hplus_gg
  {1,            1,          1,          0,          0},	// k2hplus_qqbar
  {1,            1,          1,          0,          0},	// k2hplus_prodIndep
  {1,            1,          1,          0,          0},	// k2hminus			//TO BE RENAMED to k2hminus_gg
  {1,            1,          1,          0,          0},	// k2hminus_qqbar
  {1,            1,          1,          0,          0},	// k2hminus_prodIndep
  {1,            1,          1,          0,          0},	// k2bplus			//TO BE RENAMED to k2bplus_gg
  {1,            1,          1,          0,          0},	// k2bplus_qqbar
  {1,            1,          1,          0,          0},	// k2bplus_prodIndep
  {1,            1,          0,          1,          1},	// kqqZZ
  {1,            0,          0,          1,          0},	// kqqZZ_prodIndep
  {0,            0,          0,          1,          0},	// kggZZ
  {0,            0,          1,          1,          0},	// kggZZ_SMHiggs
  {1,            0,          1,          0,          0},	// k0_g1prime2 
  {1,            1,          1,          0,          0},	// kSpin0_gg
  {1,            1,          1,          0,          0},	// kSpin0_prodIndep
  {1,            1,          1,          0,          0},	// kSpin1_qqbar
  {1,            1,          1,          0,          0},	// kSpin1_prodIndep
  {1,            1,          1,          0,          0},	// kSpin2_gg
  {1,            1,          1,          0,          0},	// kSpin2_qqbar
  {1,            1,          1,          0,          0},	// kSpin2_prodIndep
  {0,            0,          1,          0,          0},	// kJJ_SMHiggs_VBF 
  {0,            0,          1,          0,          0},	// kJJ_0minus_VBF 
  {0,            0,          1,          0,          0},	// kJJ_SMHiggs_GG 
  {0,            0,          1,          0,          0},	// kJJ_0minus_GG 
  {1,            0,          0,          0,          0},	// kJJ_SMHiggs_VH
  {1,            0,          0,          0,          0},	// kJJ_0minus_VH
  {1,            1,          1,          0,          0},	// k2h2plus_gg 
  {1,            1,          1,          0,          0},	// k2h2plus_qqbar 
  {1,            1,          1,          0,          0},	// k2h2plus_prodIndep 
  {1,            1,          1,          0,          0},	// k2h3plus_gg 
  {1,            1,          1,          0,          0},	// k2h3plus_qqbar 
  {1,            1,          1,          0,          0},	// k2h3plus_prodIndep 
  {1,            1,          1,          0,          0},	// k2h6plus_gg 
  {1,            1,          1,          0,          0},	// k2h6plus_qqbar 
  {1,            1,          1,          0,          0},	// k2h6plus_prodIndep 
  {1,            1,          1,          0,          0},	// k2h7plus_gg 
  {1,            1,          1,          0,          0},	// k2h7plus_qqbar 
  {1,            1,          1,          0,          0},	// k2h7plus_prodIndep 
  {1,            1,          1,          0,          0},	// k2h9minus_gg 
  {1,            1,          1,          0,          0},	// k2h9minus_qqbar 
  {1,            1,          1,          0,          0},	// k2h9minus_prodIndep 
  {1,            1,          1,          0,          0},	// k2h10minus_gg 
  {1,            1,          1,          0,          0},	// k2h10minus_qqbar 
  {1,            1,          1,          0,          0},	// k2h10minus_prodIndep 
  {0,            0,          0,          1,          0},	// kggHZZ_10 
  {0,            0,          1,          0,          0},	// k0_gsgs
  {0,            0,          1,          0,          0},	// k0_Zgs
  {0,            0,          1,          0,          0},	// k0_gsgs_PS
  {0,            0,          1,          0,          0},	// k0_Zgs_PS
  {0,            0,          1,          0,          0},	// k0_Zgs_g1prime2
  {0,            1,          0,          1,          0},	// kqqZ4l_s
  {0,            1,          0,          1,          0},	// kqqZ4l_t
  {0,            1,          0,          0,          0},	// k0plus_2f_gg
  {0,            1,          0,          0,          0},	// k0plus_2f_prodIndep
  {0,            1,          0,          0,          0},	// k0minus_2f_gg
  {0,            1,          0,          0,          0},	// k0minus_2f_prodIndep
  {0,            1,          0,          0,          0},	// k1plus_2f_qqbar
  {0,            1,          0,          0,          0},	// k1plus_2f_prodIndep
  {0,            1,          0,          0,          0},	// k1minus_2f_qqbar
  {0,            1,          0,          0,          0},	// k1minus_2f_prodIndep
  {0,            1,          0,          0,          0},	// k2mplus_2f_gg
  {0,            1,          0,          0,          0},	// k2mplus_2f_qqbar
  {0,            1,          0,          0,          0}
};	// k2mplus_2f_prodIndep
//////////////////////////////////////////////////////////////////////////


/// MEKD process name translation - initialisation
const TString MEMs::m_processNameMEKD[MEMNames::NUM_PROCESSES] = {
	"ggSpin0Pm", "Spin0Pm",
	"ggSpin0Ph", "Spin0Ph",
	"ggSpin0M", "Spin0M",
	"qqSpin1P", "Spin1P",
	"qqSpin1M", "Spin1M",
	"ggSpin2Pm", "qqSpin2Pm", "Spin2Pm",
	"ggSpin2Ph", "qqSpin2Ph", "Spin2Ph",
	"ggSpin2Mh", "qqSpin2Mh", "Spin2Mh",
	"ggSpin2Pb", "qqSpin2Pb", "Spin2Pb",
	
	"ZZ", "", "", "ggZZ_Higgs", "ggSpin0Lambda1",
	"ggSpin0", "Spin0",
	"qqSpin1", "Spin1",
	"ggSpin2", "qqSpin2", "Spin2",
	"VBFSpin0Pm_jj", "VBFSpin0M_jj", "ggSpin0Pm_jj", "ggSpin0M_jj", "VHSpin0Pm", "VHSpin0M_jj",
	
	"ggSpin2Ph2", "qqSpin2Ph2", "Spin2Ph2",
	"ggSpin2Ph3", "qqSpin2Ph3", "Spin2Ph3",
	"ggSpin2Ph6", "qqSpin2Ph6", "Spin2Ph6",
	"ggSpin2Ph7", "qqSpin2Ph7", "Spin2Ph7",
	"ggSpin2Mh9", "qqSpin2Mh9", "Spin2Mh9",
	"ggSpin2Mh10", "qqSpin2Mh10", "Spin2Mh10",
	"ggHZZ_10", "ggHZgs", "ggHgsgs", "ggHZgs_PS", "ggHgsgs_PS", "ggHZgsLambda1",
	"qqZ4l_Signal", "qqZ4l_Background",
	
	"ggSpin0Pm_2f", "Spin0Pm_2f",
	"ggSpin0M_2f", "Spin0M_2f",
	"qqSpin1P_2f", "Spin1P_2f",
	"qqSpin1M_2f", "Spin1M_2f",
	"ggSpin2Pm_2f", "qqSpin2Pm_2f", "Spin2Pm_2f"

};



///----------------------------------------------------------------------------------------------
/// MEMs::MEMs - constructor
///----------------------------------------------------------------------------------------------
MEMs::MEMs(double collisionEnergy, double sKD_mass, string PDFName, bool debug_)
{
    /// Mapping between MEMs process enums and MELA process enums 
    /// - initialisation (to be updated)
    MELAprocMap[kSMHiggs]         =TVar::HSMHiggs;
    MELAprocMap[k0hplus]          =TVar::H0hplus;
    MELAprocMap[k0minus]          =TVar::H0minus;
    MELAprocMap[k1plus]           =TVar::H1plus;
    MELAprocMap[k1plus_prodIndep] =TVar::H1plus;
    MELAprocMap[k1minus]          =TVar::H1minus;
    MELAprocMap[k1minus_prodIndep]=TVar::H1minus;
    MELAprocMap[k2mplus_gg]       =TVar::H2_g1g5;
    MELAprocMap[k2mplus_qqbar]    =TVar::H2_g1g5;
    MELAprocMap[k2mplus_prodIndep]=TVar::H2_g1g5;
    MELAprocMap[k2hplus]          =TVar::H2_g4;
    MELAprocMap[k2hplus_qqbar]		=TVar::H2_g4;
    MELAprocMap[k2hplus_prodIndep]=TVar::H2_g4;
    MELAprocMap[k2hminus]         =TVar::H2_g8;
    MELAprocMap[k2hminus_qqbar]   =TVar::H2_g8;
    MELAprocMap[k2hminus_prodIndep]=TVar::H2_g8;
    MELAprocMap[k2bplus]          =TVar::H2_g5;
    MELAprocMap[k2bplus_qqbar]		=TVar::H2_g5;
    MELAprocMap[k2bplus_prodIndep]=TVar::H2_g5;
    MELAprocMap[k2h2plus_gg]      =TVar::H2_g2;
    MELAprocMap[k2h2plus_qqbar]   =TVar::H2_g2;
    MELAprocMap[k2h2plus_prodIndep]=TVar::H2_g2;
    MELAprocMap[k2h3plus_gg]       =TVar::H2_g3;
    MELAprocMap[k2h3plus_qqbar]    =TVar::H2_g3;
    MELAprocMap[k2h3plus_prodIndep]=TVar::H2_g3;
    MELAprocMap[k2h6plus_gg]       =TVar::H2_g6;
    MELAprocMap[k2h6plus_qqbar]    =TVar::H2_g6;
    MELAprocMap[k2h6plus_prodIndep]=TVar::H2_g6;
    MELAprocMap[k2h7plus_gg]       =TVar::H2_g7;
    MELAprocMap[k2h7plus_qqbar]    =TVar::H2_g7;
    MELAprocMap[k2h7plus_prodIndep]=TVar::H2_g7;
    MELAprocMap[k2h9minus_gg]       =TVar::H2_g9;
    MELAprocMap[k2h9minus_qqbar]    =TVar::H2_g9;
    MELAprocMap[k2h9minus_prodIndep]=TVar::H2_g9;
    MELAprocMap[k2h10minus_gg]       =TVar::H2_g10;
    MELAprocMap[k2h10minus_qqbar]    =TVar::H2_g10;
    MELAprocMap[k2h10minus_prodIndep]=TVar::H2_g10;
    MELAprocMap[kqqZZ]            =TVar::bkgZZ;
    MELAprocMap[kqqZ4l_s]            =TVar::bkgZZ;
    MELAprocMap[kqqZ4l_t]            =TVar::bkgZZ;
    MELAprocMap[kqqZZ_prodIndep]  =TVar::bkgZZ;
    MELAprocMap[kggZZ]            =TVar::bkgZZ;
    MELAprocMap[kggZZ_SMHiggs]		=TVar::bkgZZ_SMHiggs;
    MELAprocMap[k0_g1prime2]		=TVar::H0_g1prime2;
	
	MELAprocMap[kSpin0_gg]			=TVar::SelfDefine_spin0;
	MELAprocMap[kSpin0_prodIndep]	=TVar::SelfDefine_spin0;
	MELAprocMap[kSpin1_qqbar]		=TVar::SelfDefine_spin1;
	MELAprocMap[kSpin1_prodIndep]	=TVar::SelfDefine_spin1;
	MELAprocMap[kSpin2_gg]			=TVar::SelfDefine_spin2;
	MELAprocMap[kSpin2_qqbar]		=TVar::SelfDefine_spin2;
	MELAprocMap[kSpin2_prodIndep]	=TVar::SelfDefine_spin2;
    
    MELAprocMap[kJJ_SMHiggs_VBF]	=TVar::HSMHiggs;
    MELAprocMap[kJJ_0minus_VBF]		=TVar::H0minus;
    MELAprocMap[kJJ_SMHiggs_GG]		=TVar::HSMHiggs;
    MELAprocMap[kJJ_0minus_GG]		=TVar::H0minus;
    MELAprocMap[kJJ_SMHiggs_VH]		=TVar::HSMHiggs;
    MELAprocMap[kJJ_0minus_VH]		=TVar::H0minus;

    MELAprocMap[kggHZZ_10]		=TVar::D_gg10;
    MELAprocMap[k0_Zgs]		=TVar::H0_Zgs;
    MELAprocMap[k0_gsgs]		=TVar::H0_gsgs;
    MELAprocMap[k0_Zgs_PS]		=TVar::H0_Zgs_PS;
    MELAprocMap[k0_gsgs_PS]		=TVar::H0_gsgs_PS;
    MELAprocMap[k0_Zgs_g1prime2]		=TVar::H0_Zgsg1prime2;

	MELAprocIntMap[kg1g4]			=TVar::D_g1g4;
	MELAprocIntMap[kg1g2]			=TVar::D_g1g2;
	MELAprocIntMap[kg1g4_pi_2]		=TVar::D_g1g4_pi_2;
	MELAprocIntMap[kg1g2_pi_2]		=TVar::D_g1g2_pi_2;
	MELAprocIntMap[k_g1g1prime2]	=TVar::D_g1g1prime2;
	MELAprocIntMap[kzzzg]	=TVar::D_zzzg;
	MELAprocIntMap[kzzgg]	=TVar::D_zzgg;
	MELAprocIntMap[kzzzg_PS]	=TVar::D_zzzg_PS;
	MELAprocIntMap[kzzgg_PS]	=TVar::D_zzgg_PS;
	MELAprocIntMap[kzzzg_g1prime2]	=TVar::D_zzzg_g1prime2;
	MELAprocIntMap[kzzzg_g1prime2_pi_2]	=TVar::D_zzzg_g1prime2_pi_2;
    
    /// Mapping between MEMs process enums and MELA production enums 
    /// - initialisation (to be updated)
    MELAprodMap[kSMHiggs]         =TVar::ZZGG;
    MELAprodMap[k0hplus]          =TVar::ZZGG;
    MELAprodMap[k0minus]          =TVar::ZZGG;
    MELAprodMap[k1plus]           =TVar::ZZQQB;
    MELAprodMap[k1plus_prodIndep] =TVar::ZZINDEPENDENT;
    MELAprodMap[k1minus]          =TVar::ZZQQB;
    MELAprodMap[k1minus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2mplus_gg]       =TVar::ZZGG;
    MELAprodMap[k2mplus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2mplus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2hplus]          =TVar::ZZGG;
    MELAprodMap[k2hplus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2hplus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2hminus]         =TVar::ZZGG;
    MELAprodMap[k2hminus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2hminus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2bplus]          =TVar::ZZGG;
    MELAprodMap[k2bplus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2bplus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2h2plus_gg]       =TVar::ZZGG;
    MELAprodMap[k2h2plus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2h2plus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2h3plus_gg]       =TVar::ZZGG;
    MELAprodMap[k2h3plus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2h3plus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2h6plus_gg]       =TVar::ZZGG;
    MELAprodMap[k2h6plus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2h6plus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2h7plus_gg]       =TVar::ZZGG;
    MELAprodMap[k2h7plus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2h7plus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2h9minus_gg]       =TVar::ZZGG;
    MELAprodMap[k2h9minus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2h9minus_prodIndep]=TVar::ZZINDEPENDENT;
    MELAprodMap[k2h10minus_gg]       =TVar::ZZGG;
    MELAprodMap[k2h10minus_qqbar]    =TVar::ZZQQB;
    MELAprodMap[k2h10minus_prodIndep]=TVar::ZZINDEPENDENT;

    MELAprodMap[kqqZZ]            =TVar::ZZQQB;
    MELAprodMap[kqqZ4l_s]            =TVar::ZZQQB_S;
    MELAprodMap[kqqZ4l_t]            =TVar::ZZQQB_TU;
    MELAprodMap[kqqZZ_prodIndep]  =TVar::ZZINDEPENDENT;
    MELAprodMap[kggZZ]            =TVar::ZZGG;
    MELAprodMap[kggZZ_SMHiggs]    =TVar::ZZGG;
    MELAprodMap[k0_g1prime2]      =TVar::ZZGG;
    MELAprodMap[kggHZZ_10]      =TVar::ZZGG;
    MELAprodMap[k0_Zgs]      =TVar::ZZGG;
    MELAprodMap[k0_gsgs]      =TVar::ZZGG;
    MELAprodMap[k0_Zgs_PS]      =TVar::ZZGG;
    MELAprodMap[k0_gsgs_PS]      =TVar::ZZGG;
    MELAprodMap[k0_Zgs_g1prime2]		=TVar::ZZGG;
	
	MELAprodMap[kSpin0_gg]			=TVar::ZZGG;
	MELAprodMap[kSpin0_prodIndep]	=TVar::ZZINDEPENDENT;
	MELAprodMap[kSpin1_qqbar]		=TVar::ZZQQB;
	MELAprodMap[kSpin1_prodIndep]	=TVar::ZZINDEPENDENT;
	MELAprodMap[kSpin2_gg]			=TVar::ZZGG;
	MELAprodMap[kSpin2_qqbar]		=TVar::ZZQQB;
	MELAprodMap[kSpin2_prodIndep]	=TVar::ZZINDEPENDENT;

    MELAprodMap[kJJ_SMHiggs_VBF]	=TVar::JJVBF;
    MELAprodMap[kJJ_0minus_VBF]		=TVar::JJVBF;
    MELAprodMap[kJJ_SMHiggs_GG]		=TVar::JJQCD;
    MELAprodMap[kJJ_0minus_GG]		=TVar::JJQCD;
    MELAprodMap[kJJ_SMHiggs_VH]		=TVar::Had_ZH;
    MELAprodMap[kJJ_0minus_VH]		=TVar::Had_ZH;

	
    MELAprodIntMap[kg1g4]			=TVar::ZZGG;
    MELAprodIntMap[kg1g2]			=TVar::ZZGG;
    MELAprodIntMap[kg1g4_pi_2]		=TVar::ZZGG;
    MELAprodIntMap[kg1g2_pi_2]		=TVar::ZZGG;
    MELAprodIntMap[k_g1g1prime2]	=TVar::ZZGG;
    MELAprodIntMap[kzzzg]	=TVar::ZZGG;
    MELAprodIntMap[kzzgg]	=TVar::ZZGG;
    MELAprodIntMap[kzzzg_PS]	=TVar::ZZGG;
    MELAprodIntMap[kzzgg_PS]	=TVar::ZZGG;
    MELAprodIntMap[kzzzg_g1prime2]		=TVar::ZZGG;
    MELAprodIntMap[kzzzg_g1prime2_pi_2]		=TVar::ZZGG;
	
    /// Mapping between MEMs calculator enums and MELA MatrixElement enums 
    /// - initialisation (to be updated)
    MELAcalcMap[kMCFM]      =TVar::MCFM;
    MELAcalcMap[kJHUGen]    =TVar::JHUGen;
    MELAcalcMap[kAnalytical]=TVar::ANALYTICAL;
    MELAcalcMap[kMELA_HCP]  =TVar::ANALYTICAL; 
//    MELAcalcMap[kMEKD]      =TVar::MadGraph;
	
	m_Lambda_z1 = 10000;
	m_Lambda_z2 = 10000;
	m_Lambda_z3 = 10000;
	m_Lambda_z4 = 10000;
	
    debug=debug_;
	if( debug ) cout << "MEMs::MEMs. The debug flag is ON\n";
	
	/// Number of processes for precalculation
	NUM_PROCESSES_PRECALC = 27;

    /// Initialise MEKD
    m_MEKD = new MEKD(collisionEnergy, PDFName);
    /// Initialise MELA
    m_MELA = new Mela(collisionEnergy, sKD_mass); //sMELA_mass for SuperMELA calculation
    
    /// Set some non-physical values for MEs initially
    for(int iMemCalc = 0; iMemCalc < NUM_MEMCALCS; iMemCalc++ )
        for(int iProcess = 0; iProcess < NUM_PROCESSES; iProcess++ )
            m_computedME[iProcess][iMemCalc] = -999.;

    m_weight = 0.0;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeME - Compute ME for the specified process.
///----------------------------------------------------------------------------------------------
int MEMs::computeME(Processes process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, double& me2process)
{
	return computeME(process, calculator, partP, partId, (vector<complex<double> >*) NULL, (vector<complex<double> >*) NULL, me2process);
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeME - Compute ME for the specified process. A generic case
///----------------------------------------------------------------------------------------------
int MEMs::computeME(Processes process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings, double& me2process)
{
	if( debug ) cout << "MEMs::computeME started.\n";
	if( debug ) cout << "MEMs::computeME. Selected calculator: " << calculator << "\n";
	
	/// check if process is supported
	if( !isProcSupported[process][calculator] ) return ERR_PROCESS;
	
	/// Check the couplings for consistency
	if( process==kSpin0_gg || process==kSpin0_prodIndep ||
		process==kSpin1_qqbar || process==kSpin1_prodIndep ||
		process==kSpin2_gg || process==kSpin2_qqbar || process==kSpin2_prodIndep
	)
		if( (Check_Couplings( process, ProdCouplings, DecayCouplings)) != 0 ) return ERR_PROCESS;
	
	
	if( debug ) cout << "MEMs::computeME. Process is supported!\n";
  
	/// perform computation according to the specified process and MEM package
	switch ( calculator )
	{
		case kMEKD:			/// compute ME with MEKD
			if( ProdCouplings!=(vector<complex<double> >*) NULL || DecayCouplings!=(vector<complex<double> >*) NULL )
				if( (m_err=MEKD_Mixed_State( m_processNameMEKD[process], ProdCouplings, DecayCouplings )) != 0 ) return ERR_COMPUTE;
			if( (m_MEKD->computeME(m_processNameMEKD[process], partP, partId, me2process)) != 0 ) return ERR_COMPUTE;
			break;
			
		case kAnalytical:	/// compute ME with MELA
			if( debug )
				cout << "MEMs::computeME. Analytical -> process: " << process << endl;
			if (ProdCouplings!=(vector<complex<double> >*) NULL || DecayCouplings!=(vector<complex<double> >*) NULL){
				if ( cacheMELAcalculation(process,calculator,partP,partId,ProdCouplings, DecayCouplings,me2process) != 0) return ERR_COMPUTE;
			}
			else	return cacheMELAcalculation(process,calculator,partP,partId,me2process); 
			break;
			
		case kJHUGen:       /// compute ME with JHUGen
			if( debug )
				cout << "MEMs::computeME. JHUGen -> process: " << process << endl;
			if (ProdCouplings!=(vector<complex<double> >*) NULL || DecayCouplings!=(vector<complex<double> >*) NULL){
				if ( cacheMELAcalculation(process,calculator,partP,partId,ProdCouplings, DecayCouplings,me2process) != 0) return ERR_COMPUTE;
			}
			else
				return cacheMELAcalculation(process,calculator,partP,partId,me2process);
			break;

    case kMCFM:       /// compute ME with JHUGen
      if( debug )
        cout << "MEMs::computeME. kMCFM-> process: " << process << endl;
      if (ProdCouplings!=(vector<complex<double> >*) NULL || DecayCouplings!=(vector<complex<double> >*) NULL){
        if ( cacheMELAcalculation(process,calculator,partP,partId,ProdCouplings, DecayCouplings,me2process) != 0) return ERR_COMPUTE;
      }
      else
        return cacheMELAcalculation(process,calculator,partP,partId,me2process);
      break;
			
			
		case kMELA_HCP:     /// compute ME with MELA_HCP
			if( debug )
				cout << "MEMs::computeME. MELA_HCP -> process: " << process << endl;
			return ERR_PROCESS;
			break;
			
		default:
			if( debug )
				cout << "MEMs::computeME. default case hit... don't recognize calculator" << endl;
			return ERR_PROCESS;
			break;
	}
	
	return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeME_Interference - Compute individual mixed MEs interference term for the specified "model". Intended for the production-independent models PLUS gg -> Spin 0
///----------------------------------------------------------------------------------------------
int MEMs::computeME_Interference(Processes process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *DecayCouplings, double& me2process)
{
	if( debug ) cout << "MEMs::computeME_Interference started.\n";
	
	/// Calculate the full term
	if( (m_err=computeME( process, calculator, partP, partId, (vector<complex<double> >*) NULL, DecayCouplings, me2process))!=0 ) return m_err;
	
	/// Prepare a buffer vector
	m_VCbuffer.resize( (*DecayCouplings).size(), complex<double>( 0, 0 ) );	// should be a vector of zeroes
	
	/// Subtract individual pure term(s)
	for( m_uIbuffer=0; m_uIbuffer<(*DecayCouplings).size(); m_uIbuffer++ )
	{
		if( norm((*DecayCouplings)[m_uIbuffer]) > 0 ) 
		{
			m_VCbuffer[m_uIbuffer] = (*DecayCouplings)[m_uIbuffer];	// load a current coupling
			if( (m_err=computeME( process, calculator, partP, partId, (vector<complex<double> >*) NULL, &m_VCbuffer, m_Dbuffer))!=0 ) return m_err;	// pure term(s)
			me2process -= m_Dbuffer;	// subtracting a pure term
			
			m_VCbuffer[m_uIbuffer] = complex<double>( 0, 0 );	// reverting back to 0 coupling
		}
	}
	
	return NO_ERR;
}



/// Work in progress method. Currently serves as a bridge to MELA package implementations.
int MEMs::computeME_Interference(Processes_int process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId,  double& me2process)
{
	if( calculator == kJHUGen || calculator ==kAnalytical )
		cacheMELAcalculation( static_cast<int>(process), calculator, partP, partId, (vector<complex<double> >*) NULL, (vector<complex<double> >*) NULL, me2process);
	else 
		return ERR_COMPUTE;
	return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeKD - Compute KD and MEs for the specified processes and MEM calculator.
///----------------------------------------------------------------------------------------------
int MEMs::computeKD(Processes processA, Processes processB, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, double& kd, double& me2processA, double& me2processB )
{    
	return computeKD( processA, processB, calculator, partP, partId, (vector<complex<double> >*) NULL, (vector<complex<double> >*) NULL, (vector<complex<double> >*) NULL, (vector<complex<double> >*) NULL, kd, me2processA, me2processB );
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeKD - Compute KD and MEs for the specified processes and MEM calculator. A generic case
///----------------------------------------------------------------------------------------------
int MEMs::computeKD(Processes processA, Processes processB, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplingsA, vector<complex<double> > *DecayCouplingsA, vector<complex<double> > *ProdCouplingsB, vector<complex<double> > *DecayCouplingsB, double& kd, double& me2processA, double& me2processB )
{    
	/// check if processes are supported
	if (!isProcSupported[processA][calculator]) return ERR_PROCESS;
	if (!isProcSupported[processB][calculator]) return ERR_PROCESS;
	
	/// Check the couplings for consistency; A
	if( processA==kSpin0_gg || processA==kSpin0_prodIndep ||
		processA==kSpin1_qqbar || processA==kSpin1_prodIndep ||
		processA==kSpin2_gg || processA==kSpin2_qqbar || processA==kSpin2_prodIndep
	)
		if( (Check_Couplings( processA, ProdCouplingsA, DecayCouplingsA)) != 0 ) return ERR_PROCESS;
		
	/// Check the couplings for consistency; B
	if( processB==kSpin0_gg || processB==kSpin0_prodIndep ||
		processB==kSpin1_qqbar || processB==kSpin1_prodIndep ||
		processB==kSpin2_gg || processB==kSpin2_qqbar || processB==kSpin2_prodIndep
	)
		if( (Check_Couplings( processB, ProdCouplingsB, DecayCouplingsB)) != 0 ) return ERR_PROCESS;
	
	/// perform computation according to the specified process and MEM package
	switch ( calculator )
	{
		case kMEKD:			/// compute KD with MEKD
			if( ProdCouplingsA!=(vector<complex<double> >*) NULL || DecayCouplingsA!=(vector<complex<double> >*) NULL )
				if( (m_err=MEKD_Mixed_State( m_processNameMEKD[processA], ProdCouplingsA, DecayCouplingsA )) != 0 ) return ERR_COMPUTE;
			if( (m_MEKD->computeME(m_processNameMEKD[processA], partP, partId, me2processA)) != 0 ) return ERR_COMPUTE;
			
			if( ProdCouplingsB!=(vector<complex<double> >*) NULL || DecayCouplingsB!=(vector<complex<double> >*) NULL )
				if( (m_err=MEKD_Mixed_State( m_processNameMEKD[processB], ProdCouplingsB, DecayCouplingsB )) != 0 ) return ERR_COMPUTE;
			if( (m_MEKD->computeME(m_processNameMEKD[processB], partP, partId, me2processB)) != 0 ) return ERR_COMPUTE;
			
			kd = log( me2processA/me2processB );
			break;
			
		case kAnalytical:	/// compute KD with MELA
			if(cacheMELAcalculation(processA,calculator,partP,partId,me2processA) || 
				cacheMELAcalculation(processB,calculator,partP,partId,me2processB) )
				return ERR_COMPUTE;
			else{
				kd=me2processA/(me2processA+me2processB);
				return NO_ERR;
			}
			break;
			
		case kJHUGen:		/// compute KD with JHUGen
			if(cacheMELAcalculation(processA,calculator,partP,partId,me2processA) || 
				cacheMELAcalculation(processB,calculator,partP,partId,me2processB) )
				return ERR_COMPUTE;
			else{
				kd=me2processA/(me2processA+me2processB);
				return NO_ERR;
			}
			break;
			
		case kMCFM:			/// compute KD with MCFM
			if(cacheMELAcalculation(processA,calculator,partP,partId,me2processA) || 
				cacheMELAcalculation(processB,calculator,partP,partId,me2processB) )
				return ERR_COMPUTE;
			else{
				kd=me2processA/(me2processA+me2processB);
				return NO_ERR;
			}
			break;
			
		case kMELA_HCP:		/// compute KD with HCP MELA
			return ERR_PROCESS;
			break;
			
		default:
			return ERR_PROCESS;
			break;
	}
  
	return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeMEs - Compute MEs for the supported set of processes.
///----------------------------------------------------------------------------------------------
int MEMs::computeMEs(vector<TLorentzVector> partP, vector<int> partId)
{
	double me2process;
	
	//loop over MEMCalcs and loop over Processes
	for(int iMemCalc = 0; iMemCalc < NUM_MEMCALCS; iMemCalc++ )
	{
		for(int iProcess = 0; iProcess < NUM_PROCESSES_PRECALC; iProcess++ )
		{
			if (!isProcSupported[iProcess][iMemCalc]) continue;
			if( (computeME(static_cast<Processes>(iProcess), static_cast<MEMCalcs>(iMemCalc), partP, partId, me2process)) != 0 ) return ERR_COMPUTE;
			m_computedME[iProcess][iMemCalc] = me2process;
		}
	}
	
	// compute and store the sig. and bkg. pdf(m4l) values for all systs
	computePm4ls(partP, partId);
	
	//return NO_ERR only if all ME computations were successful
	return 0;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computePm4ls - Compute pdf(m4l) with computePm4l(...) for all systs
///----------------------------------------------------------------------------------------------
void MEMs::computePm4ls(vector<TLorentzVector> partP, vector<int> partId)
{
    for(int iSuperKDsyst = 0; iSuperKDsyst < NUM_SuperKDsyst; iSuperKDsyst++ ) {
        double sigProb, bkgProb;
        computePm4l(partP, partId, static_cast<SuperKDsyst>(iSuperKDsyst), sigProb, bkgProb);
        m_computedPm4lSig[iSuperKDsyst] = sigProb;
        m_computedPm4lBkg[iSuperKDsyst] = bkgProb;
    }
}



///----------------------------------------------------------------------------------------------
/// MEMs::retrieveME - Retrieve ME for specified process and specified calculator tool.
///----------------------------------------------------------------------------------------------
int MEMs::retrieveME(Processes process, MEMCalcs calculator, double& me2process)
{
    /// check if process is supported
    if (!isProcSupported[process][calculator]) return ERR_PROCESS;
    
    /// retrieve ME
    me2process = m_computedME[process][calculator];
    
    return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeKD - Compute KD for process A and process B, for specified calculator.
///----------------------------------------------------------------------------------------------
int MEMs::computeKD(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB, double (MEMs::*funcKD)(double, double), double& kd, double& me2processA, double& me2processB )
{
    /// check if processes are supported
    if (!isProcSupported[processA][calculatorA]) return ERR_PROCESS;
    if (!isProcSupported[processB][calculatorB]) return ERR_PROCESS;

	/// retrieve already computed MEs
    me2processA = m_computedME[processA][calculatorA];
    me2processB = m_computedME[processB][calculatorB];
	/// compute KD
    kd = (*this.*funcKD)(me2processA, me2processB);
    
    return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeKD - Compute KD for process A and process B, for specified calculator.
///----------------------------------------------------------------------------------------------
int MEMs::computeKD(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB, double (MEMs::*funcKD)(Processes, MEMCalcs, Processes, MEMCalcs), double& kd, double& me2processA, double& me2processB )
{
    /// check if processes are supported
    if (!isProcSupported[processA][calculatorA]) return ERR_PROCESS;
    if (!isProcSupported[processB][calculatorB]) return ERR_PROCESS;
    
    /// retrieve already computed MEs
    me2processA = m_computedME[processA][calculatorA];
    me2processB = m_computedME[processB][calculatorB];
    /// compute KD
    kd = (*this.*funcKD)(processA, calculatorA, processB, calculatorB);
    
    return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::computeKD - Compute KD for process A and process B with pdf(m4l) folded in.
///----------------------------------------------------------------------------------------------
int MEMs::computeKD(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB, double (MEMs::*funcKD)(double, double, SuperKDsyst), double& kd, double& me2processA, double& me2processB, SuperKDsyst syst )
{
    /// check if processes are supported
    if( !isProcSupported[processA][calculatorA] ) return ERR_PROCESS;
    if( !isProcSupported[processB][calculatorB] ) return ERR_PROCESS;
    /// check if processB is kqqZZ or kqqZZ_prodIndep
    if( processB != kqqZZ && processB != kqqZZ_prodIndep ) return ERR_PROCESS;

	/// retrieve already computed MEs
    me2processA = m_computedME[processA][calculatorA];
    me2processB = m_computedME[processB][calculatorB];
	/// compute KD with pdf(m4l) folded in
    kd = (*this.*funcKD)(me2processA, me2processB, syst);

    return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::logRatio - KD function which returns ln( me2processA / me2processB )
///----------------------------------------------------------------------------------------------
double MEMs::logRatio(double me2processA, double me2processB){
	if (me2processB == 0) return -999.;
	return log( me2processA / me2processB );
}



///----------------------------------------------------------------------------------------------
/// MEMs::probRatio - KD function which returns me2processA / ( me2processA + c * me2processB )
///----------------------------------------------------------------------------------------------
double MEMs::probRatio(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB)
{
    /// check if processes are supported
    if (!isProcSupported[processA][calculatorA]) return ERR_PROCESS;
    if (!isProcSupported[processB][calculatorB]) return ERR_PROCESS;

    /// retrieve already computed MEs
    double me2processA = m_computedME[processA][calculatorA];
    double me2processB = m_computedME[processB][calculatorB];

    // compute KD per case basis (for the time being, find more elegant solution later)
    double c;
    // determine c
    // keep c = 1. for all MELA_HCP calculations
    // if case is not known, use c = 1. - this is not necessarily wrong though.
    if( (calculatorA==kJHUGen || calculatorA==kMEKD) && (calculatorB==kJHUGen || calculatorB==kMEKD) ){ // (JHUGen or MEKD)
        if( processA==kSMHiggs && processB==k0minus ){
            c = 1.; // for JHUGen or MEKD when 0+ vs 0-
        }else if( processA==kSMHiggs && processB==k2mplus_gg ){
            c = 1.; // for JHUGen or MEKD when 0+ vs 2m+
        }else if ( processB==kqqZZ ){
            c = 1.;
//            me2processB = qqZZ_MCFMNorm; // qqZZ_MCFMNorm/qqZZ_MCFM should be used for (JHUGen or MEKD) signal vs MEKD bkg
        }else{
            c = 1.; // default for all "non-known" cases
        }
    }else if( (calculatorA==kJHUGen || calculatorA==kMEKD) && (calculatorB==kMCFM) ){ // (JHUGen or MEKD) vs. MCFM
        if( processB==kqqZZ ){
            c = 1.;
//            me2processB = qqZZ_MCFMNorm; // qqZZ_MCFMNorm/qqZZ_MCFM should be used for (JHUGen or MEKD) signal vs MCFM bkg
        }else{
            c = 1.; // default for all "non-known" cases
        }
    }else{
        c = 1.; // default for all "non-known" cases
    }
    
    if (me2processA + c * me2processB == 0) return -999.;
    return me2processA/( me2processA + c * me2processB );
}



///----------------------------------------------------------------------------------------------
/// MEMs::PDFm4lRatio - KD function: Pm4lSig * me2sig / ( Pm4lSig * me2sig + Pm4lBkg * me2bkg )
///----------------------------------------------------------------------------------------------
double MEMs::PDFm4lRatio(double me2processA, double me2processB, SuperKDsyst syst)
{
    if (m_computedPm4lSig[syst] * me2processA + m_computedPm4lBkg[syst] * me2processB == 0) return -999.;
    return m_computedPm4lSig[syst]*me2processA/( m_computedPm4lSig[syst] * me2processA + m_computedPm4lBkg[syst] * me2processB );
}



int MEMs::Check_Couplings( Processes process, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings )
{
	if( ProdCouplings==(vector<complex<double> >*) NULL && DecayCouplings==(vector<complex<double> >*) NULL )
	{
		if( debug ) cout << "MEMs::Check_Couplings. Error in provided couplings. Is the correct model being used?\n";
		return 1;
	}
	if( process==kSpin0_gg || process==kSpin0_prodIndep )	// checking Spin-0 case
	{
		if( ProdCouplings!=(vector<complex<double> >*) NULL && (*DecayCouplings).size() != 4 && (*DecayCouplings).size() != SIZE_HVV)
		{
			if( debug ) cout << "MEMs::Check_Couplings. Error in provided decay couplings. Expected size: 4 or SIZE_HVV (form-factor case), provided: "  << (*DecayCouplings).size() << endl;
			return 1;
		}
		
		return 0;
	}
	else if( process==kSpin1_qqbar || process==kSpin1_prodIndep )	// checking Spin-1 case
	{
		if( process==kSpin1_qqbar && (*ProdCouplings).size() != SIZE_ZQQ )
		{
			if( debug ) cout << "MEMs::Check_Couplings. Error in provided prod. couplings. Expected size: SIZE_ZQQ, provided: "  << (*ProdCouplings).size() << endl;
			return 1;
		}
		if( (*DecayCouplings).size() != SIZE_ZVV )
		{
			if( debug ) cout << "MEMs::Check_Couplings. Error in provided decay couplings. Expected size: SIZE_ZVV, provided: "  << (*DecayCouplings).size() << endl;
			return 1;
		}
		
		return 0;
	}
	else if( process==kSpin2_gg || process==kSpin2_qqbar || process==kSpin2_prodIndep )	// checking Spin-2 case
	{
		if( process==kSpin2_gg && (*ProdCouplings).size() != 10 && (*ProdCouplings).size() != SIZE_GGG)
		{
			if( debug ) cout << "MEMs::Check_Couplings. Error in provided prod. couplings. Expected size: 10 for MEKD, SIZE_GGG for MELA, provided: "  << (*ProdCouplings).size() << endl;
			return 1;
		}
		if( process==kSpin2_qqbar && (*ProdCouplings).size() != 4 )
		{
			if( debug ) cout << "MEMs::Check_Couplings. Error in provided prod. couplings. Expected size: 4, provided: "  << (*ProdCouplings).size() << endl;
			return 1;
		}
		if( (*DecayCouplings).size() != SIZE_GVV )
		{
			if( debug ) cout << "MEMs::Check_Couplings. Error in provided decay couplings. Expected size: 10, provided: "  << (*DecayCouplings).size() << endl;
			return 1;
		}
		
		return 0;
	}
	
	
	return 1;
}



///----------------------------------------------------------------------------------------------
/// MEMs::MEKD_Mixed_State - Sets up a mixed state in the MEKD
///----------------------------------------------------------------------------------------------
int MEMs::MEKD_Mixed_State( TString Model, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings )
{
	/// Setting couplings inside of MEKD
	if( Model=="ggSpin0" || Model=="Spin0" )
	{
		m_MEKD->m_Mixing_Coefficients_Spin0[0] = (*DecayCouplings)[0];
		m_MEKD->m_Mixing_Coefficients_Spin0[1] = (*DecayCouplings)[1];
		m_MEKD->m_Mixing_Coefficients_Spin0[2] = (*DecayCouplings)[2];
		m_MEKD->m_Mixing_Coefficients_Spin0[3] = (*DecayCouplings)[3];
		
		return 0;
	}
	else if( Model=="qqSpin1" || Model=="Spin1" )
	{
		if( Model=="qqSpin1" ) m_MEKD->m_Mixing_Coefficients_Spin1[0] = (*ProdCouplings)[0];
		if( Model=="qqSpin1" ) m_MEKD->m_Mixing_Coefficients_Spin1[1] = (*ProdCouplings)[1];
		if( Model=="qqSpin1" ) m_MEKD->m_Mixing_Coefficients_Spin1[2] = (*ProdCouplings)[2];
		if( Model=="qqSpin1" ) m_MEKD->m_Mixing_Coefficients_Spin1[3] = (*ProdCouplings)[3];
		m_MEKD->m_Mixing_Coefficients_Spin1[4] = (*DecayCouplings)[0];
		m_MEKD->m_Mixing_Coefficients_Spin1[5] = (*DecayCouplings)[1];
		
		return 0;
	}
	else if( Model=="ggSpin2" || Model=="qqSpin2" || Model=="Spin2" )
	{
		if( Model=="ggSpin2" || Model=="qqSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[0] = (*ProdCouplings)[0];
		if( Model=="ggSpin2" || Model=="qqSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[1] = (*ProdCouplings)[1];
		if( Model=="ggSpin2" || Model=="qqSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[2] = (*ProdCouplings)[2];
		if( Model=="ggSpin2" || Model=="qqSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[3] = (*ProdCouplings)[3];
		if( Model=="ggSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[4] = (*ProdCouplings)[4];
		if( Model=="ggSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[5] = (*ProdCouplings)[5];
		if( Model=="ggSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[6] = (*ProdCouplings)[6];
		if( Model=="ggSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[7] = (*ProdCouplings)[7];
		if( Model=="ggSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[8] = (*ProdCouplings)[8];
		if( Model=="ggSpin2" ) m_MEKD->m_Mixing_Coefficients_Spin2[9] = (*ProdCouplings)[9];
		m_MEKD->m_Mixing_Coefficients_Spin2[10] = (*DecayCouplings)[0];
		m_MEKD->m_Mixing_Coefficients_Spin2[11] = (*DecayCouplings)[1];
		m_MEKD->m_Mixing_Coefficients_Spin2[12] = (*DecayCouplings)[2];
		m_MEKD->m_Mixing_Coefficients_Spin2[13] = (*DecayCouplings)[3];
		m_MEKD->m_Mixing_Coefficients_Spin2[14] = (*DecayCouplings)[4];
		m_MEKD->m_Mixing_Coefficients_Spin2[15] = (*DecayCouplings)[5];
		m_MEKD->m_Mixing_Coefficients_Spin2[16] = (*DecayCouplings)[6];
		m_MEKD->m_Mixing_Coefficients_Spin2[17] = (*DecayCouplings)[7];
		m_MEKD->m_Mixing_Coefficients_Spin2[18] = (*DecayCouplings)[8];
		m_MEKD->m_Mixing_Coefficients_Spin2[19] = (*DecayCouplings)[9];
		
		return 0;
	}
	
	return 1;
}



//////////////////////////////////////////////////////////////////////////
///----------------------------------------------------------------------------------------------
/// MEMCalculators::cacheMELAcalculation - method to interface with Mela::computeP and cache results
///----------------------------------------------------------------------------------------------
int MEMs::cacheMELAcalculation(Processes process, MEMCalcs calculator,vector<TLorentzVector> partP, vector<int> partId, double& me2process)
{
	return MEMs::cacheMELAcalculation( static_cast<int>(process), calculator, partP, partId, (vector<complex<double> >*) NULL, (vector<complex<double> >*) NULL, me2process);
}



///----------------------------------------------------------------------------------------------
/// MEMCalculators::cacheMELAcalculation - method to interface with Mela::computeP and cache results. A transfer function
///----------------------------------------------------------------------------------------------
int MEMs::cacheMELAcalculation(Processes process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings, double& me2process)
{
	return cacheMELAcalculation( static_cast<int>(process), calculator, partP, partId, ProdCouplings, DecayCouplings, me2process);
}



///----------------------------------------------------------------------------------------------
/// MEMCalculators::cacheMELAcalculation - method to interface with Mela::computeP and cache results. A generic case
///----------------------------------------------------------------------------------------------
int MEMs::cacheMELAcalculation(int process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings, double& me2process){

  if (debug){
    std::cout << "MEMs::cacheMELAcalculation started." << std::endl;
    std::cout << "MEMs::cacheMELAcalculation. Process: " << process << std::endl;
    std::cout << "MEMs::cacheMELAcalculation. Calculator: " << calculator << std::endl;
  }

  partPCache = partP;
  partIdCache = partId;

  SimpleParticleCollection_t daughters;
  SimpleParticleCollection_t associateds;
  for (unsigned int idau=0; idau<4; idau++) daughters.push_back(SimpleParticle_t(partId.at(idau), partP.at(idau))); // Needs generalization for final state
  for (unsigned int iap=4; iap<partP.size(); iap++) associateds.push_back(SimpleParticle_t(partId.at(iap), partP.at(iap)));
  // Mothers, blah...
  m_MELA->setInputEvent(
    &daughters,
    &associateds,
    0,
    false
    );

  //if(MELAprocMap[static_cast<Processes>(process)] == TVar::HJJVBF || MELAprocMap[static_cast<Processes>(process)] == TVar::PSHJJVBF || MELAprocMap[static_cast<Processes>(process)] == TVar::HJJNONVBF || MELAprocMap[static_cast<Processes>(process)] == TVar::PSHJJNONVBF )
  //	if(MELAprodMap[static_cast<Processes>(process)] == TVar::JJVBF|| MELAprodMap[static_cast<Processes>(process)] == TVar::JJQCD || MELAprodMap[static_cast<Processes>(process)] == TVar::JJVH)
  //  if(process == kJJ_SMHiggs_VBF || process == kJJ_0minus_VBF || process == kJJ_SMHiggs_GG || process == kJJ_0minus_GG || process == kJJ_0minus_VH || process == kJJ_SMHiggs_VH)
  if (process == kJJ_SMHiggs_VBF || process == kJJ_0minus_VBF || process == kJJ_SMHiggs_GG || process == kJJ_0minus_GG)
  {
    float me2process_float;
    m_MELA->setProcess(MELAprocMap[static_cast<Processes>(process)], MELAcalcMap[calculator], MELAprodMap[static_cast<Processes>(process)]);
    m_MELA->computeProdP(me2process_float, true);
    me2process = (double)me2process_float;
  }
  else
  {
    // retrieve ME calculations
    // ---------------------------------------------------

    float me2process_float;


    if (process==kSpin0_gg || process==kSpin0_prodIndep ||
      process==kSpin1_qqbar || process==kSpin1_prodIndep ||
      process==kSpin2_gg || process==kSpin2_qqbar || process==kSpin2_prodIndep || process==kggZZ_SMHiggs)
    {
      if (process==kSpin0_gg || process==kSpin0_prodIndep){
        double translation[nSupportedHiggses][SIZE_HVV][2]={ { { 0 } } };
        if (DecayCouplings!=0){
          for (int i=0; i<min((int)(*DecayCouplings).size(), (int)SIZE_HVV); i++){
            translation[0][i][0] = (*DecayCouplings)[i].real();
            translation[0][i][1] = (*DecayCouplings)[i].imag();
          }
        }

        //                 TVar::Process        TVar::MatrixElement     TVar::Production
        m_MELA->setProcess(MELAprocMap[static_cast<Processes>(process)], MELAcalcMap[calculator], MELAprodMap[static_cast<Processes>(process)]);
        if (
          MELAprocMap[static_cast<Processes>(process)]==TVar::SelfDefine_spin0 && DecayCouplings!=0
          ) m_MELA->computeP_selfDspin0(
          translation,
          me2process_float,
          true
          );
        else m_MELA->computeP(
          me2process_float,
          true
          );
      }
      else if (process == kSpin1_qqbar || process ==kSpin1_prodIndep){
        double translation[SIZE_ZVV][2];
        double translationProd[SIZE_ZQQ][2];

        if (DecayCouplings!=0){
          for (int i=0; i<min((int)(*DecayCouplings).size(), (int)SIZE_ZVV); i++){
            translation[i][0] = (*DecayCouplings)[i].real();
            translation[i][1] = (*DecayCouplings)[i].imag();
          }
        }
        if (ProdCouplings!=0){
          for (int i=0; i<min((int)(*ProdCouplings).size(), (int)SIZE_ZQQ); i++){
            translationProd[i][0] = (*ProdCouplings)[i].real();
            translationProd[i][1] = (*ProdCouplings)[i].imag();
          }
        }
        m_MELA->setProcess(MELAprocMap[static_cast<Processes>(process)], MELAcalcMap[calculator], MELAprodMap[static_cast<Processes>(process)]);
        if (
          MELAprocMap[static_cast<Processes>(process)]==TVar::SelfDefine_spin1 && DecayCouplings!=0
          ){
          if (ProdCouplings!=0) m_MELA->computeP_selfDspin1(
            translationProd,
            translation,
            me2process_float,
            true
            );
          else m_MELA->computeP_selfDspin1(
            translation,
            me2process_float,
            true
            );
        }
        else m_MELA->computeP(
          me2process_float,
          true
          );
      }
      else if (process==kSpin2_gg || process==kSpin2_qqbar || process==kSpin2_prodIndep){
        double translation[SIZE_GVV][2];
        double translationProd[SIZE_GGG][2];
        if (DecayCouplings!=0){
          for (int i=0; i<min((int)(*DecayCouplings).size(), (int)SIZE_GVV); i++){
            translation[i][0] = (*DecayCouplings)[i].real();
            translation[i][1] = (*DecayCouplings)[i].imag();
          }
        }
        if (ProdCouplings!=0){
          if (process==kSpin2_gg){
            for (int i=0; i<min((int)(*ProdCouplings).size(), (int)SIZE_GGG); i++){
              translationProd[i][0] = (*ProdCouplings)[i].real();
              translationProd[i][1] = (*ProdCouplings)[i].imag();
            }
          }
          else if (process==kSpin2_qqbar){
            for (int i=0; i<min((int)(*ProdCouplings).size(), (int)SIZE_GQQ); i++){
              translationProd[i][0] = (*ProdCouplings)[i].real();
              translationProd[i][1] = (*ProdCouplings)[i].imag();
            }
          }
        }

        m_MELA->setProcess(MELAprocMap[static_cast<Processes>(process)], MELAcalcMap[calculator], MELAprodMap[static_cast<Processes>(process)]);
        if (
          MELAprocMap[static_cast<Processes>(process)]==TVar::SelfDefine_spin2 && DecayCouplings!=0 && ProdCouplings!=0
          ) m_MELA->computeP_selfDspin2(
          translationProd, translation,
          me2process_float,
          true
          );
        else m_MELA->computeP(
          me2process_float,
          true
          );
      }
      else return ERR_PROCESS;	// not yet implemented
    }
    else if (process==kg1g4 || process==kg1g2 || process==kg1g4_pi_2 ||
      process==kg1g2_pi_2 || process==k_g1g1prime2 || process ==kzzzg || process == kzzgg || process == kzzzg_PS || process ==kzzgg_PS)
    {
      m_MELA->computeD_CP(
        MELAcalcMap[calculator], MELAprocIntMap[static_cast<Processes_int>(process)],
        me2process_float);
    }
    else if (process == kggHZZ_10)
    {
      m_MELA->computeD_gg(
        MELAcalcMap[calculator], MELAprocMap[static_cast<Processes>(process)],
        me2process_float);
    }
    else
    {
      //                 TVar::Process        TVar::MatrixElement     TVar::Production
      m_MELA->setProcess(MELAprocMap[static_cast<Processes>(process)], MELAcalcMap[calculator], MELAprodMap[static_cast<Processes>(process)]);

      // check if ZZ_4e is configured and event is 2e2mu event
      //		if(MELAprocMap[static_cast<Processes>(process)]==TVar::ZZ_4e && MELAcalcMap[calculator]==TVar::MCFM && flavor==3)
      //			m_MELA->setProcess(TVar::ZZ_2e2m,MELAcalcMap[calculator],MELAprodMap[static_cast<Processes>(process)]);

      m_MELA->computeP(
        me2process_float,
        true
        );
    }


    me2process = (double)me2process_float;

    if (debug) cout << "MEMs::cacheMELAcalculation. me2process: " << me2process << endl;
  }

  if (debug) cout << "MEMs::cacheMELAcalculation. Done!" << endl;

  m_MELA->resetInputEvent(); // Do not forget this!
  return NO_ERR;
}



///----------------------------------------------------------------------------------------------
/// MEMs::Convert_couplings_a_to_kappa - Coupling conversion function
///----------------------------------------------------------------------------------------------
int MEMs::Convert_couplings_a_to_kappa( Processes process, vector<complex<double> > *ProdCouplings_a, vector<complex<double> > *DecayCouplings_a, vector<complex<double> > *ProdCouplings_kappa, vector<complex<double> > *DecayCouplings_kappa )
{
	if( (Check_Couplings( process, ProdCouplings_a, DecayCouplings_a)) != 0 ) return ERR_PROCESS;
	
	if( process==kSpin0_gg || process==kSpin0_prodIndep )
	{
		if( (*DecayCouplings_kappa).size()!=4 ) (*DecayCouplings_kappa).resize( 4, complex<double>(0.0, 0.0) );
		
		(*DecayCouplings_kappa)[0] =  0.5*(*DecayCouplings_a)[0];
		(*DecayCouplings_kappa)[1] = -1.0*(*DecayCouplings_a)[1];
		(*DecayCouplings_kappa)[2] = -1.0*(*DecayCouplings_a)[2];
		(*DecayCouplings_kappa)[3] = -1.0*(*DecayCouplings_a)[3];
		
		if( (*DecayCouplings_kappa).size()==4 ) return NO_ERR;
		// |q1**2+q2**2|**2 is no longer supported in JHUGenMELA or analyticalMELA; prime5==(q1**4 + q2**4) and prime6==(q1**4 - q2**4) are supported instead
		(*DecayCouplings_kappa)[0] +=  0.5*XZZ_form_factor( (*DecayCouplings_a)[10], (*DecayCouplings_a)[11], 0, (*DecayCouplings_a)[32], m_mZ1, m_mZ2, m_Lambda_z1 );
		(*DecayCouplings_kappa)[1] += -1.0*XZZ_form_factor( (*DecayCouplings_a)[15], (*DecayCouplings_a)[16], 0, (*DecayCouplings_a)[34], m_mZ1, m_mZ2, m_Lambda_z2 );
		(*DecayCouplings_kappa)[2] += -1.0*XZZ_form_factor( (*DecayCouplings_a)[20], (*DecayCouplings_a)[21], 0, (*DecayCouplings_a)[36], m_mZ1, m_mZ2, m_Lambda_z3 );
		(*DecayCouplings_kappa)[3] += -1.0*XZZ_form_factor( (*DecayCouplings_a)[25], (*DecayCouplings_a)[26], 0, (*DecayCouplings_a)[38], m_mZ1, m_mZ2, m_Lambda_z4 );
		
		return NO_ERR;
	}
	else if( process==kSpin1_qqbar || process==kSpin1_prodIndep )	// WARNING NOT well defined yet
	{
		if( (*DecayCouplings_kappa).size()!=2 ) (*DecayCouplings_kappa).resize( 2, complex<double>(0.0, 0.0) );
		
		(*DecayCouplings_kappa)[0] =  1.0*(*DecayCouplings_a)[0];
		(*DecayCouplings_kappa)[1] =  1.0*(*DecayCouplings_a)[1];
		
		// Production
		if( process==kSpin1_qqbar )
		{
			if( (*ProdCouplings_kappa).size()!=2 ) (*ProdCouplings_kappa).resize( 2, complex<double>(0.0, 0.0) );
			
			(*ProdCouplings_kappa)[0] =  1.0*(*ProdCouplings_a)[0];
			(*ProdCouplings_kappa)[1] =  1.0*(*ProdCouplings_a)[1];
		}
		
		return NO_ERR;
	}
	else if( process==kSpin2_gg || process==kSpin2_qqbar || process==kSpin2_prodIndep )	// WARNING NOT well defined yet
	{
		if( (*DecayCouplings_kappa).size()!=10 ) (*DecayCouplings_kappa).resize( 10, complex<double>(0.0, 0.0) );
		
		(*DecayCouplings_kappa)[0] = -1.0*(*DecayCouplings_a)[0];
		(*DecayCouplings_kappa)[1] =  1.0*(*DecayCouplings_a)[1];
		(*DecayCouplings_kappa)[2] =  1.0*(*DecayCouplings_a)[2];
		(*DecayCouplings_kappa)[3] =  1.0*(*DecayCouplings_a)[3];
		(*DecayCouplings_kappa)[4] =  1.0*(*DecayCouplings_a)[4];
		(*DecayCouplings_kappa)[5] =  1.0*(*DecayCouplings_a)[5];
		(*DecayCouplings_kappa)[6] =  1.0*(*DecayCouplings_a)[6];
		(*DecayCouplings_kappa)[7] =  1.0*(*DecayCouplings_a)[4];
		(*DecayCouplings_kappa)[8] =  1.0*(*DecayCouplings_a)[8];
		(*DecayCouplings_kappa)[9] =  1.0*(*DecayCouplings_a)[9];
		
		// Production
		if( process==kSpin2_gg )
		{
			if( (*ProdCouplings_kappa).size()!=10 ) (*ProdCouplings_kappa).resize( 10, complex<double>(0.0, 0.0) );
			
			(*ProdCouplings_kappa)[0] = -1.0*(*ProdCouplings_a)[0];
			(*ProdCouplings_kappa)[1] =  1.0*(*ProdCouplings_a)[1];
			(*ProdCouplings_kappa)[2] =  1.0*(*ProdCouplings_a)[2];
			(*ProdCouplings_kappa)[3] =  1.0*(*ProdCouplings_a)[3];
			(*ProdCouplings_kappa)[4] =  complex<double>(0.0, 0.0);
			(*ProdCouplings_kappa)[5] =  complex<double>(0.0, 0.0);
			(*ProdCouplings_kappa)[6] =  complex<double>(0.0, 0.0);
			(*ProdCouplings_kappa)[7] =  1.0*(*ProdCouplings_a)[4];
			(*ProdCouplings_kappa)[8] =  complex<double>(0.0, 0.0);
			(*ProdCouplings_kappa)[9] =  complex<double>(0.0, 0.0);
		}
		if( process==kSpin2_qqbar )
		{
			if( (*ProdCouplings_kappa).size()!=4 ) (*ProdCouplings_kappa).resize( 4, complex<double>(0.0, 0.0) );
			
			(*ProdCouplings_kappa)[0] =  1.0*(*ProdCouplings_a)[0];
			(*ProdCouplings_kappa)[1] =  1.0*(*ProdCouplings_a)[1];
			(*ProdCouplings_kappa)[2] =  complex<double>(0.0, 0.0);
			(*ProdCouplings_kappa)[3] =  complex<double>(0.0, 0.0);
		}
		
		return NO_ERR;
	}
	
	return ERR_PROCESS;
}



///----------------------------------------------------------------------------------------------
/// MEMs::Convert_couplings_kappa_to_a - Coupling conversion function
///----------------------------------------------------------------------------------------------
int MEMs::Convert_couplings_kappa_to_a( Processes process, vector<complex<double> > *ProdCouplings_kappa, vector<complex<double> > *DecayCouplings_kappa, vector<complex<double> > *ProdCouplings_a, vector<complex<double> > *DecayCouplings_a )
{
	if( (Check_Couplings( process, ProdCouplings_kappa, DecayCouplings_kappa)) != 0 ) return ERR_PROCESS;
	
	if( process==kSpin0_gg || process==kSpin0_prodIndep )
	{
		if( (*DecayCouplings_a).size()<4 ) (*DecayCouplings_a).resize( 4, complex<double>(0.0, 0.0) );
		
		(*DecayCouplings_a)[0] =  2.0*(*DecayCouplings_kappa)[0];
		(*DecayCouplings_a)[1] = -1.0*(*DecayCouplings_kappa)[1];
		(*DecayCouplings_a)[2] = -1.0*(*DecayCouplings_kappa)[2];
		(*DecayCouplings_a)[3] = -1.0*(*DecayCouplings_kappa)[3];
		
		return NO_ERR;
	}
	else if( process==kSpin1_qqbar || process==kSpin1_prodIndep )	// WARNING NOT well defined yet
	{
		if( (*DecayCouplings_a).size()!=SIZE_ZVV ) (*DecayCouplings_a).resize( SIZE_ZVV, complex<double>(0.0, 0.0) );
		(*DecayCouplings_a)[0] =  1.0*(*DecayCouplings_kappa)[0];
		(*DecayCouplings_a)[1] =  1.0*(*DecayCouplings_kappa)[1];
		
		// Production
		if( process==kSpin1_qqbar )
		{
			if( (*ProdCouplings_a).size()!=SIZE_ZVV ) (*ProdCouplings_a).resize( SIZE_ZVV, complex<double>(0.0, 0.0) );
			
			(*ProdCouplings_a)[0] =  1.0*(*ProdCouplings_kappa)[0];
			(*ProdCouplings_a)[1] =  1.0*(*ProdCouplings_kappa)[1];
		}
		
		return NO_ERR;
	}
	else if( process==kSpin2_gg || process==kSpin2_qqbar || process==kSpin2_prodIndep )	// WARNING NOT well defined yet
	{
		if( (*DecayCouplings_a).size()!=SIZE_GVV ) (*DecayCouplings_a).resize( SIZE_GVV, complex<double>(0.0, 0.0) );
		
		(*DecayCouplings_a)[0] = -1.0*(*DecayCouplings_kappa)[0];
		(*DecayCouplings_a)[1] =  1.0*(*DecayCouplings_kappa)[1];
		(*DecayCouplings_a)[2] =  1.0*(*DecayCouplings_kappa)[2];
		(*DecayCouplings_a)[3] =  1.0*(*DecayCouplings_kappa)[3];
		(*DecayCouplings_a)[4] =  1.0*(*DecayCouplings_kappa)[4];
		(*DecayCouplings_a)[5] =  1.0*(*DecayCouplings_kappa)[5];
		(*DecayCouplings_a)[6] =  1.0*(*DecayCouplings_kappa)[6];
		(*DecayCouplings_a)[7] =  1.0*(*DecayCouplings_kappa)[4];
		(*DecayCouplings_a)[8] =  1.0*(*DecayCouplings_kappa)[8];
		(*DecayCouplings_a)[9] =  1.0*(*DecayCouplings_kappa)[9];
		
		// Production
		if( process==kSpin2_gg )
		{
			if( (*ProdCouplings_a).size()!=SIZE_GGG ) (*ProdCouplings_a).resize( SIZE_GGG, complex<double>(0.0, 0.0) );
			
			(*ProdCouplings_a)[0] = -1.0*(*ProdCouplings_kappa)[0];
			(*ProdCouplings_a)[1] =  1.0*(*ProdCouplings_kappa)[1];
			(*ProdCouplings_a)[2] =  1.0*(*ProdCouplings_kappa)[2];
			(*ProdCouplings_a)[3] =  1.0*(*ProdCouplings_kappa)[3];
			(*ProdCouplings_a)[4] =  1.0*(*ProdCouplings_kappa)[7];
		}
		if( process==kSpin2_qqbar )
		{
			if( (*ProdCouplings_kappa).size()!=2 ) (*ProdCouplings_kappa).resize( 2, complex<double>(0.0, 0.0) );
			// ????
			(*ProdCouplings_a)[0] =  1.0*(*ProdCouplings_a)[0];
			(*ProdCouplings_a)[1] =  1.0*(*ProdCouplings_a)[1];
		}
		
		return NO_ERR;
	}
	
	return ERR_PROCESS;
}



///----------------------------------------------------------------------------------------------
/// MEMs::XZZ_form_factor - XZZ coupling form factors
///----------------------------------------------------------------------------------------------
complex<double> MEMs::XZZ_form_factor( complex<double> form_c1, complex<double> form_c2, complex<double> form_c3, complex<double> form_c4, double mZ1, double mZ2, double Lambda_z )
{
	return (  form_c1*pow(Lambda_z,4)/( pow(Lambda_z,2) + mZ1*mZ1 )/( pow(Lambda_z,2) + mZ2*mZ2 ) 
			+ form_c2*( mZ1*mZ1+mZ2*mZ2 )/pow(Lambda_z,2)
			+ form_c3*pow( ( mZ1*mZ1+mZ2*mZ2 ),2 )/pow(Lambda_z,4)
			+ form_c4*( mZ1*mZ1*mZ2*mZ2 )/pow(Lambda_z,4)  );
}



///----------------------------------------------------------------------------------------------
/// interface for calculating P(m4l) for superKD
///----------------------------------------------------------------------------------------------
/// Possible syst values:
///   kNone: nominal shape is used
///   kScaleUp/kScaleDown: mean mass shifted up/down appropriate scale error
///   kResolUp/kResolDown: width is varied by appropriate resolution error
///----------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
void MEMs::computePm4l(
  vector<TLorentzVector> partP,
  vector<int> partId,
  SuperKDsyst syst,
  double& sigProb,
  double& bkgProb
  ){
  float prob_float;

  SimpleParticleCollection_t daughters;
  for (unsigned int idau=0; idau<4; idau++) daughters.push_back(SimpleParticle_t(partId.at(idau), partP.at(idau))); // Needs generalization for final state
  m_MELA->setInputEvent(
    &daughters,
    0,
    0,
    false
    );

  m_MELA->setProcess(TVar::bkgZZ, TVar::JHUGen, TVar::ZZGG);
  m_MELA->computePM4l((TVar::SuperMelaSyst)syst, prob_float);
  bkgProb = (double)prob_float;

  m_MELA->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::ZZGG);
  m_MELA->computePM4l((TVar::SuperMelaSyst)syst, prob_float);
  sigProb = (double)prob_float;

  m_MELA->resetInputEvent(); // Do not forget this!
}

void MEMs::removeLeptonMasses(bool doRemove){ m_MELA->setRemoveLeptonMasses(doRemove); }


#endif
