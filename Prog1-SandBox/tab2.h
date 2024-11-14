#pragma once
template<class T>
class Tab
{
	T* tab;
	u_int size;

public:

	int GetSize()const
	{
		return size;
	}

public:

	Tab()
	{
		size = 0;
		tab = new T[size];
	}

	Tab(const int _size)
	{
		size = _size;
		tab = new T[size];
	}

	Tab(const T* _tab, const int _size)
	{
		size = _size;
		tab = _tab;
	}

	virtual ~Tab()
	{
		delete[] tab;
	}

	virtual T operator[](const int _index)
	{
		return tab[_index];
	}

	virtual const T& operator[](const int _index)const
	{
		return tab[_index];
	}

	virtual bool Add(const T& _object, int _index = -1)
	{
		if (_index < 0) _index = size;
		if (!IsValidIndex(_index) && _index != size) return false;

		T* newTab = new T[size + 1];
		bool _isPut = false;
		for (u_int _i = 0; _i <= size; _i++)
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

	virtual bool Remove(const T& _object)
	{
		if (!IsIn(_object)) return false;
	}

	virtual bool IsIn(const T& _object)const
	{
		for (u_int _i = 0; _i < size; _i++)
		{
			if (_object == tab[_i]) return true;
		}

		return false;
	}

private:
	bool IsValidIndex(const int _index)const
	{
		return _index >= 0 && _index < size;
	}
};