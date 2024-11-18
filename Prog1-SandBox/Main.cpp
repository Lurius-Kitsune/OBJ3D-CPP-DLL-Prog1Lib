#include <iostream>

using namespace std;

#include "SaveManager.h"
using namespace Save;

int main()
{
	SaveManager _sm = SaveManager("uwu.txt");
	cout << _sm.GetData<string>("ddfefdefd");
	return 0;
}