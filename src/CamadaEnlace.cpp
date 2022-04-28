using namespace std;
#include "../include/CamadaEnlace.hpp"

/*********** TRANSMISSÃO **********/

void CamadaEnlaceDadosTransmissora(vector<int> quadro){
    
}

void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (vector<int> quadro);

/************ RECEPÇÃO ************/

void CamadaEnlaceDadosReceptora(vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleDeErroCRC (vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (vector<int> quadro);