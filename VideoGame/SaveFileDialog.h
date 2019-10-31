#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>
#ifndef NOMINMAX
#define NOMINMAX
#endif

class SaveFileDialog {
public:
	SaveFileDialog();
	void saveFileDialog(std::string &s);
	~SaveFileDialog();
};

