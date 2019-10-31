#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#ifndef NOMINMAX
#define NOMINMAX
#endif

class OpenFileDialog {
public:
	OpenFileDialog();
	void openFileDialog(std::string &file);
	~OpenFileDialog();
};

