#include "automata.h"
#include "struct_array.h"
#include "suffixes.h"
#include <vector>
//String Matching Automata(SMA)
class SMA: public automata{
	private:
		
		string p;	//pattern
		
		//METODI PRIVATI
		int countDistinct(string p){	//ritorna il numero di caratteri distinti in p, utilizzato per ottenere la dimensione dell'array sigma
			int len = 0;
			unordered_map<char,bool> seen; //tiene in considerazione i caratteri gia'  visti
			//setta tutto a false
			for(int i = 0 ; i < p.length(); i++)
				seen[p.at(i)] = false;
			//controlla se un carattere non e' stato contato(e in tal caso aumenta len di 1)
			for(int i = 0 ; i < p.length(); i++){
				if(!seen[p.at(i)]){
					seen[p.at(i)] = true;
					len++;
				}
			}
			return len;
		}
		Array<char>* computeSigma(string p){ 	//ritorna un array di tutti i differenti caratteri presenti nel pattern e aggiorna la dimensione
			int len = countDistinct(p);
			Array<char>* _sigma = new Array<char>();
			_sigma->array = new char[len];
			_sigma->length = len;
			int x=0;//indice
			unordered_map<char,bool> seen; //tiene in considerazione i caratteri gia'  visti
			//setta tutto a false
			for(int i = 0 ; i < p.length(); i++)
				seen[p.at(i)] = false;
			//controlla se un carattere non e' stato contato(e in tal caso aumenta x di 1)
			for(int i = 0 ; i < p.length(); i++){
				if(!seen[p.at(i)]){
					seen[p.at(i)] = true;
					_sigma->array[x] = p.at(i);
					x++;
				}
			}
			return _sigma;	
		}
		int** computeDelta(string p){ 	//ritorna la matrice della funzione di transizione 
			int _Q = getQ();
			char* _sigma = getSigma();
			int n_sigma = getSigmaDim(); //n_sigma contiene il valore di sigma
			int** delta = new int*[_Q];
			
			//OBIETTIVO: trovare la piu' grande sottostringa di p (sub_p) che risulta essere suffisso di str
			for(int i = 0; i < _Q; i++){ 
				int k = i < p.size()-1 ? i : p.size()-1;//Per evitare i casi impossibili e non far avvenire l'errore IndexOutOfRange
				string sub_p = p.substr(0, 1 + k);
				delta[i] = new int[n_sigma + 1]; 		//(n_sigma + 1) perche' delta[i][0] e' riservato ai caratteri non presenti nel pattern
				delta[i][0] = 0;						//Se il carattere in questione non e' presente in p allora sicuramente lo stato dovra'  essere 0
				for(int j = 0; j < n_sigma; j++){
					string str = p.substr(0,i);
					str += _sigma[j];
					delta[i][j + 1] = bestSubSuffix(sub_p, str);
				}
			}
			return delta;
		}
		int* computeF(string p){ 	//ritorna l'insieme F
			int* F = new int[1];
			F[0] = p.size();
			return F;
		}
		
		vector<int>* _match(string s){
			vector<int>* v = new vector<int>();
			int q = getS0();//stato iniziale(0)
			for(int i=0;i<s.length();i++){
				q = getDelta()[q][getIndexOf(s.at(i))];
			 	if(isFinal(q)) v->push_back(i - p.size() + 1);
			}
			return v;
		}
	public:
		SMA(string p){
			this->p = p;
			
			//Sigma
			Array<char>* _sigma = computeSigma(p);
			setSigma(_sigma->array,_sigma->length);
			
			//Q
			setQ(p.length()+1);
			
			//Delta
			setDelta(computeDelta(p));
			
			//S0
			setS0(0);
			
			//F
			int* _F = computeF(p);
			setF(_F, 1);
		}
		
		//Stampa tutte le occorrenze del pattern con il relativo spostamento
		void match(string s){
			vector<int>* v = getMatches(s);
			for(const auto &match : *v)
				cout << match << "	";
		}
		
		
		//GET
		string getPattern(){
			return p;
		}
		//ritorna un vettore contenente tutte gli spostamenti validi del pattern p nel testo s
		vector<int>* getMatches(string s){
			vector<int>* v = _match(s);
			return v;
		}
};
