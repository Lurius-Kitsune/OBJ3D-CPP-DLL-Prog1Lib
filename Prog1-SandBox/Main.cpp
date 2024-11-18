#include <iostream>

using namespace std;

#include "SaveManager.h"
using namespace Save;

int main()
{
	SaveManager _sm = SaveManager("uwu.txt");


	//SaveManager _owo = SaveManager("secret_owo.txt", "feur");


	_sm.SaveData<string>("thomas", "fd");
	//cout << "Valeur : " << _sm.GetData<string>("thomas") << endl;

	//_owo.SaveData<string>("test", "uwu");
	//cout << _owo.GetData<string>("test");
	return 0;
}