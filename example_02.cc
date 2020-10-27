#include "PMTClass.C"
#include "FitFunction.C"
double ExtractGain(TH1D*,TF1*);

void example_02(){
    // Change the default setting of plotting fitResults or not.
    gStyle->SetOptFit(1);

    // Preparing the informations for PMTClass, for exampple like file name of data, index of PMT, high voltage you set.
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

    // Creating a vector, which can save multiple files, for example data file 1,2,3,4,5 will be in the data[0],data[1],data[2].data[3].data[4].
    vector<PMTClass> data;
    for(int i = 0;i<5;i++)
        data.push_back(PMTClass(fileName[i],pmtName,pmtHV[i]));// Processing data in this line.
    
    // TGraphErrors is a class that can save multiple x-y points with error bar, in our case is HV-Gain.
    TGraphErrors* GainCurve = new TGraphErrors();

    // Array of double for saving Gain, 5 data files = 5 Gains.
    double Gain[5];

    // Create canvas for the previous graph to plot on.
    // and devude this canvas to 3x2 (horizontal x vertical)
    TCanvas* c = new TCanvas("c","c",2400,900);
    c->Divide(3,2);

    TF1* array_f[5];// Array of 5 TF1 to fit 5 CH2 charges spectrum.
    for(int i = 0;i<5;i++){
        array_f[i] = new TF1(TString::Format("f%i",i),"[7]*Sreal(x,[0],[1],[2],[3],[4],[5],[6])",0,1000);
        c->cd(i+1);
        Gain[i] = ExtractGain( data[i].LG_charge_hists[2], array_f[i]);// Fitting was done in this function, and this function will return the gain value from fitting.
        GainCurve->SetPoint(i,CH2_HV[i],Gain[i]);// Set x-y value, the first "i" is the index of this point.
    }
    
    gStyle->SetOptFit(0);
    TCanvas* c1 = new TCanvas("c2","c2",1600,900);

    GainCurve->SetTitle("PMT 74548 Gain versus HV;HV;Gain");// SetTitle("Title; X-title; Y-title")
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
    f->SetNpx(1000);// Horizontal resolution of drawing this formula.
    h->Fit(f);
    return f->GetParameter(1)*25e-15/1.6e-19;
}
