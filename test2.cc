#include "PMTClass.C"
#include "FitFunction.C"
double ExtractGain(TH1D*,TF1*);

void test2(){
    gStyle->SetOptFit(1);

    string fileName[5] = {
        "./dataFile/74548_HV1100_qdcCH2.txt",
        "./dataFile/74548_HV1150_qdcCH2.txt",
        "./dataFile/74548_HV1200_qdcCH2.txt",
        "./dataFile/74548_HV1250_qdcCH2.txt",
        "./dataFile/74548_HV1300_qdcCH2.txt"
    };
    vector<int> pmtName{0,1,74548,3,4,5,6,7};
    int CH2_HV[5] = {1100,1150,1200,1250,1300};
    vector<int> pmtHV[5];
    for(int i = 0;i<5;i++){
        pmtHV[i].resize(8);
        pmtHV[i][2] = CH2_HV[i];
    }

    vector<PMTClass> data;
    for(int i = 0;i<5;i++)
        data.push_back(PMTClass(fileName[i],pmtName,pmtHV[i]));

    TGraphErrors* GainCurve = new TGraphErrors();
    double Gain[5];
    TCanvas* c = new TCanvas("c","c",2400,900);
    c->Divide(3,2);
    TF1* array_f[5];
    for(int i = 0;i<5;i++){
        array_f[i] = new TF1(TString::Format("f%i",i),"[7]*Sreal(x,[0],[1],[2],[3],[4],[5],[6])",0,1000);
        c->cd(i+1);
        Gain[i] = ExtractGain(data[i].LG_charge_hists[2],array_f[i]);
        GainCurve->SetPoint(i,CH2_HV[i],Gain[i]);
    }
    
    gStyle->SetOptFit(0);
    TCanvas* c1 = new TCanvas("c2","c2",1600,900);

    GainCurve->SetTitle("PMT 74548 Gain versus HV;HV;Gain");
    GainCurve->GetXaxis()->CenterTitle(kTRUE);
    GainCurve->GetYaxis()->CenterTitle(kTRUE);
    GainCurve->SetMarkerStyle(8);
    GainCurve->SetMarkerSize(1.5);
    GainCurve->SetMarkerColor(kBlue);
    GainCurve->GetYaxis()->SetMoreLogLabels();

    GainCurve->Fit("expo");
    GainCurve->GetFunction("expo")->SetLineColor(kBlue);
    GainCurve->GetFunction("expo")->SetLineStyle(3);

    c1->cd();
    gPad->SetLogy();
    gPad->SetGrid();
    GainCurve->Draw("ap");
}

double ExtractGain(TH1D* h, TF1* f){
    f->SetParNames("Q_{0}","Q_{1}","#sigma_{0}","#sigma_{1}","#alpha","w","#mu","N");
    f->SetParameters(h->GetMaximumBin(),20,3,10,0.1,0.01,0.10,h->GetEntries());
    f->SetNpx(1000);
    h->Fit(f);
    return f->GetParameter(1)*25e-15/1.6e-19;
}
