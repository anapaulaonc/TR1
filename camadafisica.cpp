#include <iostream>
#include "./camadafisica.hpp"

#define TIPO_CODIFICACAO 2

void AplicacaoTransmissora() {
  string mensagem;
  cout << "Digite a mensagem: " << endl;
  cin >> mensagem;

  CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
  vector<int> quadro = codificaString(mensagem);

  CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora(vector<int> quadro) {
  int tipoDeCodificacao = TIPO_CODIFICACAO;
  vector<int> fluxoBrutoDeBits;

  switch (tipoDeCodificacao) {
  case 0: // codificacao binaria
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
    break;
  case 1: // codificacao manchester
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
    break;
  case 2: // codificacao bipolar
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
    break;
  }

  MeioDeComunicacao(fluxoBrutoDeBits);
}

// usa 5v para 1 e 0v para 0
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro) {
  vector<int> fluxoBrutoDeBits;

  for(int i = 0; i < quadro.size(); i++) {
    fluxoBrutoDeBits.push_back(quadro[i] * 5);
  }

  return fluxoBrutoDeBits;
}

// usa 5v e -5v para 1 e 0v para 0
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {
  vector<int> fluxoBrutoDeBits(quadro.size() * 2);

  for (int i = 0; i < quadro.size(); i++) {
    fluxoBrutoDeBits[i * 2] = quadro[i] * 5;
    fluxoBrutoDeBits[i * 2 + 1] = quadro[i] * -5;
  }

  return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {
  vector<int> fluxoBrutoDeBits(quadro.size() * 2);
  bool alternador = true;

  for (int i = 0; i < quadro.size(); i++) {
    fluxoBrutoDeBits[i * 2] = alternador ? quadro[i] * 5 : quadro[i] * -5;
    fluxoBrutoDeBits[i * 2 + 1] = alternador ? quadro[i] * -5 : quadro[i] * 5;
    alternador = !alternador;
  }

  return fluxoBrutoDeBits;
}

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) {
  vector<int> fluxoBrutoDeBitsPontoA;
  vector<int> fluxoBrutoDeBitsPontoB;

  // simula o meio de comunicação
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

  for (int i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
    fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
  }

  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora(vector<int> quadro) {
  int tipoDeCodificacao = TIPO_CODIFICACAO;
  vector<int> fluxoBrutoDeBits;

  switch (tipoDeCodificacao) {
    case 0: // codificacao binaria
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
      break;
    case 1: // codificacao manchester
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
      break;
    case 2: // codificacao bipolar
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
      break;
  }

  CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro) {
  vector<int> fluxoBrutoDeBits;

  for (int i = 0; i < quadro.size(); i++) {
    fluxoBrutoDeBits.push_back(quadro[i] / 5);
  }

  return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> quadro) {
  vector<int> fluxoBrutoDeBits(quadro.size() / 2);

  for (int i = 0; i < quadro.size(); i += 2) {
    fluxoBrutoDeBits[i / 2] = quadro[i] / 5;
  }

  return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> quadro) {
  vector<int> fluxoBrutoDeBits(quadro.size() / 2);
  bool alternador = true;

  for (int i = 0; i < quadro.size(); i += 2) {
    fluxoBrutoDeBits[i / 2] = alternador ? quadro[i] / 5 : quadro[i] / -5;
    alternador = !alternador;
  }

  return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora(vector<int> quadro) {
  string mensagem = decodificaString(quadro);

  AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(string mensagem) {
  cout << "Mensagem recebida: " << mensagem << endl;
}

// converte uma string em um vector de bits representando cada caractere
vector<int> codificaString(string mensagem) {
  vector<int> quadro;

  for (int i = 0; i < mensagem.size(); i++) {
    for (int j = 7; j >= 0; j--) {
      quadro.push_back((mensagem[i] >> j) & 1);
    }
  }

  return quadro;
}

// converte um vector de bits em uma string
string decodificaString(vector<int> bits) {
  string mensagem;

  for (int i = 0; i < bits.size(); i += 8) {
    char caractere = 0;

    for (int j = 0; j < 8; j++) {
      caractere |= bits[i + j] << (7 - j);
    }

    mensagem += caractere;
  }

  return mensagem;
}