#include "string_matching_automata.h"
void TryMatch(SMA& sma, string s){
	cout << "\n\n\nRICERCA DEL PATTERN: \""<< sma.getPattern() <<"\" NEL TESTO: \""<< s <<"\"\n OCCORRENZE:\n	";
	sma.match(s);
}
int main(){
	//SMA a("ciaociaoooia");
	SMA a("nanna");
	cout << "Delta di a:\n";
	a.printDelta();
	TryMatch(a, "ninna nanna nonno nanni nannnannana");
	cout << endl << endl << endl;
	cout << "Delta di b:\n";
	SMA b("ababaca");
	b.printDelta();
	TryMatch(b,"abababacaba");
	TryMatch(b,"qabakasdababacwasvababacawd ss");
}
