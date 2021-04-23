#include "string_matching_automata.h"
void TryMatch(SMA& sma, string s){
	cout << "\n\n\nRICERCA DEL PATTERN: \""<< sma.getPattern() <<"\" NEL TESTO: \""<< s <<"\"\n OCCORRENZE:\n	";
	sma.match(s);
}
int main(){
	//SMA a("ciaociaoooia");
	SMA a("nanna");
	a.printDelta();
	TryMatch(a, "ninna nanna nonno nanni nannnannana");
}
