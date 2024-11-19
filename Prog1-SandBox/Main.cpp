#include <iostream>
#include "FileStream.h"
#include "DisplaySystem.h"
#include "DynamicArray.h"
#include "CharManip.h"
#include "SaveManager.h"

using namespace std;
using namespace Tools;

void TestDynamicArray();
void TestCharManip();
void TestOptimiseRandom();
void TestEncryptDecrypt();
void TestSave();

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
};

int main()
{
    Config();
    
	//TestDynamicArray();
	//TestCharManip();
	//TestOptimiseRandom();
	//TestEncryptDecrypt();
	TestSave();
	return -1;
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

void TestOptimiseRandom()
{
	const double _testRandom = RandomValue<double>(1.5, 2.5);
	const float _testRandom2 = RandomValue<float>(1.5f, 2.2f);
	DISPLAY(_testRandom, true);
	DISPLAY(_testRandom2, true);
	Bob** _testObjectArray = new Bob * [5]
		{
			new Bob("Thomas"),
				new Bob("Sev"),
				new Bob("Kacper"),
				new Bob("Maxime"),
				new Bob("Lucas")
		};
	Bob* _testRandomBob = GetRandomObjectInArray<Bob*>(_testObjectArray, 5);
	DISPLAY(_testRandomBob->GetName(), true);
}

void TestEncryptDecrypt()
{
	FileStream _file = FileStream("Thomas.txt", true, "MaCleAMoi");
	//_file.SetIsCryptFile();
	_file.Write("Bob2", _file.ComputeLenghOfFile());
	//Console::DisplayRainbowCenterMultiLine(_file.ReadAll(), _file.ComputeLineOfFile());
	DISPLAY(_file.Read(_file.ComputeLenghOfFile()), true);
	_file.Crypt();
	DISPLAY(_file.Read(_file.ComputeLenghOfFile()), true);
	_file.Uncrypt();
	DISPLAY(_file.Read(_file.ComputeLenghOfFile()), true);
	_file.SetCryptageKey("NouvelleKeyTest");
	_file.Crypt();
	DISPLAY(_file.Read(_file.ComputeLenghOfFile()), true);
	_file.Uncrypt();
	DISPLAY(_file.Read(_file.ComputeLenghOfFile()), true);
}

void TestSave()
{
	FileStream _file = FileStream("Thomas.txt", true, "MaCleAMoi");
	cout << *_file.ReadAll() << endl;
	_file.Crypt();
	SaveManager _sm = SaveManager("Thomas.txt", "MaCleAMoi");
	SaveManager _sm = SaveManager("Truc.txt");
	//_sm.SaveData("test", "truc");
	_sm.SaveData("chepa", 100);
	_sm.SaveData("feur", 1);
	_sm.SaveData("toucher", bool(true));
	cout << _sm.GetData<string>("feur");
}
