#include "ProgressBar.h"

/// <summary>
/// Affiche une barre de progression
/// allant du rouge < 25%
/// au vert > 75%
/// </summary>
void ProgressBar::ProgressBarDisplay()
{
	pBarPourcent = pBarPourcent != 2 ? 2 : pBarPourcent;
	while (pBarPourcent != 100)
	{
		system("cls");
		cout << pBar;
		string _color = pBarPourcent < 25 ? "\033[31m" : pBarPourcent < 50 ? "\033[33m" : pBarPourcent < 75 ? "\033[93m" : "\033[32m";
		for (unsigned int _i = 0; _i < pBarPourcent; _i++)
		{
			cout << _color << "|";
		}
		cout << "\033[0m" << "]";
		pBarPourcent++;
		CALBARD(5);
	}
	system("cls");
}
/// <summary>
/// L'inverse de la barre progression
/// </summary>
void ProgressBar::UnProgressBarDisplay()
{
	pBarPourcent = pBarPourcent != 2 ? 2 : pBarPourcent;
	while (pBarPourcent != 100)
	{
		system("cls");
		cout << pBar;
		for (unsigned int _i = 0; _i < sizeBar - pBarPourcent; _i++)
		{
			cout << "|";
		}
		cout << "]";
		pBarPourcent++;
		CALBARD(5);
	}
	system("cls");
}

/// <summary>
/// Affiche un bar
/// </summary>
void ProgressBar::BarDisplay()
{
	const string _tabBar[] =
	{ "      .======================================.",
"      | ___ ___ ___               _   _   _  |",
"      | \\_/ \\_/ \\_/ C|||C|||C||| |-| |-| |-| |",
"      | _|_ _|_ _|_  ||| ||| ||| |_| |_| |_| |",
"      '===================================== ,sSSSs",
"                DUFFY'S WATERING HOLE       SSSS \"(",
"           .:.                              SSS@ =/  \\~/",
"          C|||'                             SSSS_(_  _Y_",
"        ___|||______________________________SS/ _)_) /.-",
"       [____________________________________] \\   /\\//",
"        |   ____    ____    ____    ____   | \\|==(\\_/",
"        |  (____)  (____)  (____)  (____)  | (/   ;",
"        |  |    |  |    |  |    |  |    |  | |____|",
"        |  |    |  |    |  |    |  |    |  |  \\  |\\",
"        |  |    |  |    |  |    |  |    |  |   ) ) )",
"        |  |____|  |____|  |____|  |____|  |  (  |/",
"        |  I====I  I====I  I====I  I====I  |  /\\ |",
"       jgs |    |  |    |  |    |  |    |  | /.(=\\",
"                                               Y\\_\\" };

	for (unsigned int _i = 0; _i < sizeof(_tabBar) / sizeof(string); _i++)
	{
		cout << _tabBar[_i] << endl;
		CALBARD(5);
	}
}


/// <summary>
/// Nom explicite mais blague pas
/// aussi poussée. Affiche juste
/// NUH UH
/// </summary>
void ProgressBar::NiBarDisplay()
{
	const string _tabBar[] =
	{
		  "N   N  U   U  H   H      U   U  H   H",
		  "NN  N  U   U  H   H      U   U  H   H",
		  "N N N  U   U  HHHHH      U   U  HHHHH",
		  "N  NN  U   U  H   H      U   U  H   H",
		  "N   N  UUUU   H   H      UUUU   H   H"
	};

	for (unsigned int _i = 0; _i < sizeof(_tabBar) / sizeof(string); _i++)
	{
		cout << "\033[31m" << _tabBar[_i] << "\033[0m" << endl;
		CALBARD(5);
	}
}

