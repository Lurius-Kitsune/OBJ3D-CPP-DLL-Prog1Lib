#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include "Macro.h"
#include <fstream> // fichier

#pragma warning(disable : 4251)

namespace Tools
{
	class MYTOOL_API FileStream
	{
		string fullPath;
		string cryptageKey;
		u_int cryptageKeySize;
		bool isCrypt;
		fstream stream;
		ios_base::openmode openMode;

	public:
		string GetFullPath()const
		{
			return fullPath;
		}

	public:

		FileStream() = default;

		FileStream(const string& _fullPath, const bool _autoCreate = false
			, const string& _cryptageKey = "LaCleeDesP1", const bool _isCrypt = false,
			const ios_base::openmode& _openMode = ios_base::in | ios_base::out | ios_base::binary);

	public:
		bool IsValid()const
		{
			return stream.is_open();
		}
		void SetCryptageKey(const string& _newKey)
		{
			if (isCrypt) return;
			cryptageKey = _newKey;
		}
		void SetIsCryptFile(const bool _isCrypt = true)
		{
			isCrypt = _isCrypt;
		}
		void SetCryptFileWithKey(const string& _newKey)
		{
			SetIsCryptFile();
			SetCryptageKey(_newKey);
		}

	public:

		// operator == 
		bool operator==(const FileStream& _file)const
		{
			return fullPath == _file.fullPath;
		}


		// Afficher un nombre n de lignes à partir d'un index
		string* ReadAll();

		string Read(const streamsize& _length, const streampos& _position = -1);

		string ReadLine(const u_int& _lineIndex = 0);
    
		bool RemoveLine(const u_int& _lineIndex = 0);

		bool Remove(const streamsize& _length, const streampos& _position);

		bool Clear();

		bool Write(const string& _content, const streampos& _position = -1);

		streampos GetOffset(const u_int& _horizontal, const u_int& _vertical);

		int ComputeLineOfFile();

		streampos ComputeLenghOfFile();

		bool Crypt();

		bool Uncrypt();

	private:
		bool Write(const char* _content, const streamsize& _lengh, const streampos& _position);
	};
}