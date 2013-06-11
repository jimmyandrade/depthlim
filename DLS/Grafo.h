#pragma once
#include <list>
#include <vector>

/** /class Grafo
	/brief Classe que representa um grafo.
*/
class Grafo {

	public:
		
		/** /var typedef int Indice */
		typedef int Indice;

		/** /var typedef int TipoNo
			/brief Os Nos sao representados por numeros inteiros.
		*/
		typedef int TipoNo;

		typedef std::list<TipoNo> ListaNos;

		typedef Grafo::ListaNos::const_iterator Iterador;

		typedef const std::string& TipoNomeArquivo;

		//# Construtor public que recebe como param um Indice int, indicando a quantidade de Nos do Grafo.
		Grafo(Indice Nos = 0);

		//# Construtor public que recebe como param uma string com o nome do arquivo a ser aberto.
		Grafo(TipoNomeArquivo NomeArquivo);

		// Grafo& operator=(const Grafo&);	/**< Nao foi implementada sobrecarga de operador de atribuicao */
		// ~Grafo(void);					/**< Nao foi implementada funcao destrutora */
		// Grafo(const Grafo&);				/**< Nao foi implementado construtor de copia public */

		void ImprimirListaNos(const ListaNos L, const char& Separador = '\t') const;
		bool ExisteNoNaLista(const ListaNos L, const TipoNo& N) const;

	private:
		//# Atributo interno que armazena o numero de nos
		Indice Nos_;

		/** Atributo interno que faz a contagem do numero de arestas.
			/brief Atualizado em todas as insercoes e remocoes de aresta que ocorrerem com sucesso.
		*/
		Indice Arestas_;

		//# Vetor de nos que possuem uma lista de nos adjacentes. Util para buscas no grafo.
		std::vector<ListaNos> NosAdjacentes;

		//# Metodo de busca em profundidade limitada (Depth Limited Search) no grafo.
		void DLS(TipoNo Origem, TipoNo* Visitado) const;

	public:

		/** /class Aresta
			/brief Classe que representa uma aresta. Armazena Indice de dois Nos e pode armazenar custo.
		*/
		class Aresta {

			private:
				TipoNo Destino_;	/**< Armazena o Indice do No de destino */
				TipoNo Origem_;		/**< Armazena o Indice do No de origem  */

			public:
				inline Aresta(TipoNo Destino, TipoNo Origem) : Destino_(Destino), Origem_(Origem) {}
				inline TipoNo Destino() const { return Destino_; }	/**< Getter: acessa o No de destino */
				inline TipoNo Origem() const { return Origem_; }	/**< Getter: acessa o No de origem  */

		}; // end class Aresta

	private:
		
		//# Realiza operações para inserir e remover arestas do grafo.
		bool Alterar(const Aresta& A, bool Modo);

		//# Recebe como param uma istream com informacoes sobre o grafo.
		void LeStream(std::istream& Entrada);

	public:

		//# Insere uma Aresta no Grafo
		inline bool Inserir(const Aresta& A) { return Alterar(A, 0); } 

		//# Retira uma Aresta do Grafo 
		inline bool Remover(const Aresta& A) { return Alterar(A, 1); }

		//# Retorna a quantidade de Nos no Grafo
		inline Indice Nos() const { return Nos_; }

		//# Retorna a quantidade de Aresta's no Grafo
		inline Indice Arestas() const { return Arestas_; }

		//# Verifica a existencia de uma Aresta no Grafo
		bool Existe(const Aresta& A) const;

		//# Imprime o Grafo (util para demonstracao)
		void Imprimir() const;

		TipoNo DLS(TipoNo NoInicial, TipoNo Objetivo, Indice Limite);

		ListaNos Expandir(Indice No);

}; // end class Grafo

