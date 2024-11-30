#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <map>

#include "SaveManager.h"
#include "CharManip.h"
using namespace std;

namespace Tools
{
	class MYTOOL_API Logger
	{
		multimap<string,string> gamesData;
		SaveManager* dataManager;
		FileStream* gamesDataFile;
	public:
		void operator ++ () const
		{
			if (!dataManager->KeyExists("ProgramStarted"))
			{
				dataManager->SaveData("ProgramStarted", 0);
			}
			int _programStarted = dataManager->GetData<int>("ProgramStarted");
			dataManager->SaveData("ProgramStarted", ++_programStarted);
		}

		void operator -- () const
		{
			if (!dataManager->KeyExists("GameStarted"))
			{
				dataManager->SaveData("GameStarted", 0);
			}
			int _gameStarted = dataManager->GetData<int>("GameStarted");
			dataManager->SaveData("GameStarted", ++_gameStarted);
		}
	public:
		Logger(const bool _saveGamesData = true , const string& _encryptionKey = "LoggerKey");
		~Logger();

	private:
		void RetrieveGameData();
	public:
		void AddGameData(const pair<string, string>& _difficultyAndData);
		void AddGameData(const string& _difficulty, const string& _data);

		double AverageScore(const string& _difficulty);
	};
}