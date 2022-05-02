#ifndef CAMADA_ENLACE_
#define CAMADA_ENLACE_

#include <vector>
#include "CamadaFisica.hpp"
#include <stdint.h>
#include <ncurses.h>

#define BYTE 8

/*********** TRANSMISSÃO **********/

void CamadaEnlaceDadosTransmissora(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (vector<int> quadro);

/************ RECEPÇÃO ************/

void CamadaEnlaceDadosReceptora(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (vector<int> quadro);

#endif