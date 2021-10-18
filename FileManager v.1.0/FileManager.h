#pragma once
#include <string>

using namespace std;

class FileManager
{
private:
	string fileName;
	
	// Функций для работы с файлами.
	void Show_Directory(string = "");	// Показ содержимого директории.
	void Create_File();					// Создание файла.
	void Find_File();					// Поиск файла.
	void Rename_File();					// Переименование файла.
	void Copy_File(const char*, const char*);		// Копирование файла откуда и куда.
	void Remove_File();					// Удаление файла.

	// Функций для работы с директориями.
	void Create_Directory(const char*);	// Создание папки.
	void Rename_Directory();			// Переименование папки.
	void Copy_Directory(const char*, const char*);	// Копирование папки.
	void Remove_Directory();			// Удаление папки.

public:
	FileManager();
	~FileManager();
	void mainMenu();
};

