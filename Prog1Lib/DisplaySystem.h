#pragma once
/*
	=============CREDIT=============
	- Author : Quentin OBJ3D
*/

#ifdef MYTOOL_EXPORTS
#define DISPLAYSYSTEM_API __declspec(dllexport)
#else
#define DISPLAYSYSTEM_API __declspec(dllimport)
#endif

#include <iostream>

using namespace std;
typedef unsigned int u_int;

/// <summary>
/// Structure avec x (ligne) y (colonne) pour la position du curseur
/// </summary>
struct Coord
{
	int x;
	int y;
};
namespace Tools
{
	namespace Console
	{
		/// <summary>
		/// Permet d'afficher ou non le texte en multicolore
		/// <param name="RT_OFF">désactivé</param>
		/// <param name="RT_CHAR">Couleur aléatoire pour chaque caractère</param>
		/// <param name="RT_TEXT">Couleur aléatoire à chaque ligne</param>
		/// </summary>
		enum DISPLAYSYSTEM_API RainbowType
		{
			RT_OFF,
			RT_CHAR,
			RT_TEXT
		};

		//////////////////////////
		/*		CONSOLE			*/
		//////////////////////////

		/// <summary>
		/// Permet de définir la position du curseur dans la console
		/// </summary>
		/// <param name="_x">ligne</param>
		/// <param name="_y">Colonne</param>
		/// <param name="_cursor"> Affiche ou non la barre '|' du curseur</param>
		DISPLAYSYSTEM_API void SetCursorPosition(const u_int& _x, const u_int& _y, const bool _cursor = false);

		/// <summary>
		/// Permet de récupérer la position du centre de la console
		/// </summary>
		/// <returns>Retourne les coordonnées X (ligne) et Y (colonne)</returns>
		DISPLAYSYSTEM_API Coord GetCenterConsole();

		//////////////////////////////
		/*		SINGLE LINE			*/
		//////////////////////////////

		/// <summary>
		/// Permet d'afficher au centre de la console une ligne de texte avec la possibilité de décaler l'affichage du centre (padding)
		/// Attention à ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_text">Le texte à afficher</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">Décale l'affichage du centre</param>
		/// <param name="_exitKey">Touche à appuyer pour quitter (Echap par défaut)</param>
		DISPLAYSYSTEM_API void DisplayCenterLine(const string& _text, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 }, const int _exitKey = 27);

		/// <summary>
		/// Permet d'afficher au centre de la console une ligne de texte avec la possibilité de décaler l'affichage du centre (padding)
		/// et de retourner la touche sélectionné.
		/// Attention à ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_text">Le texte à afficher</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_input">Permet de renvoyer la valeur de la touche appuyé</param>
		/// <param name="_padding">Décale l'affichage du centre</param>
		DISPLAYSYSTEM_API void DisplayCenterLineWithInput(const string& _text, int& _input, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		/// <summary>
		/// Permet d'afficher une fois au centre de la console une ligne de texte avec la possibilité de décaler l'affichage du centre (padding)
		/// Attention à ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_text">Le texte à afficher</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">Décale l'affichage du centre</param>
		DISPLAYSYSTEM_API void DisplayOnceCenterLine(const string& _text, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		//////////////////////////////
		/*		MULTI LINE			*/
		//////////////////////////////

		/// <summary>
		/// Permet d'afficher au centre de la console des lignes de textes avec la possibilité de décaler l'affichage du centre (padding)
		/// et de choisir quelle touche il faut appuyer pour quitter l'affichage.
		/// Attention à ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_textArray">Liste des mots à afficher par ligne</param>
		/// <param name="_size">Taille de la liste _textArray</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">Décale l'affichage du centre</param>
		/// <param name="_exitKey">Touche à appuyer pour quitter (Echap par défaut)</param>
		DISPLAYSYSTEM_API void DisplayCenterMultiLine(const string* _textArray, const u_int& _size, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 }, const int _exitKey = 27);

		/// <summary>
		/// Permet d'afficher au centre de la console des lignes de textes avec la possibilité de décaler l'affichage du centre (padding)
		/// et de retourner la touche sélectionné.
		/// Attention à ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_textArray">Liste des mots à afficher par ligne</param>
		/// <param name="_size">Taille de la liste _textArray</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_input">Permet de renvoyer la valeur de la touche appuyé</param>
		/// <param name="_padding">Décale l'affichage du centre</param>
		DISPLAYSYSTEM_API void DisplayCenterMultiLineWithInput(const string* _textArray, const u_int& _size, int& _input, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		/// <summary>
		/// Permet d'afficher une fois au centre de la console des lignes de textes avec la possibilité de décaler l'affichage du centre (padding)
		/// Attention à ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_textArray">Liste des mots à afficher par ligne</param>
		/// <param name="_size">Taille de la liste _textArray</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">Décale l'affichage du centre</param>
		/// <returns></returns>
		DISPLAYSYSTEM_API void DisplayOnceCenterMultiLine(const string* _textArray, const u_int& _size, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		DISPLAYSYSTEM_API void DisplayAnimatedCenterMultiLine(const string& _filePath, const string& _filePrefix, const u_int& _quantity, const u_int& _size, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

	}
}