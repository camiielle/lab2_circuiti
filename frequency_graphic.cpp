
void setStyle_frequenze() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico_frequenze() {
  
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Ampiezza in funzione della frequenza; Frequenza (Hz); Ampiezza (V)");

  TGraph *graph_W = new TGraph("Ampiezza_w.txt", "%lg %lg");
  mg->Add(graph_W);

  TGraph *graph_T = new TGraph("Ampiezza_t.txt", "%lg %lg");
  mg->Add(graph_T);

  TGraph *graph_M = new TGraph("Ampiezza_m.txt", "%lg %lg");
  mg->Add(graph_M);

  // Cosmetics

  graph_W->SetLineColor(kOrange-3);
  graph_W->SetMarkerColor(kOrange-3);
  graph_W->SetLineWidth(1);

  graph_T->SetLineColor(kGreen-9);
  graph_T->SetMarkerColor(kGreen-9);
  graph_T->SetLineWidth(1);

  graph_M->SetLineColor(kMagenta);
  graph_M->SetMarkerColor(kMagenta);
  graph_M->SetLineWidth(1);

  // Draw the 2kHz multi-graph!
  TCanvas *myCanvas = new TCanvas("myc", "myc", 720, 450);
  mg->Draw("ACP");
  // Build and Draw a legend
  TLegend *leg = new TLegend(0.7086384, 0.8323133, 0.8997072, 0.9008568, NULL, "brNDC");
  leg->AddEntry(graph_W, "woofer");
  leg->AddEntry(graph_T, "tweeter");
  leg->AddEntry(graph_M, "midrange");
  leg->SetFillStyle(1001);
  leg->Draw("Same");

  myCanvas->Print("multigrafico_ampiezze_frequenze.jpg");
  myCanvas->Print("multigrafico_ampiezze_frequenze.pdf");
  myCanvas->Print("multigrafico_ampiezze_frequenze.tex");
}
