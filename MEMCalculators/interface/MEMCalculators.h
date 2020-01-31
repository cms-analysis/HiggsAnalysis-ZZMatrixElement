/*************************************************************************
*  Authors:   MEKD & MELA fans
*************************************************************************/
#ifndef MEMCalc_MEMCalc_h
#define MEMCalc_MEMCalc_h

// C++ includes
#include <iostream>
#include <complex>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include "TString.h"
#include "TLorentzVector.h"
#include <ZZMatrixElement/MELA/interface/Mela.h>
#include <ZZMatrixElement/MEKD/interface/MEKD.h>

using namespace std;


//////////////////////////////////////////////////////////////////////////
///
///  MEMNames namespace provides enum types for names of processes and
///  names of tools/calculators supported by MELA and MEKD packages.
///
///  More details can be found at the TWiki:
///    https://twiki.cern.ch/twiki/bin/view/CMS/HZZ4lME
///
//////////////////////////////////////////////////////////////////////////
namespace MEMNames {
	/// Enum type for supported processes in MELA and MEKD packages
	enum Processes    {kSMHiggs, kSMHiggs_prodIndep,
		k0hplus, k0hplus_prodIndep,
		k0minus, k0minus_prodIndep,
		k1plus, k1plus_prodIndep,
		k1minus, k1minus_prodIndep,
		k2mplus_gg, k2mplus_qqbar, k2mplus_prodIndep,
		k2hplus, k2hplus_qqbar, k2hplus_prodIndep,
		k2hminus, k2hminus_qqbar, k2hminus_prodIndep,
		k2bplus, k2bplus_qqbar, k2bplus_prodIndep,
		
		kqqZZ, kqqZZ_prodIndep,
		kggZZ, kggZZ_SMHiggs,
		k0_g1prime2,
		kSpin0_gg, kSpin0_prodIndep,
		kSpin1_qqbar, kSpin1_prodIndep,
		kSpin2_gg, kSpin2_qqbar, kSpin2_prodIndep,
		kJJ_SMHiggs_VBF, kJJ_0minus_VBF, kJJ_SMHiggs_GG, kJJ_0minus_GG, kJJ_SMHiggs_VH, kJJ_0minus_VH,
		
		k2h2plus_gg, k2h2plus_qqbar, k2h2plus_prodIndep,
		k2h3plus_gg, k2h3plus_qqbar, k2h3plus_prodIndep,
		k2h6plus_gg, k2h6plus_qqbar, k2h6plus_prodIndep,
		k2h7plus_gg, k2h7plus_qqbar, k2h7plus_prodIndep,
		k2h9minus_gg, k2h9minus_qqbar, k2h9minus_prodIndep,
		k2h10minus_gg, k2h10minus_qqbar, k2h10minus_prodIndep,
		
		kggHZZ_10, k0_Zgs, k0_gsgs, k0_Zgs_PS, k0_gsgs_PS, k0_Zgs_g1prime2,
		kqqZ4l_s, kqqZ4l_t,
		
		k0plus_2f_gg, k0plus_2f_prodIndep,
		k0minus_2f_gg, k0minus_2f_prodIndep,
		k1plus_2f_qqbar, k1plus_2f_prodIndep,
		k1minus_2f_qqbar, k1minus_2f_prodIndep,
		k2mplus_2f_gg, k2mplus_2f_qqbar, k2mplus_2f_prodIndep,
		
		NUM_PROCESSES};
	
	/// Enum type for supported MEM calculators from MELA and MEKD packages
	enum MEMCalcs    {kAnalytical, kMEKD, kJHUGen, kMCFM, kMELA_HCP, NUM_MEMCALCS};
	
	enum SuperKDsyst {kNone, kScaleUp, kScaleDown, kResolUp, kResolDown, NUM_SuperKDsyst};
	enum Processes_int {kg1g4=1000, kg1g2, kg1g4_pi_2, kg1g2_pi_2, k_g1g1prime2, kzzzg, kzzgg, kzzzg_PS, kzzgg_PS, kzzzg_g1prime2, kzzzg_g1prime2_pi_2};
}

//////////////////////////////////////////////////////////////////////////
///
///  MEMs class provides an interface to the MEKD & MELA packages necessary
///  to compute///  for the processes and by tools specified by the user.
///
//////////////////////////////////////////////////////////////////////////
using namespace MEMNames;

