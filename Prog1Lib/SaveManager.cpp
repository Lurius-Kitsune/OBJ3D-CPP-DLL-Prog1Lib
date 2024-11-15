#include "pch.h"
#include "SaveManager.h"

Save::SaveManager::SaveManager(const string& _path)
{
	path = _path;
	if (!GetReadStream()) FileCreate();
}

ifstream Save::SaveManager::GetReadStream() const
{
	return ifstream(path, ib::binary | ib::in);
}

ofstream Save::SaveManager::GetWriteStream(const int _openmode) const
{
	return ofstream(path, ib::binary | _openmode);
}

void Save::SaveManager::FileCreate() const
{
	cout << "File " << path << " created" << endl;
	ofstream _write = GetWriteStream(ib::out);
	_write << "";
	_write.close();
}

bool Save::SaveManager::KeyExists(const string& _key) const
{
	return GetKeyIndex(_key) != -1;
}

int Save::SaveManager::GetKeyIndex(const string& _key) const
{
	ifstream _read = GetReadStream();
	unsigned int _index = 0;

	string _line;
	while (getline(_read, _line))
	{
		if (SplitString(_line, ":")[0] == _key) return _index;
		_index += _line.size() + 1;
	}
	return -1;
}


vector<string> Save::SaveManager::SplitString(const string& _text, const char* _separator) const
{
	char* _lineCopy = new char[size(_text) + 1];
	strcpy_s(_lineCopy, _text.size() + 1, _text.c_str());
	char* _context = nullptr;

	vector<string> _tokens;

	char* _token = strtok_s(_lineCopy, _separator, &_context);
	while (_token != nullptr)
	{
		_tokens.emplace_back(_token);
		_token = strtok_s(nullptr, _separator, &_context);
	}
	delete[] _lineCopy;

	return _tokens;
}