#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TStyle.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void getFlux()
{

   TF1 *f0 = new TF1("f0","9.6e-6*pow(1.0e3*x,-0.41)",0,100);

   ifstream myfile;
   myfile.open ("FermiFluxTableCut.txt");
   float upflux[300],E[300],DE[300],EFlux[300];

   int m=0;
   while (!myfile.eof()) {
     myfile >> E[m] >> upflux[m];
     m++;
   }

   for(int k=0;k<m;k++) {if(E[m]!=0) DE[k]=E[k+1]-E[k];EFlux[k]=E[k]*E[k]*upflux[k]*1e-9/DE[k];/*std::cout << "e-flux" << EFlux[k] << "DE " << DE[k] << " E " << E[k] << std::endl;*/}

   TGraph *l = new TGraph(m,E,EFlux);

   double bins[50] = { 0.1, 0.11513954, 0.13257114, 0.1526418, 0.17575106, 0.20235896, 0.23299518, 0.26826958, 0.30888436, 0.35564803, 0.40949151, 0.47148664, 0.54286754, 0.62505519, 0.71968567\
                     , 0.82864277, 0.95409548, 1.09854114, 1.26485522, 1.45634848, 1.67683294, 1.93069773, 2.22299648, 2.55954792, 2.9470517, 3.39322177, 3.90693994, 4.49843267, 5.17947468, \
                       5.96362332, 6.86648845, 7.90604321, 9.10298178, 10.48113134, 12.06792641, 13.89495494, 15.9985872, 18.42069969, 21.20950888, 24.42053095, 28.11768698, 32.37457543, 37.2759372, \
                       42.9193426, 49.41713361, 56.89866029, 65.51285569, 75.43120063, 86.85113738, 100.0};

   float mG[10]={25.5167,40.1772,58.9631,63.3216,71.9567,78.0881,83.0635,90.7892,96.8327};
   float tau_G[10]={25.2254,24.1564,23.3798,22.9731,22.6319,22.3114,21.9915,21.4196,20.7776}; 
   float Gnu[10]={0.00016856542274355113,0.0010993598140324335,2.3220081699144752e-06,8.311288960716904e-05,0.00012056237077877326,0.00011474688149140103,9.727929446923651e-05,3.438426110656486e-06,1.8326912577997526e-06};

   TFile *f[10];
   TH1F *h[10];

   TLegend *l1=new TLegend(0.65,0.2,0.87,0.6);

   std::stringstream filename,histname;

   TH1F *g[10];
   TH1F *gClone[10];

   TCanvas *c=new TCanvas("c","",1000,1000,1000,1000);
   c->Draw();

   gStyle->SetOptStat(0);

   for (int i=0;i<9;i++)
   {
       std::cout << " Now working on the pint " << mG[i] << " " << tau_G[i] << " " << Gnu[i] << std::endl;
       filename << "outputs/combined_" << mG[i] << ".root";

       histname << "h_" << i;

       //std::cout << filename.str().c_str() << std::endl;

       f[i] = TFile::Open(filename.str().c_str());

       h[i]=(TH1F*)f[i]->Get("h2_12");

       g[i]=new TH1F(histname.str().c_str(),"",49,bins);
       //g[i]=new TH1F(histname.str().c_str(),"",100,0,100);
       g[i]->GetYaxis()->SetTitleOffset(1.3);
       g[i]->GetXaxis()->SetTitle("E_{#gamma} GeV");
       g[i]->GetYaxis()->SetTitle("E^{2} d#Phi_{#gamma}/dE (GeV cm^{-2} s^{-1})");

       histname.str("");
       histname << "g_"  <<i;
       gClone[i]=new TH1F(histname.str().c_str(),"",49,bins);
       //gClone[i]=new TH1F(histname.str().c_str(),"",100,0,100);

       float tauG = pow(10,tau_G[i]);///Gnu[i];
       std::cout << " tauG " << tauG << std::endl;

       double fluxFactor = (1.9e23)/(9.314*4*3.14*mG[i]*tauG);

       float lastBinContent = 0;
       int lastBin = 0;

       for(int j=0; j<h[i]->GetXaxis()->GetNbins();j++)
       {
          if(h[i]->GetBinContent(j) != 0) {
             g[i]->SetBinContent(j,fluxFactor*h[i]->GetBinContent(j)/h[i]->GetBinWidth(j));
             std::cout << fluxFactor << " " << h[i]->GetBinContent(j) << " bin center " << h[i]->GetBinCenter(j) << " bin number " << j << std::endl;
             lastBinContent = g[i]->GetBinContent(j);
             lastBin = j;
             std::cout << " last bin content " << g[i]->GetBinContent(j) << " last bin " << lastBin << std::endl;
          }
       }

       gClone[i]->Fill(bins[lastBin-1],lastBinContent);

       //g[i]->SetMarkerStyle(7);
       //g[i]->SetMarkerColor(i+1);
       g[i]->SetLineColor(i+1);
       g[i]->SetLineWidth(2);
       g[i]->GetYaxis()->SetRangeUser(1e-12,1e-1);
       gClone[i]->SetMarkerStyle(29);
       gClone[i]->SetMarkerColor(i+1);
       gClone[i]->SetMarkerSize(2);
       if(i==0) g[i]->Draw("l");
       else g[i]->Draw("l:same");
       gClone[i]->Draw("p:same");
       f0->Draw("lp:same");
       l->SetLineWidth(2);
       l->SetLineColor(4);
       l->Draw("l:same");

       histname.str("");
       
       histname << "m_{G} = " << mG[i];

       l1->AddEntry(gClone[i],histname.str().c_str(),"p");

       filename.str("");
       histname.str("");

       
       
   }

   l1->AddEntry(f0,"Continuum bound","l");
   l1->AddEntry(l,"Line search limit","l");

   l1->Draw();

   c->SetLogy();
   c->SaveAs("outputs/photonflux_mG.png");   
}
