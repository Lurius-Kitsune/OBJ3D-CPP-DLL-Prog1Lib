#include <iostream>
#include "FileStream.h"
#include "DisplaySystem.h"
#include "Tab.h"

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
    FileStream _file = FileStream("bob.txt", true);
    //_file.Write("\nBob1", _file.ComputeLenghOfFile());
    //Console::DisplayRainbowCenterMultiLine(_file.ReadAll(), _file.ComputeLineOfFile());
    //DISPLAY(_file.ReadAll(), true);

	Bob* _bob = new Bob("Bob");
	Tab<Bob*> _tab = Tab<Bob*>();
	_tab.Add(_bob);
	_tab.Add(new Bob(*_bob));
    DISPLAY(_tab[0]->GetName(), true);
    DISPLAY(_tab[1]->GetName(), true);
    _tab.Remove(_bob, true);
    DISPLAY(_tab[0]->GetName(), true);
    //DISPLAY(_tab[1]->GetName(), true);
}