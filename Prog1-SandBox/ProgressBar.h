#pragma once
#include <iostream>
#include <Windows.h>


using namespace std;

#define CALBARD Sleep

class ProgressBar
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
	
	void ProgressBarDisplay();

	void UnProgressBarDisplay();
	
	void BarDisplay();

	void NiBarDisplay();

};

