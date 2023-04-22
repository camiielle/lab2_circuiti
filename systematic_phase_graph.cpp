
void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico_errori() {

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Fase in funzione della frequenza; Frequenza (Hz); Fase (gradi)");

  TGraph *A1 = new TGraph("sistematico_A1.txt", "%lg %lg");
  mg->Add(A1);

  TGraph *A2 = new TGraph("sistematico_A2_offset.txt", "%lg %lg");
  mg->Add(A2);

  TGraph *A3 = new TGraph("sistematico_A3_offset.txt", "%lg %lg");
  mg->Add(A3);

  // Cosmetics
  A1->SetLineColor(kOrange-3);
  A1->SetMarkerColor(kOrange-3);
  A1->SetLineWidth(2);

  A2->SetLineColor(kGreen-9);
  A2->SetMarkerColor(kGreen-9);
  A2->SetLineWidth(2);

  A3->SetLineColor(kMagenta);
  A3->SetMarkerColor(kMagenta);
  A3->SetLineWidth(2);

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


  //perofrming a linear fit 
    TF1 *f_A1 = new TF1("f_A1","([0]+[1]*x)",2050,11000);
    f_A1->SetParameter(0,0.);
    A1->Fit("f_A1","R,Q");
    std::cout << "\nFit result for A1: offset_{A1} =" << f_A1->GetParameter(0) << " +/- " << f_A1->GetParError(0) << ",  slope_{A1} = " 
    << f_A1->GetParameter(1) << " +/- " << f_A1->GetParError(1) << std::endl;
    std::cout << '\n';

    TF1 *f_A2 = new TF1("f_A2","([0]+[1]*x)",2000,11000);
    f_A2->SetParameter(0,1.);
    A2->Fit("f_A2","R,Q");
    std::cout << "\nFit result for A2: offset_{A2} =" << f_A2->GetParameter(0) << " +/- " << f_A2->GetParError(0) << ",  slope_{A2} = " 
    << f_A2->GetParameter(1) << " +/- " << f_A2->GetParError(1) << std::endl;
    std::cout << '\n';
    
    TF1 *f_A3 = new TF1("f_A3","([0]+[1]*x)",2050,11000);
    f_A3->SetParameter(0,2.);
    A3->Fit("f_A3","R,Q");
    std::cout << "\nFit result for A3: offset_{A3} =" << f_A3->GetParameter(0) << " +/- " << f_A3->GetParError(0) << ",  slope_{A3} = " 
    << f_A3->GetParameter(1) << " +/- " << f_A3->GetParError(1) << std::endl;
    std::cout << '\n';
}

void grafico_fasi(){
TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Fase in funzione della frequenza; Frequenza (Hz); Fase (gradi)");

  TGraph *fase_w = new TGraph("Fase_w.txt", "%lg %lg");
  mg->Add(fase_w);

  TGraph *fase_t = new TGraph("Fase_t.txt", "%lg %lg");
  mg->Add(fase_t);

  TGraph *fase_m = new TGraph("Fase_m.txt", "%lg %lg");
  mg->Add(fase_m);

  // Cosmetics
  fase_w->SetLineColor(kOrange-3);
  fase_w->SetMarkerColor(kOrange-3);
  fase_w->SetLineWidth(2);

  fase_t->SetLineColor(kGreen-9);
  fase_t->SetMarkerColor(kGreen-9);
  fase_t->SetLineWidth(2);

  fase_m->SetLineColor(kMagenta);
  fase_m->SetMarkerColor(kMagenta);
  fase_m->SetLineWidth(2);

  // Draw the multi-graph!
  TCanvas *myCanvas = new TCanvas("myCanvas","myCanvas", 900,500);
  mg->Draw("al");
  // Build and Draw a legend
  TLegend *leg = new TLegend(0.7862372,0.8115055,0.8850659,0.8812729,NULL,"brNDC");
  leg->AddEntry(fase_w, "woofer");
  leg->AddEntry(fase_t, "tweeter");
  leg->AddEntry(fase_m, "midrange");
  leg->SetFillStyle(1001);
  leg->Draw("Same");

  myCanvas->Print("multigrafico_fase.jpg");
  myCanvas->Print("multigrafico_fase.pdf");
  myCanvas->Print("multigrafico_fase.tex");

}