class MEMs {
public:
	///
	/// Constructor. Can specify the PDF to be use (ony CTEQ6L available at the moment).
	///
	/// \param collisionEnergy              the sqrt(s) value in TeV (DEFAULT = 8).
	/// \param PDFName                      the name of the parton density functions to be used (DEFAULT = "", Optional: "CTEQ6L").
	///
	MEMs(double collisionEnergy = 8, double sKD_mass = 125.6, string PDFName = "", bool debug_=false);
	
	///
	/// Compute individual ME for the specified process.
	///
	/// \param[in]  process                 names of the process for which the ME should be retrieved.
	/// \param[in]  calculator              name of the calculator tool to be used.
	/// \param[in]  partP                   the input vector with TLorentzVectors for 4 leptons and 1 photon.
	/// \param[in]  partId                  the input vecor with IDs (PDG) for 4 leptons and 1 photon.
	/// \param[out] me2process              retrieved |ME|^2 for the specified process and calculator.
	/// \return                             error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS, 2 = ERR_COMPUTE
	///
	int computeME(Processes process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, double& me2process);
	
	///
	/// Compute individual mixed MEs for the specified "model".
	///
	/// \param[in]  process                 names of the process for which the ME should be retrieved.
	/// \param[in]  calculator              name of the calculator tool to be used.
	/// \param[in]  partP                   the input vector with TLorentzVectors for 4 leptons and 1 photon.
	/// \param[in]  partId                  the input vecor with IDs (PDG) for 4 leptons and 1 photon.
	/// \param[in]  ProdCouplings           coupling strengths for the resonance production, affects Spin 1 and Spin 2 only
	/// \param[in]  DecayCouplings          coupling strengths for the resonance decay
	/// \param[out] me2process              retrieved |ME|^2 for the specified process and calculator.
	/// \return                             error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS, 2 = ERR_COMPUTE
	///
	int computeME(Processes process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings, double& me2process);
	
	///
	/// Compute individual mixed MEs interference term for the specified "model". Intended for the production-independent models PLUS gg -> Spin 0
	///
	/// \param[in]  process                 names of the process for which the ME should be retrieved.
	/// \param[in]  calculator              name of the calculator tool to be used.
	/// \param[in]  partP                   the input vector with TLorentzVectors for 4 leptons and 1 photon.
	/// \param[in]  partId                  the input vecor with IDs (PDG) for 4 leptons and 1 photon.
	/// \param[in]  DecayCouplings          coupling strengths for the resonance decay
	/// \param[out] me2process              retrieved |ME|^2 for the specified process and calculator.
	/// \return                             error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS, 2 = ERR_COMPUTE
	///
	int computeME_Interference(Processes process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *DecayCouplings, double& me2process);
	
	/// Work in progress method. Currently serves as a bridge to MELA package implementations.
	int computeME_Interference(Processes_int process, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId,  double& me2process);
	
	///
	/// Compute individual KD and MEs for process A and process B, obtained with the specified calculator tool.
	///
	/// \param[in]  processA, processB      names of the processes A and B for which the KDs and MEs are computed.
	/// \param[in]  calculator              name of the calculator tool to be used.
	/// \param[in]  partP                   the input vector with TLorentzVectors for 4 leptons and 1 photon.
	/// \param[in]  partId                  the input vecor with IDs (PDG) for 4 leptons and 1 photon.
	/// \param[out] kd                      computed KD value for discrimination of processes A and B.
	/// \param[out] me2processA             computed |ME|^2 for process A.
	/// \param[out] me2processB             computed |ME|^2 for process B.
	/// \return                             error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS, 2 = ERR_COMPUTE
	///
	int computeKD(Processes processA, Processes processB, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, double& kd, double& me2processA, double& me2processB );
	
