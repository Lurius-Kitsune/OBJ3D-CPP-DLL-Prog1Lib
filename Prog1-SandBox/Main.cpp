#include <iostream>
#include "FileStream.h"
#include "DisplaySystem.h"
#include "DynamicArray.h"
#include "CharManip.h"

using namespace Tools;

void TestDynamicArray();
void TestCharManip();

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

	TestDynamicArray();
	TestCharManip();
}

void TestDynamicArray()
{
	Bob* _bob = new Bob("Bob");
	DynamicArray<Bob*> _tab = DynamicArray<Bob*>();
	_tab.Add(_bob);
	_tab.Add(new Bob(*_bob));
	DISPLAY(_tab[0]->GetName(), true);
	DISPLAY(_tab[1]->GetName(), true);
	_tab.Remove(_bob, true);
	DISPLAY(_tab[0]->GetName(), true);

	try
	{
		_tab[1]->GetName();
		DISPLAY(_tab[1]->GetName(), true); // Should Crash
	}
	catch (const exception& _excep)
	{
		DISPLAY(_excep.what(), true);
	}
	
}

void TestCharManip()
{
	string _phrase = "Je suis bob";
	DynamicArray<string> _splitPhrase = SplitString(_phrase, char(32));
	string _lowerPhrase = ToLowerString(_phrase);
	string _lowerUpper = ToUpperString(_phrase);

	DISPLAY(_splitPhrase[0], true);
}