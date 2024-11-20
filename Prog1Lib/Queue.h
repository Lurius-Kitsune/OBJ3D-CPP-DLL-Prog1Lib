#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include "Node.h"

#pragma warning(disable : 4251)

namespace Tools
{
	template <class Type, class SizeType = u_int>
	class Queue
	{
		Node<Type>* first;
		Node<Type>* last;
		SizeType size;
	public:
		inline SizeType Size() const
		{
			return size;
		}
		inline Type First() const
		{
			return first->value;
		}
		inline Type Last() const
		{
			return last->value;
		}
		inline bool IsEmpty() const
		{
			return size == 0;
		}
	private:
		inline bool IsValidIndex(const SizeType& _index) const
		{
			return _index >= 0 && _index <= (size - 1);
		}
		inline void DeleteNode(Node<Type>* _node) const
		{
			_node->next = nullptr;
			delete _node;
		}
	public:
		Queue()
		{
			first = nullptr;
			last = nullptr;
			size = 0;
		}
		Queue(const initializer_list<Type>& _list)
		{
			first = nullptr;
			last = nullptr;
			size = 0;
			for (const Type& _object : _list)
			{
				Add(_object);
			}
		}
		Queue(Queue<Type>& _other)
		{
			first = nullptr;
			last = nullptr;
			size = 0;
			Node<Type>* _currentNode = _other.first;
			while (_currentNode)
			{
				Add(_currentNode->value);
				_currentNode = _currentNode->next;
			}
		}
		~Queue()
		{
			Clear();
		}
	public:
		void Add(const Type& _value)
		{
			Node<Type>* _newNode = new Node<Type>(_value);
			if (size == 0)
			{
				first = last = _newNode;
			}
			else
			{
				last->next = _newNode;
				_newNode->previous = last;
				last = _newNode;
			}
			size++;
		}

		void Remove()
		{
			try
			{
				Pop();
			}
			catch (const std::exception&)
			{
				return;
			}
		}
		Type Pop()
		{
			if (IsEmpty())
			{
				cout << "Lifo vide!" << endl;
				throw exception("Lifo empty");
			}
			Node<Type>* _newFirst = first->previous;
			_newFirst->next = nullptr;
			const Type& _valueToReturn = first->value;
			DeleteNode(first);
			first = _newFirst;
			return _valueToReturn;
		}
		void Clear()
		{
			delete first;
			first = nullptr;
			size = 0;
		}

		void Display()
		{
			Node<Type>* _currentNode = first;
			u_int _index = 0;
			while (_currentNode)
			{
				cout << _index++ << " : " << _currentNode->value << endl;
				_currentNode = _currentNode->next;
			}
		}
		void GetAllValue()
		{
			Node<Type>* _currentNode = first;
			u_int _index = 0;
			while (_currentNode)
			{
				cout << _index++ << " : " << _currentNode->value << endl;
				_currentNode = _currentNode->next;
			}
		}
		void DisplayAt(const SizeType& _indexToDisplay)
		{
			if (!IsValidIndex(_indexToDisplay)) throw exception("Invalid Index !");
			cout << _indexToDisplay << " : " << ReturnValueAtIndex(_indexToDisplay) << endl;
		}

		Node<Type>* GetNodeAtIndex(const SizeType& _indexToReturn)
		{
			Node<Type>* _currentNode;
			if (!IsValidIndex(_indexToReturn)) throw exception("Invalid Index !");
			if (_indexToReturn > static_cast<u_int>(size / 2))
			{
				_currentNode = last;
				for (u_int _index = (size - 1) - 1; _index >= _indexToReturn; _index--)
				{
					_currentNode = _currentNode->previous;
					if (!_currentNode) break;
				}
			}
			else
			{
				_currentNode = first;
				for (u_int _index = 1; _index <= _indexToReturn; _index++)
				{
					_currentNode = _currentNode->next;
					if (!_currentNode) break;
				}
			}
			return _currentNode;
		}
		Type& ReturnValueAtIndex(const SizeType& _indexToDisplayValue)
		{
			if (!IsValidIndex(_indexToDisplayValue)) throw exception("Invalid Index !");
			return GetNodeAtIndex(_indexToDisplayValue)->value;
		}
		void ChangeValueAtIndex(const SizeType& _indexToChange, const Type& _value)
		{
			if (!IsValidIndex(_indexToChange)) throw exception("Invalid Index !");
			Node* _currentNode = GetNodeAtIndex(_indexToChange);
			_currentNode->value = _value;
		}
	public:
		void operator += (const Type& _value)
		{
			Add(_value);
		}
		void operator += (Queue<Type> _linkedList)
		{
			Node<Type>* _currentNode = _linkedList.first;
			while (_currentNode)
			{
				Add(_currentNode->value);
				_currentNode = _currentNode->next;
			}
		}
		void operator += (const initializer_list<Type>& _list)
		{
			for (const Type& _value : _list)
			{
				Add(_value);
			}
		}
		void operator = (Queue<Type> _linkedList)
		{
			Clear();
			Node<Type>* _currentNode = _linkedList.first;
			while (_currentNode)
			{
				Add(_currentNode->value);
				_currentNode = _currentNode->next;
			}
		}
		void operator ++ ()
		{
			Add(Type());
		}
		Type operator -- ()
		{
			Pop();
		}
		Type& operator [] (const int _indexToDisplay)
		{
			if (_indexToDisplay >= 0)
				return ReturnValueAtIndex(static_cast<u_int>(_indexToDisplay));
			u_int _newIndex = size - (static_cast<u_int>((-_indexToDisplay)) % size);
			return ReturnValueAtIndex(_newIndex);
		}
		const Type& operator [] (const int _indexToDisplay) const
		{
			if (_indexToDisplay >= 0)
				return ReturnValueAtIndex(static_cast<u_int>(_indexToDisplay));
			u_int _newIndex = size - (static_cast<u_int>((-_indexToDisplay)) % size);
			return ReturnValueAtIndex(_newIndex);
		}
		void operator + (const u_int& _countToAdd)
		{
			for (u_int _index = 0; _index < _countToAdd; _index++)
			{
				Add(Type());
			}
		}
		void operator - (const u_int& _countToRemove)
		{
			for (u_int _index = 0; _index < _countToRemove; _index++)
			{
				if (size == 0) return;
				Remove();
			}
		}
		friend ostream& operator << (ostream& _stream, const Queue<Type>& _object)
		{
			Node<Type>* _currentNode = _object.first;
			u_int _index = 0;
			while (_currentNode)
			{
				_stream << _index++ << ": " << _currentNode->value << endl;
				_currentNode = _currentNode->next;
			}
			return _stream;
		}
	};
}