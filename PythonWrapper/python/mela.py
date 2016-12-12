"""
Python wrapper for MELA
>>> from ZZMatrixElement.PythonWrapper.mela import Mela, SimpleParticle_t, SimpleParticleCollection_t, TVar
>>> m = Mela(13, 125)
Then you can use m mostly like a C++ mela object.

>>> m.setProcess(TVar.SelfDefine_spin0, TVar.JHUGen, TVar.ZZINDEPENDENT)

The main change is that computeP and similar functions return the ME instead of modifying a reference.
(computeP_selfD* are not implemented here, but you can access the functionality through computeP)

>>> print m.computeP(False)

You can modify the couplings either by
>>> m.selfDHzzcoupl[0][0][0] = 1
>>> m.selfDHzzcoupl[0][0][1] = 2
or by the more convenient way
>>> m.ghz1 = 1+2j

SimpleParticle_t and SimpleParticleCollection_t are implemented to take inputs in ways more normal for python.
>>> daughters = SimpleParticleCollection_t([
...                                         "11 -71.89 30.50 -47.20 91.25",
...                                         #...other daughters
...                                        ])

There's also a function for convenience
>>> m.setInputEvent_fromLHE('''
... <event>
... #(...)
... </event>
... ''')
which is useful for quick tests.

See examples at the bottom.
"""

from collections import namedtuple, OrderedDict
import os
import ROOT
import tempfile

def include(filename):
  ROOT.gROOT.ProcessLine("#include <{}>".format(filename))

ROOT.gROOT.Macro(os.path.join(os.environ["CMSSW_BASE"], "src", "ZZMatrixElement", "MELA", "test", "loadMELA.C+"))
include("ZZMatrixElement/MELA/interface/Mela.h")

from ROOT import TVar
f = tempfile.NamedTemporaryFile(suffix=".C", bufsize=0)
contents = """
  #include <ZZMatrixElement/MELA/interface/TCouplingsBase.hh>
  #include <ZZMatrixElement/MELA/interface/TMCFM.hh>
  auto size_HQQ = ::SIZE_HQQ;
  auto size_HGG = ::SIZE_HGG;
  auto size_HVV = ::SIZE_HVV;
  auto size_HVV_LAMBDAQSQ = ::SIZE_HVV_LAMBDAQSQ;
  auto size_HVV_CQSQ = ::SIZE_HVV_CQSQ;
  auto size_ZQQ = ::SIZE_ZQQ;
  auto size_ZVV = ::SIZE_ZVV;
  auto size_GQQ = ::SIZE_GQQ;
  auto size_GGG = ::SIZE_GGG;
  auto size_GVV = ::SIZE_GVV;
"""
f.write(contents)
ROOT.gROOT.ProcessLine(".L {}+".format(f.name))
from ROOT import (
                  size_HQQ as SIZE_HQQ,
                  size_HGG as SIZE_HGG,
                  size_HVV as SIZE_HVV,
                  size_HVV_LAMBDAQSQ as SIZE_HVV_LAMBDAQSQ,
                  size_HVV_CQSQ as SIZE_HVV_CQSQ,
                  size_ZQQ as SIZE_ZQQ,
                  size_ZVV as SIZE_ZVV,
                  size_GQQ as SIZE_GQQ,
                  size_GGG as SIZE_GGG,
                  size_GVV as SIZE_GVV,
                 )
from ROOT import nSupportedHiggses