	///
	/// Compute individual KD and MEs for process A and process B, obtained with the specified calculator tool.
	///
	/// \param[in]  processA, processB      names of the processes A and B for which the KDs and MEs are computed.
	/// \param[in]  calculator              name of the calculator tool to be used.
	/// \param[in]  partP                   the input vector with TLorentzVectors for 4 leptons and 1 photon.
	/// \param[in]  partId                  the input vecor with IDs (PDG) for 4 leptons and 1 photon.
	/// \param[in]  ProdCouplingsA          coupling strengths for the resonance production, affects Spin 1 and Spin 2 only
	/// \param[in]  DecayCouplingsA         coupling strengths for the resonance decay
	/// \param[in]  ProdCouplingsB          coupling strengths for the resonance production, affects Spin 1 and Spin 2 only
	/// \param[in]  DecayCouplingsB         coupling strengths for the resonance decay
	/// \param[out] kd                      computed KD value for discrimination of processes A and B.
	/// \param[out] me2processA             computed |ME|^2 for process A.
	/// \param[out] me2processB             computed |ME|^2 for process B.
	/// \return                             error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS, 2 = ERR_COMPUTE
	///
	int computeKD(Processes processA, Processes processB, MEMCalcs calculator, vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplingsA, vector<complex<double> > *DecayCouplingsA, vector<complex<double> > *ProdCouplingsB, vector<complex<double> > *DecayCouplingsB, double& kd, double& me2processA, double& me2processB );
	
	///
	/// Compute MEs for all supported processes.
	///
	/// Individual MEs and KDs can be retrieved using retrieveME(Processes,MEMCalcs,double&) and computeKD(Processes,MEMCalcs,Processes,MEMCalcs,double(*)(double,double),double&,double&,double&).
	///
	/// \param[in]  partP                   the input vector with TLorentzVectors for 4 leptons and 1 photon.
	/// \param[in]  partId                  the input vecor with IDs (PDG) for 4 leptons and 1 photon.
	/// \return                             error code of the computation: 0 = NO_ERR, 2 = ERR_COMPUTE
	///
	int computeMEs(vector<TLorentzVector> partP, vector<int> partId);
	
	///
	/// Retrieve ME for specified process and specified calculator tool.
	///
	/// Method should be called only after running computeMEs(vector<TLorentzVector> partP,vector<int> partId).
	///
	/// \param[in]  process                 names of the process for which the ME should be retrieved.
	/// \param[in]  calculator              name of the calculator tool to be used.
	/// \param[out] me2process              retrieved |ME|^2 for the specified process and calculator.
	/// \return                             error codes: 0 = NO_ERR, 1 = ERR_PROCESS
	///
	int retrieveME(Processes process, MEMCalcs calculator, double& me2process);
	
	///
	/// Compute KD and retrieve MEs for process A and process B, obtained with the specified calculator tool.
	/// The KD is computed using KD function specified by the user as kd = funcKD(me2processA, me2processB).
	///
	/// Method should be called only after running computeMEs(vector<TLorentzVector> partP,vector<int> partId).
	///
	/// \param[in]  processA, processB          names of the processes for which the KD and MEs are computed.
	/// \param[in]  calculatorA, calculatorB    names of the calculator tools to be used.
	/// \param[in]  funcKD                      name of the method to be used for KD computation.
	/// \param[out] kd                          computed KD value for discrimination of processes A and B.
	/// \param[out] me2processA                 computed |ME|^2 for process A.
	/// \param[out] me2processB                 computed |ME|^2 for process B.
	/// \return                                 error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS
	///
	int computeKD(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB, double (MEMs::*funcKD)(double, double), double& kd, double& me2processA, double& me2processB );
	
	///
	/// Compute KD and retrieve MEs for process A and process B, obtained with the specified calculator tool.
	/// The KD is computed using KD function specified by the user which has defferent implementations for
	/// different combinations of processes and calculator tools. Functions is of the form
	/// kd = funcKD(processA, calculatorA, processB, calculatorB).
	///
	/// Method should be called only after running computeMEs(vector<TLorentzVector> partP,vector<int> partId).
	///
	/// \param[in]  processA, processB          names of the processes for which the KD and MEs are computed.
	/// \param[in]  calculatorA, calculatorB    names of the calculator tools to be used.
	/// \param[in]  funcKD                      name of the method to be used for KD computation.
	/// \param[out] kd                          computed KD value for discrimination of processes A and B.
	/// \param[out] me2processA                 computed |ME|^2 for process A.
	/// \param[out] me2processB                 computed |ME|^2 for process B.
	/// \return                                 error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS
	///
	int computeKD(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB, double (MEMs::*funcKD)(Processes, MEMCalcs, Processes, MEMCalcs), double& kd, double& me2processA, double& me2processB );
	
