#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

typedef unsigned int u_int;

namespace Tools
{
	template<class T>
	class DynamicArray
	{
		T* tab;
		u_int size;

	public:

		int GetSize()const
		{
			return size;
		}

	public:

		DynamicArray()
		{
			size = 0;
			tab = new T[size];
		}

		DynamicArray(const T* _tab, const int _size)
		{
			size = _size;
			tab = _tab;
		}

		virtual ~DynamicArray()
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

			T* _tempTab = new T[size + 1];
			bool _isPut = false;
			for (u_int _i = 0; _i <= size; _i++)
			{
				if (_i == _index)
				{
					_tempTab[_i] = _object;
					_isPut = true;
					continue;
				}
				_tempTab[_i + _isPut] = tab[_i];
			}

			delete[] tab;
			tab = _tempTab;
			size++;
			return true;
		}

		virtual bool Remove(const T& _object)
		{
			if (!IsIn(_object)) return false;
			return Remove(FindIndexOfObject(_object));
		}

		virtual bool Remove(int _index = -1)
		{
			if (_index < 0) _index = size - 1;
			if (!IsValidIndex(_index)) return false;

			T** _tempTab = new T * [size - 1];
			bool _isRemoved = false;
			for (u_int _i = 0; _i < size; _i++)
			{
				if (_i == _index && !_isRemoved)
				{
					_isRemoved = true;
					continue;
				}
				_tempTab[_i - _isRemoved] = tab[_i];
			}

			delete[] tab;
			tab = _tempTab;
			size--;
			return true;
		}

		virtual bool IsIn(const T& _object)const
		{
			for (u_int _i = 0; _i < size; _i++)
			{
				if (_object == tab[_i]) return true; //TODO: == operator on object !
			}

			return false;
		}

		virtual u_int FindIndexOfObject(const T& _object)const
		{
			for (u_int _i = 0; _i < size; _i++)
			{
				if (_object == tab[_i]) return _i; //TODO: == operator on object !
			}

			throw exception("Object not found in the tab !");
		}
	private:
		bool IsValidIndex(const u_int& _index)const
		{
			return _index >= 0 && _index < size;
		}
	};

	template<class T>
	class DynamicArray<T*>
	{
		T** tab;
		u_int size;

	public:

		int GetSize()const
		{
			return size;
		}

	public:

		DynamicArray()
		{
			size = 0;
			tab = new T*[size];
		}

		DynamicArray(const T** _tab, const int _size)
		{
			size = _size;
			tab = _tab;
		}

		virtual ~DynamicArray()
		{
			for (u_int _i = 0; _i < size; _i++)
			{
				delete tab[_i];
			}
			delete[] tab;
		}

		virtual T* operator[](const int _index)
		{
			return tab[_index];
		}

		virtual const T* operator[](const int _index)const
		{
			return tab[_index];
		}

		virtual bool Add(T* _object, int _index = -1)
		{
			if (_index < 0) _index = size;
			if (!IsValidIndex(_index) && _index != size) return false;

			T** _tempTab = new T*[size + 1];
			bool _isPut = false;
			for (u_int _i = 0; _i <= size; _i++)
			{
				if (_i == _index)
				{
					_tempTab[_i] = _object;
					_isPut = true;
					continue;
				}
				_tempTab[_i + _isPut] = tab[_i];
			}

			delete[] tab;
			tab = _tempTab;
			size++;
			return true;
		}

		virtual bool Remove(T* _object, const bool _needToBeDelete = false)
		{
			if (!IsIn(_object)) return false;
			return Remove(FindIndexOfObject(_object), _needToBeDelete);
		}

		virtual bool Remove(int _index = -1, const bool _needToBeDelete = false)
		{
			if (_index < 0) _index = size-1;
			if (!IsValidIndex(_index)) return false;

			T** _tempTab = new T * [size - 1];
			bool _isRemoved = false;
			for (u_int _i = 0; _i < size; _i++)
			{
				if (_i == _index && !_isRemoved)
				{
					_isRemoved = true;
					if (_needToBeDelete)
					{
						delete tab[_i];
					}
					continue;
				}
				_tempTab[_i - _isRemoved] = tab[_i];
			}

			delete[] tab;
			tab = _tempTab;
			size--;
			return true;
		}

		virtual bool IsIn(const T* _object)const
		{
			for (u_int _i = 0; _i < size; _i++)
			{
				if (_object == tab[_i]) return true; //TODO: == operator on object !
			}

			return false;
		}

		virtual u_int FindIndexOfObject(T* _object)const
		{
			for (u_int _i = 0; _i < size; _i++)
			{
				if (_object == tab[_i]) return _i; //TODO: == operator on object !
			}

			throw exception("Object not found in the tab !");
		}

	private:
		bool IsValidIndex(const u_int& _index)const
		{
			return _index >= 0 && _index < size;
		}
	};
}