class MultiDimensionalCppArray(object):
  functionfiletemplate = """
    #include <type_traits>
    {includes}
    auto {name}_getitem({cppargs}) -> std::remove_reference<decltype({cppvariable}[item])>::type {{return {cppvariable}[item];}}
    void {name}_setitem({cppargs}, std::remove_reference<decltype({cppvariable}[item])>::type value) {{{cppvariable}[item] = value;}}
  """

  uniqueids = []
  functionfiles = {}
  getitems = {}
  setitems = {}

  def __init__(self, uniqueid, cppvariable, includes, othercppargs, *dimensions):

    self.uniqueid = uniqueid
    for i in self.uniqueids:
      if i == uniqueid:
        raise ValueError("Two MultiDimensionalCppArrays can't have the same id\n{}".format(i, self.uniqueid))
    self.uniqueids.append(uniqueid)

    self.cppvariable = cppvariable
    self.dimensions = dimensions
    self.ndim = len(self.dimensions)
    if self.ndim == 0:
      raise TypeError("Can't have a 0 dimensional array!")

    if self.ndim > 1:
      self.subarrays = []
      for i in range(dimensions[0]):
          othercppargs["int index{}".format(len(dimensions))] = i
          self.subarrays.append(
                                MultiDimensionalCppArray(
                                                         "{}_{}".format(self.uniqueid, i),
                                                         "{}[index{}]".format(cppvariable, len(dimensions)),
                                                         includes,
                                                         othercppargs,
                                                         *dimensions[1:]
                                                        )
                               )
    else:
      self.othercppargs = OrderedDict(othercppargs)
      self.functionfilecontents = self.functionfiletemplate.format(
                                                                   name="NAME",
                                                                   cppvariable=self.cppvariable,
                                                                   cppargs=",".join([key for key in self.othercppargs]+["int item"]),
                                                                   includes="\n".join("#include <{}>".format(_) for _ in includes),
                                                                  )
      self.includes = includes
      self.functionfile = self.getitem = self.setitem = None

  def writecpp(self, f=None):
    if self.ndim > 1:
      for subarray in self.subarrays:
        f = subarray.writecpp(f)
      return f

    if self.functionfilecontents not in self.functionfiles:
      if f is None:
        f = tempfile.NamedTemporaryFile(suffix=".C", bufsize=0)
      self.functionfiles[self.functionfilecontents] = f
      f.write(self.functionfilecontents.replace("NAME", self.uniqueid))
      return f
    else:
      return self.functionfiles[self.functionfilecontents]

  def compilecpp(self, f):
    if self.ndim > 1:
      for subarray in self.subarrays:
        subarray.compilecpp(f)
      return

    if self.functionfilecontents not in self.getitems:
      ROOT.gROOT.ProcessLine(".L {}+".format(f.name))
      self.functionfiles[self.functionfilecontents] = f
      self.getitems[self.functionfilecontents] = getattr(ROOT, "{}_getitem".format(self.uniqueid))
      self.setitems[self.functionfilecontents] = getattr(ROOT, "{}_setitem".format(self.uniqueid))

    self.functionfile = self.functionfiles[self.functionfilecontents]
    self.getitem = self.getitems[self.functionfilecontents]
    self.setitem = self.setitems[self.functionfilecontents]


  def __getitem__(self, item):
    if self.ndim > 1:
      return self.subarrays[item]
    else:
      if self.getitem is None: self.compilecpp(self.writecpp())
      if item >= self.dimensions[0]:
        raise IndexError("Index {} out of range (0-{})".format(item, self.dimensions[0]))
      return self.getitem(*(self.othercppargs.values()+[item]))

  def __setitem__(self, item, value):
    if self.ndim > 1:
      raise TypeError("Need to specify all indices to write to the array.")
    else:
      if self.setitem is None: self.compilecpp()
      if item >= self.dimensions[0]:
        raise IndexError("Index {} out of range (0-{})".format(item, self.dimensions[0]))
      self.setitem(*(self.othercppargs.values()+[item, value]))

class SelfDParameter(object):
  def __init__(self, arrayname, *indices):
    self.arrayname = arrayname
    self.indices = indices

  def __get__(self, obj, objtype):
    array = getattr(obj, self.arrayname)
    for index in self.indices[:-1]:
      array = array[index]
    return array[self.indices[-1]]

  def __set__(self, obj, val):
    array = getattr(obj, self.arrayname)
    for index in self.indices[:-1]:
      array = array[index]
    array[self.indices[-1]] = val

class SelfDCoupling(object):
  def __init__(self, arrayname, *indices):
    self.arrayname = arrayname
    self.indices = indices
    self.real = SelfDParameter(arrayname, *indices+(0,))
    self.imag = SelfDParameter(arrayname, *indices+(1,))

  def __get__(self, obj, objtype):
    #self.real does not call __get__ on real, because it's an instance variable not a class variable
    return complex(self.real.__get__(obj, objtype), self.imag.__get__(obj, objtype))

  def __set__(self, obj, val):
    self.real.__set__(obj, val.real)
    self.imag.__set__(obj, val.imag)

