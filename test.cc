#include "PMTClass.C"
#include "FitFunction.C"
void test(){
    gStyle->SetOptFit(1);

    vector<int> pmtName{0,1,74548,3,4,5,6,7};
    vector<int> pmtHV{0,0,1300,0,0,0,0,0};
    PMTClass data1("./dataFile/74548_HV1300_qdcCH2.txt",pmtName,pmtHV);

    TCanvas* c = new TCanvas("c","c",3200,900);
    c->Divide(2,1);
    for(int ch = 0;ch<8;ch++){
        data1.LG_charge_hists[ch]->SetLineColor(ch+1);
        data1.HG_charge_hists[ch]->SetLineColor(ch+1);
        if(ch==0){
            c->cd(1);
            data1.LG_charge_hists[ch]->Draw();
            c->cd(2);
            data1.HG_charge_hists[ch]->Draw();
        }
        else{
            c->cd(1);
            data1.LG_charge_hists[ch]->Draw("SAME");
            c->cd(2);
            data1.HG_charge_hists[ch]->Draw("SAME");
        }
    }
    c->SaveAs("test.png");
    

    TH1D* h = data1.LG_charge_hists[2];
    TF1* f = new TF1("f","[7]*Sreal(x,[0],[1],[2],[3],[4],[5],[6])",0,1000);
    f->SetParNames("Q_{0}","Q_{1}","#sigma_{0}","#sigma_{1}","#alpha","w","#mu","N");
    f->SetParameters(h->GetMaximumBin(),20,3,10,0.1,0.01,0.10,h->GetEntries());
    TCanvas* c1 = new TCanvas("c1","c1",1600,900);
    c1->cd();
    f->SetNpx(1000);
    h->Fit(f);

    c1->SaveAs("fitExample.png");
}
