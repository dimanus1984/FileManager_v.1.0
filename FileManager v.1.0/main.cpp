#include<iostream>
#include<Windows.h>
#include"FileManager.h"

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FileManager* editor = new FileManager;
	editor->mainMenu();
	delete editor;
}