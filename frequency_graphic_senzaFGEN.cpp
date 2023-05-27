
void setStyle_frequenze_senzaFGEN() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico_frequenze_senzaFGEN() {
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(
      "Gain in funzione della frequenza; Frequenza (Hz); Gain (adimensionale)");

  TGraphErrors *graph_W =
      new TGraphErrors("Ampiezza_w_div5.txt", "%lg %lg %lg %lg");
  mg->Add(graph_W);

  TGraphErrors *graph_T =
      new TGraphErrors("Ampiezza_t_div5.txt", "%lg %lg %lg %lg");
  mg->Add(graph_T);

  TGraphErrors *graph_M =
      new TGraphErrors("Ampiezza_m_div5.txt", "%lg %lg %lg %lg");
  mg->Add(graph_M);

  // Cosmetics

  graph_W->SetLineColor(kOrange - 3);
  graph_W->SetMarkerColor(kOrange - 3);
  graph_W->SetLineWidth(1);

  graph_T->SetLineColor(kGreen - 9);
  graph_T->SetMarkerColor(kGreen - 9);
  graph_T->SetLineWidth(1);

  graph_M->SetLineColor(kMagenta);
  graph_M->SetMarkerColor(kMagenta);
  graph_M->SetLineWidth(1);

  // Draw the 2kHz multi-graph!
  TCanvas *myCanvas = new TCanvas("myc", "myc", 720, 450);
  mg->Draw("ACP");
  // Build and Draw a legend
  TLegend *leg =
      new TLegend(0.7086384, 0.8323133, 0.8997072, 0.9008568, NULL, "brNDC");
  leg->AddEntry(graph_W, "woofer");
  leg->AddEntry(graph_T, "tweeter");
  leg->AddEntry(graph_M, "midrange");
  leg->SetFillStyle(1001);
  leg->Draw("Same");

  // fitting gain function, i.e. Voltage/5V
  TF1 *fitwoofer = new TF1(
      "fitwoofer", "1./(sqrt([0]*[0]+4*pi*pi*(x*x)*([1]*[1])))", 4000, 6000);
  fitwoofer->SetParameter(0, 1.28);
  fitwoofer->SetParameter(1, 0.0000063);
  graph_W->Fit("fitwoofer", "R,Q");
  std::cout << "\nFit result for V_W: mu_{w} =" << fitwoofer->GetParameter(0)
            << " +/- " << fitwoofer->GetParError(0)
            << ",   tau_{w} = " << fitwoofer->GetParameter(1) << " +/- "
            << fitwoofer->GetParError(1)
            << " chi2:" << fitwoofer->GetChisquare() / fitwoofer->GetNDF()
            << std::endl;

  TF1 *fittweeter = new TF1(
      "fittweeter", "1./(sqrt([0]*[0]+1/(4*pi*pi*x*x*[1]*[1])))", 4000, 6000);
  fittweeter->SetParameter(0, -1.2);
  fittweeter->SetParameter(1, 0.0000063);
  graph_T->Fit("fittweeter", "R,Q");
  std::cout << "\nFit result for V_T: mu_{t} =" << fittweeter->GetParameter(0)
            << " +/- " << fittweeter->GetParError(0)
            << ",  tau_{t} = " << fittweeter->GetParameter(1) << " +/- "
            << fittweeter->GetParError(1)
            << " chi2: " << fittweeter->GetChisquare() / fittweeter->GetNDF()
            << std::endl;

  TF1 *fitmidrange =
      new TF1("fitmidrange",
              "1./(sqrt( [0]*[0] + ( [1]*x*2*pi - (1/([2]*x*2*pi)) )^2 ))",
              2000, 11000);
  fitmidrange->SetParameter(0, 1.28);
  fitmidrange->SetParameter(1, 0.000063);
  fitmidrange->SetParameter(2, 0.000063);
  graph_M->Fit("fitmidrange", "R,Q");
  std::cout << "\nFit result for V_M: mu_{m} =" << fitmidrange->GetParameter(0)
            << " +/- " << fitmidrange->GetParError(0)
            << ",  tau_{lm} = " << fitmidrange->GetParameter(1) << " +/- "
            << fitmidrange->GetParError(1)
            << ",   tau_{cm} = " << fitmidrange->GetParameter(2) << " +/- "
            << fitmidrange->GetParError(2)
            << " chi2: " << fitmidrange->GetChisquare() / fitmidrange->GetNDF()
            << std::endl;

  myCanvas->Print("multigrafico_ampiezze_frequenze.jpg");
  myCanvas->Print("multigrafico_ampiezze_frequenze.pdf");
  myCanvas->Print("multigrafico_ampiezze_frequenze.tex");
}
