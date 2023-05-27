
void setStyle_frequenze() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico_frequenze() {
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(
      "Gain in funzione della frequenza; Frequenza (Hz); Gain (adimensionale)");

  TGraphErrors *graph_W =
      new TGraphErrors("Ampiezza_w_div_vin.txt", "%lg %lg %lg %lg");
  mg->Add(graph_W);

  TGraphErrors *graph_T =
      new TGraphErrors("Ampiezza_t_div_vin.txt", "%lg %lg %lg %lg");
  mg->Add(graph_T);

  TGraphErrors *graph_M =
      new TGraphErrors("Ampiezza_m_div_vin.txt", "%lg %lg %lg %lg");
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
      "fitwoofer", "1./(sqrt([0]*[0]+4*pi*pi*(x*x)*([1]*[1])))", 2000, 11000);
  fitwoofer->SetParameter(0, 1.18);
  fitwoofer->SetParameter(1, 0.0000063);
  graph_W->Fit("fitwoofer", "Q");
  std::cout << "\nFit result for V_W: mu_{w} =" << fitwoofer->GetParameter(0)
            << " +/- " << fitwoofer->GetParError(0)
            << ",   tau_{w} = " << fitwoofer->GetParameter(1) << " +/- "
            << fitwoofer->GetParError(1) << std::endl;

  std::cout << "Chi_{w} " << fitwoofer->GetChisquare() / fitwoofer->GetNDF()
            << '\n';
  TF1 *fittweeter = new TF1(
      "fittweeter", "1./(sqrt([0]*[0]+1/(4*pi*pi*x*x*[1]*[1])))", 2000, 11000);
  fittweeter->SetParameter(0, 1.17);
  fittweeter->SetParameter(1, 0.0000063);
  graph_T->Fit("fittweeter", "Q");
  std::cout << "\nFit result for V_T: mu_{t} =" << fittweeter->GetParameter(0)
            << " +/- " << fittweeter->GetParError(0)
            << ",  tau_{t} = " << fittweeter->GetParameter(1) << " +/- "
            << fittweeter->GetParError(1) << std::endl;
  std::cout << "Chi_{t} " << fittweeter->GetChisquare() / fittweeter->GetNDF()
            << '\n';
  std::cout << '\n';

  TF1 *fitmidrange = new TF1(
      "fitmidrange",
      "1./(sqrt([0]*[0] + ( [1]*x*2*pi - (1/([2]*x*2*pi)) )^2 ))", 2000, 11000);
  fitmidrange->SetParameter(0, 1.1725748);
  fitmidrange->SetParameter(1, 0.00003944449078);
  fitmidrange->SetParameter(2, 0.00002613602);
  graph_M->Fit("fitmidrange", "R");
  std::cout << "\nFit result for V_M: mu_{m} =" << fitmidrange->GetParameter(0)
            << " +/- " << fitmidrange->GetParError(0)
            << ",  tau_{lm} = " << fitmidrange->GetParameter(1) << " +/- "
            << fitmidrange->GetParError(1)
            << ",   tau_{cm} = " << fitmidrange->GetParameter(2) << " +/- "
            << fitmidrange->GetParError(2) << std::endl;
  std::cout << "Chi_{m} " << fitmidrange->GetChisquare() / fitmidrange->GetNDF() << '\n';
  std::cout << '\n';

  myCanvas->Print("multigrafico_ampiezze_frequenze.jpg");
  myCanvas->Print("multigrafico_ampiezze_frequenze.pdf");
  myCanvas->Print("multigrafico_ampiezze_frequenze.tex");
}
