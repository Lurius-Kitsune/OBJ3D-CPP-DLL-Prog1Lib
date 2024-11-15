#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <type_traits>

#include <vector>

using namespace std;

typedef ios_base ib;

namespace Save
{
	template<typename T>
	struct MYTOOL_API DataNode
	{
		string name;
		T value;

		DataNode(const string& _name, const T& _value)
		{
			name = _name;
			value = _value;
		}

		/// <summary>
		/// Cette méthode retourne une représentation sous forme de chaîne de caractères de l'objet.
		/// </summary>
		/// <returns>
		/// string -->
		/// Par exemple, si `name` est "age" et `value` est "30", la méthode retournera "age:30".
		/// </returns>
		string ToString() const
		{
			return name + ":" + value;
		}
	};

	class MYTOOL_API SaveManager
	{
		string path;

	public:
		SaveManager(const string& _path);

		template<typename T>
		void SaveData(const DataNode<T>& _node);

		template<typename T>
		T GetData(const string& _key)
		{
			if (!KeyExists(_key)) throw exception("Key doesn't exist");
			
			ifstream _read = GetReadStream();
			unsigned int _index = GetKeyIndex(_key);
			_read.clear();
			_read.seekg(_index);
			T _data;
			try {
				string _lineValue;
				getline(_read, _lineValue);
				_lineValue.erase(std::remove(_lineValue.begin(), _lineValue.end(), '\0'), _lineValue.end());
				_lineValue.erase(std::remove(_lineValue.begin(), _lineValue.end(), ' '), _lineValue.end());
				_lineValue.erase(std::remove(_lineValue.begin(), _lineValue.end(), '\n'), _lineValue.end());
				_lineValue.erase(std::remove(_lineValue.begin(), _lineValue.end(), '\r'), _lineValue.end());
				_data = Convert<string, T>(SplitString(_lineValue, ":")[1]);
				cout << endl;
				return _data;
			}
			catch (const exception& _e)
			{
				throw exception("Unable to cast to type T");
			}
		}

		/// <summary>
		/// Vérifier si une clé donnée existe
		/// </summary>
		/// <param name="_key">string : clé</param>
		/// <returns>bool : existe ?</returns>
		bool KeyExists(const string& _key) const;


	//private:
		/// <summary>
		/// Créer le fichier
		/// </summary>
		void FileCreate() const;

		/// <summary>
		/// Récupérer une instance flux entrant
		/// </summary>
		/// <returns>ifstream</returns>
		ifstream GetReadStream() const;

		/// <summary>
		/// Récupérer une istance de flux sortant
		/// </summary>
		/// <param name="_openmode">ios_base::openmode --> Préciser quel mode d'ouverture (binary est compris dedans)</param>
		/// <returns>ofstream</returns>
		ofstream GetWriteStream(const int _openmode) const;

		/// <summary>
		/// Récupérer la ligne à laquelle se trouve la clé
		/// </summary>
		/// <param name="_key">string : clé</param>
		/// <returns>int : -1 si non trouvée | l'index de la ligne</returns>
		int GetKeyIndex(const string& _key) const;

		/// <summary>
		/// Méthode pour recréer le split d'un string
		/// </summary>
		/// <param name="_text">string : à split</param>
		/// <param name="_separator">char : sur quoi split</param>
		/// <returns>vector : tableau de string</returns>
		vector<string> SplitString(const string& _text, const char* _separator) const;


		/// <summary>
		/// Convertisseur entre types
		/// </summary>
		/// <typeparam name="Input">Type d'entrée</typeparam>
		/// <typeparam name="Result">Type de sortie attendu</typeparam>
		/// <param name="_input">Valeur</param>
		/// <returns>Valeur en type attendu</returns>
		template<typename Input, typename Result>
		Result Convert(const Input& _input) const
		{

			if (is_same<Input, string>::value) // Si la valeur d'entrée est un string
			{
				if (is_same<Result, int>::value) return std::stoi(_input);
				else if (is_same<Result, bool>::value) return (_input == "true");
				else if (is_same<Result, char>::value) return _input[0];
				// TODO A FAIRE LE STRING
			}
		}


	};


}



