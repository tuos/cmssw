// #include "TFile.h"
// #include "TDirectory.h"
// #include "TCanvas.h"
// #include "TH1D.h"
// #include "TProfile.h"

/**
 * This uncompiled macro draws the resolution histograms superimposed on the same canvas for the various quantities. <br>
 * It draws the reco-gen derived resolution (true resolution), those from the resolution functions from 0_MuScleFit.root
 * and those from the resolution functions from 1_MuScleFit.root for a comparison of the change before and after the fit.
 */

draw( const TString & resolName, TDirectory * resolDir,
      const TString & functionResolName, TDirectory * functionResolDir,
      const TString & canvasName, TFile * outputFile,
      const TString & title = "", const TString & xAxisTitle = "", const TString & yAxisTitle = "", double Ymax,
      TDirectory * functionResolDirAfter = 0, TDirectory * resolDirAfter = 0 )
{
  TProfile * functionResolVSpt = (TProfile*) functionResolDir->Get(functionResolName);
  TProfile * functionResolVsptAfter = 0;
  if( functionResolDirAfter != 0 ) functionResolVSptAfter = (TProfile*) functionResolDirAfter->Get(functionResolName);
  TH1D * resolVSpt = (TH1D*) resolDir->Get(resolName);
  TH1D * resolVSptAfter = 0;
  if( resolDirAfter != 0 ) {
    resolVSptAfter = (TH1D*) resolDirAfter->Get(resolName);
  }

  TString resolVSptName("from reco-gen comparison");
  TCanvas * c = new TCanvas(canvasName, canvasName, 1000, 800);
  c->cd();
  TLegend * legend = new TLegend(0.7,0.71,0.98,1.);
  legend->SetTextSize(0.02);
  legend->SetFillColor(0); // Have a white background
  if( resolDirAfter == 0 ) legend->AddEntry(resolVSpt, resolVSptName);
  else legend->AddEntry(resolVSpt, resolVSptName+" before");
  resolVSpt->SetTitle(title);
  resolVSpt->Draw();
  resolVSpt->GetXaxis()->SetTitle(xAxisTitle);
  resolVSpt->GetYaxis()->SetTitle(yAxisTitle);
  resolVSpt->SetMaximum(Ymax);
  //  resolVSpt->SetMinimum(-Ymax/2);
  resolVSpt->SetMinimum(0);
  resolVSpt->Draw();
  if( resolDirAfter != 0 ) {
    resolVSptAfter->SetLineColor(kGreen);
    legend->AddEntry(resolVSptAfter, resolVSptName + " after");
    resolVSptAfter->Draw("SAME");
  }

  TString functionLegendName("from resolution function");
  TString functionLegendNameAfter;
  functionResolVSpt->SetMarkerColor(kRed);
  functionResolVSpt->SetLineColor(kRed);
  if( functionResolDirAfter != 0 ) {
    functionLegendNameAfter = functionLegendName + " after";
    functionLegendName += " before";
    functionResolVSptAfter->SetMarkerColor(kBlue);
    functionResolVSptAfter->SetLineColor(kBlue);
  }
  legend->AddEntry(functionResolVSpt, functionLegendName);
  functionResolVSpt->Draw("same");

  if( functionResolDirAfter != 0 ) {
    legend->AddEntry(functionResolVSptAfter, functionLegendNameAfter);
    functionResolVSptAfter->Draw("same");
  }

  legend->Draw("same");
  // c->Draw();
  outputFile->cd();
  c->Write();
}

/**
 * This macro compares the resolutions found with the resolution functions with those
 * obtained from recMu-genMu comparison in MuScleFit.
 * The true resolutions are writted in the "redrawed.root" file by the ResolDraw.cc macro.
 */
