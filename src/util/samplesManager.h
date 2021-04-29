#include <iostream>
#include <dirent.h>
#include <math.h>
#include<fstream>
using namespace std;


bool finishWith(char word[], int len, string end){
	int d = end.length(); // lunghezza del suffisso
	if(len<d) return false;
	for(int i = 1; i <= d; i++ )
		if(word[len-i] != end.at(d-i))
			return false;
	return true;
}
void concatInto(char dest[], char src1[], char src2[], int size1, int size2){
	for(int i = 0; i < size1; i++)
		dest[i] = src1[i];
	for(int i = 0; i < size2; i++)
		dest[size1 + i] = src2[i];
}
void printStar(int i=1){
	while(i--)cout<<'*';
}

/*	Ho fatto questa classe per poter gestire l'utilizzo dei campioni di testo
	presenti nella cartella 'samples'(ma samplesManager funziona con una directory generica, non si
	limita al nome di questa directory specifica).
	In questo modo, quando dovrò comparare gli algoritmi di string matching(specialmente per quanto riguarda 
	i tempi di esecuzione) potrò importare a run-time il testo che più preferisco, potendomi anche basare sulla dimensione
	dei vari file(espressa con gli asterischi, richiamando il metodo printStarryInfo()).
	Così facendo posso fare dei test utilizzando un testo molto grande e che contiene un alfabeto di caratteri alfanumerici vasto(interessante
	specialmente dal punto di vista dell'automa a stati finiti per quanto concerne il computo della funzione di transizione).
	Ad ogni nuova esecuzione, l'istanza della classe va a prelevare i nomi dei file di testo(potrebbe prendere anche altri tipi di file, ma 
	non ne abbiamo bisogno) presenti nella cartella specificata. Quindi, in qualsiasi momento si possono inserire nuovi file di testo
	campioni per effettuare nuovi test.
*/

class samplesManager{
	private:
		int n; //numero di file
		string extension; //estensione del file, "" se non si vogliono file con una estensione specifica 
		string* fileNames;
		int*   fileDimensions;
		string  dirName;
		
		int findNumberOfFiles(){
			int x = 0;
			struct dirent *de; 
			
			DIR *dr = opendir(dirName.c_str());
			
    		while ((de = readdir(dr)) != NULL)
				if(de->d_name[0] != '.' and finishWith(de->d_name, de->d_namlen, extension))
					x++;
    		closedir(dr);
    		return x;
		}
			
		string* findFileNames(){
			struct dirent *de; 
			DIR *dr = opendir(dirName.c_str());
			string *names = new string[n];
			int i=0;
			
    		while ((de = readdir(dr)) != NULL)
    			if(de->d_name[0] != '.' and finishWith(de->d_name, de->d_namlen, extension))//TO DO: de->d_name[0] != '.' in effetti potrebbe anche essere omesso(con le nuove modifiche non dovrebbe servire piu')
            		names[i++] = de->d_name;
			
    		closedir(dr);
    		return names;
		}
		
		string findCorrectDirName(const char _dirName[]){
			string s = _dirName;			
			if(s.at(s.length()-1)!='/')
            		s+="/";
            return s;
		}
		
		long int findSize(const char file_name[]){
		
		    FILE* fp = fopen(file_name, "r");
		  
		    if (fp == NULL) {
		        cout << "File Not Found!\n";
		        return -1;
		    }
		  
		    fseek(fp, 0L, SEEK_END);
		  
		    // ottenere la dimensione del file(in byte)
		    long int res = ftell(fp);
		  
		    fclose(fp);
		  
		    return res;
		}
		
		int* findFileDimensions(){
			int* dims = new int[n];
			for(int i = 0 ; i < n ; i++){
				string fullName = dirName + fileNames[i];
				dims[i] = findSize(fullName.c_str()); 
			}
			return dims;
		}

		string _selectSampleText(string name){
			string fullName = dirName + name;
			ifstream t(fullName);
			string str;
			
			t.seekg(0, ios::end);  
			str.reserve(t.tellg());
			t.seekg(0, ios::beg);

			str.assign((istreambuf_iterator<char>(t)),
			            istreambuf_iterator<char>());
			            
			return str; 
		}
		
	public:
		samplesManager(const char _dirName[], string extensionType=""){
			this->dirName = findCorrectDirName(_dirName);
			this->extension = extensionType;
			n = findNumberOfFiles();
			fileNames = findFileNames();
			fileDimensions = findFileDimensions();		
		}
		static bool directoryExists(char _dir[]){
			DIR *dr = opendir(_dir);
			if (dr == NULL)  // ritorna false se non può aprire la directory
				return false;
			return true;
		}
		string* getFileNames(){
			return fileNames;
		}
		void printFiles(){
			for(int i = 0 ; i < n ; i++)
				cout << fileNames[i] << endl;
		}
		void printFilesWithDimensions(){
			for(int i = 0 ; i < n ; i++)
				cout << fileNames[i] << "			" << fileDimensions[i];
		}
		int maxDimension(){
			int max = -1;
			for(int i = 0 ; i < n ; i++)
				if(max < fileDimensions[i])
					max = fileDimensions[i];
			return max;
		}
		int minDimension(){
			int min = fileDimensions[0];
			for(int i = 1 ; i < n ; i++)
				if(min > fileDimensions[i])
					min = fileDimensions[i];
			return min;
		}
		void printFilesWithStarWeight(int max_stars){//param max_stars sta ad indicare il massimo numero di stelle
			int max = maxDimension();
			int min = minDimension();
			int dif = max - min;
			if(dif == 0) dif = 1;
			
			for(int i = 0 ; i < n ; i++){
				int val =  fileDimensions[i] - min;
				double q = round((max_stars - 1) * val / (dif * 1.0));
				cout << i+1 << ") " << fileNames[i] << "			";printStar(q + 1);
				cout << endl;
			}
		}
		void printStarryInfo(int max_stars=5){
			cout<<"	FILE				DIMENSIONE\n";
			printFilesWithStarWeight(5);
		}
		string selectFileName(int it){
			return fileNames[it];
		}
		string selectSampleText(int it){
			return _selectSampleText(selectFileName(it));
		}
		string selectSampleText(string name){
			return _selectSampleText(name);
		}
		void printSampleText(int it){
			cout << _selectSampleText(selectFileName(it));
		}
		void printSampleText(string name){
			cout << _selectSampleText(name);
		}
		
};
