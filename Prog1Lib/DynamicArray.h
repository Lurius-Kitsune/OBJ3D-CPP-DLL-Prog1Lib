#pragma once
#include <iostream>
#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

typedef unsigned int u_int;
using namespace std; 
namespace Tools
{
	bool IsValidIndexInArray(const int _index, const u_int& _arraySize)
	{
		return (_index >= 0 && _index <= static_cast<int>(_arraySize) - 1);
	}

	template <typename Type>
	bool AddInArray(Type*& _array, Type _valueToAdd, u_int& _arraySize, int _indexToAdd = -1)
	{
		_indexToAdd = _indexToAdd == -1 ? _arraySize : _indexToAdd;
		if (!IsValidIndexInArray(_indexToAdd, _arraySize)) return false;
		Type* _newArray = new Type[_arraySize + 1];
		bool _isPut = false;
		for (u_int _index = 0; _index < _arraySize ; _index++)
		{
			if (_index == static_cast<u_int>(_indexToAdd))
			{
				_newArray[_index] = _valueToAdd;
				_isPut = true;
			}
			_newArray[_index + _isPut] = _array[_index];
		}
		_newArray[_arraySize] = _valueToAdd;
		delete[] _array;
		_array = _newArray;
		_arraySize++;
		return true;
	}

	template <typename Type>
	bool RemoveInArray(Type*& _array, u_int& _arraySize, int _indexToRemove = -1)
	{
		_indexToRemove = _indexToRemove <= -1 ? _arraySize - 1 : _indexToRemove;
		if (!IsValidIndexInArray(_indexToRemove, _arraySize)) return false;
		Type* _newArray = new Type[--_arraySize];
		bool _hasSkip = false;
		for (u_int _index = 0; _index < _arraySize; _index++)
		{
			if (_index == static_cast<u_int>(_indexToRemove)) _hasSkip = true;
			_newArray[_arraySize] = _array[_index + _hasSkip];
		}
		delete[] _array;
		_array = _newArray;
		return true;
	}

	
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
			if (!IsValidIndex(_index)) throw std::exception("Index out of range");
			return tab[_index];
		}

		virtual const T& operator[](const int _index)const
		{
			if (!IsValidIndex(_index)) throw std::exception("Index out of range");
			return tab[_index];
		}

		/// <summary>
		/// Ajoute un objet <Type> dans le tableau à l'index donner
		/// </summary>
		/// <param name="_object">L'objet à ajouter</param>
		/// <param name="_index">L'index concerner</param>
		/// <returns>Vrai si l'operation c'est faite</returns>
		virtual bool Add(const T& _object, int _index = -1)
		{
			return AddInArray(tab, _object,size, _index);
		}


		/// <summary>
		/// Retire le premier objet de <Type> trouver dans le tableau
		/// </summary>
		/// <param name="_object">L'objet à retirer</param>
		/// <returns>Vrai si l'operation c'est faite</returns>
		virtual bool Remove(const T& _object)
		{
			if (!IsIn(_object)) return false;
			return Remove(FindIndexOfObject(_object));
		}

		/// <summary>
		/// Retire un objet de <Type> dans le tableau à l'index donner
		/// </summary>
		/// <param name="_object">L'index concerner</param>
		/// <returns>Vrai si l'operation c'est faite</returns>
		virtual bool Remove(int _index = -1)
		{
			return RemoveInArray(tab,size, _index);
		}

		/// <summary>
		/// Indique si l'objet de <type> est présent dans le tableau
		/// </summary>
		/// <param name="_object">L'objet à trouver</param>
		/// <returns>Vrai si trouver</returns>
		virtual bool IsIn(const T& _object)const
		{
			for (u_int _i = 0; _i < size; _i++)
			{
				if (_object == tab[_i]) return true; //TODO: == operator on object !
			}

			return false;
		}

		/// <summary>
		/// Trouve l'index du premier objet trouver dans le tableau
		/// </summary>
		/// <param name="_object">L'objet à rechercher</param>
		/// <returns>L'index trouver, sinon EXCEPTION</returns>
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
			return IsValidIndexInArray(static_cast<int>(_index), size);
		}
	};
}

