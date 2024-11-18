#include "pch.h"
#include "FileStream.h"

Tools::FileStream::FileStream(const string& _fullPath, const bool _autoCreate,
	const string& _cryptageKey, const bool _isCrypt,
	const ios_base::openmode& _openMode)
{
	openMode = _openMode;
	openMode |= ios_base::binary;
	fullPath = _fullPath;
	isCrypt = _isCrypt;
	cryptageKey = _cryptageKey;
	cryptageKeySize = static_cast<u_int>(cryptageKey.size());
	if (_autoCreate)
	{
		ifstream(_fullPath, ios_base::app);
	}
	stream = fstream(_fullPath, openMode);
}

string* Tools::FileStream::ReadAll()
{
	const u_int& _fileSize = ComputeLineOfFile();
	string* _contents = new string[_fileSize];
	for (u_int _i = 0; _i < _fileSize; _i++)
	{
		_contents[_i] = ReadLine(static_cast<u_int>(GetOffset(0, _i)));
	}
	return _contents;
}

string Tools::FileStream::Read(const streamsize& _length, const streampos& _position)
{
	if (!IsValid()) return "";

	string _content(_length, '\0');

	if (_position != -1)
	{
		stream.seekg(_position);
	}
	stream.read(&_content[0], _length);
	return _content;
}

string Tools::FileStream::ReadLine(const u_int& _lineIndex)
{
	if (!IsValid()) return "";

	streampos _position = GetOffset(0, _lineIndex);
	string _content = "";

	stream.seekg(GetOffset(0, _lineIndex));
	getline(stream, _content);
	return _content;
}

bool Tools::FileStream::RemoveLine(const u_int& _lineIndex)
{
	streampos _cursor = _lineIndex > static_cast<u_int>(ComputeLineOfFile()) ? ComputeLenghOfFile() : GetOffset(0, _lineIndex) ;
	if(ComputeLineOfFile() > 1) _cursor = _cursor.operator-(_lineIndex == ComputeLineOfFile() ? 1 : 0);
	return Remove(ReadLine(_lineIndex).size() + 1, _cursor);
}

bool Tools::FileStream::Remove(const streamsize& _length, const streampos& _position)
{
	if (!IsValid()) return false;

	stream.clear();

	string _content = Read(_position, 0);
	_content += Read(ComputeLenghOfFile() - _position, _position + _length);
	_content.erase(remove(_content.begin(), _content.end(), '\r'), _content.end());
	_content.erase(remove(_content.begin(), _content.end(), '\0'), _content.end());

	fstream _write = fstream(fullPath, ios::out | ios_base::binary);
	_write << _content;
	_write.close();

	stream.open(fullPath, openMode);

	return stream.good();
}

bool Tools::FileStream::Clear()
{
	if (ComputeLenghOfFile() == 0) return false;
	return Remove(ComputeLenghOfFile(), 0);;
}

bool Tools::FileStream::Write(const string& _content, const streampos& _position)
{
	if (isCrypt) 
		return Uncrypt() && 
		Write(_content.c_str(), _content.size(), _position) 
		&& Crypt();
	return Write(_content.c_str(), _content.size(), _position);
}


streampos Tools::FileStream::GetOffset(const u_int& _horizontal, const u_int& _vertical)
{
	u_int _index = 0, _l = 0;
	char _c;
	stream.seekg(0, stream.beg);
	while (_l != _vertical) // Aller � la bonne ligne
	{
		if (stream.get(_c))
		{
			const int _bob = static_cast<const int>(stream.tellg());
			if (_c == '\n') _l++;
			_index++;
		}
		else
		{
			break;
		}
	}
	stream.seekg(_index);
	const streampos& _pos = stream.tellg();

	stream.clear();
	stream.seekg(0, stream.beg);
	return _pos;
}

streampos Tools::FileStream::ComputeLenghOfFile()
{

	stream.seekp(0, stream.end);
	const streampos& _lengh = stream.tellg();
	stream.seekp(0);
	return _lengh;
}

bool Tools::FileStream::Crypt()
{
	if (!IsValid() || isCrypt) return false;
	string _modifiedText;
	const string& _baseText = Read(ComputeLenghOfFile());
	const u_int& _baseTextSize = static_cast<u_int>(_baseText.size());
	int _modifiedInt;
	for (u_int _index = 0; _index < _baseTextSize; _index++)
	{
		_modifiedInt = int(_baseText[_index] + cryptageKey[_index % cryptageKeySize]);
		_modifiedText += char(_modifiedInt);
	}
	Clear();
	Write(_modifiedText.c_str(), _modifiedText.size(), -1);
	isCrypt = true;
	return true;
}

bool Tools::FileStream::Uncrypt()
{
	if (!IsValid() || !isCrypt) return false;
	string _modifiedText;
	const string& _baseText = Read(ComputeLenghOfFile());
	const u_int& _baseTextSize = static_cast<u_int>(_baseText.size());
	int _modifiedInt;
	for (u_int _index = 0; _index < _baseTextSize; _index++)
	{
		_modifiedInt = int(_baseText[_index] - cryptageKey[_index % cryptageKeySize]);
		_modifiedText += char(_modifiedInt);
	}
	Clear();
	Write(_modifiedText.c_str(), _modifiedText.size(), -1);
	isCrypt = false;
	return true;
}

bool Tools::FileStream::Write(const char* _content, const streamsize& _lengh, const streampos& _position)
{
	if (!IsValid()) return false;

	string _remainingContent;

	if (_position != -1)
	{
		stream.seekp(_position);
		getline(stream, _remainingContent, '\0');

		stream.clear();
		stream.seekg(_position);
	}
	stream.write(_content, _lengh);

	if (!_remainingContent.empty())
	{
		stream.write(_remainingContent.c_str(), _remainingContent.size());
	}
	return stream.good();
}

int Tools::FileStream::ComputeLineOfFile()
{
	int _line = 1;
	char _c;
	while (stream.get(_c))
	{
		if (_c == '\n' || _c == '\r') _line++;
	}
	stream.clear();

	stream.seekg(0, stream.beg);
	return _line;
}