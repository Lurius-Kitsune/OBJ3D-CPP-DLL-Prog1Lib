#include "pch.h"
#include "Sound.h"

Sound::Sound(const string& _soundPath)
{
	path = _soundPath;
}


bool Sound::Play(const bool _loop)
{
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
	const wstring& _wPath = _converter.from_bytes(path);
	DWORD _soundCaracteristic = SND_FILENAME | SND_SYNC;
	if (_loop)
		_soundCaracteristic |= SND_LOOP;
	return PlaySound(_wPath.c_str(), NULL, _soundCaracteristic);
}
void Sound::Stop()
{
	PlaySound(NULL, NULL, 0);
}



Playlist::Playlist()
{
	currentMusicIndex = 0;
	soundCount = 0;
}
Playlist::Playlist(const initializer_list<Sound>& _sounds)
{
	for (const Sound& _sound : _sounds)
	{
		AddSound(_sound);
	}
	currentMusicIndex = 0;
	soundCount = 0;
}
Playlist::Playlist(const initializer_list<string>& _soundPaths)
{
	for (const string& _soundPath : _soundPaths)
	{
		AddSound(Sound(_soundPath));
	}
	currentMusicIndex = 0;
	soundCount = 0;
}


void Playlist::AddSound(const Sound& _sound)
{
	soundList.push_back(_sound);
	soundCount++;
}
bool Playlist::RemoveSound(const u_int& _index)
{
	if (!IsValidIndex(_index)) return false;
	vector<Sound>::iterator _iteratorIndex
		= soundList.begin() + _index;
	soundList.erase(_iteratorIndex);
	return true;
}
bool Playlist::Clear()
{
	if (IsEmpty()) return false;
	soundList.erase(soundList.begin(), soundList.end());
	return true;
}

bool Playlist::Play()
{
	if (IsEmpty()) return false;
	if (soundList[currentMusicIndex].Play())
	{
		currentMusicIndex++;
		currentMusicIndex %= soundCount;
		soundList[currentMusicIndex].Play();
		return true;
	}
	return false;
}
void Playlist::Stop()
{
	PlaySound(NULL, NULL, 0);
}
