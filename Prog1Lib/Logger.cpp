#include "pch.h"
#include "Logger.h"
#define CRYPT 
#define UNCRYPT 

Tools::Logger::Logger(const bool _saveGamesData, const string& _encryptionKey)
{
	dataManager = new SaveManager("Data.log", _encryptionKey);
	gamesDataFile = nullptr;
	if (_saveGamesData)
	{
		gamesDataFile = new FileStream("GamesData.log", true, _encryptionKey, true);
	}
}

Tools::Logger::~Logger()
{
	delete dataManager;
}


void Tools::Logger::RetrieveGameData()
{
	gamesData = multimap<string, string>();
	gamesDataFile->Uncrypt();
	const u_int& _linesOfFile = gamesDataFile->ComputeLineOfFile();
	vector<string> _mapInVector;
	string _lineValue;

	for (u_int _indexLine = 0; _indexLine < _linesOfFile; _indexLine++)
	{
		_lineValue = gamesDataFile->ReadLine(_indexLine);
		_mapInVector = SplitString(_lineValue, ':');
		gamesData.insert(make_pair(_mapInVector[0], _mapInVector[1]));
	}
	gamesDataFile->Crypt();
}

void Tools::Logger::AddGameData(const pair<string, string>& _difficultyAndData)
{
	gamesData.insert(_difficultyAndData);
	const string& _valueInFile = _difficultyAndData.first + ":" + _difficultyAndData.second + "\n";
	gamesDataFile->Write(_valueInFile, gamesDataFile->ComputeLenghOfFile());
}

void Tools::Logger::AddGameData(const string& _difficulty, const string& _data)
{
	AddGameData(make_pair(_difficulty, _data));
}

double Tools::Logger::AverageScore(const string& _difficulty)
{
	double _count = 0;
	double _allScoresAdd = 0.0;
	string _scoreString;
	pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
		_scoresInDifficulty = gamesData.equal_range(_difficulty);
	for (multimap<string, string>::iterator _score = _scoresInDifficulty.first;
		_score != _scoresInDifficulty.second; ++_score)
	{
		_scoreString = _score->second;
		_allScoresAdd += stod(_scoreString);
		++_count;
	}
	return _allScoresAdd / _count;
}
