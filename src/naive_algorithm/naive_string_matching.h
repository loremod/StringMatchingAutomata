#include<iostream>
#include<vector>

using namespace std;

bool string_match(string a, string b){
	return (!a.compare(b));
}

vector<int>* naive_string_matching(string T, string p){ //T: testo, p: stringa da trovare nel testo
	vector<int>* sol = new vector<int>();				//Vettore delle soluzioni
	int n = T.length();
	int m = p.length();
//	if(!n or !m) return NULL;//nel caso in cui una delle due stringhe sia vuota
	for(int i = 0; i < n - m + 1; i++){
		if(string_match(T.substr(i,m),p))
			sol->push_back(i);
	}
	return sol;
}
