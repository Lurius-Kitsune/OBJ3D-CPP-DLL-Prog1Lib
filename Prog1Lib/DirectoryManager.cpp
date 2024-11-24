#include "pch.h"
#include "DirectoryManager.h"

void DirectoryManager::BrowseSubDirectory(const wstring& _pathDirectory, const wstring& _baseRelativePath, 
    vector<string>& _relativePaths, const bool _depthDirectory)
{
    HANDLE _hList;
    WIN32_FIND_DATA _fileData;

    wstring _fullPath = _pathDirectory + L"\\*.*";
    if ((_hList = FindFirstFile(_fullPath.c_str(), &_fileData)) == INVALID_HANDLE_VALUE) return;

    do
    {
        wstring _element = _fileData.cFileName;

        wstring _relativePath = _baseRelativePath + L"\\" + _element;
        if (_fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (_element != L"." && _element != L".." && _depthDirectory)
                BrowseSubDirectory((_pathDirectory + L"\\" + _element), (_baseRelativePath + L"\\" + _element), _relativePaths, _depthDirectory);
        }
        else
            //if (_element != L"." && _element != L"..")
            _relativePaths.push_back(string(_relativePath.begin(), _relativePath.end()));

    } while (FindNextFile(_hList, &_fileData));

    FindClose(_hList);
}

string DirectoryManager::GetCurrentPathDirectory()
{
    const int _capacity = MAX_PATH;
    wchar_t _name[_capacity];
    int _currentDirectory = GetCurrentDirectory(_capacity, _name);
    if (_currentDirectory == ERROR_INSUFFICIENT_BUFFER) throw exception();
    const wstring& _wstringPath = wstring(_name + 0, _name + _currentDirectory);
    return string(_wstringPath.begin(), _wstringPath.end());
}

vector<string> DirectoryManager::DirectoriesOfDirectory(const bool _fullDirectory)
{
    vector<string> _directories;
    HANDLE _hList;
    WIN32_FIND_DATA _fileData;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> _converter;
    wstring _pathDirectory = _converter.from_bytes(GetCurrentPathDirectory()) + L"\\" + _converter.from_bytes(directoryPath);
    wstring _fullPath = _pathDirectory + L"\\*.*";
    if ((_hList = FindFirstFile(_fullPath.c_str(), &_fileData)) == INVALID_HANDLE_VALUE)
        return _directories;
    do
    {
        wstring _element = _fileData.cFileName;

        if ((_fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            (_element != L"." && _element != L".."))
            _directories.push_back(string(_element.begin(), _element.end()));

    } while (FindNextFile(_hList, &_fileData));

    FindClose(_hList);
    if (_fullDirectory)
        return AddFullPathToRelativePaths(_directories);
    return _directories;
}

vector<string> DirectoryManager::ContentOfDirectory(const bool _depthDirectory, const bool _fullDirectory)
{
    wstring_convert<codecvt_utf8_utf16<wchar_t>> _converter;
    wstring _pathDirectory = _converter.from_bytes(GetCurrentPathDirectory()) + L"\\" + _converter.from_bytes(directoryPath),
            _relativeDirectoryName = _converter.from_bytes(directoryPath);
    if (_pathDirectory[_pathDirectory.size() - 1] != L'\\')
    {
        _pathDirectory += L'\\';
    }

    vector<string> _relativePaths;

    BrowseSubDirectory(_pathDirectory, _relativeDirectoryName, _relativePaths, _depthDirectory);

    if (_fullDirectory)
        return AddFullPathToRelativePaths(_relativePaths);
    return _relativePaths;
}


string DirectoryManager::AddFullPathToRelativePath(const string& _relativePath)
{
    return GetCurrentPathDirectory() + _relativePath;
}

vector<string> DirectoryManager::AddFullPathToRelativePaths(const vector<string>& _relativePaths)
{
	vector<string> _fullPaths;
	for (const string& _path : _relativePaths)
	{
		_fullPaths.push_back(AddFullPathToRelativePath(_path));
	}
	return _fullPaths;
}
