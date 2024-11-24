#pragma once
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)

#include <iostream>
#include <windows.h> 
#include <utility>
#include <vector>
#include <string>
#include <codecvt>

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
    /// <summary>
    /// Obtient le full path par rapport a un path relatif au dossier actuel
    /// </summary>
    /// <returns>Le full path</returns>
    string GetFullPath()
    {
        return AddFullPathToRelativePath(directoryPath);
    }

public:
    /// <summary>
    /// Constructeur avec le dossier avec lequel travailler
    /// </summary>
    /// <param name="_directoryPath">Le dossier dans lequel du va check le contenu</param>
    DirectoryManager(const string& _directoryPath)
    {
        directoryPath = _directoryPath;
    }


private:
    /// <summary>
    /// Parcours les sous dossier
    /// </summary>
    /// <param name="_pathDirectory"> Dossier dans lequel il checher </param>
    /// <param name="_baseRelativePath"> Trouve le path relatif par rapport au _pathDirectory</param>
    /// <param name="_relativePaths">Modification par référence de la liste de path a l'intérieur du dossier</param>
    /// <param name="_depthDirectory">Si on doit parcours a l'intérieur des dossier trouver</param>
    void BrowseSubDirectory(const wstring& _pathDirectory, const wstring& _baseRelativePath, 
        vector<string>& _relativePaths, const bool _depthDirectory = false);
public:
    /// <summary>
    /// Obtien le fullpath du dossier actuel
    /// </summary>
    /// <returns>fullpath du dossier</returns>
    string GetCurrentPathDirectory();
    
    /// <summary>
    /// Obtiens les dossier contenu dans le dossier 
    /// </summary>
    /// <param name="_fullDirectory">Si il faut retourner le path relatif (false) ou le fullpath(true)</param>
    /// <returns>paths dans le dossiers actuel</returns>
    vector<string> DirectoriesOfDirectory(const bool _fullDirectory = false);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="_depthDirectory">Si on doit parcours a l'intérieur des dossier trouver</param>
    /// <param name="_fullDirectory">Si il faut retourner le path relatif (false) ou le fullpath(true)</param>
    /// <returns>Paths du contenu dans le dossier et sous dossiers si _depthDirectory est true </returns>
    vector<string> ContentOfDirectory(const bool _depthDirectory = false, const bool _fullDirectory = false);

public:
    /// <summary>
    /// Tranforme un path relatif en fullpath 
    /// </summary>
    /// <param name="_path">le path relatif</param>
    /// <returns>le fullpath</returns>
    string AddFullPathToRelativePath(const string& _path);
    /// <summary>
    /// Tranforme des paths relatifs en fullpaths
    /// </summary>
    /// <param name="_paths">les paths relatifs</param>
    /// <returns>les fullpaths</returns>
    vector<string> AddFullPathToRelativePaths(const vector<string>& _paths);

};






