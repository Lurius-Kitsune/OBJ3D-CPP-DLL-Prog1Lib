#include <iostream>

using namespace std;

#include "SaveManager.h"
using namespace Save;

int main()
{
	SaveManager _sm = SaveManager("uwu.txt");


	//SaveManager _owo = SaveManager("secret_owo.txt", "feur");


	_sm.SaveData<string>("thomas", "marguerite");
	//_owo.SaveData<string>("quoi", "feur");
	//cout << _owo.GetData<string>("quoi") << endl;

	cout << _sm.GetData<string>("thomas") << endl;


	return 0;
}