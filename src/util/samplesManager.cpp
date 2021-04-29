#include <iostream>
#include <dirent.h>

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
long int findSize(char file_name[])
{

    FILE* fp = fopen(file_name, "r");
  
    if (fp == NULL) {
        cout << "File Not Found!\n";
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file(in bytes)
    long int res = ftell(fp);
  
    fclose(fp);
  
    return res;
}
class samplesManager{
	private:
		int n; //numero di file
		string extension; //estensione del file, "" se non si vogliono file con una estensione specifica 
		string* fileNames;
		string  dirName;
		
		int getNumberOfFiles(){
			int x = 0;
			struct dirent *de; 
			
			DIR *dr = opendir(dirName.c_str());
			
    		while ((de = readdir(dr)) != NULL)
				if(de->d_name[0] != '.' and finishWith(de->d_name, de->d_namlen, ".txt"))
					x++;
    		closedir(dr);
    		return x;
		}
		
		string* getFileNames(){
			struct dirent *de; 
			
			DIR *dr = opendir(dirName.c_str());
			
    		while ((de = readdir(dr)) != NULL)
    		if(de->d_name[0] != '.' and finishWith(de->d_name, de->d_namlen, ".txt"))//TO DO: de->d_name[0] != '.' in effetti potrebbe anche essere omesso(con le nuove modifiche non dovrebbe servire piu')
            {
				string s = "";
				s = dirName + s + de->d_name;
				int totalDim = s.length() + 1;//dirNameLength + de->d_namlen;
            	char fileName[totalDim];
            	strcpy(fileName, s.c_str());
            	//concatInto(fileName, dirName, de->d_name, dirNameLength, de->d_namlen);
            	cout << fileName;
				cout << de->d_name << " " << de->d_namlen << "	" << findSize(fileName) << endl;
			}
            	
    		closedir(dr);
		}
		string getCorrectDirName(char _dirName[]){
			string s = _dirName;			
			if(s.at(s.length()-1)!='/')
            		s+="/";
            return s;
		}
	public:
		samplesManager(const char _dirName[], string extensionType=""){
			this->dirName = getCorrectDirName(_dirName);
			this->extension = extensionType;
			n = getNumberOfFiles();
			cout << n;
			fileNames = getFileNames();
//			struct dirent *de; 
//			
//			DIR *dr = opendir(_dirName);
//			
//			if (dr == NULL)  // ritorna null se non può aprire la directory
//    		{
//        		cout << "Could not open current directory";
//    		}
//    		while ((de = readdir(dr)) != NULL)
//    		if(de->d_name[0] != '.' and finishWith(de->d_name, de->d_namlen, ".txt"))//TO DO: de->d_name[0] != '.' in effetti potrebbe anche essere omesso(con le nuove modifiche non dovrebbe servire piu')
//            {
//				string s = "";
//            	if(dirName.at(dirName.length()-1)!='/')
//            		s="/";
//				s = dirName + s + de->d_name;
//				int totalDim = s.length() + 1;//dirNameLength + de->d_namlen;
//            	char fileName[totalDim];
//            	strcpy(fileName, s.c_str());
//            	//concatInto(fileName, dirName, de->d_name, dirNameLength, de->d_namlen);
//            	cout << fileName;
//				cout << de->d_name << " " << de->d_namlen << "	" << findSize(fileName) << endl;
//			}
//            	
//    		closedir(dr);
    		
		}
		static bool directoryExists(char _dir[]){
			DIR *dr = opendir(_dir);
			if (dr == NULL)  // ritorna false se non può aprire la directory
				return false;
			return true;
		}
		
};
int main(void)
{
	samplesManager sm("./samples",".txt");
//    struct dirent *de; 
//   
//   char dirName[] = "./samples/";
//   int dirNameLength = sizeof(dirName)/sizeof(char) - 1;
//   cout << dirNameLength << endl;
//    DIR *dr = opendir(dirName);
//  
//    if (dr == NULL)  // ritorna null se non può aprire la directory
//    {
//        cout << "Could not open current directory";
//        return 0;
//    }
//  
//    while ((de = readdir(dr)) != NULL)
//    		if(de->d_name[0] != '.' and finishWith(de->d_name, de->d_namlen, ".txt"))//TO DO: de->d_name[0] != '.' in effetti potrebbe anche essere omesso(con le nuove modifiche non dovrebbe servire piu')
//            {
//            	string s = "";
//				s = dirName + s + de->d_name;
//				int totalDim = s.length() + 1;//dirNameLength + de->d_namlen;
//            	char fileName[totalDim];
//            	strcpy(fileName, s.c_str());
//            	//concatInto(fileName, dirName, de->d_name, dirNameLength, de->d_namlen);
//            	string s2 = fileName;
//            	cout << fileName;
//				cout << de->d_name << " " << de->d_namlen << "	" << findSize(fileName) << endl;
//			}
//            	
//    closedir(dr);    
    return 0;
}
