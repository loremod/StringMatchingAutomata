#include "naive_string_matching.h"

int main(){
	string T = "lorem ipsum lorenzo yes lore lore";
	string p = "lore";
	vector<int>* v  = naive_string_matching(T, p);
	cout << "\n\n\nRICERCA DEL PATTERN: \""<< p <<"\" NEL TESTO: \""<< T <<"\"\n OCCORRENZE:\n	";
	for(int _ = 0; _ < v->size(); _++)
		cout << v->at(_) << "	";
}