void ResolCompare(const TString & stringNumBefore = "0", const TString & stringNumAfter = "1") {

  // Remove the stat box
  gStyle->SetOptStat(0);

  TFile * outputFile = new TFile("ComparedResol.root", "RECREATE");

  TFile * resolFileBefore = new TFile("redrawed_"+stringNumBefore+".root", "READ");
  TFile * resolFileAfter = 0;
  resolFileAfter = new TFile("redrawed_"+stringNumAfter+".root", "READ");
  TFile * functionResolFileBefore = new TFile(stringNumBefore+"_MuScleFit.root", "READ");
  TFile * functionResolFileAfter = new TFile(stringNumAfter+"_MuScleFit.root", "READ");

  TDirectory * resolDirBefore = 0;
  TDirectory * resolDirAfter = 0;
  TDirectory * functionResolDirBefore = 0;
  TDirectory * functionResolDirAfter = 0;


  // SigmaMass/Mass
  // --------------
  resolDirBefore = (TDirectory*) resolFileBefore->Get("DeltaMassOverGenMassVsPt");
  if( resolFileAfter == 0 ) resolDirAfter = 0;
  else resolDirAfter = (TDirectory*) resolFileAfter->Get("DeltaMassOverGenMassVsPt");
  functionResolDirBefore = (TDirectory*) functionResolFileBefore->Get("hFunctionResolMassVSMu");
  functionResolDirAfter = (TDirectory*) functionResolFileAfter->Get("hFunctionResolMassVSMu");
  // Vs Pt
  draw("DeltaMassOverGenMassVsPt_resol", resolDirBefore,
       "hFunctionResolMassVSMu_ResoVSPt_prof", functionResolDirBefore,
       "massResolVSpt", outputFile,
       "resolution on mass vs pt",
       "pt(GeV)", "#sigmaM/M",0.15,
       functionResolDirAfter, resolDirAfter );
  // VsEta
  resolDirBefore = (TDirectory*) resolFileBefore->Get("DeltaMassOverGenMassVsEta");
  if( resolFileAfter == 0 ) resolDirAfter = 0;
  else resolDirAfter = (TDirectory*) resolFileAfter->Get("DeltaMassOverGenMassVsEta");
  draw("DeltaMassOverGenMassVsEta_resol", resolDirBefore,
       "hFunctionResolMassVSMu_ResoVSEta_prof", functionResolDirBefore,
       "massResolVSeta", outputFile,
       "resolution on mass vs eta",
       "eta", "#sigmaM/M",0.09,
       functionResolDirAfter, resolDirAfter );


  // sigmaPt/Pt
  // ----------
  resolDirBefore = (TDirectory*) resolFileBefore->Get("hResolPtGenVSMu");
  if( resolFileAfter == 0 ) resolDirAfter = 0;
  else resolDirAfter = (TDirectory*) resolFileAfter->Get("hResolPtGenVSMu");
  functionResolDirBefore = (TDirectory*) functionResolFileBefore->Get("hFunctionResolPt");
  functionResolDirAfter = (TDirectory*) functionResolFileAfter->Get("hFunctionResolPt");

  //=====> All
  // VS Pt
  draw("hResolPtGenVSMu_ResoVSPt_resol", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_prof", functionResolDirBefore,
       "resolPtVSpt", outputFile,
       "resolution on pt vs pt",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );
  // VS Pt RMS
  draw("hResolPtGenVSMu_ResoVSPt_resolRMS", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_prof", functionResolDirBefore,
       "resolPtVSptRMS", outputFile,
       "resolution on pt vs pt",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );

  //=====> Barrel
  // VS Pt
  draw("hResolPtGenVSMu_ResoVSPt_Bar_resol", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Bar_prof", functionResolDirBefore,
       "resolPtVSptBar", outputFile,
       "resolution on pt vs pt, barrel",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );
  // VS Pt RMS
  draw("hResolPtGenVSMu_ResoVSPt_Bar_resolRMS", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Bar_prof", functionResolDirBefore,
       "resolPtVSptBarRMS", outputFile,
       "resolution on pt vs pt, barrel",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );

  //=====> Endcap 1
  // VS Pt
  draw("hResolPtGenVSMu_ResoVSPt_Endc_1.7_resol", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Endc_1.7_prof", functionResolDirBefore,
       "resolPtVSptEndc_1.7", outputFile,
       "resolution on pt vs pt, endcap",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );
  // VS Pt RMS
  draw("hResolPtGenVSMu_ResoVSPt_Endc_1.7_resolRMS", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Endc_1.7_prof", functionResolDirBefore,
       "resolPtVSptEndc1.7RMS", outputFile,
       "resolution on pt vs pt, endcap",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );

  //=====> Endcap 2
  // VS Pt
  draw("hResolPtGenVSMu_ResoVSPt_Endc_2.0_resol", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Endc_2.0_prof", functionResolDirBefore,
       "resolPtVSptEndc2.0", outputFile,
       "resolution on pt vs pt, endcap",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );
  // VS Pt RMS
  draw("hResolPtGenVSMu_ResoVSPt_Endc_2.0_resolRMS", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Endc_2.0_prof", functionResolDirBefore,
       "resolPtVSptEndc2.0RMS", outputFile,
       "resolution on pt vs pt, endcap",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );

  //=====> Endcap 3
  // VS Pt
  draw("hResolPtGenVSMu_ResoVSPt_Endc_2.4_resol", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Endc_2.4_prof", functionResolDirBefore,
       "resolPtVSptEndc2.4", outputFile,
       "resolution on pt vs pt, endcap",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );
  // VS Pt RMS
  draw("hResolPtGenVSMu_ResoVSPt_Endc_2.4_resolRMS", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Endc_2.4_prof", functionResolDirBefore,
       "resolPtVSptEndc2.4RMS", outputFile,
       "resolution on pt vs pt, endcap",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );


  //=====> overlap
  // VS Pt
  draw("hResolPtGenVSMu_ResoVSPt_Ovlap_resol", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Ovlap_prof", functionResolDirBefore,
       "resolPtVSptOvlap", outputFile,
       "resolution on pt vs pt, overlap",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );
  // VS Pt RMS
  draw("hResolPtGenVSMu_ResoVSPt_Ovlap_resolRMS", resolDirBefore,
       "hFunctionResolPt_ResoVSPt_Ovlap_prof", functionResolDirBefore,
       "resolPtVSptOvlapRMS", outputFile,
       "resolution on pt vs pt",
       "pt(GeV)", "#sigmapt/pt",0.09,
       functionResolDirAfter, resolDirAfter );

  // VS Eta
  draw("hResolPtGenVSMu_ResoVSEta_resol", resolDirBefore,
       "hFunctionResolPt_ResoVSEta_prof", functionResolDirBefore,
       "resolPtVSeta", outputFile,
       "resolution on pt vs #eta",
       "#eta", "#sigmapt/pt",0.15,
       functionResolDirAfter, resolDirAfter );
  // VS Eta RMS
  draw("hResolPtGenVSMu_ResoVSEta_resolRMS", resolDirBefore,
       "hFunctionResolPt_ResoVSEta_prof", functionResolDirBefore,
       "resolPtVSetaRMS", outputFile,
       "resolution on pt vs #eta",
       "#eta", "#sigmapt/pt",0.15,
       functionResolDirAfter, resolDirAfter );

  // sigmaCotgTheta
  // --------------
  resolDirBefore = (TDirectory*) resolFileBefore->Get("hResolCotgThetaGenVSMu");
  if( resolFileAfter == 0 ) resolDirAfter = 0;
  else resolDirAfter = (TDirectory*) resolFileAfter->Get("hResolCotgThetaGenVSMu");
  functionResolDirBefore = (TDirectory*) functionResolFileBefore->Get("hFunctionResolCotgTheta");
  functionResolDirAfter = (TDirectory*) functionResolFileAfter->Get("hFunctionResolCotgTheta");
  // VS Pt
  draw("hResolCotgThetaGenVSMu_ResoVSPt_resol", resolDirBefore,
       "hFunctionResolCotgTheta_ResoVSPt_prof", functionResolDirBefore,
       "resolCotgThetaVSpt", outputFile,
       "resolution on cotg(#theta) vs pt",
       "pt(GeV)", "#sigmacotg(#theta)",0.01,
       functionResolDirAfter, resolDirAfter );
  // VS Eta
  draw("hResolCotgThetaGenVSMu_ResoVSEta_resol", resolDirBefore,
       "hFunctionResolCotgTheta_ResoVSEta_prof", functionResolDirBefore,
       "resolCotgThetaVSeta", outputFile,
       "resolution on cotg(#theta) vs #eta",
       "#eta", "#sigmacotg(#theta)",0.01,
       functionResolDirAfter, resolDirAfter );
  // sigmaPhi
  // --------
  resolDirBefore = (TDirectory*) resolFileBefore->Get("hResolPhiGenVSMu");
  if( resolFileAfter == 0 ) resolDirAfter = 0;
  else resolDirAfter = (TDirectory*) resolFileAfter->Get("hResolPhiGenVSMu");
  functionResolDirBefore = (TDirectory*) functionResolFileBefore->Get("hFunctionResolPhi");
  functionResolDirAfter = (TDirectory*) functionResolFileAfter->Get("hFunctionResolPhi");
  // VS Pt
  draw("hResolPhiGenVSMu_ResoVSPt_resol", resolDirBefore,
       "hFunctionResolPhi_ResoVSPt_prof", functionResolDirBefore,
       "resolPhiVSpt", outputFile,
       "resolution on #phi vs pt",
       "pt(GeV)", "#sigma#phi",0.01,
       functionResolDirAfter, resolDirAfter );
  // VS Eta
  draw("hResolPhiGenVSMu_ResoVSEta_resol", resolDirBefore,
       "hFunctionResolPhi_ResoVSEta_prof", functionResolDirBefore,
       "resolPhiVSeta", outputFile,
       "resolution on #phi vs #eta",
       "#eta", "#sigma#phi",0.01,
       functionResolDirAfter, resolDirAfter );
}
