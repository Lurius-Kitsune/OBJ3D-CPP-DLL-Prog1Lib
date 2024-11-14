#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

typedef unsigned int u_int;

namespace Tools
{
	template<typename T>
	class MYTOOL_API Tab
	{
		T* tab;
		u_int size;

	public:

		int GetSize()const
		{
			return size;
		}
		
	public:

		Tab();
		Tab(const int _size);
		Tab(const T* _tab, const int _size);
		virtual ~Tab();

		virtual T operator[](const int _index);
		virtual const T& operator[](const int _index)const;

		virtual bool Add(const T& _object, const int _index = -1);
		virtual bool Remove(const T& _object);

		virtual bool IsIn(const T& _object)const;
	private:
		bool IsValidIndex(const int _index)const;
	};

	template<typename T>
	class MYTOOL_API Tab<T*>
	{
		T** tab;
		u_int size;

	public:

		int GetSize()const
		{
			return size;
		}

	public:
		Tab();
		Tab(const int _size);
		Tab(const T** _tab, const int _size);
		virtual ~Tab();

		virtual T* operator[](const int _index);
		virtual const T*& operator[](const int _index)const;

		virtual bool Add(const T* _object, const int _index = -1);
		virtual bool Remove(const T* _object);

		virtual bool IsIn(const T& _value)const;
	private:
		bool IsValidIndex(const int _index)const;
	};
}

