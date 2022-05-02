using namespace std;
#include "../include/CamadaFisica.hpp"
#include "../include/CamadaEnlace.hpp"

/*********** TRANSMISSÃO **********/

void CamadaEnlaceDadosTransmissora(vector<int> quadro){

	attron(COLOR_PAIR(2));
	printw("Camada de Enlace de dados Transmissora\n");
	attroff(COLOR_PAIR(2));
	vector<int> quadro_enquadrado;

	quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
	quadro_enquadrado = CamadaEnlaceDadosTransmissoraControleDeErro(quadro_enquadrado);

	attron(COLOR_PAIR(2));
	printw("Quadro Enquadrado e Controlado de Erros: \n");
	attroff(COLOR_PAIR(2));
	for (int i : quadro_enquadrado)
		printw("%d", i);
	printw("\n\n");

	refresh();

	// manda pra camada física depois do enquadramento e contole de erro
	CamadaFisicaTransmissora(quadro_enquadrado);

}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro){
	// escolhe o tipo de enquadramento
	// 0 = Contagem de Caracters
	// 1 = inserção de bytes
	int enquadramento = 1;
	vector<int> quadro_enquadrado;
	// enquadra o fluxo de bits passado
	switch (enquadramento){
		case 0:

			quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);

			break;

		case 1:

			quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);

			break;
	}

	attron(COLOR_PAIR(2));
	printw("Quadro Enquadrado: \n\n");
	attroff(COLOR_PAIR(2));
	for (int i : quadro)
		printw("%d", i);
	printw("\n\n");
	
	return quadro_enquadrado;
}

// Tipos de enquadramentos 

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro){

	attron(COLOR_PAIR(2));
	printw("Enquadramento com contagem de caracteres\n\n");
	attroff(COLOR_PAIR(2));

    uint8_t qtd_bytes = ceil(quadro.size() / 8);
    vector<int> quadro_enquadrado_caracteres = quadro;
    vector<int> binario;

    bitset<8> bits(qtd_bytes);
    for (int i = 0; i < 8; i++){
        if (int(bits[i]) == 1)
            quadro_enquadrado_caracteres.insert(quadro_enquadrado_caracteres.begin(), int(bits[i]));
        else
            quadro_enquadrado_caracteres.insert(quadro_enquadrado_caracteres.begin(), int(0));
    }
		attron(COLOR_PAIR(2));
		printw("Quardo enquadrado com contagem de caracteres: \n");
		attroff(COLOR_PAIR(2));
    for (int i = 0; i < quadro_enquadrado_caracteres.size(); i++){
        printw("%d", quadro_enquadrado_caracteres.at(i));
    }
		printw("\n");
		return quadro_enquadrado_caracteres;
}


vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro){
	attron(COLOR_PAIR(2));
	printw("Enquadramento com insercao de bytes\n\n");
	attroff(COLOR_PAIR(2));
	
	string flag = "00001111";
	string esc = "11110000";
	string flag_bit = "01111110";
	string byte_str = "", quadro_str = flag;

    vector<int> novo_quadro;
    int counter = 1;

    for (int i = 0; i < quadro.size(); i++){
        byte_str += to_string(quadro[i]);

        if (counter == (BYTE)){
            if ((byte_str == flag) || (byte_str == esc))
                quadro_str += esc;

            quadro_str += byte_str;

            counter = 0;
            byte_str = "";
        }
        counter++;
    }

    quadro_str += flag;

    for (auto &i : quadro_str)
        novo_quadro.push_back(i - '0');

		attron(COLOR_PAIR(2));
		printw("Quardo enquadrado com insercao de bytes: \n");
		attroff(COLOR_PAIR(2));
		
    for (int i = 0; i < novo_quadro.size(); i++){
        printw("%d", novo_quadro.at(i));
    }
	printw("\n\n");

    return novo_quadro;
}

