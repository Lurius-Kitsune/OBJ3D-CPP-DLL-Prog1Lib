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
	template <typename Type>
	struct Node
	{
		Type value;
		Node* next;
		Node* previous;

		Node(const int _value, Node* _previous = nullptr, Node* _next = nullptr)
		{
			value = _value;
			next = _next;
			previous = _previous;
		}
		~Node()
		{
			delete next;
		}

		bool operator == (Node* _otherNode)
		{
			return _otherNode->value == value;
		}
		friend ostream& operator << (ostream& _stream, Node<Type>* _object)
		{
			return _object->value;
		}
		friend ostream& operator << (ostream& _stream, const Node<Type>& _object)
		{
			return _object.value;
		}
	};
}