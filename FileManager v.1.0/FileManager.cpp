#include "FileManager.h"
#include<iostream>
#include<string.h>
#include<string>
#include<stdio.h>	// ������� ��� ������ � �������.
#include<io.h>		// ������� ��� ������ � ������� � ����� �������.
#include<Windows.h>
#include<direct.h>	// ���������� ��� ������ � ������������.

using namespace std;

FileManager::FileManager() {}
FileManager::~FileManager() {}

static int CountDir = 0;	// ���������� ������������� ����������.
static int CountFile = 0;	// ���������� ������������� ������.

void FileManager::mainMenu()
{
	string selection;

	do {
		cout << "===============================\n";
		cout << "**�������� ������ � ���������**\n\n";
		cout << "����������, �������� ������ �������:\n";
		cout << " 1...�������� ���������� ����������\n";
		cout << " 2...������� ����\n";
		cout << " 3...����� �����\n";
		cout << " 4...������������� ����\n";
		cout << " 5...���������� ����\n";
		cout << " 6...������� ����\n";
		cout << " 7...������� �����\n";
		cout << " 8...������������� �����\n";
		cout << " 9...���������� �����\n";
		cout << "10...������� �����\n";
		cout << " 0...�����\n";
		cout << "===============================\n\n>";

		getline(cin, selection);
		cout << "\n";

		if (selection == "0")
		{
			cout << "����� �� ���������...\n";
			return;
		}
		else if (selection == "1")
			Show_Directory();
		else if (selection == "2")
			Create_File();
		else if (selection == "3")
			Find_File();
		else if (selection == "4")
			Rename_File();
		else if (selection == "5")
		{
			system("cls");
			char Source[MAX_PATH];
			char Destination[MAX_PATH];
			cout << "������� ��� � ���� � ��������� �����: ";
			cin.getline(Source, MAX_PATH);
			cout << "������� ��� � ���� � ����� ����������: ";
			cin.getline(Destination, MAX_PATH);
			Copy_File(Source, Destination);
			cout << "���� ������� ����������!" << endl << endl;
			system("pause");
			cout << endl;
			system("cls");
		}
		else if (selection == "6")
			Remove_File();
		else if (selection == "7")
		{
			system("cls");
			char Name[MAX_PATH];
			cout << "������� ��� � ���� � ����������: ";
			cin.getline(Name, MAX_PATH);
			Create_Directory(Name);
			cout << "���������� ������� �������!" << endl << endl;
			system("pause");
			cout << endl;
			system("cls");
		}
		else if (selection == "8")
			Rename_Directory();
		else if (selection == "9")
		{
			system("cls");
			char Source[MAX_PATH];
			char Destination[MAX_PATH];
			cout << "������� ��� � ���� � ���������� ����������: ";
			cin.getline(Source, MAX_PATH);
			cout << "������� ��� � ���� � ���������� ����������: ";
			cin.getline(Destination, MAX_PATH);
			Copy_Directory(Source, Destination);
			cout << "�����������: " << CountDir << " �����(�) � " << CountFile << " ����(�)!" << endl << endl;
			system("pause");
			cout << endl;
			system("cls");
		}
		else if (selection == "10")
		{
			system("cls");
			Remove_Directory();
			cout << endl;
			system("pause");
			system("cls");
		}
		else
			cout << "����������, ������� �������������� �����\n\n";
	} while (true);
}

void FileManager::Show_Directory(string Name)	// ����� ����������� ����������.
{
	system("cls");
	if (Name == "")
	{
		cout << "������� ���� � ����������: " << endl;
		getline(cin, Name);
	}
	// ������ ���� � ������ ��� ������ ����� ����������� ����������.
	char Path[MAX_PATH];
	strcpy_s(Path, Name.c_str());
	strcat_s(Path, "\\*.*");
	system("cls");
	
	_finddata_t Find;		// ������ ���������, �������� ������ � ������.
	long Done = _findfirst(Path, &Find);
	int MayWeWork = Done;	// ����������, ����� � �� ����������� ������ �� ���������� ��������.
	if (MayWeWork == -1)	// ���� Done = -1 �� ������ ���.
	{
		cout << "���������� �� ����������!" << endl;
		return;
	}
	cout << "���������� ����������: " << Name << endl;
	cout << "________________________________________________" << endl;
	int CountDir = 0;
	int CountFile = 0;
	while (MayWeWork != -1)
	{
		// ��������, ������ ����� �������� ���� �� ������ ��������
		if (strcmp(Find.name, ".") && (strcmp(Find.name, "..")))
		{
			if (Find.attrib & _A_SUBDIR)	// ���� ������� �����
			{
				cout << "�����: \t|";
				CountDir++;
			}
			else
			{
				cout << "����: \t|" << Find.size;
				CountFile++;
			}
			if (Find.size <= 999999)cout << "\t";
			cout << "\t|" << Find.name <<endl;
		}
		MayWeWork = _findnext(Done, &Find);
	}
	cout << "________________________________________________" << endl;
	cout << "���������� ������: " << CountFile << " ���������� �����: " << CountDir << endl << endl;
	_findclose(Done);
	system("pause");
	cout << endl;
}

