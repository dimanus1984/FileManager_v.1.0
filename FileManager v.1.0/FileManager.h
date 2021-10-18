#pragma once
#include <string>

using namespace std;

class FileManager
{
private:
	string fileName;
	
	// ������� ��� ������ � �������.
	void Show_Directory(string = "");	// ����� ����������� ����������.
	void Create_File();					// �������� �����.
	void Find_File();					// ����� �����.
	void Rename_File();					// �������������� �����.
	void Copy_File(const char*, const char*);		// ����������� ����� ������ � ����.
	void Remove_File();					// �������� �����.

	// ������� ��� ������ � ������������.
	void Create_Directory(const char*);	// �������� �����.
	void Rename_Directory();			// �������������� �����.
	void Copy_Directory(const char*, const char*);	// ����������� �����.
	void Remove_Directory();			// �������� �����.

public:
	FileManager();
	~FileManager();
	void mainMenu();
};

