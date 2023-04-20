
void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico() {
  // 2kHz graph
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Frequenza - 2kHz; Tempo (ms); Ampiezza (V)");

  TGraph *graph_Gen = new TGraph("Vgen(2kHz)ms.txt", "%lg %lg");
  mg->Add(graph_Gen);

  TGraph *graph_W = new TGraph("Vw(2kHz)ms.txt", "%lg %lg");
  mg->Add(graph_W);

  TGraph *graph_T = new TGraph("Vt(2kHz)ms.txt", "%lg %lg");
  mg->Add(graph_T);

  TGraph *graph_M = new TGraph("Vm(2kHz)ms.txt", "%lg %lg");
  mg->Add(graph_M);

  // Cosmetics
  graph_Gen->SetLineColor(kBlue);
  graph_Gen->SetMarkerColor(kBlue);
  graph_Gen->SetLineWidth(2);

  graph_W->SetLineColor(kRed);
  graph_W->SetMarkerColor(kRed);
  graph_W->SetLineWidth(2);

  graph_T->SetLineColor(kGreen);
  graph_T->SetMarkerColor(kGreen);
  graph_T->SetLineWidth(2);

  graph_M->SetLineColor(kMagenta);
  graph_M->SetMarkerColor(kMagenta);
  graph_M->SetLineWidth(2);

  // Draw the 2kHz multi-graph!
  TCanvas *myCanvas = new TCanvas("myCanvas","myCanvas", 1000,380);
  myCanvas->Divide(2,1);
  myCanvas->cd(1);
  mg->Draw("al");
  // Build and Draw a legend
  TLegend *leg = new TLegend(0.7086384, 0.8323133, 0.8997072, 0.9008568, NULL, "brNDC");
  leg->AddEntry(graph_Gen, "gen");
  leg->AddEntry(graph_W, "woofer");
  leg->AddEntry(graph_T, "tweeter");
  leg->AddEntry(graph_M, "midrange");
  leg->SetFillStyle(1001);
  leg->SetNColumns(2);
  leg->Draw("Same");

  // 11kHz graph
  TMultiGraph *mg2 = new TMultiGraph();
  mg2->SetTitle("Frequenza - 11kHz; Tempo (ms); Ampiezza (V)");

  TGraph *graph_Gen2 = new TGraph("Vgen(11kHz)ms.txt", "%lg %lg");
  mg2->Add(graph_Gen2);

  TGraph *graph_W2 = new TGraph("Vw(11kHz)ms.txt", "%lg %lg");
  mg2->Add(graph_W2);

  TGraph *graph_T2 = new TGraph("Vt(11kHz)ms.txt", "%lg %lg");
  mg2->Add(graph_T2);

  TGraph *graph_M2 = new TGraph("Vm(11kHz)ms.txt", "%lg %lg");
  mg2->Add(graph_M2);

  // Cosmetics
  graph_Gen2->SetLineColor(kBlue);
  graph_Gen2->SetMarkerColor(kBlue);
  graph_Gen2->SetLineWidth(2);

  graph_W2->SetLineColor(kRed);
  graph_W2->SetMarkerColor(kRed);
  graph_W2->SetLineWidth(2);

  graph_T2->SetLineColor(kGreen);
  graph_T2->SetMarkerColor(kGreen);
  graph_T2->SetLineWidth(2);

  graph_M2->SetLineColor(kMagenta);
  graph_M2->SetMarkerColor(kMagenta);
  graph_M2->SetLineWidth(2);

  // Draw the 11kHz multi-graph!
  myCanvas->cd(2);
  mg2->Draw("al");
  // Build and Draw a legend
  TLegend *leg2 =
      new TLegend(0.7086384, 0.8323133, 0.8997072, 0.9008568, NULL, "brNDC");
  leg2->AddEntry(graph_Gen2, "gen");
  leg2->AddEntry(graph_W2, "woofer");
  leg2->AddEntry(graph_T2, "tweeter");
  leg2->AddEntry(graph_M2, "midrange");
  leg2->SetFillStyle(1001);
  leg2->SetNColumns(2);
  leg2->Draw("Same");

  // 5.3kHz graph
  TMultiGraph *mg3 = new TMultiGraph();
  mg3->SetTitle("Frequenza - 5.3kHz; Tempo (ms); Ampiezza (V)");

  TGraph *graph_Gen3 = new TGraph("Vgen(5.3kHz)ms - Copia.txt", "%lg %lg");
  mg3->Add(graph_Gen3);

  TGraph *graph_W3 = new TGraph("Vm(5.3kHz)ms - Copia.txt", "%lg %lg");
  mg3->Add(graph_W3);

  TGraph *graph_T3 = new TGraph("Vw(5.3kHz)ms - Copia.txt", "%lg %lg");
  mg3->Add(graph_T3);

  TGraph *graph_M3 = new TGraph("Vt(5.3kHz)ms - Copia.txt", "%lg %lg");
  mg3->Add(graph_M3);

  // Cosmetics
  graph_Gen3->SetLineColor(kBlue);
  graph_Gen3->SetMarkerColor(kBlue);
  graph_Gen3->SetLineWidth(2);

  graph_W3->SetLineColor(kRed);
  graph_W3->SetMarkerColor(kRed);
  graph_W3->SetLineWidth(2);

  graph_T3->SetLineColor(kGreen);
  graph_T3->SetMarkerColor(kGreen);
  graph_T3->SetLineWidth(2);

  graph_M3->SetLineColor(kMagenta);
  graph_M3->SetMarkerColor(kMagenta);
  graph_M3->SetLineWidth(2);

  TCanvas *myCanvas3 = new TCanvas();
  // Draw the 5.3kHz multi-graph!
  mg3->Draw("al");
  // Build and Draw a legend
  TLegend *leg3 =
      new TLegend(0.7086384, 0.8323133, 0.8997072, 0.9008568, NULL, "brNDC");
  leg3->AddEntry(graph_Gen3, "gen");
  leg3->AddEntry(graph_W3, "woofer");
  leg3->AddEntry(graph_T3, "tweeter");
  leg3->AddEntry(graph_M3, "midrange");
  leg3->SetFillStyle(1001);
  leg3->SetNColumns(2);
  leg3->Draw("Same");

  myCanvas->Print("multigrafico_tempo_2kHz_11kHz.jpg");
  myCanvas3->Print("multigrafico_tempo_5.3kHz.jpg");

  myCanvas->Print("multigrafico_tempo_2kHz_11kHz.pdf");
  myCanvas3->Print("multigrafico_tempo_5.3kHz.pdf");

  myCanvas->Print("multigrafico_tempo_2kHz_11kHz.tex");
  myCanvas3->Print("multigrafico_tempo_5.3kHz.tex");
}
