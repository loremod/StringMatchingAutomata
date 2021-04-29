#include <chrono>
#include "../string_matching_automata.h"
#include "../naive_algorithm/naive_string_matching.h"
#include "../util/useful_code.h"
#include "../util/samplesManager.h"

#define NUM_FUNC	2 //numero di funzioni da confrontare

using namespace std::chrono;

//template<class T> void ask(string question, T& response);
//template<class T> void showVector(vector<T>* v);
vector<int>* automata_string_matching(string T, string p);
void fetch_function_results(vector<int>** where_to_store, vector<int>* (**functions_to_execute)(string,string), string T, string p);
bool checkCorrectness(vector<int>**);
void samplesOrInput(string& txt);

vector<int>* (*string_matching[NUM_FUNC])(string, string) {naive_string_matching, automata_string_matching};
string funcs[NUM_FUNC] = {"Naive algorithm","Finite Automata algorithm"};
vector<int>* f_results[NUM_FUNC];
double f_times[NUM_FUNC];

int main(){
	
	//Titolo e descrzione
	cout << "\nConfronto tra algoritmi di string matching\n\n";
	cout << "Gli algoritmi considerati sono: ";printArray(funcs,NUM_FUNC,"; ");
	cout << endl << endl;
	
	//Richiedere Testo e pattern
	string T,p;
 	samplesOrInput(T);
	ask("\nInserisci pattern: ",p);
	
	//Eseguire gli algoritmi e ottenere output e tempi di esecuzione
	fetch_function_results(f_results,string_matching,T,p);
	
	//Naive
	cout << endl << funcs[0] <<":\n";
	showVector(f_results[0]);
	
	//Automata
	cout << endl << funcs[1] <<":\n";
	showVector(f_results[1]);
	
	//Correctness
	if(checkCorrectness(f_results))cout << "\nGli algoritmi hanno prodotto lo stesso risultato";
	else	cout << "\nI valori non coincidono";
	
	//Comparing functions time execution 
}

vector<int>* automata_string_matching(string T, string p){
	SMA sma(p);
	return sma.getMatches(T);
}

void fetch_function_results(vector<int>** where_to_store, vector<int>* (**functions_to_execute)(string,string), string T, string p){
	for(int i = 0 ; i < NUM_FUNC ; i++){
		auto start = high_resolution_clock::now();
		where_to_store[i] = functions_to_execute[i](T, p);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count() << endl;
	}
}
bool checkCorrectness(vector<int>** sequences){
	//Controllare le dimensioni
	for(int i = 0 ; i < NUM_FUNC ; i++)
		if(sequences[i]->size() != sequences[0]->size()) return false;
	//Controllare i valori(con l'ipotesi che siano gia' ordinati)
	for(int j = 0 ; j < sequences[0]->size() ; j++)
		for(int i = 0 ; i < NUM_FUNC ; i++)
			if(sequences[0]->at(j) != sequences[i]->at(j))	return false;
	return true;
}
void samplesOrInput(string& txt){
	char r;
	
	while(true){
		ask("\nVuoi utilizzare dei campioni di testo prelevati da file?(S/N): ",r);
		if(r=='S' or r=='s' or r=='n' or r=='N')
			break;
	}
	
	if(r=='n' or r=='N'){
		ask("\nInserisci testo: ", txt);
		return;	
	}
	
	int i;
	samplesManager sm("../util/samples",".txt");
	sm.printStarryInfo();
	ask("\nScegli l'id del file da selezionare: ",i);
	txt = sm.selectSampleText(i - 1);
}
//template<class T>
//void ask(string question, T& response){
//	cout << question;
//	getline(cin, response);
//}
//template<class T> 
//void showVector(vector<T>* v){
//	for(const auto &e : *v)
//		cout << e << "	";
//	cout << endl;
//}

