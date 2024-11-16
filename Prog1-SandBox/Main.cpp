#include <iostream>

using namespace std;

#include "SaveManager.h"
using namespace Save;

int main()
{
	SaveManager _sm = SaveManager("uwu.txt");


	cout << _sm.GetData<string>("thomas") << endl;
	_sm.SaveData<int>("uwu", 8);
	//_sm.SaveData<string>("uwu", "owo");
	return 0;
}