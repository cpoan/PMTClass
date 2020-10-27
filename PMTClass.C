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
        this->LG_charge_hists[ch] = new TH1D(TString::Format("LG_CH%i_PMT%i_HV%i",ch,pmtName[ch],pmtHV[ch]),TString::Format("LG CH%i PMT%i HV%i;Charges[QDC unit];Counts",ch,pmtName[ch],pmtHV[ch]),1000,0,1000);
        this->HG_charge_hists[ch] = new TH1D(TString::Format("HG_CH%i_PMT%i_HV%i",ch,pmtName[ch],pmtHV[ch]),TString::Format("HG CH%i PMT%i HV%i;Charges[QDC unit];Counts",ch,pmtName[ch],pmtHV[ch]),1000,0,1000);
    }

    ifstream dataOutput(filename.c_str());
    string str_data;
    while(!dataOutput.eof()){
        // Read data
        dataOutput>>str_data;
        //cout<<str_data<<"\n";
        
        // Judge data 
        if(str_data[1]!='0'&&str_data[1]!='8')
            continue;

        // Charges calculation
        int charges  = strtol(&(str_data[5]),NULL,16);

        // HG or LG judgement, channel judgement
        string str_ChannelRG[2];
        str_ChannelRG[1]+=str_data[3];
        str_ChannelRG[0]+=str_data[2];

        int int_ChannelRG = strtol(str_ChannelRG[1].c_str(),NULL,16);
        int_ChannelRG/=2;

        int RG = int_ChannelRG%2;

        int Channel = int_ChannelRG/2 + (strtol(str_ChannelRG[0].c_str(),NULL,16)%2)*4;
        //cout << "RG = " << RG << ",Channel = " << Channel << ", Charges = " << charges << "\n";

        // Filling histograms based on channel and HG/LG
        if(RG==0)
            HG_charge_hists[Channel]->Fill(charges);
        else
            LG_charge_hists[Channel]->Fill(charges);
    }
    
}

PMTClass::~PMTClass(){
    for(int ch = 0;ch<8;ch++){
//        delete this->LG_charge_hists[ch];
//        delete this->HG_charge_hists[ch];
    }
}
