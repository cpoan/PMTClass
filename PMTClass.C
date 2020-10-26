#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TFile.h"
#include "TString.h"

#include "PMTClass.h"

using std::cout;
using std::ifstream;
PMTClass::PMTClass(string filename,vector<int> pmtName,vector<int> pmtHV){

    this->LG_charge_hists.resize(8); 
    this->HG_charge_hists.resize(8); 

    for(int ch = 0;ch<8;ch++){
        this->LG_charge_hists[ch] = new TH1D(TString::Format("LG_CH%i",ch),TString::Format("LG CH%i PMT%i HV%i",ch,pmtName[ch],pmtHV[ch]),1000,0,1000);
        this->HG_charge_hists[ch] = new TH1D(TString::Format("HG_CH%i",ch),TString::Format("HG CH%i PMT%i HV%i",ch,pmtName[ch],pmtHV[ch]),1000,0,1000);
    }

    ifstream dataOutput(filename.c_str());
    string str_data;
    while(!dataOutput.eof()){
        dataOutput>>str_data;
        cout<<str_data<<"\n";
    }
    
}

//~PMTClass(){
//    for(int ch = 0;ch<8;ch++){
//        delete this.LG_charge_hists[ch];
//        delete this.HG_charge_hists[ch];
//    }
//}
