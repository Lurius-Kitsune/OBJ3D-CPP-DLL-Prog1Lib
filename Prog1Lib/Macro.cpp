#include "pch.h"
#include "Macro.h"

MYTOOL_API void Tools::Config()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detection de fuite de mémoire
	//locale::global(locale("FR-fr")); // UTF8
}