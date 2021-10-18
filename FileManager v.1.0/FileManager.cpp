#include "FileManager.h"
#include<iostream>
#include<string.h>
#include<string>
#include<stdio.h>	// Функции для работы с файлами.
#include<io.h>		// Функции для работы с файлами в плане доступа.
#include<Windows.h>
#include<direct.h>	// Библиотека для работы с директориями.

using namespace std;

FileManager::FileManager() {}
FileManager::~FileManager() {}

static int CountDir = 0;	// Количество скопированных директорий.
static int CountFile = 0;	// Количество скопированных файлов.

void FileManager::mainMenu()
{
	string selection;

	do {
		cout << "===============================\n";
		cout << "**Редактор файлов и каталогов**\n\n";
		cout << "Пожалуйста, выберите нужный вариант:\n";
		cout << " 1...Показать содержимое директории\n";
		cout << " 2...Создать файл\n";
		cout << " 3...Поиск файла\n";
		cout << " 4...Переименовать файл\n";
		cout << " 5...Копировать файл\n";
		cout << " 6...Удалить файл\n";
		cout << " 7...Создать папку\n";
		cout << " 8...Переименовать папку\n";
		cout << " 9...Копировать папку\n";
		cout << "10...Удалить папку\n";
		cout << " 0...Выход\n";
		cout << "===============================\n\n>";

		getline(cin, selection);
		cout << "\n";

		if (selection == "0")
		{
			cout << "Выйти из программы...\n";
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
			cout << "Введите имя и путь к исходному файлу: ";
			cin.getline(Source, MAX_PATH);
			cout << "Введите имя и путь к файлу назначения: ";
			cin.getline(Destination, MAX_PATH);
			Copy_File(Source, Destination);
			cout << "Файл успешно скопирован!" << endl << endl;
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
			cout << "Введите имя и путь к директории: ";
			cin.getline(Name, MAX_PATH);
			Create_Directory(Name);
			cout << "Директория успешно создана!" << endl << endl;
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
			cout << "Введите имя и путь к копируемой директории: ";
			cin.getline(Source, MAX_PATH);
			cout << "Введите имя и путь к директории назначения: ";
			cin.getline(Destination, MAX_PATH);
			Copy_Directory(Source, Destination);
			cout << "Скопировано: " << CountDir << " папка(и) и " << CountFile << " файл(а)!" << endl << endl;
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
			cout << "Пожалуйста, введите действительный пункт\n\n";
	} while (true);
}

void FileManager::Show_Directory(string Name)	// Показ содержимого директории.
{
	system("cls");
	if (Name == "")
	{
		cout << "Введите путь к директории: " << endl;
		getline(cin, Name);
	}
	// Полный путь с маской для вывода всего содержимого директории.
	char Path[MAX_PATH];
	strcpy_s(Path, Name.c_str());
	strcat_s(Path, "\\*.*");
	system("cls");
	
	_finddata_t Find;		// Объект структуры, хранящей данные о файлах.
	long Done = _findfirst(Path, &Find);
	int MayWeWork = Done;	// Переменная, чтобы в неё последующие поиски их результаты помещать.
	if (MayWeWork == -1)	// Если Done = -1 то файлов нет.
	{
		cout << "Директория не существует!" << endl;
		return;
	}
	cout << "Содержимое директории: " << Name << endl;
	cout << "________________________________________________" << endl;
	int CountDir = 0;
	int CountFile = 0;
	while (MayWeWork != -1)
	{
		// Проверка, внутри этого каталога есть ли другие каталоги
		if (strcmp(Find.name, ".") && (strcmp(Find.name, "..")))
		{
			if (Find.attrib & _A_SUBDIR)	// Если атрибут папка
			{
				cout << "Папка: \t|";
				CountDir++;
			}
			else
			{
				cout << "Файл: \t|" << Find.size;
				CountFile++;
			}
			if (Find.size <= 999999)cout << "\t";
			cout << "\t|" << Find.name <<endl;
		}
		MayWeWork = _findnext(Done, &Find);
	}
	cout << "________________________________________________" << endl;
	cout << "Количество файлов: " << CountFile << " Количество папок: " << CountDir << endl << endl;
	_findclose(Done);
	system("pause");
	cout << endl;
}

void FileManager::Create_File()	// Создание файла.
{
	system("cls");
	char fileName[MAX_PATH];	// define MAX_PATH - максимальный путь 260 символов.
	cout << "Введите имя для создания файла с указаннием пути: ";
	cin.getline(fileName, MAX_PATH);
	FILE* check;
	if (!fopen_s(&check, fileName, "r") != 0)	// Попытка открыть файл на чтение.
	{
		cout << "Файл с таким именем уже существует!" << endl << endl;
		fclose(check);
		return;
	}
	fopen_s(&check, fileName, "w");	// Открытие файла на запись (создание).
	if (!check)	// Если указатель на файл нулевой.
	{
		cout << "Ошибка создания файла!" << endl << endl;
		return;
	}
	cout << "Файл успешно создан!" << endl << endl;
	fclose(check);
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Find_File()	// Поиск файла.
{
	system("cls");
	char Path[MAX_PATH];		// Запрос пути к файлу
	cout << "Введите путь к директории для поиска файлов: ";
	cin.getline(Path, MAX_PATH);
	char Mask[MAX_PATH];		// Запрос маски для поиска файла
	cout << "Введите маску для поиска файлов (например *.* или *.txt): ";
	cin.getline(Mask, MAX_PATH);
	char FullPath[MAX_PATH];	// Соединение пути и маски
	strcpy_s(FullPath, Path);	// Копирование.
	strcat_s(FullPath, Mask);	// Добавление.
	_finddata_t* InfoFile = new _finddata_t;	// Создание объекта структуры, хранящей данные о файлах.
	long Done = _findfirst(FullPath, InfoFile);	// Поиск.
	int MayWeWork = Done;		// Переменная, чтобы в неё последующие поиски их результаты помещать.
	int Count = 0;				// Счетчик количества найденных файлов.
	while (MayWeWork != -1)
	{
		Count++;
		cout << InfoFile->name << endl;			// Вывод имени найденного файла.
		MayWeWork = _findnext(Done, InfoFile);	// Поиск следующего файла.
	}
	cout << "Было найдено " << Count << " файл(а/ов) в директории " << Path << " по маске: " << Mask << endl << endl;
	_findclose(Done);	// Освобождение памяти, выделеной под структуру finddata.
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Rename_File()	// Переименование файла.
{
	system("cls");
	// Текущее и новое имя файла:
	char OldName[MAX_PATH];
	char NewName[MAX_PATH];
	cout << "Введите старое имя файла для переименования, с указанием пути: ";
	cin.getline(OldName, MAX_PATH);
	cout << "Введите новое имя файла для переименования, с указанием пути: ";
	cin.getline(NewName, MAX_PATH);
	// Переименование и проверка.
	if (rename(OldName, NewName))	// rename возвращает 0 если успешно, и код ошибки если не удалось.
	{
		cout << "Ошибка переименования файла! Проверьте имя и закрыт ли файл!" << endl << endl;
		return;
	}
	else cout << "Файл успешно переименован!" << endl << endl;
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Copy_File(const char* Source, const char* Destination)	// Копирование файла откуда и куда.
{
	// Указатели на файлы:
	FILE* Src, * Dest;
	// Открытие оригинального файла в бинарном(двоичном) режиме на чтение.
	if (fopen_s(&Src, Source, "rb") != 0)
	{
		cout << "Файл не найден! Проверьте имя и путь к файлу!" << endl << endl;
		return;
	}
	int hSrc = _fileno(Src);		// Получить дискриптор файла.
	int Size = _filelength(hSrc);	// Определить размер файла.
	char* Data = new char[Size];	// Выделить память под буфер для копирования содержимого файла.
	if (!Data)
	{
		cout << "Ошибка выделения памяти, при создании буфера для копирования файла!" << endl << endl;
		fclose(Src);
		return;
	}
	if (fopen_s(&Dest, Destination, "wb") != 0)	// Открывтие файла назначения, в бинарном режиме на запись.
	{
		cout << "Ошибка копирования файла! Проверьте имя и путь назначения!" << endl << endl;
		fclose(Src);
		delete[] Data;
		return;
	}
	int DataValue;		// Объем данных.
	// Считать данные:
	while (!feof(Src))	// Пока не дошли до конца исходного файла.
	{
		// Считать данные в строку Data, подсчитывая объем данных в строке и помещая его в DataValue
		DataValue = fread(Data, sizeof(char), Size, Src);			// fread работает в бинарном режиме.
		if (DataValue)fwrite(Data, sizeof(char), DataValue, Dest);	// Записать строку в файл назначения.
		else break;	// Если закончились данные заканчиваем запись.
	}
	// Закрыть файлы:
	fclose(Src);
	fclose(Dest);
	// Освобождение памяти, выделенную под буфер.
	delete[] Data;
}

void FileManager::Remove_File()	// Удаление файла.
{
	system("cls");
	char Name[MAX_PATH];	// Текущее и новое имя файла.
	cout << "Введите имя файла для удаления, с указанием пути: ";
	cin.getline(Name, MAX_PATH);
	if (remove(Name))		//	Удалить файл и проверить результат
	{
		cout << "Ошибка удаления файла! Проверьте имя и закрыт ли файл" << endl << endl;
		return;
	}
	else cout << "Файл успешно удален!" << endl << endl;
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Create_Directory(const char* Name)	// Создание папки.
{
	// Создать папку и проверить.
	if (_mkdir(Name) == -1)
	{
		cout << "Ошибка создания папки! Проверьте имя и путь!" << endl << endl;
		return;
	}
}

void FileManager::Rename_Directory()	// Переименование папки.
{
	system("cls");
	// Текущее и новое имя папки:
	char OldName[MAX_PATH];
	char NewName[MAX_PATH];
	cout << "Введите старое имя папки для переименования, с указанием пути: ";
	cin.getline(OldName, MAX_PATH);
	cout << "Введите новое имя папки для переименования, с указанием пути: ";
	cin.getline(NewName, MAX_PATH);
	// Переименование и проверка.
	if (rename(OldName, NewName))	// rename возвращает 0 если успешно, и код ошибки если не удалось.
	{
		cout << "Ошибка переименования папки! Проверьте старый и новый путь и имя папки!" << endl << endl;
		return;
	}
	else cout << "Папка успешно переименована!" << endl << endl;
	system("pause");
	cout << endl;
	system("cls");
}

void FileManager::Copy_Directory(const char* Source, const char* Destination)	// Копирование папки.
{
	char Path[MAX_PATH];
	strcpy_s(Path, Source);		// Копировать текущий путь и имя папки.
	strcat_s(Path, "\\*.*");	// Присоединить маску для поиска всех файлов в директории.
	_finddata_t Find;			// Структура для хранения результатов поиска.
	// Начало поиска:
	long Done = _findfirst(Path, &Find);
	// Если Done = -1 то файлов нет.
	int MayWeWork = Done;	// Переменная, чтобы в неё последующие поиски их результаты помещать.
	if (MayWeWork == -1)
	{
		cout << "Папка не существует!" << endl;
		return;
	}
	Create_Directory(Destination);	// Создание папки назначения.
	while (MayWeWork != -1)
	{
		if (strcmp(Find.name, ".") && strcmp(Find.name, ".."))
		{
			if (Find.attrib & _A_SUBDIR)		// Проверка файл или папка найдена.
			{
				// Копирую папки
				char SubDirSrc[MAX_PATH];		// Временная строка для хранения пути к подпапке в источнике.
				strcpy_s(SubDirSrc, Source);	// Запоминаю путь к подпапке для источника.
				strcat_s(SubDirSrc, "\\");
				strcat_s(SubDirSrc, Find.name);

				char SubDirDest[MAX_PATH];			// Временная строка для хранения пути к подпапке в источнике.
				strcpy_s(SubDirDest, Destination);	// Запоминаю путь к подпапке для назначения.
				strcat_s(SubDirDest, "\\");
				strcat_s(SubDirDest, Find.name);
				CountDir++;
				Copy_Directory(SubDirSrc, SubDirDest);	// Вызов функции для копирования подпапки.
			}
			else
			{
				// Копирую файл.
				char FileSrc[MAX_PATH];				// Временная строка для хранения пути к файлу в источнике.
				strcpy_s(FileSrc, Source);			// Запоминаю путь к подпапке для источника.
				strcat_s(FileSrc, "\\");
				strcat_s(FileSrc, Find.name);

				char FileDest[MAX_PATH];			// Временная строка для хранения пути к подпапке в назначении.
				strcpy_s(FileDest, Destination);	// Запоминаю путь к подпапке для назначения.
				strcat_s(FileDest, "\\");
				strcat_s(FileDest, Find.name);
				CountFile++;
				Copy_File(FileSrc, FileDest);		// Вызываем функцию для копирования файла.
			}
		}
		MayWeWork = _findnext(Done, &Find);			// Поиск дальше.
	}
	_findclose(Done);
}

void FileManager::Remove_Directory()	// Удаление папки.
{
	char Name[MAX_PATH];	// Имя папки.
	cout << "Введите имя папки для удаления, с указанием пути: ";
	cin.getline(Name, MAX_PATH);
	// Переименование и проверка.
	if (_rmdir(Name) == -1)
	{
		// Добавить рекурсивный вызов функции удаления содержимого директории
		//Remove_file();	//для файлов.
		//Remove_directory();	//для каталога.
		cout << "Ошибка удаления папки! Проверьте путь и имя папки и пуста ли она!" << endl;
		return;
	}
	else cout << "Папка успешно удалена!" << endl;
}