//-----------------------------//
vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro){
	int tipo_erro = 2; //alterar de acordo com o teste
	vector<int> controle_erro;

	attron(COLOR_PAIR(2));
	printw("TIPO DE CONTROLE DE ERRO:");
	attroff(COLOR_PAIR(2));
	printw("%d\n\n", tipo_erro);
	switch (tipo_erro){
		case 0: //bit de paridade par
			controle_erro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
			break;
		case 1: //CRC
			controle_erro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
			break;
		case 2: //codigo de Hamming
				controle_erro = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
			break;
	}
	
	printw("Quardo apos controle de erro realizado:\n");
    for (int i = 0; i < controle_erro.size(); i++){
        printw("%d", controle_erro.at(i));
    }
	printw("\n\n");
	return controle_erro;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (vector<int> quadro)
{
	printw("\n\nControle de Paridade Par...\n\n");

	vector<int> controle_paridade_par;
	bool paridade = true;

	for (int i = 0; i < quadro.size(); i++)
		controle_paridade_par.push_back(quadro.at(i));

	for (int i = 0; i < quadro.size(); i++)
		if (quadro.at(i) == 1)
			paridade = !paridade;

	controle_paridade_par.push_back(paridade);

	for (int i = 0; i < controle_paridade_par.size(); i++)
		printw("%d", controle_paridade_par.at(i));
	printw("\n\n");

	return controle_paridade_par;
}
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro){
	printw("\n\nTransmissao com controle de erro CRC...\n\n");

    vector<int> novo_quadro = quadro;
	string polinomio_crc_32 = "100110000010001110110110111";

    if (quadro.size() <= polinomio_crc_32.length()){
		printw("\n\nErro, o quadro possui menos bits que o polinomio\n\n");
        exit(1);
    }

    for (int i = 0; i < polinomio_crc_32.length(); i++)
        novo_quadro.push_back(0);

    for (int i = 0; i < quadro.size(); i++){
        if (novo_quadro[i] == 1){
            for (int j = 0; j < polinomio_crc_32.length(); j++)
                novo_quadro[i + j] ^= (polinomio_crc_32[j] - '0');
            // XOR entre o elemento i+j do novo quadro e o polinômio CRC 32bits; Armazena no próprio elemento i+j do novo quadro
        }
    }

    for (int i = 0; i < quadro.size(); i++)
        novo_quadro[i] = quadro[i];

	for (int i = 0; i < novo_quadro.size(); i++)
		printw("%d", novo_quadro.at(i));
	printw("\n\n");
    return novo_quadro;
}
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (vector<int> quadro){
	printw("\n\nControle de erro utilizando codigo de Hamming...\n\n");

    int bit_redundancia = 0;
    vector<int> codigo_hamming;
    vector<int> bits_paridade;
	/* Neste loop verifica-se a quantidade de bits de paridade que são necessários */
    while (quadro.size() + bit_redundancia + 1 > pow(2, bit_redundancia)){
        bit_redundancia++;
    }
    
    int tamanho_hamming = bit_redundancia + quadro.size();
    
    int posicao_paridade = 0;
    int posicao_dado = 0;

	/* Considera-se os bits enumerados a partir de 1*/
	/* Criado novo quadro contendo 0 nas posições de bit de´paridade */
    for (int i = 1; i <= tamanho_hamming; i++){
        if (i == pow(2, posicao_paridade)){
            codigo_hamming.push_back(0);
            posicao_paridade++;
        }
        else{
            codigo_hamming.push_back(quadro.at(posicao_dado));
            posicao_dado++;
        }
    }
	
	/* Calcula-se os bits de paridade pelo segundo método visto em sala de aula */
	/* Usa-se um vetor auxiliar para armazenar os bits de paridade: bits_paridade*/
    int posicao_analise;
    int xor_analise;
    bool primeiro_elemento;

    for (int i = 0; i < bit_redundancia; i++){
        primeiro_elemento = true;
        xor_analise = 0;
        posicao_analise = pow(2, i) - 1;
        while (posicao_analise < codigo_hamming.size()){
            if (primeiro_elemento == true){
                xor_analise = codigo_hamming[posicao_analise + 1];
                primeiro_elemento = false;
            }
            else{
                xor_analise ^= codigo_hamming[posicao_analise];
                xor_analise ^= codigo_hamming[posicao_analise + 1];
            }
            posicao_analise += 1;
            posicao_analise += pow(2, i) - 1 + 1;
        }
        bits_paridade.push_back(xor_analise);
    }

	/* O novo quadro é atualizado com bis de paridade nas posições corretas */
    int pos = 0;
    posicao_paridade = 0;

    for (int i = 1; i <= codigo_hamming.size(); i++)
    {
        if (i == pow(2, posicao_paridade))
        {
            codigo_hamming[i - 1] = bits_paridade.at(bit_redundancia - 1 - pos);
            pos++;
            posicao_paridade++;
        }
    }

    printw("\n\ncodigo_hamming: ");
    for (int i = 0; i < codigo_hamming.size(); i++)
        printw("%d",codigo_hamming.at(i));
    printw("\n\n");

    return codigo_hamming;

}

/************ RECEPÇÃO ************/

void CamadaEnlaceDadosReceptora(vector<int> quadro){
	
	printw("\n\nCamada de enlace dados receptora\n\n");

	vector<int> quadro_desenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro); //enquadramento feito por contagem de caracteres
	quadro_desenquadrado = CamadaEnlaceDadosReceptoraControleDeErro(quadro_desenquadrado);

	refresh();

	printw("\nMensagem desenquadrada: ");
	for (int i : quadro_desenquadrado)
		printw("%d", i);
	printw("\n\n");

	//chama proxima camada
	CamadaDeAplicacaoReceptora(quadro_desenquadrado);
}


vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro){
	vector<int> quadro_desenquadrado;

	// escolhe o tipo de enquadramento
	// 0 = Contagem de Caracters
	// 1 = inserção de bytes
	int enquadramento = 1;

	switch (enquadramento)
	{
	case 0: //contagem de caracteres
		quadro_desenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
		break;
	case 1: //insercao de bytes
		quadro_desenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
		break;
	default:
		exit(1);
		break;
	}
	return quadro_desenquadrado;
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro)
{

	vector<int> quadro_desenquadrado;

	for (int i = 8; i < quadro.size(); i++)
		quadro_desenquadrado.push_back(quadro[i]);

	return quadro_desenquadrado;
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro)
{
	refresh();

	string byte_str = "";
	string quadro_str = "";
	string flag = "00001111";
	string esc = "11110000";

	vector<int> novo_quadro;
	int counter = 1;
	bool ignore = false;

	for (int i = 0; i < quadro.size(); i++)
	{
		byte_str += to_string(quadro[i]);

		if (counter == BYTE)
		{
			if (((byte_str == flag) || (byte_str == esc)) && !ignore)
				ignore = true;
			else
			{
				quadro_str += byte_str;
				ignore = false;
			}

			counter = 0;
			byte_str = "";
		}
		counter++;
    }
    for (auto &i : quadro_str){
		novo_quadro.push_back(i - '0');
	}

	attron(COLOR_PAIR(2));
	printw("Desenquadramento inserção de bytes: ");
	attroff(COLOR_PAIR(2));

	for (int k : novo_quadro)
		printw("%d", k);
	printw("\n\n");

	return novo_quadro;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro)
{
	attron(COLOR_PAIR(2));
	printw("Camada de Enlace - Controle de Erros\n");
	attroff(COLOR_PAIR(2));

	int tipo_de_controle_de_erro = 2; //alterar de acordo com o teste
	vector<int> controle_erro;

	switch (tipo_de_controle_de_erro)
	{
	case 0: //bit de paridade par
		controle_erro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
		break;
	case 1: //CRC
		controle_erro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
		break;
	case 2: //codigo de hamming
		controle_erro = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
		break;
	}
	
	return controle_erro;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (vector<int> quadro)
{
	printw("\nRecebimento do controle de Paridade Par...\n");
	
	vector<int> recebimento_paridade_par;
	bool paridade = true;

	for (int i = 0; i < quadro.size() - 1; i++)
		recebimento_paridade_par.push_back(quadro.at(i));

	for (int i = 0; i < recebimento_paridade_par.size(); i++)
		if (recebimento_paridade_par.at(i) == 1)
			paridade = !paridade;

	if (quadro.back() == paridade)
		printw("\nRecebeu com sucesso\n");

	for (int i = 0; i < recebimento_paridade_par.size(); i++)
		printw("%d", recebimento_paridade_par.at(i));
	printw("\n");

	return recebimento_paridade_par;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (vector<int> quadro){
	
    printw("\n\nRealizando o controle de erro CRC receptor...\n\n");
	string polinomio_crc_32 = "100110000010001110110110111";
    vector<int> mensagem, novo_quadro;
    bool valido = true;

    if (quadro.size() <= polinomio_crc_32.length())
    {
        printw("\n\nErro, o quadro possui menos bits que o polinômio\n\n");
        exit(1);
    }

    novo_quadro = quadro;
    mensagem = quadro;
    mensagem.erase(mensagem.end() - 31, mensagem.end());

    for (int i = 0; i < mensagem.size(); i++)
    {
        if (quadro[i] == 1)
        {
            for (int j = 0; j < polinomio_crc_32.length(); j++)
                novo_quadro[j + i] = novo_quadro[j + i] == polinomio_crc_32[j] ? 0 : 1;
            /*  Compara o item i+j do novo quadro com o polinômio CRC 32 bits e armazena, no mesmo elemento,
                    0 se forem iguais, e 1 caso sejam diferentes. */
        }
    }

    for (int i = 0; i < mensagem.size(); i++)
    {
        if (novo_quadro[i] != 0)
            valido = false;
    }

    if (valido){
		for (int k : mensagem)
			printw("%d", k);
		printw("\n\n");
        return mensagem;
	}
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro){
	printw("\n\nDecodificando do codigo de hamming...\n\n");

    vector<int> decodificacao_hamming;
    int posicao_paridade = 0;

    for (int i = 1; i <= quadro.size(); i++){
        if (i == pow(2, posicao_paridade)){
            posicao_paridade++;
        }
        else{
            decodificacao_hamming.push_back(quadro.at(i - 1));
        }
    }
    for (int i = 0; i < decodificacao_hamming.size(); i++)
        printw("%d", decodificacao_hamming.at(i));
	printw("\n\n");

	return decodificacao_hamming;
}