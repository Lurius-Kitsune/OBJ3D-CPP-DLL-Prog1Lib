#include <iostream>

using namespace std;

#include "SaveManager.h"
using namespace Save;

int main()
{
	SaveManager _sm = SaveManager("uwu.txt");


	_sm.SaveData<string>("thomas", "marguerite");
	cout << _sm.GetData<string>("thomas") << endl;


	return 0;
}