	///
	/// Compute KD with pdf(m4l) folded in and retrieve MEs for process A (signal) and process B (background), obtained with the specified calculator tool.
	/// The KD is computed using KD function specified by the user as kd = funcKD(me2processA, me2processB, syst).
	///
	/// Method should be called only after running computeMEs(vector<TLorentzVector> partP,vector<int> partId).
	///
	/// \param[in]  processA, processB          names of the processes for which the KD and MEs are computed (processB must be kqqZZ or kqqZZ_prodIndep).
	/// \param[in]  calculatorA, calculatorB    names of the calculator tools to be used.
	/// \param[in]  funcKD                      name of the method to be used for KD computation.
	/// \param[out] kd                          computed KD value for discrimination of processes A and B.
	/// \param[out] me2processA                 computed |ME|^2 for process A.
	/// \param[out] me2processB                 computed |ME|^2 for process B.
	/// \param[in]  syst                        controls whether PDF mean or width is adjusted to gauge the systematic effects (DEFAULT = kNone)
	/// \return                                 error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS
	///
	int computeKD(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB, double (MEMs::*funcKD)(double, double, SuperKDsyst), double& kd, double& me2processA, double& me2processB, SuperKDsyst syst = MEMNames::kNone );
	
	///
	/// Retrieve the interference reweighting factor for the given event, computed using the JHUGen.
	///
	/// Method should be called only after running computeMEs(vector<TLorentzVector> partP,vector<int> partId).
	///
	/// \return                                 interference reweighting factor for the given event.
	///
	double getMELAWeight() { return m_weight;}
	
	///
	/// Interface for calculating the P(m4l) for SM signal and ZZ background (e.g. processes kSMHiggs and kqqZZ, respectively).
	///
	/// \param[in]  partP                   the input vector with TLorentzVectors for 4 leptons.
	/// \param[in]  partId                  the input vecor with IDs (PDG) for 4 leptons.
	/// \param[in]  syst                    controls whether PDF mean or width is adjusted to gauge the systematic effects
	/// \param[out] sigProb                 calculated P(m4l) for signal
	/// \param[out] bkgProb                 calculated P(m4l) for background
	///
	void computePm4l(vector<TLorentzVector> partP, vector<int> partId, SuperKDsyst syst, double& sigProb, double& bkgProb);
	
	
	///
	/// Coupling conversion function
	///
	/// \param[in]	process					The name of a process. Only generic processes should be considered: kSpinX_YYY.
	/// \param[in]	ProdCouplings_a			An input complex vector of amplitude notation production couplings (MELA).
	/// \param[in]	DecayCouplings_a		An input complex vector of amplitude notation decay couplings (MELA).
	/// \param[out]	ProdCouplings_kappa		An output complex vector of lagrangian/kappa notation production couplings (MEKD).
	/// \param[out]	DecayCouplings_kappa	An output complex vector of lagrangian/kappa notation decay couplings (MEKD). Here kappa_3 is the 4th coupling in a vector.
	/// \return								Error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS
	///
	int Convert_couplings_a_to_kappa( Processes process, vector<complex<double> > *ProdCouplings_a, vector<complex<double> > *DecayCouplings_a, vector<complex<double> > *ProdCouplings_kappa, vector<complex<double> > *DecayCouplings_kappa );
	
	///
	/// Coupling conversion function
	///
	/// \param[in]	process					The name of a process. Only generic processes should be considered: kSpinX_YYY.
	/// \param[in]	ProdCouplings_kappa		An input complex vector of lagrangian/kappa notation production couplings (MEKD).
	/// \param[in]	DecayCouplings_kappa	An input complex vector of lagrangian/kappa notation decay couplings (MEKD). Here kappa_3 is the 4th coupling in a vector.
	/// \param[out]	ProdCouplings_a			An output complex vector of amplitude notation production couplings (MELA).
	/// \param[out]	DecayCouplings_a		An output complex vector of amplitude notation decay couplings (MELA).
	/// \return								Error code of the computation: 0 = NO_ERR, 1 = ERR_PROCESS
	///
	int Convert_couplings_kappa_to_a( Processes process, vector<complex<double> > *ProdCouplings_kappa, vector<complex<double> > *DecayCouplings_kappa, vector<complex<double> > *ProdCouplings_a, vector<complex<double> > *DecayCouplings_a );
	
	
	///
	/// XZZ coupling form factors
	///
	/// \param[in]	form_c1					The first form factor
	/// \param[in]	form_c2					The second form factor
	/// \param[in]	form_c3					The third form factor
	/// \param[in]	form_c4					The fourth form factor
	/// \param[in]	mZ1						Z1 mass
	/// \param[in]	mZ2						Z2 mass
	/// \param[in]	Lambda_z				Coefficient
	/// \return								Evaluated form factor value
	///
	complex<double> XZZ_form_factor( complex<double> form_c1, complex<double> form_c2, complex<double> form_c3, complex<double> form_c4, double mZ1, double mZ2, double Lambda_z );
	
	
	/// Simple KD function: kd = log(me2processA / me2processB).
	double logRatio(double me2processA, double me2processB);
	