void FileManager::Create_File()	// �������� �����.
{
	system("cls");
	char fileName[MAX_PATH];	// define MAX_PATH - ������������ ���� 260 ��������.
	cout << "������� ��� ��� �������� ����� � ���������� ����: ";
	cin.getline(fileName, MAX_PATH);
	FILE* check;
	if (!fopen_s(&check, fileName, "r") != 0)	// ������� ������� ���� �� ������.
	{
		cout << "���� � ����� ������ ��� ����������!" << endl << endl;
		fclose(check);
		return;
	}
	fopen_s(&check, fileName, "w");	// �������� ����� �� ������ (��������).
	if (!check)	// ���� ��������� �� ���� �������.
	{
		cout << "������ �������� �����!" << endl << endl;
		return;
	}
	cout << "���� ������� ������!" << endl << endl;
	fclose(check);
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Find_File()	// ����� �����.
{
	system("cls");
	char Path[MAX_PATH];		// ������ ���� � �����
	cout << "������� ���� � ���������� ��� ������ ������: ";
	cin.getline(Path, MAX_PATH);
	char Mask[MAX_PATH];		// ������ ����� ��� ������ �����
	cout << "������� ����� ��� ������ ������ (�������� *.* ��� *.txt): ";
	cin.getline(Mask, MAX_PATH);
	char FullPath[MAX_PATH];	// ���������� ���� � �����
	strcpy_s(FullPath, Path);	// �����������.
	strcat_s(FullPath, Mask);	// ����������.
	_finddata_t* InfoFile = new _finddata_t;	// �������� ������� ���������, �������� ������ � ������.
	long Done = _findfirst(FullPath, InfoFile);	// �����.
	int MayWeWork = Done;		// ����������, ����� � �� ����������� ������ �� ���������� ��������.
	int Count = 0;				// ������� ���������� ��������� ������.
	while (MayWeWork != -1)
	{
		Count++;
		cout << InfoFile->name << endl;			// ����� ����� ���������� �����.
		MayWeWork = _findnext(Done, InfoFile);	// ����� ���������� �����.
	}
	cout << "���� ������� " << Count << " ����(�/��) � ���������� " << Path << " �� �����: " << Mask << endl << endl;
	_findclose(Done);	// ������������ ������, ��������� ��� ��������� finddata.
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Rename_File()	// �������������� �����.
{
	system("cls");
	// ������� � ����� ��� �����:
	char OldName[MAX_PATH];
	char NewName[MAX_PATH];
	cout << "������� ������ ��� ����� ��� ��������������, � ��������� ����: ";
	cin.getline(OldName, MAX_PATH);
	cout << "������� ����� ��� ����� ��� ��������������, � ��������� ����: ";
	cin.getline(NewName, MAX_PATH);
	// �������������� � ��������.
	if (rename(OldName, NewName))	// rename ���������� 0 ���� �������, � ��� ������ ���� �� �������.
	{
		cout << "������ �������������� �����! ��������� ��� � ������ �� ����!" << endl << endl;
		return;
	}
	else cout << "���� ������� ������������!" << endl << endl;
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Copy_File(const char* Source, const char* Destination)	// ����������� ����� ������ � ����.
{
	// ��������� �� �����:
	FILE* Src, * Dest;
	// �������� ������������� ����� � ��������(��������) ������ �� ������.
	if (fopen_s(&Src, Source, "rb") != 0)
	{
		cout << "���� �� ������! ��������� ��� � ���� � �����!" << endl << endl;
		return;
	}
	int hSrc = _fileno(Src);		// �������� ���������� �����.
	int Size = _filelength(hSrc);	// ���������� ������ �����.
	char* Data = new char[Size];	// �������� ������ ��� ����� ��� ����������� ����������� �����.
	if (!Data)
	{
		cout << "������ ��������� ������, ��� �������� ������ ��� ����������� �����!" << endl << endl;
		fclose(Src);
		return;
	}
	if (fopen_s(&Dest, Destination, "wb") != 0)	// ��������� ����� ����������, � �������� ������ �� ������.
	{
		cout << "������ ����������� �����! ��������� ��� � ���� ����������!" << endl << endl;
		fclose(Src);
		delete[] Data;
		return;
	}
	int DataValue;		// ����� ������.
	// ������� ������:
	while (!feof(Src))	// ���� �� ����� �� ����� ��������� �����.
	{
		// ������� ������ � ������ Data, ����������� ����� ������ � ������ � ������� ��� � DataValue
		DataValue = fread(Data, sizeof(char), Size, Src);			// fread �������� � �������� ������.
		if (DataValue)fwrite(Data, sizeof(char), DataValue, Dest);	// �������� ������ � ���� ����������.
		else break;	// ���� ����������� ������ ����������� ������.
	}
	// ������� �����:
	fclose(Src);
	fclose(Dest);
	// ������������ ������, ���������� ��� �����.
	delete[] Data;
}

void FileManager::Remove_File()	// �������� �����.
{
	system("cls");
	char Name[MAX_PATH];	// ������� � ����� ��� �����.
	cout << "������� ��� ����� ��� ��������, � ��������� ����: ";
	cin.getline(Name, MAX_PATH);
	if (remove(Name))		//	������� ���� � ��������� ���������
	{
		cout << "������ �������� �����! ��������� ��� � ������ �� ����" << endl << endl;
		return;
	}
	else cout << "���� ������� ������!" << endl << endl;
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Create_Directory(const char* Name)	// �������� �����.
{
	// ������� ����� � ���������.
	if (_mkdir(Name) == -1)
	{
		cout << "������ �������� �����! ��������� ��� � ����!" << endl << endl;
		return;
	}
}

void FileManager::Rename_Directory()	// �������������� �����.
{
	system("cls");
	// ������� � ����� ��� �����:
	char OldName[MAX_PATH];
	char NewName[MAX_PATH];
	cout << "������� ������ ��� ����� ��� ��������������, � ��������� ����: ";
	cin.getline(OldName, MAX_PATH);
	cout << "������� ����� ��� ����� ��� ��������������, � ��������� ����: ";
	cin.getline(NewName, MAX_PATH);
	// �������������� � ��������.
	if (rename(OldName, NewName))	// rename ���������� 0 ���� �������, � ��� ������ ���� �� �������.
	{
		cout << "������ �������������� �����! ��������� ������ � ����� ���� � ��� �����!" << endl << endl;
		return;
	}
	else cout << "����� ������� �������������!" << endl << endl;
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Copy_Directory(const char* Source, const char* Destination)	// ����������� �����.
{
	char Path[MAX_PATH];
	strcpy_s(Path, Source);		// ���������� ������� ���� � ��� �����.
	strcat_s(Path, "\\*.*");	// ������������ ����� ��� ������ ���� ������ � ����������.
	_finddata_t Find;			// ��������� ��� �������� ����������� ������.
	// ������ ������:
	long Done = _findfirst(Path, &Find);
	// ���� Done = -1 �� ������ ���.
	int MayWeWork = Done;	// ����������, ����� � �� ����������� ������ �� ���������� ��������.
	if (MayWeWork == -1)
	{
		cout << "����� �� ����������!" << endl;
		return;
	}
	Create_Directory(Destination);	// �������� ����� ����������.
	while (MayWeWork != -1)
	{
		if (strcmp(Find.name, ".") && strcmp(Find.name, ".."))
		{
			if (Find.attrib & _A_SUBDIR)		// �������� ���� ��� ����� �������.
			{
				// ������� �����
				char SubDirSrc[MAX_PATH];		// ��������� ������ ��� �������� ���� � �������� � ���������.
				strcpy_s(SubDirSrc, Source);	// ��������� ���� � �������� ��� ���������.
				strcat_s(SubDirSrc, "\\");
				strcat_s(SubDirSrc, Find.name);

				char SubDirDest[MAX_PATH];			// ��������� ������ ��� �������� ���� � �������� � ���������.
				strcpy_s(SubDirDest, Destination);	// ��������� ���� � �������� ��� ����������.
				strcat_s(SubDirDest, "\\");
				strcat_s(SubDirDest, Find.name);
				CountDir++;
				Copy_Directory(SubDirSrc, SubDirDest);	// ����� ������� ��� ����������� ��������.
			}
			else
			{
				// ������� ����.
				char FileSrc[MAX_PATH];				// ��������� ������ ��� �������� ���� � ����� � ���������.
				strcpy_s(FileSrc, Source);			// ��������� ���� � �������� ��� ���������.
				strcat_s(FileSrc, "\\");
				strcat_s(FileSrc, Find.name);

				char FileDest[MAX_PATH];			// ��������� ������ ��� �������� ���� � �������� � ����������.
				strcpy_s(FileDest, Destination);	// ��������� ���� � �������� ��� ����������.
				strcat_s(FileDest, "\\");
				strcat_s(FileDest, Find.name);
				CountFile++;
				Copy_File(FileSrc, FileDest);		// �������� ������� ��� ����������� �����.
			}
		}
		MayWeWork = _findnext(Done, &Find);			// ����� ������.
	}
	_findclose(Done);
}

void FileManager::Remove_Directory()	// �������� �����.
{
	char Name[MAX_PATH];	// ��� �����.
	cout << "������� ��� ����� ��� ��������, � ��������� ����: ";
	cin.getline(Name, MAX_PATH);
	// �������������� � ��������.
	if (_rmdir(Name) == -1)
	{
		// �������� ����������� ����� ������� �������� ����������� ����������
		//Remove_file();	//��� ������.
		//Remove_directory();	//��� ��������.
		cout << "������ �������� �����! ��������� ���� � ��� ����� � ����� �� ���!" << endl;
		return;
	}
	else cout << "����� ������� �������!" << endl;
}