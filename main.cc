#include "PMTClass.h"
int main(){
    vector<int> pmtName{0,1,74548,3,4,5,6,7};
    vector<int> pmtHV{0,0,1300,0,0,0,0,0};
    PMTClass("./dataFile/74548_HV1300_qdcCH2.txt",pmtName,pmtHV);
    return 1;
}
