#include "automata.h"

int main(){
	/*	--Sono presenti due funzioni di transioni differenti, l'automa modificherà il proprio delta sulla base del valore del flag:
				-True) la funzione di transizione rappresenta un automa che accetta le stringhe con un numero pari di 'a'
				-False) la funzione di transizione rappresenta un automa che accetta le stringhe con un numero pari di 'b'
		COMANDI:
			stop: termina l'esecuzione del programma.
			change: inverte il flag
	*/
	bool flag=true;
	int dim_sigma = 2;
	char sigma[dim_sigma] = {'a','b'};
	int Q = 2;
	
	int **delta = new int*[Q];
	for(int i=0;i<Q;i++){
		delta[i] = new int[dim_sigma + 1]; //+1 perchè si tengono in considerazione tutti i caratteri mancanti
		delta[i][0] = 0;
	}
	delta[0][1] = 1 ;
	delta[0][2] = 0 ;
	delta[1][1] = 0 ;
	delta[1][2] = 1 ;
	
	int s0 = 0;
	int dim_F = 1;
	int F[] = {0};
	
	automata a1(sigma,Q,delta,s0,F,dim_sigma,dim_F);
	cout << "--Automa che accetta le stringhe con un numero pari di 'a'--\n";
	while(true){
		string s;
		cin >> s;
		if(s=="stop")break;
		if(s=="change"){
			flag = !flag;
			if(flag){
				//la funzione di transizione rappresenta un automa che accetta le stringhe con un numero pari di 'a'
				a1.change_delta(0,sigma[0],1)
				  	.change_delta(0,sigma[1],0)
					.change_delta(1,sigma[0],0)
					.change_delta(1,sigma[1],1);
				cout << "--Automa che accetta le stringhe con un numero pari di 'a'--\n";
			}else{
				//la funzione di transizione rappresenta un automa che accetta le stringhe con un numero pari di 'b'
				a1.change_delta(0,sigma[0],0)
					.change_delta(0,sigma[1],1)
					.change_delta(1,sigma[0],1)
					.change_delta(1,sigma[1],0);
				cout << "--Automa che accetta le stringhe con un numero pari di 'b'--\n";
			}
			cin >> s;
		}
		if(a1.evaluate(s)) //evaluate(s) ritorna true se la stringa termina in uno stato accettante 
			cout << "La stringa e' accettata" << endl;
		else
			cout << "La stringa non e' accettata" << endl;
	}
}
