void setStyle1() {
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetGridColor(kGray);
}

void grafico_frequenze_senzaFGEN() {
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(
      "Guadagno in funzione della frequenza (Metodo 1); Frequenza (Hz); G (un. arb.)");

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
  graph_W->SetMarkerStyle(6);

  graph_T->SetLineColor(kGreen - 9);
  graph_T->SetMarkerColor(kGreen - 9);
  graph_T->SetLineWidth(1);
  graph_T->SetMarkerStyle(6);

  graph_M->SetLineColor(kMagenta);
  graph_M->SetMarkerColor(kMagenta);
  graph_M->SetLineWidth(1);
  graph_M->SetMarkerStyle(6);

// Draw the 2kHz multi-graph!
  TCanvas *myCanvas = new TCanvas("myCanvas", "myCanvas", 1000, 380);
  myCanvas->SetGrid();
  myCanvas->SetGridx();
  myCanvas->SetGridy();
  myCanvas->Divide(2, 1);
  myCanvas->cd(1);
  // Set the title of the TMultiGraph
  mg->Draw("ALPX");
  // Build and Draw a legend
  TLegend *leg1 =
      new TLegend(0.7086384, 0.8323133, 0.8997072, 0.9008568, NULL, "brNDC");
  leg1->AddEntry(graph_W, "woofer");
  leg1->AddEntry(graph_T, "tweeter");
  leg1->AddEntry(graph_M, "midrange");
  leg1->Draw("Same");




  myCanvas->cd(2);

  TMultiGraph *mg1 = new TMultiGraph();
  mg1->SetTitle(
      "Fit su range ridotto; Frequenza (Hz); G (un. arb.)");

  TGraphErrors *graph_W1 =
      new TGraphErrors("Ampiezza_w_div5.txt", "%lg %lg %lg %lg");
  mg1->Add(graph_W1);

  TGraphErrors *graph_T1 =
      new TGraphErrors("Ampiezza_t_div5.txt", "%lg %lg %lg %lg");
  mg1->Add(graph_T1);

  TGraphErrors *graph_M1 =
      new TGraphErrors("Ampiezza_m_div5.txt", "%lg %lg %lg %lg");
  mg1->Add(graph_M1);

  // Cosmetics

  graph_W1->SetLineColor(kOrange - 3);
  graph_W1->SetMarkerColor(kOrange - 3);
  graph_W1->SetLineWidth(1);
  graph_W1->SetMarkerStyle(6);

  graph_T1->SetLineColor(kGreen - 9);
  graph_T1->SetMarkerColor(kGreen - 9);
  graph_T1->SetLineWidth(1);
  graph_T1->SetMarkerStyle(6);

  graph_M1->SetLineColor(kMagenta);
  graph_M1->SetMarkerColor(kMagenta);
  graph_M1->SetLineWidth(1);
  graph_M1->SetMarkerStyle(6);

  // fitting gain function, i.e. Voltage/5V
  TF1 *fitwoofer = new TF1(
      "fitwoofer", "1./(sqrt([0]*[0]+4*pi*pi*(x*x)*([1]*[1])))", 4000, 6000);
  fitwoofer->SetLineWidth(1);
  fitwoofer->SetLineColor(kBlack);
  fitwoofer->SetParameter(0, 1.28);
  fitwoofer->SetParameter(1, 0.0000063);
  graph_W1->Fit("fitwoofer", "R,Q");
  std::cout << "\nFit result for V_W: mu_{w} =" << fitwoofer->GetParameter(0)
            << " +/- " << fitwoofer->GetParError(0)
            << ",   tau_{w} = " << fitwoofer->GetParameter(1) << " +/- "
            << fitwoofer->GetParError(1)
            << " chi2:" << fitwoofer->GetChisquare() / fitwoofer->GetNDF()
            << std::endl;

  TF1 *fittweeter = new TF1(
      "fittweeter", "1./(sqrt([0]*[0]+1/(4*pi*pi*x*x*[1]*[1])))", 4000, 6000);
  fittweeter->SetLineWidth(1);
  fittweeter->SetLineColor(kBlack);
  fittweeter->SetParameter(0, -1.2);
  fittweeter->SetParameter(1, 0.0000063);
  graph_T1->Fit("fittweeter", "R,Q");
  std::cout << "\nFit result for V_T: mu_{t} =" << fittweeter->GetParameter(0)
            << " +/- " << fittweeter->GetParError(0)
            << ",  tau_{t} = " << fittweeter->GetParameter(1) << " +/- "
            << fittweeter->GetParError(1)
            << " chi2: " << fittweeter->GetChisquare() / fittweeter->GetNDF()
            << std::endl;

  TF1 *fitmidrange =
      new TF1("fitmidrange",
              "1./(sqrt( [0]*[0] + ( [1]*x*2*pi - (1/([2]*x*2*pi)) )^2 ))",
              4000, 6000);
  fitmidrange->SetLineWidth(1);
  fitmidrange->SetLineColor(kBlack);
  fitmidrange->SetParameter(0, 1.28);
  fitmidrange->SetParameter(1, 0.000063);
  fitmidrange->SetParameter(2, 0.000063);
  graph_M1->Fit("fitmidrange", "R,Q");
  std::cout << "\nFit result for V_M: mu_{m} =" << fitmidrange->GetParameter(0)
            << " +/- " << fitmidrange->GetParError(0)
            << ",  tau_{lm} = " << fitmidrange->GetParameter(1) << " +/- "
            << fitmidrange->GetParError(1)
            << ",   tau_{cm} = " << fitmidrange->GetParameter(2) << " +/- "
            << fitmidrange->GetParError(2)
            << " chi2: " << fitmidrange->GetChisquare() / fitmidrange->GetNDF()
            << std::endl;
  myCanvas->cd(2);
  mg1->Draw("ACPX");

  // Build and Draw a legend
  TLegend *leg =
      new TLegend(0.7086384, 0.8323133, 0.8997072, 0.9008568, NULL, "brNDC");
  leg->AddEntry(graph_W, "woofer");
  leg->AddEntry(graph_T, "tweeter");
  leg->AddEntry(graph_M, "midrange");
  leg->AddEntry(fitwoofer, "fit");
  leg->SetFillStyle(1001);
  leg->Draw("Same");

  myCanvas->Print("multigrafico_ampiezze_frequenze.jpg");
  myCanvas->Print("multigrafico_ampiezze_frequenze.pdf");
  myCanvas->Print("multigrafico_ampiezze_frequenze.tex");
}
