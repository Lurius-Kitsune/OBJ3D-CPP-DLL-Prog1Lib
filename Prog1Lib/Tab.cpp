#include "pch.h"
#include "Tab.h"

template<typename T>
Tools::Tab<T>::Tab()
{
	tab = nullptr;
	size = 0;
}

template<typename T>
Tools::Tab<T>::Tab(const int _size)
{
	size = _size;
	tab = new T[size];
}

template<typename T>
Tools::Tab<T*>::Tab(const T** _tab, const int _size)
{
	size = _size;
	tab = _tab;
}

template<typename T>
Tools::Tab<T>::Tab(const T* _tab, const int _size)
{
	size = _size;
	tab = _tab;
}

template<typename T>
Tools::Tab<T>::~Tab()
{
	delete[] tab;
}

template<typename T>
Tools::Tab<T*>::~Tab()
{
	for (u_int _i = 0; _i < size; _i++)
	{
		delete tab[_i];
	}
	delete[] tab;
}

template<typename T>
T Tools::Tab<T>::operator[](const int _index)
{
	return tab[_index];
}

template<typename T>
const T& Tools::Tab<T>::operator[](const int _index) const
{
	return tab[_index];
}

template<typename T>
bool Tools::Tab<T*>::Add(const T* _object, const int _index)
{
	if (_index < 0) _index = size;
	if (!IsValidIndex(_index) && _index != size) return false;

	T* newTab = new T[size + 1];
	bool _isPut = false;
	for (u_int _i = 0; _i < size; _i++)
	{
		if (_i == _index)
		{
			newTab[_i] = _object;
			_isPut = true;
			continue;
		}
		newTab[_i + _isPut] = tab[_i];
	}

	delete[] tab;
	tab = newTab;
	size++;
	return true;
}

template<typename T>
bool Tools::Tab<T>::Add(const T& _object, const int _index)
{
	if (_index < 0) _index = size;
	if(!IsValidIndex(_index) && _index != size) return false;

	T* newTab = new T[size + 1];
	bool _isPut = false;
	for (u_int _i = 0; _i < size; _i++)
	{
		if (_i == _index)
		{
			newTab[_i] = _object;
			_isPut = true;
			continue;
		}
		newTab[_i + _isPut] = tab[_i];
	}

	delete[] tab;
	tab = newTab;
	size++;
	return true;
}

template<typename T>
bool Tools::Tab<T>::Remove(const T& _object)
{
	if (!IsIn(_object)) return false;
}

template<typename T>
bool Tools::Tab<T>::IsIn(const T& _object) const
{
	for (u_int _i = 0; _i < size; _i++)
	{
		if (_object == tab[_i]) return true;
	}

	return false;
}

template<typename T>
bool Tools::Tab<T>::IsValidIndex(const int _index) const
{
	return _index >= 0 && _index < size;
}

