#ifndef SUPERDIJETMELA
#define SUPERDIJETMELA

#include <unordered_map>
#include "MELADifermionResolutionModel.h"


class SuperDijetMela{
protected:
  float sqrts;
  TVar::VerbosityLevel verbosity;
  /***** RESOLUTION HANDLES *****/
  std::unordered_map<int, MELADifermionResolutionModel*> ResolutionModelMap;

public:
  SuperDijetMela(float sqrts_, TVar::VerbosityLevel verbosity_);
  ~SuperDijetMela();

  void SetVerbosity(const TVar::VerbosityLevel verbosity_){ verbosity=verbosity_; }

  void SetupResolutionModel(TVar::Production prod);
  float GetConvBW(TVar::Production prod, MELACandidate* cand);

};

#endif