	/// Case-dependent KD function of a general form: kd = me2processA / (me2processA + c * me2processB).
	double probRatio(Processes processA, MEMCalcs calculatorA, Processes processB, MEMCalcs calculatorB);
	
	/// KD function with pdf(m4l) folded in, in a form: kd = Pm4lSig * me2sig / ( Pm4lSig * me2sig + Pm4lBkg * me2bkg ).
	double PDFm4lRatio(double me2processA, double me2processB, SuperKDsyst syst);
	
	
	/// Matrix of supproted processes
	static const bool isProcSupported[NUM_PROCESSES][NUM_MEMCALCS];
	
	/// enums for supported return values/errors
	enum ERRCodes    {NO_ERR, ERR_PROCESS, ERR_COMPUTE, NUM_ERRORS};
	
	double qqZZ_MCFMNorm;
	
	/// Needed for form-factor integration into couplings from amplitude-type couplings to kappa-type couplings
	double m_mZ1, m_mZ2;
	double m_Lambda_z1, m_Lambda_z2, m_Lambda_z3, m_Lambda_z4;
	
	
	/// MEM calculators: MEKD (FeynRules+MadGraph5_v1) and MELA (Analytic, JHUGen, MCFM). Placed here for the expert use.
	MEKD* m_MEKD;
	Mela* m_MELA;

  /// Enable removing of lepton masses from the MEs
  void removeLeptonMasses(bool doRemove = false);

private:
	/// For error handling and supported precalculations
	int m_err, NUM_PROCESSES_PRECALC;
	
	/// Used for temporary data
	unsigned int m_uIbuffer;
	double m_Dbuffer;
	vector<complex<double> > m_VCbuffer;
	
	/// debug flag
	bool debug;
	
	/// stored results of MEs computed with computeMEs(...)
	double m_computedME[NUM_PROCESSES][NUM_MEMCALCS];
	
	/// stored results of P(m4l) computed with computePm4l(...)
	double m_computedPm4lSig[NUM_SuperKDsyst];
	double m_computedPm4lBkg[NUM_SuperKDsyst];
	
	/// compute pdf(m4l) with computePm4l(...) for all systs
	void computePm4ls(vector<TLorentzVector> partP, vector<int> partId);
	
	/// Checks the couplings' vectors for the consistent size
	int Check_Couplings( Processes process, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings );
	
	
	
	/// MEKD process name translation
	static const TString m_processNameMEKD[NUM_PROCESSES];
	
	/// Sets up a mixed state in the MEKD
	int MEKD_Mixed_State( TString Model, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings );
	
	
	
	/// for calculating JHUGen/MCFM signal vs background KD
	
	// caches to avoid multiplemela computations
	std::vector<TLorentzVector> partPCache;
	std::vector<int> partIdCache;
	
	/// mapping of process enums between MEMNames and MELA (defined in TVar.hh
	map<Processes,TVar::Process> MELAprocMap;
	map<Processes,TVar::Production> MELAprodMap;
	map<MEMCalcs,TVar::MatrixElement> MELAcalcMap;
	
	map<Processes_int,TVar::Process> MELAprocIntMap;
	map<Processes_int,TVar::Production> MELAprodIntMap;
	///Mike : Also add weights for interference in caching
	float m_weight;
	
	/// MELA calculation
	int cacheMELAcalculation(Processes process, MEMCalcs calculator,vector<TLorentzVector> partP, vector<int> partId, double& me2process);
	int cacheMELAcalculation(Processes process, MEMCalcs calculator,vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings, double& me2process);
	int cacheMELAcalculation(int process, MEMCalcs calculator,vector<TLorentzVector> partP, vector<int> partId, vector<complex<double> > *ProdCouplings, vector<complex<double> > *DecayCouplings, double& me2process);
};


#endif

