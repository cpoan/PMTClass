#include "TMath.h"
#include "FitFunction.h"
using std::abs;
double I_GnxE(double x,int n,double Q0,double Q1,double sigma0,double sigma1,double alpha) {
	double Qn = Q0+n*Q1;
	double sigma_n = sqrt(pow(sigma0,2)+n*pow(sigma1,2));
	double erf1 = TMath::Erf(abs(Q0-Qn-sigma_n*sigma_n*alpha)/(sigma_n*sqrt(2)));
	double erf2 = TMath::Erf(abs(x-Qn-sigma_n*sigma_n*alpha)/(sigma_n*sqrt(2)));
	double sign = TMath::Sign(1,x-Qn-sigma_n*sigma_n*alpha);
	double aexp = 0.5 * abs(alpha) * exp(-1*alpha*abs(x-Qn-sigma_n*sigma_n*alpha));
	return aexp*(erf1+sign*erf2);
}

double Gn(double x,int n,double Q0,double Q1,double sigma0,double sigma1) {
	double Qn = Q0+n*Q1;
	double sigma_n = sqrt(pow(sigma0,2)+n*pow(sigma1,2));
	return TMath::Gaus(x,Qn,sigma_n,kTRUE);
}

double Sreal(double x,double Q0,double Q1,double sigma0,double sigma1,double alpha,double w,double mu) {
	double calculation = 0;
	for(int i = 0;i < 15;i++) {
		calculation += TMath::PoissonI(i,mu)*((1-w)*Gn(x,i,Q0,Q1,sigma0,sigma1)+w*I_GnxE(x,i,Q0,Q1,sigma0,sigma1,alpha));
	}
	return calculation;
}
