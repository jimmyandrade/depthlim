#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Grafo.h"

/** /var typedef const char* CString
	/brief String utilizada para compatibilidade com C
*/

//# Construtor do Grafo
Grafo::Grafo(Indice Nos) : Nos_(Nos), Arestas_(0) {

	std::cout << std::endl << "Construindo grafo com " << Nos << " nos" << std::endl;

	for (Indice i=0; i<Nos; ++i) {
		ListaNos Lista;
		NosAdjacentes.push_back(Lista);
	}

}

bool Grafo::ExisteNoNaLista(const ListaNos L, const TipoNo& N) const {

	for(Iterador i = L.begin(); i!=L.end(); ++i) {
		if(*i == N) { return true; }
	}

	return false;

}

bool Grafo::Alterar(const Aresta& A, bool Modo) {

	TipoNo NoDestino = A.Destino();
	TipoNo NoOrigem =  A.Origem();

	if ( NoDestino >= Nos_ || NoOrigem >= Nos_) {
		return false;
	}

	// Verifica se a Aresta que está tentando Inserir/Remover existe no Grafo
	bool Existe = ExisteNoNaLista ( NosAdjacentes[NoDestino], NoOrigem );
	
	if (Modo==0) {
		if(Existe) { return false; }
		NosAdjacentes[NoOrigem].push_back(NoDestino);
		NosAdjacentes[NoDestino].push_back(NoOrigem);
		++Arestas_;

	}
	else {
		if(!Existe) { return false; }
		NosAdjacentes[NoOrigem].remove(NoDestino);
		NosAdjacentes[NoDestino].remove(NoOrigem);
		--Arestas_;
	}

	return true;

}

void Grafo::ImprimirListaNos(const ListaNos L, const char& Separador) const {

	for (Grafo::Iterador i = L.begin(); i!=L.end(); ++i) {

		std::cout<< *i << Separador;

	}

}

void Grafo::Imprimir() const {

	for(Indice i=0; i<Nos_; ++i) {

		std::cout << i << " => ";
		ImprimirListaNos(NosAdjacentes[i]);
		std::cout << std::endl;

	}

}

bool Grafo::Existe(const Aresta& A) const {

	TipoNo Destino = A.Destino();
	TipoNo Origem = A.Origem();

	if ( Destino >= Nos_ || Origem >= Nos_) {
		return false;
	}

	if (ExisteNoNaLista(NosAdjacentes[Destino], Origem)) {
		return true;
	}
	else {
		return false;
	}

}

Grafo::ListaNos Grafo::Expandir(Indice No) {

	return NosAdjacentes[No];

}

void Grafo::LeStream(std::istream& Entrada) {

	TipoNo Origem, Destino;

	if(!Entrada.eof()) {
		//# Le no arquivo de dados o numero de Nos do grafo.
		Entrada >> Nos_;
	}

	std::cout << std::endl << "Foram lidos " << Nos_ << " nos no grafo." << std::endl;

	while(!Entrada.eof()) {

		Entrada >> Origem >> Destino;
		Aresta A(Destino, Origem);

		std::cout << std::endl << "Encontrada aresta representada por " << std::endl << Origem << "," << Destino << ")" << std::endl;

		//# Adiciona as Aresta's lidas no Grafo
		if (!Inserir(A)) {

			std::cout << std::endl << "Problema ao tentar inserir aresta." << std::endl;
			return;

		}

	}

}

//# Le um arquivo os dados de um grafo

Grafo::Grafo(TipoNomeArquivo NomeArquivo) {

	std::cout << std::endl << "Iniciando leitura do arquivo " << NomeArquivo << "..." << std::endl;

	std::ifstream Entrada(NomeArquivo, std::ifstream::in);

	if(!Entrada.is_open()) {
		std::cout << std::endl << "Nao foi possivel abrir o arquivo " << NomeArquivo << std::endl;
		std::cout << "Verifique se o arquivo se encontra na mesma pasta que o programa" << std::endl;
		return;
	}
	else {
		std::cout << "Arquivo " << NomeArquivo << " lido com sucesso. Montando grafo..." << std::endl;
		LeStream(Entrada);
		Entrada.close();
		std::cout << "Grafo montado." << std::endl;
	}
	
}

Grafo::TipoNo Grafo::DLS(TipoNo No, TipoNo Objetivo, Indice Limite) {

	if( Limite >= 0 ) {
		if ( No == Objetivo ) {
			return No;
		}

		ListaNos Expandidos = Expandir(No);

		for (Iterador i = Expandidos.begin(); i != Expandidos.end(); ++i) {
			DLS(*i, Objetivo, Limite-1);
		}

	}

	return -1;

}