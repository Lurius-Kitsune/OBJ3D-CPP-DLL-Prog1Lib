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
	ifstream _read = GetReadStream();

	string _line;
	while (getline(_read, _line))
	{
		char* _data = strtok_s(const_cast<char*>(_line.c_str()), ":", nullptr);
		if (_data == _key) return true;
	}
	return false;
}