class Mela(object):
  counter = 0
  doneinit = False
  computeptemplate = """
    #include <ZZMatrixElement/MELA/interface/Mela.h>
    float getPAux(Mela& mela) {
      float result;
      mela.getPAux(result);
      return result;
    }
    vector<float> computeDecayAngles(Mela& mela) {
      vector<float> result(8);
      mela.computeDecayAngles(
        result[0],
        result[1],
        result[2],
        result[3],
        result[4],
        result[5],
        result[6],
        result[7]
      );
      return result;
    }
    //not implementing the computeP_selfD* functions here
    //would be easier to do in pure python but not worth it anyway
    float computeP(Mela& mela, bool useconstant) {
      float result;
      mela.computeP(result, useconstant);
      return result;
    }
    float computeD_CP(Mela& mela, TVar::MatrixElement myME, TVar::Process myType) {
      float result;
      mela.computeD_CP(myME, myType, result);
      return result;
    }
    float computeProdP(Mela& mela, bool useconstant) {
      float result;
      mela.computeProdP(result, useconstant);
      return result;
    }
    float computeProdDecP(Mela& mela, bool useconstant) {
      float result;
      mela.computeProdDecP(result, useconstant);
      return result;
    }
    //not implementing the separate computeProdP_VH, etc.  Just use computeProdP.
    float compute4FermionWeight(Mela& mela) {
      float result;
      mela.compute4FermionWeight(result);
      return result;
    }
    float getXPropagator(Mela& mela, TVar::ResonancePropagatorScheme scheme) {
      float result;
      mela.getXPropagator(scheme, result);
      return result;
    }
    float computePM4l(Mela& mela, TVar::SuperMelaSyst syst) {
      float result;
      mela.computePM4l(syst, result);
      return result;
    }
    float computeD_gg(Mela& mela, TVar::MatrixElement myME, TVar::Process myType) {
      float result;
      mela.computeD_gg(myME, myType, result);
      return result;
    }
  """
  def __init__(self, *args, **kwargs):
    self.__mela = ROOT.Mela(*args, **kwargs)
    self.index = self.counter
    type(self).counter += 1

    arrays  = (
               ("selfDHggcoupl", (nSupportedHiggses, SIZE_HGG, 2)),
               ("selfDHg4g4coupl", (nSupportedHiggses, SIZE_HGG, 2)),
               ("selfDHqqcoupl", (nSupportedHiggses, SIZE_HQQ, 2)),
               ("selfDHbbcoupl", (nSupportedHiggses, SIZE_HQQ, 2)),
               ("selfDHttcoupl", (nSupportedHiggses, SIZE_HQQ, 2)),
               ("selfDHb4b4coupl", (nSupportedHiggses, SIZE_HQQ, 2)),
               ("selfDHt4t4coupl", (nSupportedHiggses, SIZE_HQQ, 2)),
               ("selfDHzzcoupl", (nSupportedHiggses, SIZE_HVV, 2)),
               ("selfDHwwcoupl", (nSupportedHiggses, SIZE_HVV, 2)),
               ("selfDHzzLambda_qsq", (nSupportedHiggses, SIZE_HVV_LAMBDAQSQ, SIZE_HVV_CQSQ)),
               ("selfDHwwLambda_qsq", (nSupportedHiggses, SIZE_HVV_LAMBDAQSQ, SIZE_HVV_CQSQ)),
               ("selfDHzzCLambda_qsq", (nSupportedHiggses, SIZE_HVV_CQSQ)),
               ("selfDHwwCLambda_qsq", (nSupportedHiggses, SIZE_HVV_CQSQ)),
               ("selfDZqqcoupl", (SIZE_ZQQ, 2)),
               ("selfDZvvcoupl", (SIZE_ZVV, 2)),
               ("selfDGqqcoupl", (SIZE_GQQ, 2)),
               ("selfDGggcoupl", (SIZE_GGG, 2)),
               ("selfDGvvcoupl", (SIZE_GVV, 2)),
              )

    f = None
    for name, dimensions in arrays:
        setattr(
                self,
                name,
                MultiDimensionalCppArray(
                                         "mela{}{}".format(self.index, name),
                                         "mela.{}".format(name),
                                         ["ZZMatrixElement/MELA/interface/Mela.h"],
                                         {"Mela& mela": self.__mela},
                                         *dimensions
                                        )
               )
        f = getattr(self, name).writecpp(f)
    bkpgErrorIgnoreLevel, ROOT.gErrorIgnoreLevel = ROOT.gErrorIgnoreLevel, ROOT.kInfo+1
    f.write(self.computeptemplate)
    for name, dimensions in arrays:
        getattr(self, name).compilecpp(f)
    ROOT.gErrorIgnoreLevel = bkpgErrorIgnoreLevel
    self.doneinit = True

  def __getattr__(self, name):
    return getattr(self.__mela, name)

  def __setattr__(self, name, value):
    if self.doneinit and hasattr(self.__mela, name):
      return setattr(self.__mela, name, value)
    else:
      super(Mela, self).__setattr__(name, value)

  def setInputEvent_fromLHE(self, event, isgen):
    lines = event.split("\n")
    lines = [line for line in lines if not ("<event>" in line or "</event>" in line or not line.split("#")[0].strip())]
    nparticles, _, _, _, _, _ = lines[0].split()
    nparticles = int(nparticles)
    if nparticles != len(lines)-1:
      raise ValueError("Wrong number of particles! Should be {}, have {}".replace(nparticles, len(lines)-1))
    daughters, mothers, associated = [], [], []
    ids = [None]
    mother1s = [None]
    mother2s = [None]
    for line in lines[1:]:
      id, status, mother1, mother2 = (int(_) for _ in line.split()[0:4])
      ids.append(id)
      mother1s.append(mother1)
      mother2s.append(mother2)
      if status == -1:
        mothers.append(line)
      elif status == 1 and (1 <= abs(id) <= 6 or 11 <= abs(id) <= 16 or abs(id) == 22):
        while True:
          if mother1 != mother2 or mother1 is None:
            associated.append(line)
            break
          if ids[mother1] == 25:
            daughters.append(line)
            break
          mother2 = mother2s[mother1]
          mother1 = mother1s[mother1]
    #print "mothers"
    #for _ in mothers: print _
    #print "daughters"
    #for _ in daughters: print _
    #print "associated"
    #for _ in associated: print _
    self.setInputEvent(SimpleParticleCollection_t(daughters), SimpleParticleCollection_t(associated), SimpleParticleCollection_t(mothers), isgen)

  def getPAux(self): return ROOT.getPAux(self.__mela)
  DecayAngles = namedtuple("DecayAngles", "qH m1 m2 costheta1 costheta2 Phi costhetastar Phi1")
  def computeDecayAngles(self): return self.DecayAngles(*ROOT.computeDecayAngles(self.__mela))
  def computeP(self, useconstant=True): return ROOT.computeP(self.__mela, useconstant)
  def computeD_CP(self, myME, myType): return ROOT.computeD_CP(self.__mela, myME, myType)
  def computeProdP(self, useconstant=True): return ROOT.computeProdP(self.__mela, useconstant)
  def computeProdDecP(self, useconstant=True): return ROOT.computeProdDecP(self.__mela, useconstant)
  def compute4FermionWeight(self): return ROOT.compute4FermionWeight(self.__mela)
  def getXPropagator(self, scheme): return ROOT.getXPropagator(self.__mela, scheme)
  def computePM4l(self, syst): return ROOT.computePM4l(self.__mela, syst)
  def computeD_gg(self, myME, myType): return ROOT.myME(self.__mela, myME, myType)

  ghg2 = SelfDCoupling("selfDHggcoupl", 0, 0)
  ghg3 = SelfDCoupling("selfDHggcoupl", 0, 1)
  ghg4 = SelfDCoupling("selfDHggcoupl", 0, 2)

  #https://github.com/cms-analysis/HiggsAnalysis-ZZMatrixElement/blob/41232f911b4f03065ae2b83752b5bcd4daacaa2c/MELA/fortran/mod_JHUGenMELA.F90#L123-L168
  ghz1 = SelfDCoupling("selfDHzzcoupl", 0, 0)
  ghz2 = SelfDCoupling("selfDHzzcoupl", 0, 1)
  ghz3 = SelfDCoupling("selfDHzzcoupl", 0, 2)
  ghz4 = SelfDCoupling("selfDHzzcoupl", 0, 3)

  ghzgs2 = SelfDCoupling("selfDHzzcoupl", 0, 4)
  ghzgs3 = SelfDCoupling("selfDHzzcoupl", 0, 5)
  ghzgs4 = SelfDCoupling("selfDHzzcoupl", 0, 6)
  ghgsgs2 = SelfDCoupling("selfDHzzcoupl", 0, 7)
  ghgsgs3 = SelfDCoupling("selfDHzzcoupl", 0, 8)
  ghgsgs4 = SelfDCoupling("selfDHzzcoupl", 0, 9)

  ghz1_prime = SelfDCoupling("selfDHzzcoupl", 0, 10)
  ghz1_prime2 = SelfDCoupling("selfDHzzcoupl", 0, 11)
  ghz1_prime3 = SelfDCoupling("selfDHzzcoupl", 0, 12)
  ghz1_prime4 = SelfDCoupling("selfDHzzcoupl", 0, 13)
  ghz1_prime5 = SelfDCoupling("selfDHzzcoupl", 0, 14)

  ghz2_prime = SelfDCoupling("selfDHzzcoupl", 0, 15)
  ghz2_prime2 = SelfDCoupling("selfDHzzcoupl", 0, 16)
  ghz2_prime3 = SelfDCoupling("selfDHzzcoupl", 0, 17)
  ghz2_prime4 = SelfDCoupling("selfDHzzcoupl", 0, 18)
  ghz2_prime5 = SelfDCoupling("selfDHzzcoupl", 0, 19)

  ghz3_prime = SelfDCoupling("selfDHzzcoupl", 0, 20)
  ghz3_prime2 = SelfDCoupling("selfDHzzcoupl", 0, 21)
  ghz3_prime3 = SelfDCoupling("selfDHzzcoupl", 0, 22)
  ghz3_prime4 = SelfDCoupling("selfDHzzcoupl", 0, 23)
  ghz3_prime5 = SelfDCoupling("selfDHzzcoupl", 0, 24)

  ghz4_prime = SelfDCoupling("selfDHzzcoupl", 0, 25)
  ghz4_prime2 = SelfDCoupling("selfDHzzcoupl", 0, 26)
  ghz4_prime3 = SelfDCoupling("selfDHzzcoupl", 0, 27)
  ghz4_prime4 = SelfDCoupling("selfDHzzcoupl", 0, 28)
  ghz4_prime5 = SelfDCoupling("selfDHzzcoupl", 0, 29)

  ghzgs1_prime2 = SelfDCoupling("selfDHzzcoupl", 0, 30)

  ghz1_prime6 = SelfDCoupling("selfDHzzcoupl", 0, 31)
  ghz1_prime7 = SelfDCoupling("selfDHzzcoupl", 0, 32)
  ghz2_prime6 = SelfDCoupling("selfDHzzcoupl", 0, 33)
  ghz2_prime7 = SelfDCoupling("selfDHzzcoupl", 0, 34)
  ghz3_prime6 = SelfDCoupling("selfDHzzcoupl", 0, 35)
  ghz3_prime7 = SelfDCoupling("selfDHzzcoupl", 0, 36)
  ghz4_prime6 = SelfDCoupling("selfDHzzcoupl", 0, 37)
  ghz4_prime7 = SelfDCoupling("selfDHzzcoupl", 0, 38)

  cz_q1sq = SelfDParameter("selfDHzzCLambda_qsq", 0, 0)
  Lambda_z11 = SelfDParameter("selfDHzzLambda_qsq", 0, 0)
  Lambda_z12 = SelfDParameter("selfDHzzLambda_qsq", 0, 1)
  Lambda_z13 = SelfDParameter("selfDHzzLambda_qsq", 0, 2)
  Lambda_z14 = SelfDParameter("selfDHzzLambda_qsq", 0, 3)

  cz_q2sq = SelfDParameter("selfDHzzCLambda_qsq", 0, 1)
  Lambda_z21 = SelfDParameter("selfDHzzLambda_qsq", 0, 4)
  Lambda_z22 = SelfDParameter("selfDHzzLambda_qsq", 0, 5)
  Lambda_z23 = SelfDParameter("selfDHzzLambda_qsq", 0, 6)
  Lambda_z24 = SelfDParameter("selfDHzzLambda_qsq", 0, 7)

  cz_q12sq = SelfDParameter("selfDHzzCLambda_qsq", 0, 2)
  Lambda_z01 = SelfDParameter("selfDHzzLambda_qsq", 0, 8)
  Lambda_z02 = SelfDParameter("selfDHzzLambda_qsq", 0, 9)
  Lambda_z03 = SelfDParameter("selfDHzzLambda_qsq", 0, 10)
  Lambda_z04 = SelfDParameter("selfDHzzLambda_qsq", 0, 11)

  ghw1 = SelfDCoupling("selfDHwwcoupl", 0, 0)
  ghw2 = SelfDCoupling("selfDHwwcoupl", 0, 1)
  ghw3 = SelfDCoupling("selfDHwwcoupl", 0, 2)
  ghw4 = SelfDCoupling("selfDHwwcoupl", 0, 3)

  ghw1_prime = SelfDCoupling("selfDHwwcoupl", 0, 10)
  ghw1_prime2 = SelfDCoupling("selfDHwwcoupl", 0, 11)
  ghw1_prime3 = SelfDCoupling("selfDHwwcoupl", 0, 12)
  ghw1_prime4 = SelfDCoupling("selfDHwwcoupl", 0, 13)
  ghw1_prime5 = SelfDCoupling("selfDHwwcoupl", 0, 14)

  ghw2_prime = SelfDCoupling("selfDHwwcoupl", 0, 15)
  ghw2_prime2 = SelfDCoupling("selfDHwwcoupl", 0, 16)
  ghw2_prime3 = SelfDCoupling("selfDHwwcoupl", 0, 17)
  ghw2_prime4 = SelfDCoupling("selfDHwwcoupl", 0, 18)
  ghw2_prime5 = SelfDCoupling("selfDHwwcoupl", 0, 19)

  ghw3_prime = SelfDCoupling("selfDHwwcoupl", 0, 20)
  ghw3_prime2 = SelfDCoupling("selfDHwwcoupl", 0, 21)
  ghw3_prime3 = SelfDCoupling("selfDHwwcoupl", 0, 22)
  ghw3_prime4 = SelfDCoupling("selfDHwwcoupl", 0, 23)
  ghw3_prime5 = SelfDCoupling("selfDHwwcoupl", 0, 24)

  ghw4_prime = SelfDCoupling("selfDHwwcoupl", 0, 25)
  ghw4_prime2 = SelfDCoupling("selfDHwwcoupl", 0, 26)
  ghw4_prime3 = SelfDCoupling("selfDHwwcoupl", 0, 27)
  ghw4_prime4 = SelfDCoupling("selfDHwwcoupl", 0, 28)
  ghw4_prime5 = SelfDCoupling("selfDHwwcoupl", 0, 29)

  ghw1_prime6 = SelfDCoupling("selfDHwwcoupl", 0, 31)
  ghw1_prime7 = SelfDCoupling("selfDHwwcoupl", 0, 32)
  ghw2_prime6 = SelfDCoupling("selfDHwwcoupl", 0, 33)
  ghw2_prime7 = SelfDCoupling("selfDHwwcoupl", 0, 34)
  ghw3_prime6 = SelfDCoupling("selfDHwwcoupl", 0, 35)
  ghw3_prime7 = SelfDCoupling("selfDHwwcoupl", 0, 36)
  ghw4_prime6 = SelfDCoupling("selfDHwwcoupl", 0, 37)
  ghw4_prime7 = SelfDCoupling("selfDHwwcoupl", 0, 38)

  cw_q1sq = SelfDParameter("selfDHwwCLambda_qsq", 0, 0)
  Lambda_w11 = SelfDParameter("selfDHwwLambda_qsq", 0, 0)
  Lambda_w12 = SelfDParameter("selfDHwwLambda_qsq", 0, 1)
  Lambda_w13 = SelfDParameter("selfDHwwLambda_qsq", 0, 2)
  Lambda_w14 = SelfDParameter("selfDHwwLambda_qsq", 0, 3)

  cw_q2sq = SelfDParameter("selfDHwwCLambda_qsq", 0, 1)
  Lambda_w21 = SelfDParameter("selfDHwwLambda_qsq", 0, 4)
  Lambda_w22 = SelfDParameter("selfDHwwLambda_qsq", 0, 5)
  Lambda_w23 = SelfDParameter("selfDHwwLambda_qsq", 0, 6)
  Lambda_w24 = SelfDParameter("selfDHwwLambda_qsq", 0, 7)

  cw_q12sq = SelfDParameter("selfDHwwCLambda_qsq", 0, 2)
  Lambda_w01 = SelfDParameter("selfDHwwLambda_qsq", 0, 8)
  Lambda_w02 = SelfDParameter("selfDHwwLambda_qsq", 0, 9)
  Lambda_w03 = SelfDParameter("selfDHwwLambda_qsq", 0, 10)
  Lambda_w04 = SelfDParameter("selfDHwwLambda_qsq", 0, 11)

  kappa = SelfDCoupling("selfDHqqcoupl", 0)
  kappa_tilde = SelfDCoupling("selfDHqqcoupl", 1)

  zprime_qq_left = SelfDCoupling("selfDZqqcoupl", 0)
  zprime_qq_right = SelfDCoupling("selfDZqqcoupl", 1)
  zprime_zz_1 = SelfDCoupling("selfDZvvcoupl", 0)
  zprime_zz_2 = SelfDCoupling("selfDZvvcoupl", 1)

  graviton_qq_left = SelfDCoupling("selfDGqqcoupl", 0)
  graviton_qq_right = SelfDCoupling("selfDGqqcoupl", 1)

  a1 = SelfDCoupling("selfDGggcoupl", 0)
  a2 = SelfDCoupling("selfDGggcoupl", 1)
  a3 = SelfDCoupling("selfDGggcoupl", 2)
  a4 = SelfDCoupling("selfDGggcoupl", 3)
  a5 = SelfDCoupling("selfDGggcoupl", 4)

  b1 = SelfDCoupling("selfDGvvcoupl", 0)
  b2 = SelfDCoupling("selfDGvvcoupl", 1)
  b3 = SelfDCoupling("selfDGvvcoupl", 2)
  b4 = SelfDCoupling("selfDGvvcoupl", 3)
  b5 = SelfDCoupling("selfDGvvcoupl", 4)
  b6 = SelfDCoupling("selfDGvvcoupl", 5)
  b7 = SelfDCoupling("selfDGvvcoupl", 6)
  b8 = SelfDCoupling("selfDGvvcoupl", 7)
  b9 = SelfDCoupling("selfDGvvcoupl", 8)
  b10 = SelfDCoupling("selfDGvvcoupl", 9)



