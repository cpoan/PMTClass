#include <vector>
#include <string>

#include "FitFunction.h"

#include "TH1D.h"
using std::vector;
using std::string;

class PMTClass {
    public:
        vector<TH1D*> LG_charge_hists;
        vector<TH1D*> HG_charge_hists;

        PMTClass(string filename, vector<int> pmtname, vector<int> pmtHV);
 //       ~PMTClass();
};
