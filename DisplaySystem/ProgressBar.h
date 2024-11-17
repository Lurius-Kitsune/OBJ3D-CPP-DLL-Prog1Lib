#pragma once
#include <iostream>
#include <Windows.h>

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif


#pragma warning(disable : 4251)

using namespace std;

#define CALBARD Sleep
namespace Tools
{
	/// <summary>
	/// Classe permettant de gérer une barre de progression
	/// </summary>
	class MYTOOL_API ProgressBar
	{
		unsigned int pBarPourcent;
		string pBar;
		const unsigned int sizeBar = 100;


	public:
		ProgressBar()
		{
			pBarPourcent = 2;
			pBar = "[";
		}

	public:

		/// <summary>
		/// Affiche une barre de progression
		/// allant du rouge < 25%
		/// au vert > 75%
		/// </summary>
		void ProgressBarDisplay();

		/// <summary>
		/// L'inverse de la barre progression
		/// </summary>
		void UnProgressBarDisplay();

		/// <summary>
		/// Affiche un bar
		/// </summary>
		void BarDisplay();

		/// <summary>
		/// Nom explicite mais blague pas
		/// aussi poussée. Affiche juste
		/// NUH UH
		/// </summary>
		void NiBarDisplay();

	};
}

