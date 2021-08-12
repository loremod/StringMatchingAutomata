#include "string_matching_automata.h"

void TryMatch(SMA& sma, string s){
	cout << "\n\n\nRICERCA DEL PATTERN: \""<< sma.getPattern() <<"\" NEL TESTO: \""<< s <<"\"\n OCCORRENZE:\n	";
	sma.match(s);
}
int main(){
	//SMA a("ciaociaoooia");
	SMA a("nanna");
	cout << "Funzione di transizione di a:\n";
	a.printDelta();
	TryMatch(a, "ninna nanna nonfj nannik nannnannana");
	cout << endl << endl << endl;
	cout << "Funzione di transizione di b:\n";
	SMA b("ababaca");
	b.printDelta();
	TryMatch(b,"abababacaba");
	TryMatch(b,"qabakasdababacwasvababacawd sababacas");
}
