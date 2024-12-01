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
			AddStatistic("ProgramStarted");
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
		inline multimap<string, string> GetGamesData() const
		{
			return gamesData;
		}
	public:
		Logger(const bool _saveGamesData = true , const string& _encryptionKey = "LoggerKey");
		~Logger();

	private:
		void RecoverGamesData();
	public:
		void AddGameData(const pair<string, string>& _difficultyAndData);
		void AddGameData(const string& _difficulty, const string& _data);
		inline double AverageScore(const string& _difficulty);
		void AddStatistic(const pair<string, string>& _keyAndStatistic) const;
		void AddStatistic(const string& _key, const string& _statistic) const;
		void AddStatistic(const string& _key) const; //Adder
		template<typename Type = string>
		inline Type RetrieveStatistic(const string& _key) const
		{
			return dataManager->GetData<Type>(_key);
		}
	};
}