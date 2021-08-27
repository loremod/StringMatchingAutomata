#include <iostream>
#include<vector>
using namespace std;
//Delle funzioni per raggruppare codice utile

void ask(string question, string& response){
	cout << question;
	getline(cin >> ws, response);
}

template<class T>
void ask(string question, T& response){
	cout << question;
	cin >> response;
}

template<class T> 
void printVectorElements(vector<T>* v){
	for(const auto &e : *v)
		cout << e << "	";
	cout << endl;
}

template<class T>
void showVector(vector<T>* v){
	cout << "Number of occurences: " << v->size() << endl;
	if(v->size()){
		cout << "Occurences: ";
		printVectorElements(v);
	}
}

template<class T>
void printArray(T* arr, int len, string separator=" "){
	for(int i = 0 ; i < len ; i++) 
		cout << *(arr + i) << separator;
}
