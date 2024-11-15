#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef ios_base ib;

namespace Save
{
	template<typename T>
	struct DataNode
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

	class SaveManager
	{
		string path;

	public:
		SaveManager(const string& _path);

		template<typename T>
		void SaveData(const DataNode<T>& _node);

		template<typename T>
		T GetData(const string& _key);

		bool KeyExists(const string& _key) const;


	private:
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

	};

}