def SimpleParticleCollection_t(iterable=None):
  if iterable is None: return ROOT.SimpleParticleCollection_t()
  result = ROOT.SimpleParticleCollection_t()
  for _ in iterable:
    result.push_back(SimpleParticle_t(_))
  return result

def SimpleParticle_t(lineorid, pxortlv=None, py=None, pz=None, e=None):
  if pxortlv is py is pz is e is None:
    if isinstance(lineorid, basestring):
      lineorid = lineorid.split()
    if len(lineorid) == 13:
      id, status, mother1, mother2, color1, color2, px, py, pz, e, m, lifetime, spin = (f(_) for f, _ in zip((int, int, int, int, int, int, float, float, float, float, float, float, float), lineorid))
    elif len(lineorid) == 5:
      id, px, py, pz, e = (f(_) for f, _ in zip((int, float, float, float, float), lineorid))
    else:
      raise ValueError("len(lineorid) has to be 5 or 13, not {}".format(len(lineorid)))
  else:
    id = lineorid
    px = pxortlv

  if py is pz is e is None:
    tlv = pxortlv
  else:
    tlv = ROOT.TLorentzVector(px, py, pz, e)

  return ROOT.SimpleParticle_t(id, tlv)

if __name__ == "__main__":
  m = Mela()
  event1 = """
<event>
12  50   1.0000000E+00   1.2500000E+02   7.8125000E-03   1.2380607E-01
        2   -1    0    0  503    0  0.00000000000E+00  0.00000000000E+00  1.65430825479E+03  1.65430825479E+03  0.00000000000E+00 0.00000000000E+00  1.
       -1   -1    0    0    0  503  0.00000000000E+00  0.00000000000E+00 -1.42857195999E+01  1.42857195999E+01  0.00000000000E+00 0.00000000000E+00  1.
       24    2    1    2    0    0 -2.29473352103E+00 -1.04804828491E+02  4.95291431378E+02  5.12296652853E+02  7.83896718395E+01 0.00000000000E+00  1.
       25    2    1    2    0    0  2.29473352103E+00  1.04804828491E+02  1.14473110382E+03  1.15629732154E+03  1.24999511524E+02 0.00000000000E+00  1.
       14    1    3    3    0    0  4.42035961901E+00 -5.60456350211E+01  4.09886160671E+02  4.13723721213E+02  8.42936970218E-06 0.00000000000E+00  1.
      -13    1    3    3    0    0 -6.71509314004E+00 -4.87591934698E+01  8.54052707068E+01  9.85729316407E+01  1.05660000144E-01 0.00000000000E+00  1.
       23    2    4    4    0    0 -2.00748771644E+01  3.21702667586E+01  3.27018956548E+02  3.30034988785E+02  2.33188576920E+01 0.00000000000E+00  1.
       23    2    4    4    0    0  2.23696106855E+01  7.26345617324E+01  8.17712147272E+02  8.26262332755E+02  9.09950970840E+01 0.00000000000E+00  1.
      -11    1    7    7    0    0 -1.74223737299E+01  9.11950220870E+00  1.06644211152E+02  1.08442114510E+02  5.11001208360E-04 0.00000000000E+00  1.
       11    1    7    7    0    0 -2.65250343458E+00  2.30507645499E+01  2.20374745396E+02  2.21592874275E+02  5.10994690391E-04 0.00000000000E+00  1.
      -13    1    8    8    0    0  8.81223774828E+00  8.87930337607E+01  5.03683096793E+02  5.11525690007E+02  1.05660000328E-01 0.00000000000E+00  1.
       13    1    8    8    0    0  1.35573729372E+01 -1.61584720283E+01  3.14029050479E+02  3.14736642748E+02  1.05659999907E-01 0.00000000000E+00  1.
</event>
  """
  event2 = """
<event>
12  50   1.0000000E+00   1.2500000E+02   7.8125000E-03   1.2380607E-01
        1   -1    0    0  503    0  0.00000000000E+00  0.00000000000E+00  1.58591490197E+03  1.58591490197E+03  0.00000000000E+00 0.00000000000E+00  1.
       -1   -1    0    0    0  503  0.00000000000E+00  0.00000000000E+00 -8.99084923758E+00  8.99084923758E+00  0.00000000000E+00 0.00000000000E+00  1.
       23    2    1    2    0    0  4.31808951699E+01  1.18843550193E+01  8.22005355890E+02  8.28398612649E+02  9.24425698805E+01 0.00000000000E+00  1.
       25    2    1    2    0    0 -4.31808951699E+01 -1.18843550193E+01  7.54918696840E+02  7.66507138556E+02  1.25000508063E+02 0.00000000000E+00  1.
       11    1    3    3    0    0 -1.35803884002E+01 -5.28931958672E+00  5.41360784563E+02  5.41556924907E+02  5.11072900539E-04 0.00000000000E+00  1.
      -11    1    3    3    0    0  5.67612835701E+01  1.71736746060E+01  2.80644571326E+02  2.86841687743E+02  5.11012071458E-04 0.00000000000E+00  1.
       23    2    4    4    0    0 -2.43038338852E+01  5.06442605250E+00  2.48359236741E+02  2.53284239962E+02  4.30612469142E+01 0.00000000000E+00  1.
       23    2    4    4    0    0 -1.88770612847E+01 -1.69487810718E+01  5.06559460099E+02  5.13222898594E+02  7.84324703350E+01 0.00000000000E+00  1.
      -13    1    7    7    0    0 -3.25370809281E+01 -6.79837669312E+00  2.02354268485E+02  2.05066186143E+02  1.05659999991E-01 0.00000000000E+00  1.
       13    1    7    7    0    0  8.23324704291E+00  1.18628027456E+01  4.60049682560E+01  4.82180538193E+01  1.05659999989E-01 0.00000000000E+00  1.
      -13    1    8    8    0    0  4.59433181687E+00 -3.18015647781E+01  4.39027117172E+02  4.40201395027E+02  1.05659999655E-01 0.00000000000E+00  1.
       13    1    8    8    0    0 -2.34713931016E+01  1.48527837063E+01  6.75323429266E+01  7.30215035668E+01  1.05660000010E-01 0.00000000000E+00  1.
</event>
  """
  event3 = """
<event>
11  60   1.0000000E+00   1.2500000E+02   7.8125000E-03   1.2380607E-01
        1   -1    0    0  501    0  0.00000000000E+00  0.00000000000E+00  8.38349783822E+01  8.38349783822E+01  0.00000000000E+00 0.00000000000E+00  1.
        2   -1    0    0  502    0  0.00000000000E+00  0.00000000000E+00 -8.69647303563E+02  8.69647303563E+02  0.00000000000E+00 0.00000000000E+00  1.
        4    1    1    2  501    0  4.93534233194E+01 -7.45486758049E+00  2.54822242213E+01  5.60417629563E+01  0.00000000000E+00 0.00000000000E+00  1.
        1    1    1    2  502    0 -4.29482465415E+01  4.39907893858E+01 -7.51475061906E+02  7.53985749267E+02  0.00000000000E+00 0.00000000000E+00  1.
       25    2    1    2    0    0 -6.40517677787E+00 -3.65359218053E+01 -5.98194874970E+01  1.43454769722E+02  1.25000000000E+02 0.00000000000E+00  1.
       23    2    5    5    0    0 -1.61638014503E+01 -3.55963825472E+01 -2.51394501445E+01  1.03431837860E+02  9.24001201399E+01 0.00000000000E+00  1.
       23    2    5    5    0    0  9.75862467247E+00 -9.39539258134E-01 -3.46800373525E+01  4.00229318615E+01  1.74073718437E+01 0.00000000000E+00  1.
      -11    1    6    6    0    0  3.37109433312E+01 -2.97615359833E+01  4.38251799494E+00  4.51816687231E+01  5.11000134768E-04 0.00000000000E+00  1.
       11    1    6    6    0    0 -4.98747447816E+01 -5.83484656388E+00 -2.95219681394E+01  5.82501691374E+01  5.11001208360E-04 0.00000000000E+00  1.
      -13    1    7    7    0    0  1.46596263059E+01  5.33582780943E-01 -2.31337995488E+01  2.73929406894E+01  1.05660000000E-01 0.00000000000E+00  1.
       13    1    7    7    0    0 -4.90100163341E+00 -1.47312203908E+00 -1.15462378037E+01  1.26299911721E+01  1.05660000000E-01 0.00000000000E+00  1.
</event>
  """

  daughters = """
  11 -71.89077865749999319 30.50307494750000004 -47.20025487019999844 91.25012710839999386
  -11 -25.13451734110000046 -18.85931656560000036 -81.42283896300000379 87.27597887359999618
  11 -51.80274100940000181 1.64269040236999997 -41.79162596869999646 66.57899375339999892
  -11 -93.72924763700000028 39.45060783929999815 -92.98363978320000456 137.79506373300000632
  """
  associated = """
  -11 211.33318543799998679 -14.90577872979999974 3.74371777679000006 211.89127619999999297
  12 31.22409920730000010 -37.83127789369999761 1.23465418111000003 49.06805813689999951
  """
  mothers = """
  -1 0.00000000000000000 0.00000000000000000 192.71975508899998886 192.71975508899998886
  2 0.00000000000000000 0.00000000000000000 -451.13974271600000066 451.13974271600000066
  """

  m.setInputEvent(
                  SimpleParticleCollection_t(line.split() for line in daughters.split("\n") if line.split()),
                  SimpleParticleCollection_t(line.split() for line in associated.split("\n") if line.split()),
                  SimpleParticleCollection_t(line.split() for line in mothers.split("\n") if line.split()),
                  True,
                 )
  #or:
  #m.setInputEvent_fromLHE(event1)

  couplings = (
               (1, 0, 0, 0),
               (0, 1, 0, 0),
               (0, 0, 1, 0),
               (0, 0, 0, 1),
               (1, 1.663195, 0, 0),
               (1, 0, 2.55502, 0),
               (1, 0, 0, -12110.20),
              )
  for _ in couplings:
    m.ghz1, m.ghz2, m.ghz4, m.ghz1_prime2 = _
    m.setProcess(TVar.SelfDefine_spin0, TVar.JHUGen, TVar.Lep_WH)
    prod = m.computeProdP(False)
    m.ghz1, m.ghz2, m.ghz4, m.ghz1_prime2 = _
    m.setProcess(TVar.SelfDefine_spin0, TVar.JHUGen, TVar.ZZINDEPENDENT)
    dec = m.computeP(False)
    print prod, dec, prod*dec

  print m.computeDecayAngles()
  print "propagator:"
  print "   BW:", m.getXPropagator(TVar.FixedWidth)
  print "  CPS:", m.getXPropagator(TVar.CPS)
