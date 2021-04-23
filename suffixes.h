
using namespace std;
//confronta due stringhe: ritorna true se a � suffisso di b, 0 altrimenti
bool isSuffix(string a, string b){
	for(int i = 1; i <= a.length(); i++)
		if(a.at(a.length() - i) != b.at(b.length() - i))
			return false;
	return true;
}
//Trova la dimensione della pi� grande sottostringa di sf che � suffissa di p
int bestSubSuffix(string sf, string p){
	for(int i = sf.length(); i > 0; i--)
		if(isSuffix(sf.substr(0,i), p))
			return i;
	return 0;
}
