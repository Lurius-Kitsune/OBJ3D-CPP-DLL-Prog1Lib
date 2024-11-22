#pragma once
#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include "Macro.h"
#include "Random.h"
#include <chrono>
#include <string>
#include <iostream>
#include <thread>

using namespace std;
using namespace chrono;
using namespace this_thread;

typedef unsigned int u_int;


namespace Tools
{
	namespace Console
	{
		#define BOLD_TEXT "\033[1m"					// Gras
		#define ITALIC_TEXT "\033[3m"				// Italique
		#define UNDERLINE_TEXT "\033[4m"			// Soulign�
		#define STRIKETHROUGH_TEXT "\033[9m"		// Barr�
		#define INVERSE_TEXT "\033[7m"				// Inverse les couleurs
		#define BLINK_TEXT "\033[5m"				// Clignotant
		#define DIM_TEXT "\033[2m"					// Semi-gras
		#define HIDDEN_TEXT "\033[8m"				// Masqu�
		#define DOUBLE_UNDERLINE_TEXT "\033[21m"	// Double soulign�e

		#define BLINK_COLOR(x) "\033[5m" << x		// Clignotant

		// Resets
		#define RESET "\033[0m"
		#define RESET_BOLD "\033[22m"
		#define RESET_ITALIC "\033[23m"
		#define RESET_UNDERLINE "\033[24m"
		#define RESET_BLINK "\033[25m"
		#define RESET_INVERSE "\033[27m"
		#define RESET_STRIKETHROUGH "\033[29m"

		// Text colors
		#define BLACK "\x1B[38;5;232m"
		#define DARK_GRAY "\x1B[38;5;237m"
		#define GRAY "\x1B[38;5;244m"
		#define LIGHT_GRAY "\x1B[38;5;249m"
		#define WHITE "\x1B[38;5;255m"
		#define DARK_RED "\x1B[38;5;124m"
		#define RED "\x1B[38;5;196m"
		#define DARK_ORANGE "\x1B[38;5;130m"
		#define ORANGE "\x1B[38;5;208m"
		#define DARK_YELLOW "\x1B[38;5;136m"
		#define YELLOW "\x1B[38;5;226m"
		#define LIME "\x1B[38;5;82m"
		#define GREEN "\033[32m"
		#define BLUE "\x1B[38;5;63m"
		#define LIGHT_BLUE "\x1B[38;5;12m"
		#define CYAN "\x1B[38;5;51m"
		#define PINK "\x1B[38;5;219m"
		#define MAGENTA "\x1B[38;5;199m"
		#define PURPLE "\x1B[38;5;99m"
		#define BROWN "\x1B[38;5;130m"

		//Base Colors
		#define BLACK_BASE "\u001b[30m"
		#define RED_BASE "\u001b[31m"
		#define GREEN_BASE "\u001b[32m"
		#define YELLOW_BASE "\u001b[33m"
		#define BLUE_BASE "\u001b[34m"
		#define PURPLE_BASE "\u001b[35m"
		#define CYAN_BASE "\u001b[36m"
		#define WHITE_BASE "\u001b[37m"

		// Background colors
		#define BG_BLACK "\x1B[48;5;232m"
		#define BG_DARK_GRAY "\x1B[48;5;237m"
		#define BG_GRAY "\x1B[48;5;244m"
		#define BG_LIGHT_GRAY "\x1B[48;5;249m"
		#define BG_WHITE "\x1B[48;5;255m"
		#define BG_DARK_RED "\x1B[48;5;124m"
		#define BG_RED "\x1B[48;5;196m"
		#define BG_DARK_ORANGE "\x1B[48;5;130m"
		#define BG_ORANGE "\x1B[48;5;208m"
		#define BG_DARK_YELLOW "\x1B[48;5;136m"
		#define BG_YELLOW "\x1B[48;5;226m"
		#define BG_LIME "\x1B[48;5;82m"
		#define BG_GREEN "\x1B[48;5;106m"
		#define BG_BLUE "\x1B[48;5;63m"
		#define BG_LIGHT_BLUE "\x1B[48;5;12m"
		#define BG_CYAN "\x1B[48;5;51m"
		#define BG_PINK "\x1B[48;5;219m"
		#define BG_MAGENTA "\x1B[48;5;199m"
		#define BG_PURPLE "\x1B[48;5;99m"
		#define BG_BROWN "\x1B[48;5;130m"


		// High intensity text colors
		#define BLACK_INTENSE_TEXT "\033[90m"
		#define RED_INTENSE_TEXT "\033[91m"
		#define GREEN_INTENSE_TEXT "\033[92m"
		#define YELLOW_INTENSE_TEXT "\033[93m"
		#define BLUE_INTENSE_TEXT "\033[94m"
		#define MAGENTA_INTENSE_TEXT "\033[95m"
		#define CYAN_INTENSE_TEXT "\033[96m"
		#define WHITE_INTENSE_TEXT "\033[97m"

		// High intensity background colors
		#define BLACK_INTENSE_BG "\033[100m"
		#define RED_INTENSE_BG "\033[101m"
		#define GREEN_INTENSE_BG "\033[102m"
		#define YELLOW_INTENSE_BG "\033[103m"
		#define BLUE_INTENSE_BG "\033[104m"
		#define MAGENTA_INTENSE_BG "\033[105m"
		#define CYAN_INTENSE_BG "\033[106m"
		#define WHITE_INTENSE_BG "\033[107m"

		#define SWAP "\033[7m" // Swap background and foreground colors

		// x => Color code between 0 and 255
		#define COLOR(x) "\x1B[38;5;"<<x<<"m"
		#define BG_COLOR(x) "\x1B[48;5;"<<x<<"m"

		MYTOOL_API string RainbowEveryChar(const string& _word);

		MYTOOL_API string RainbowString(const string& _word);
		MYTOOL_API void DisplayRainbow(const string& _text);
		MYTOOL_API string GetRandomColor();
	}
}
