#include <iostream>
#include "FileStream.h"
#include "DisplaySystem.h"
#include "DynamicArray.h"

using namespace Tools;

class Bob
{
    string name;
public:

	Bob()
	{
		name = "";
	}

	Bob(const string& _name)
	{
		name = _name;
	}
	string GetName()const
	{
		return name;
	}

	// Operator == 
	bool operator==(const Bob& _bob)const
	{
		return name == _bob.name;
	}
};

int main()
{
    Config();
    FileStream _file = FileStream("Thomas.txt", true);
    _file.Write("\nBob1", 0);
    //Console::DisplayRainbowCenterMultiLine(_file.ReadAll(), _file.ComputeLineOfFile());
    //DISPLAY(, true);
}