
void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico() {
  // 2kHz graph
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Fase in funzione della frequenza; Frequenza (Hz); Fase (gradi)");

  TGraph *A1 = new TGraph("sistematico_A1.txt", "%lg %lg");
  mg->Add(A1);

  TGraph *A2 = new TGraph("sistematico_A2_offset.txt", "%lg %lg");
  mg->Add(A2);

  TGraph *A3 = new TGraph("sistematico_A3_offset.txt", "%lg %lg");
  mg->Add(A3);

  // Cosmetics
  A3->SetLineColor(kMagenta);
  A3->SetMarkerColor(kMagenta);
  A3->SetLineWidth(2);

  A1->SetLineColor(kOrange-3);
  A1->SetMarkerColor(kOrange-3);
  A1->SetLineWidth(2);

  A2->SetLineColor(kGreen-9);
  A2->SetMarkerColor(kGreen-9);
  A2->SetLineWidth(2);

  // Draw the multi-graph!
  TCanvas *myCanvas = new TCanvas("myCanvas","myCanvas", 800,380);
  mg->Draw("al");
  // Build and Draw a legend
  TLegend *leg = new TLegend(0.1290727,0.8230337,0.2092732,0.8848315,NULL,"brNDC");
  leg->AddEntry(A1, "AI_1");
  leg->AddEntry(A2, "AI_2");
  leg->AddEntry(A3, "AI_3");
  leg->SetFillStyle(1001);
  leg->Draw("Same");

  myCanvas->Print("multigrafico_sistematico_fase.jpg");
  myCanvas->Print("multigrafico_sistematico_fase.pdf");
  myCanvas->Print("multigrafico_sistematico_fase.tex");
}
