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
		/// Cette m�thode retourne une repr�sentation sous forme de cha�ne de caract�res de l'objet.
		/// </summary>
		/// <returns>
		/// string -->
		/// Par exemple, si `name` est "age" et `value` est "30", la m�thode retournera "age:30".
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
		/// V�rifier si une cl� donn�e existe
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>bool : existe ?</returns>
		bool KeyExists(const string& _key) const;


	//private:
		/// <summary>
		/// Cr�er le fichier
		/// </summary>
		void FileCreate() const;

		/// <summary>
		/// R�cup�rer une instance flux entrant
		/// </summary>
		/// <returns>ifstream</returns>
		ifstream GetReadStream() const;

		/// <summary>
		/// R�cup�rer une istance de flux sortant
		/// </summary>
		/// <param name="_openmode">ios_base::openmode --> Pr�ciser quel mode d'ouverture (binary est compris dedans)</param>
		/// <returns>ofstream</returns>
		ofstream GetWriteStream(const int _openmode) const;

		/// <summary>
		/// R�cup�rer la ligne � laquelle se trouve la cl�
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>int : -1 si non trouv�e | l'index de la ligne</returns>
		int GetKeyIndex(const string& _key) const;

		/// <summary>
		/// M�thode pour recr�er le split d'un string
		/// </summary>
		/// <param name="_text">string : � split</param>
		/// <param name="_separator">char : sur quoi split</param>
		/// <returns>vector : tableau de string</returns>
		vector<string> SplitString(const string& _text, const char* _separator) const;


		/// <summary>
		/// Convertisseur entre types
		/// </summary>
		/// <typeparam name="Input">Type d'entr�e</typeparam>
		/// <typeparam name="Result">Type de sortie attendu</typeparam>
		/// <param name="_input">Valeur</param>
		/// <returns>Valeur en type attendu</returns>
		template<typename Input, typename Result>
		Result Convert(const Input& _input) const
		{

			if (is_same<Input, string>::value) // Si la valeur d'entr�e est un string
			{
				if (is_same<Result, int>::value) return std::stoi(_input);
				else if (is_same<Result, bool>::value) return (_input == "true");
				else if (is_same<Result, char>::value) return _input[0];
				// TODO A FAIRE LE STRING
			}
		}


	};


}



