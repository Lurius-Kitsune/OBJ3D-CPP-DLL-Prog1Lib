#pragma once
#pragma warning(disable : 4984)

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <type_traits>

#include "FileStream.h"
#include "DynamicArray.h"

#define if_c if constexpr

#define CRYPT if(encryptionKey) _stream.Crypt()
#define UNCRYPT if(encryptionKey) _stream.Uncrypt()

using namespace std;

typedef ios_base ib;

namespace Tools
{
	class MYTOOL_API SaveManager
	{
		string path;
		string* encryptionKey;

	public:
		SaveManager(const string& _path);
		SaveManager(const string& _path, const string& _encryptionKey);
		~SaveManager();

		/// <summary>
		/// Sauvegarder une donn�e
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <param name="_data">Valeur</param>
		template<typename T>
		void SaveData(const string& _key, const T& _data)
		{
			FileStream _fs = GetStream(ios_base::in | ios_base::out);
			const string& _sData = _key + ":" + Convert<T, string>(_data) + "\n";
			UNCRYPT;
			if (KeyExists(_key))
			{
				DynamicArray<int> _keyPos = GetKeyIndex(_key);
				_fs.RemoveLine(GetKeyIndex(_key)[1]);
			}
			_fs.Write(_sData);
			CRYPT;
		}
		 
		/// <summary>
		/// Obtenir une donn�e � partir de sa cl�
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <returns>Donn�e</returns>
		template<typename T>
		T GetData(const string& _key)
		{
			//FileStream* _decrypt = new FileStream(path, false, (encryptionKey ? *encryptionKey : "\0"), encryptionKey, ios_base::binary | ios_base::in | ios_base::out);
			//if(encryptionKey) _decrypt->Uncrypt();
			//delete _decrypt;

			//FileStream* _write = new FileStream(path, false, *encryptionKey, false, ios_base::binary | ios_base::in | ios_base::out);
			//if (!KeyExists(_key))
			//{
			//	_write->Crypt();
			//	delete _write;
			//	throw exception("Key doesn't exist");
			//}
			//string _lineValue = _write->ReadLine(GetKeyIndex(_key)[1]);
			//ostringstream _content = _write->ReadAll();
			//DynamicArray<string> _tokens = SplitString(_lineValue, ":");
			//unsigned int _contentParts = _tokens.GetSize();
			//string _totalContent = "";

			//for (unsigned int _i = 1; _i < _contentParts; _i++)
			//{
			//	_totalContent += string(_i > 1 ? ":" : "") + _tokens[_i];
			//} // Tout �a au cas o� la cha�ne r�cup�r�e contient le symbole :
			//

			//delete _write;

 		//	FileStream* _crypt = new FileStream(path, false, *encryptionKey, false, ios_base::out | ios_base::in);
			//_crypt->Clear();
			//*_crypt << _content;
			//if(encryptionKey) _crypt->Crypt();
			//delete _crypt;

			FileStream _stream = GetStream(ios_base::out | ios_base::in);
			UNCRYPT;
			if (!KeyExists(_key))
			{
				CRYPT; _stream.Crypt();
				throw exception("Key doesn't exist");
			}
			string _lineValue = _stream.ReadLine(GetKeyIndex(_key)[1]);
			DynamicArray<string> _tokens = SplitString(_lineValue, ":");
			unsigned int _contentParts = _tokens.GetSize();
			string _totalContent = "";

			for (unsigned int _i = 1; _i < _contentParts; _i++)
			{
				_totalContent += string(_i > 1 ? ":" : "") + _tokens[_i];
			} // Tout �a au cas o� la cha�ne r�cup�r�e contient le symbole :
			
			CRYPT;

			return Convert<string, T>(_totalContent);
		}

		/// <summary>
		/// V�rifier si une cl� donn�e existe
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>bool : existe ?</returns>
		bool KeyExists(const string& _key) const;


	private:
		/// <summary>
		/// Cr�er le fichier
		/// </summary>
		void FileCreate() const;

		/// <summary>
		/// V�rifier si le fichier existe
		/// </summary>
		/// <returns>bool</returns>
		bool FileExists() const;

		/// <summary>
		/// Construire un FileStream
		/// </summary>
		/// <param name="_openmode">Mode d'�criture</param>
		/// <returns>FileStream</returns>
		inline FileStream GetStream(const int _openmode) const;

		/// <summary>
		/// R�cup�rer l'index de la cl� et la ligne sur laquelle elle se trouve
		/// </summary>
		/// <param name="_key">Cl�</param>
		/// <returns>DynamicArray<int> (0 : index | 1 : ligne) | -1 si non trouv�e</returns>
		DynamicArray<int> GetKeyIndex(const string& _key) const;
		
		/// <summary>
		/// M�thode pour recr�er le split d'un string
		/// </summary>
		/// <param name="_text">string : � split</param>
		/// <param name="_separator">char : sur quoi split</param>
		/// <returns>vector : tableau de string</returns>
		DynamicArray<string> SplitString(const string& _text, const char* _separator) const;

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
			cout << is_same<Input, Result>::value << endl;

			// Si les types sont identiques
			if_c(is_same<Input, Result>::value) return _input;

			// Si l'entr�e est un string
			if_c(is_same<Input, string>::value) return static_cast<Result>(_input);

			// Si l'entr�e est un tableau de caract�res (char[])
			if_c(is_same<Input, char*>::value) {
				return static_cast<Result>(string(_input)); // Convertit const char[] en std::string
			}

			// Si l'entr�e est un type arithm�tique (comme int, float)
			if_c(is_arithmetic_v<Input>) return to_string(_input);

			throw exception("Unable to convert type");
		}


	};
}




