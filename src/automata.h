#include<iostream>
#include<unordered_map>

#define MISSING 0

using namespace std;

class automata{
	
	private:
		
		//ELEMENTI DELLA QUINTUPLA
		char* sigma;		//alfabeto delle lettere usate
		int Q;				//numero di stati(vanno da 0 a Q-1)
		int **delta;		//matrice della funzione di transizione
		int s0;				//stato iniziale
		int *F;      		//stati finali in cui la stringa in input è "accettata", con F sottoinsieme dell'insieme degli stati
		
		//DIMENSIONI E TABELLA HASH
		int dim_sigma; 						//dimensione di sigma
		int dim_F;  						//dimensione di F
		unordered_map<char,int> indexOf; 	//per ogni carattere dell'alfabeto sigma associa un indice distinto
		
		//METODI PRIVATE
		void initialize_hash_table(){		//all'i-esimo carattere viene associato i
			indexOf[MISSING] = 0;
			for(int i=0;i<dim_sigma;i++)
				indexOf[sigma[i]] = i + 1;  //0 è riservato ai caratteri mancanti(MISSING)
		}
		
	protected:
		
		//METODI PROTECTED: in modo che sia anche visibile alle funzioni membro della classe derivata
		bool isFinal(int state){			//per vedere se lo stato in questione fa parte di uno stato accettante
			for(int i=0;i<dim_F;i++)
				if(state == F[i])
					return true;
			return false;
		}
		
	public:
		//COSTRUTTORI
		//richiede, come parametro, ogni singolo elemento della quintupla(e le dimensioni degli array)
		automata(char* alphabet, int states, int** transition, int start, int* accepted,int n_sigma, int n_F){
			sigma = alphabet;
			Q = states;
			delta = transition;
			s0 = start;
			F = accepted;
			dim_sigma = n_sigma;
			dim_F = n_F;
			initialize_hash_table();
		}
		//setta tutto a NULL o a 0, tutto da definire in seguito con l'ausilio dei metodi public definiti
		automata(){
			sigma = NULL;
			delta = NULL;
			F = NULL;
			Q = s0 = dim_sigma = dim_F = 0;
		}
		
		//valuta la stringa in input sulla base della funzione di transizione dell'automa
		bool evaluate(string s){
			int q = s0;//stato corrente
			for(int i=0;i<s.length();i++)
				q = delta[q][indexOf[s.at(i)]];
			return isFinal(q);
		}
		
		//PRINT
		automata& printSigma(){
			for(int i = 0; i < dim_sigma; i++)
				cout << sigma[i] << "	";
			return *this;
		}
		automata& printDelta(){
			cout <<"	";
			printSigma();
			for(int i = 0; i < Q; i++){
				cout << endl << i << ")	";
				if(delta == NULL) cout << "NULL";
				else
				for(int j = 0; j < dim_sigma; j++)
					cout << delta[i][j + 1] << "	";
			}
			return *this;
		}
		
		//GET
		char* getSigma(){
			return sigma;
		}
		int getSigmaDim(){
			return dim_sigma;
		}
		int getQ(){
			return Q;
		}
		int** getDelta(){
			return delta;
		}
		int getS0(){
			return s0;
		}
		int* getF(){
			return F;
		}
		int getIndexOf(char c){
			return indexOf[c];
		}
		
		//SET
		automata& setSigma(char* new_sigma,int n){
			sigma = new_sigma;
			dim_sigma = n;
			initialize_hash_table();
			return *this;
		}
		automata& setQ(int new_Q){
			Q = new_Q;
			return *this;
		}
		automata& setDelta(int** new_delta){
			delta = new_delta;
			return *this;
		}
		automata& setS0(int new_s0){
			s0 = new_s0;
			return *this;
		}
		automata& setF(int* new_F, int n){
			F = new_F;
			dim_F = n;
			return *this;
		}
		automata& change_delta(int q, char a, int new_state){
			delta[q][indexOf[a]] = new_state; 
			return *this;
		}
};


