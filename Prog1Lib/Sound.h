#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include "DirectoryManager.h"
#include <mmsystem.h>

typedef unsigned int u_int;


class MYTOOL_API Sound
{
	string path;
public:
	Sound(const string& _soundPath);
public:
	/// <summary>
	/// Lance la musique 
	/// </summary>
	/// <param name="_loop"> si la musique doit etre lu en boucle</param>
	/// <returns>Si la musique est fini retourne vrai</returns>
	bool Play(const bool _loop = false);
	/// <summary>
	/// Arrete toutes les musiques
	/// </summary>
	void Stop();
	
};

class MYTOOL_API Playlist
{
	vector<Sound> soundList;
	u_int currentMusicIndex;
	u_int soundCount;
public:
	inline bool IsValidIndex(const u_int& _index) const
	{
		return _index >= 0 &&
			_index < soundCount;
	}
	inline bool IsEmpty() const
	{
		return soundCount == 0;
	}
	inline u_int GetCurrentSoundIndex() const
	{
		return currentMusicIndex;
	}
public:

	Playlist();
	Playlist(const initializer_list<Sound>& _sounds);
	Playlist(const initializer_list<string>& _soundPaths);

public:
	/// <summary>
	/// ajoute un song a la playlist
	/// </summary>
	/// <param name="_sound">song a rajouter</param>
	void AddSound(const Sound& _sound);
	/// <summary>
	/// Suprime une musique avec son index
	/// </summary>
	/// <param name="_index">index de la music a supprimer</param>
	/// <returns>retourne si le song a bien étét suprimé</returns>
	bool RemoveSound(const u_int& _index);
	/// <summary>
	/// vide la playlist
	/// </summary>
	/// <returns>retourne si elle a étét vider correcter</returns>
	bool Clear();

	/// <summary>
	/// Lance la prochaine musique si une n'est pas deja en cours
	/// </summary>
	/// <returns>retourne si la musique a été changer (que l'ancienne est fini)</returns>
	bool Play();
	/// <summary>
	/// Passe a la musique suivante de force
	/// </summary>
	void Skip();
	/// <summary>
	/// Stop la playlist
	/// </summary>
	void Stop();
};