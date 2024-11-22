#pragma once
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)

#include <iostream>
#include <windows.h> 
#include <utility>
#include <vector>
#include <string>
#include <codecvt>
#include <string>

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

using namespace std;

class MYTOOL_API DirectoryManager
{
    string directoryPath;
public:
    string GetFullPath()
    {
        return AddFullPathToRelativePath(directoryPath);
    }

public:
    DirectoryManager(const string& _directoryPath)
    {
        directoryPath = _directoryPath;
    }


private:
    void BrowseSubDirectory(const wstring& _pathDirectory, const wstring& _baseRelativePath, 
        vector<string>& _relativePaths, const bool _depthDirectory = false);
public:
    string GetCurrentPathDirectory();
    
    vector<string> DirectoriesOfDirectory(const bool _fullDirectory = false);

    vector<string> ContentOfDirectory(const bool _depthDirectory = false, const bool _fullDirectory = false);

public:
    string AddFullPathToRelativePath(const string& _path);
    vector<string> AddFullPathToRelativePaths(const vector<string>& _paths);

};






