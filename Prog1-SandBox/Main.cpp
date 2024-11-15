#include <iostream>

using namespace std;

#include "SaveManager.h"
using namespace Save;

int main()
{
	SaveManager _sm = SaveManager("uwu.txt");

	int _savedInt = _sm.GetData<int>("feur");
	bool _test = _sm.GetData<bool>("sodomite");
	cout << _savedInt+100 << endl;
	cout << _test << endl;

	return 0;
}