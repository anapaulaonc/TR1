#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

//Camada Fisica de transmissao
 void AplicacaoTransmissora();
 void CamadaDeAplicacaoTransmissora(string mensagem);
 void CamadaFisicaTransmissora(vector<int> quadro);
 vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro);
 vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro);
 vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro);

//Camada Fisica de Meio de Comunicacao
 void MeioDeComunicacao(vector<int> fluxoBrutoDeBits);

//Camada fisica de recepcao
 void CamadaFisicaReceptora(vector<int> quadro);
 vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro);
 vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> quadro);
 vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> quadro);
 void CamadaDeAplicacaoReceptora(vector<int> quadro);
 void AplicacaoReceptora(string mensagem);

vector<int> codificaString(string mensagem);
string decodificaString(vector<int> bits);