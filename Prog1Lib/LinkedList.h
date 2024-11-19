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
	template <class Type>
	class LinkedList
	{
	protected:
		Node<Type>* first;
		Node<Type>* last;
		u_int size;
	public:

		inline Type Last() const
		{
			return last->value;
		}
		inline Type First() const
		{
			return first->value;
		}
		inline u_int Size() const
		{
			return size;
		}

	private:
		inline bool IsValidIndex(const u_int& _index) const
		{
			return _index >= 0 && _index <= (size - 1);
		}
		inline void DeleteNode(Node<Type>*& _node) const
		{
			_node->next = nullptr;
			delete _node;
		}
	public:
		LinkedList<Type>()
		{
			first = nullptr;
			last = nullptr;

			size = 0;
		}
		LinkedList<Type>(const initializer_list<Type>& _list)
		{
			first = nullptr;
			last = nullptr;
			size = 0;

			for (const Type& _value : _list)
			{
				AddBack(_value);
			}
		}
		LinkedList<Type>(LinkedList<Type>& _other)
		{
			first = nullptr;
			last = nullptr;
			size = 0;
			Node<Type>* _current = _other.first;
			while (_current)
			{
				AddBack(_current->value);
				_current = _current->next;
			}
		}
		~LinkedList()
		{
			Clear();
		}

	public:
		void AddFront(const Type& _value)
		{
			Node<Type>* _newNode = new Node<Type>(_value);
			if (size == 0)
			{
				first = _newNode;
				last = _newNode;
			}
			else
			{
				first->previous = _newNode;
				_newNode->next = first;
				first = _newNode;
			}
			size++;
		}
		void InsertAt(const u_int& _indexToAdd, const Type& _value)
		{
			if (_indexToAdd == 0)
			{
				AddFront(_value);
				return;
			}
			if (_indexToAdd == size)
			{
				AddBack(_value);
				return;
			}
			if (!IsValidIndex(_indexToAdd)) throw exception("Invalid Index !");
			Node<Type>* _currentNode = GetNodeAtIndex(_indexToAdd);
			Node<Type>* _previousNode = _currentNode->previous;
			Node<Type>* _nodeToAdd = new Node(_value, _previousNode, _currentNode);
			_currentNode->previous = _nodeToAdd;
			_previousNode->next = _nodeToAdd;
			size++;
		}
		void AddBack(const Type& _value)
		{
			Node<Type>* _newNode = new Node<Type>(_value);
			if (size == 0)
			{
				first = _newNode;
				last = _newNode;
			}
			else
			{
				last->next = _newNode;
				_newNode->previous = first;
				last = _newNode;
			}
			size++;
		}

		Type PopFront()
		{
			if (!first) throw exception("No Node !");
			const int _valueToReturn = first->value;
			Node<Type>* _newFrontNode = first->next;
			DeleteNode(first);
			first = _newFrontNode;
			first->previous = nullptr;
			size--;
			return _valueToReturn;
		}
		void RemoveAt(const u_int& _indexToRemove)
		{
			if (!first) throw exception("No Node !");
			if (_indexToRemove == 0)
			{
				PopFront();
				return;
			}
			if (_indexToRemove == size)
			{
				PopBack();
				return;
			}
			if (!IsValidIndex(_indexToRemove)) throw exception("Invalid Index !");
			Node<Type>* _currentNode = GetNodeAtIndex(_indexToRemove);
			Node<Type>* _previousNode = _currentNode->previous;
			Node<Type>* _nextNode = _currentNode->next;
			DeleteNode(_currentNode);
			_previousNode->next = _nextNode;
			_nextNode->previous = _previousNode;
			size--;
		}
		Type PopBack()
		{
			if (!last) throw exception("No Node !");
			const Type& _valueToReturn = last->value;
			Node<Type>* _newLastNode = last->previous;
			DeleteNode(last);
			last = _newLastNode;
			size--;
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
		void DisplayAt(const u_int& _indexToDisplay)
		{
			if (!IsValidIndex(_indexToDisplay)) throw exception("Invalid Index !");
			cout << _indexToDisplay << " : " << ReturnValueAtIndex(_indexToDisplay) << endl;
		}

		Node<Type>* GetNodeAtIndex(const u_int& _indexToReturn)
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
		Type& ReturnValueAtIndex(const u_int& _indexToDisplayValue)
		{
			if (!IsValidIndex(_indexToDisplayValue)) throw exception("Invalid Index !");
			return GetNodeAtIndex(_indexToDisplayValue)->value;
		}
		void ChangeValueAtIndex(const u_int& _indexToChange, const Type& _value)
		{
			if (!IsValidIndex(_indexToChange)) throw exception("Invalid Index !");
			Node* _currentNode = GetNodeAtIndex(_indexToChange);
			_currentNode->value = _value;
		}
	public:
		void operator += (const Type& _value)
		{
			AddBack(_value);
		}
		void operator += (LinkedList<Type> _linkedList)
		{
			Node<Type>* _currentNode = _linkedList.first;
			while (_currentNode)
			{
				AddBack(_currentNode->value);
				_currentNode = _currentNode->next;
			}
		}
		void operator += (const initializer_list<Type>& _list)
		{
			for (const Type& _value : _list)
			{
				AddBack(_value);
			}
		}
		void operator = (LinkedList<Type> _linkedList)
		{
			Clear();
			Node<Type>* _currentNode = _linkedList.first;
			while (_currentNode)
			{
				AddBack(_currentNode->value);
				_currentNode = _currentNode->next;
			}
		}
		void operator ++ ()
		{
			AddBack(Type());
		}
		void operator -- ()
		{
			PopBack();
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
				AddBack(Type());
			}
		}
		void operator - (const u_int& _countToRemove)
		{
			for (u_int _index = 0; _index < _countToRemove; _index++)
			{
				if (size == 0) return;
				PopBack();
			}
		}
		friend ostream& operator << (ostream& _stream, const LinkedList<Type>& _object)
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