#include "pch.h"
#include "SaveManager.h"

Tools::SaveManager::SaveManager(const string& _path)
{
	path = _path;
	encryptionKey = nullptr;
	if (!FileExists()) FileCreate();
}

Tools::SaveManager::SaveManager(const string& _path, const string& _encryptionKey)
{
	path = _path;
	encryptionKey = new string(_encryptionKey);
	if (!FileExists()) FileCreate();
}

Tools::SaveManager::~SaveManager()
{
	if (encryptionKey) delete encryptionKey;
}

void Tools::SaveManager::FileCreate() const
{
	GetStream(ios_base::out).Write("", 0);
}

bool Tools::SaveManager::KeyExists(const string& _key) const
{
	return GetKeyIndex(_key)[0] != -1;
}

Tools::DynamicArray<int> Tools::SaveManager::GetKeyIndex(const string& _key) const
{
	DynamicArray<int> _result = DynamicArray<int>();
	FileStream _fs = GetStream(ios_base::in);
	FileStream _fs = GetStream(ios_base::in | ios_base::out);
	_fs.Uncrypt();
	unsigned int _index = 0, _line = 0;

	string _lineValue = _fs.ReadLine(0);
	while (_lineValue.size() > 0)
	{
		if (SplitString(_lineValue, ":")[0] == _key)
		{
			_result.Add(_index);
			_result.Add(_line);
			return _result;
		}
		_line++;
		_index += static_cast<u_int>(_lineValue.size()) + 1;
		_index += static_cast<int>(_lineValue.size()) + 1;
		_lineValue = _fs.ReadLine(_line);
	}
	_result.Add(-1);

	return _result;
}


Tools::FileStream Tools::SaveManager::GetStream(const int _openmode) const
{
	return FileStream(path, false, (encryptionKey ? *encryptionKey : " "), true, ios_base::binary | _openmode);
}

bool Tools::SaveManager::FileExists() const
{
	return GetStream(ios_base::in).IsValid();
}

Tools::DynamicArray<string> Tools::SaveManager::SplitString(const string& _text, const char* _separator) const
{
	DynamicArray<string> _tokens = DynamicArray<string>();
	char* _lineCopy = new char[size(_text) + 1];
	strcpy_s(_lineCopy, _text.size() + 1, _text.c_str());
	char* _context = nullptr;

	char* _token = strtok_s(_lineCopy, _separator, &_context);
	while (_token != nullptr)
	{
		_tokens.Add(_token);
		_token = strtok_s(nullptr, _separator, &_context);
	}
	delete[] _lineCopy;

	return _tokens;
}