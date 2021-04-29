#include "samplesManager.h"
int main(void)
{
	samplesManager sm("./samples",".txt");
	sm.printStarryInfo();
	cout << "\nScegli l'id del file da selezionare: ";
	int i;
	cin >> i;
	cout <<"\n\n\n"<< sm.selectSampleText(i - 1);    
    return 0;
}
