#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <Shellapi.h>
#include "NOVEL.h"

using namespace std;

// OTHER
int Novel::HowManyChapters(Novel novel)
{
	string folderPath = "RanobeLib\\" + novel.title;
	int count = 0;
	WIN32_FIND_DATAA findData;
	HANDLE hFind;

	string searchPath = folderPath + "\\*.*";
	hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				string fileName = findData.cFileName;
				string extension = fileName.substr(fileName.find_last_of(".") + 1);
				if (extension == "txt")
				{
					count++;
				}
			}
		} while (FindNextFileA(hFind, &findData) != 0);

		FindClose(hFind);
	}

	count--; return count;
}
bool Novel::ChapterNameCheck(string chapter, string title)
{
	string path = "RanobeLib\\" + title;

	ifstream file;
	file.open(path);
	if (!file)
	{
		cout << "Invalid directory: " << path << endl;
		return false;
	}

	string filename;
	while (getline(file, filename))
	{
		if (filename.substr(0, filename.find_last_of('.')) == chapter && filename.substr(filename.find_last_of('.') + 1) == "txt")
		{
			cout << "Chapter: " << filename.substr(0, filename.find_last_of('.')) << endl;
			file.close();
			return true;
		}
	}

	cout << "Wrong chapter name!" << endl;
	file.close();
	return false;
}

// Novel work
void Novel::NewChapter(Novel novel)
{
	string fileName;
	cout << "Write chapter name (without spaces! For example: FirstChapter) ~~~ "; cin >> fileName;
	bool hasSpaces = false;
	for (char c : fileName)
	{
		if (c == ' ')
		{
			hasSpaces = true; cout << "Chapter has spaces! Try again later!" << endl;
			break;
		}
	}
	if (hasSpaces == false)
	{
		string filePath = "RanobeLib\\" + novel.title + "\\" + fileName + ".txt";

		ofstream file(filePath);
		cout << (file.is_open() ? "The chapter was successfully created!" : "The chapter was not created!") << endl;
	}

	RedactChapter(novel, fileName);
}
bool Novel::DeleteNovel(Novel novel)
{
	string filename = "RanobeLib\\" + novel.title;
	LPCSTR path = filename.c_str();

	if (!RemoveDirectoryA(path))
	{
		cout << "I couldn't delete the novel!" << endl;
		return false;
	}

	cout << "The novel has been successfully deleted!" << filename << endl; return true;
}
void Novel::RewriteInfo(Novel& novel)
{
	bool ex = false; int option;
	while (ex == false)
	{
		cout << "___---___---___---___---___---___---___" << endl;
		cout << "What do you want to change?\n[0] - Go back\n[1] - Title\n[2] - Rating\n[3] - Volumes\n[4] - Chapters\n[5] - Full name\n[6] - Age rating\n[7] - Status\n[8] - Released year\n[9] - Genres\n[10] - Description\n[11] - Author" << endl;
		cout << "Your choice  (/`^_^)/'  "; cin >> option;
		cout << "___---___---___---___---___---___---___" << endl;

		switch (option)
		{
		case 0: ex = true; break;
		case 1: // Title
			cout << "Enter a new title: "; cin >> novel.title; break;
		case 2: // Rating
			cout << "Enter a new rating: "; cin >> novel.rating; break;
		case 3: // Volumes
			cout << "Enter a new volumes number: "; cin >> novel.volumes; break;
		case 4: // Chapters
			cout << "Enter a new chapters number: "; cin >> novel.chapters; break;
		case 5: // Full name
			cout << "Enter a new full name: "; cin >> novel.FullName; break;
		case 6: // Age rating
			cout << "Enter a new rating: "; cin >> novel.rating; break;
		case 7: // Status
			cout << "Enter a new status: "; cin >> novel.status; break;
		case 8: // Released year
			cout << "Enter a new released year: "; cin >> novel.releasedYear; break;
		case 9: // Genres
			GenresPrint(); cout << endl;
			cout << "Enter the new genre numbers (from the table above) and enter [0] when you finish entering!" << endl;

			for (int i = 0; i < 30; i++)
			{
				cin >> novel.genre[i];
				if (novel.genre[i] == 0)
				{
					i = 30;
				}
				else if (novel.genre[i] > 30 || novel.genre[i] < 1)
				{
					cout << "Incorrect genre number! Try a number between [1] and [30]!" << endl;
					i--;
				}
				for (int j = 0; j < 30; j++)
				{
					if (novel.genre[i] == novel.genre[j])
					{
						cout << "You have already entered this genre try entering something else!" << endl;
						i--;
					}
				}
			}
			break;
		case 10: // Description
			system("cls");
			cout << "Enter the new description of the title storyline: ";
			cin.ignore(); getline(cin, novel.description); break;
		case 11:
			cout << "Enter the new author of the title: "; novel.author;
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause"); break;
		}
	}
}
bool Novel::NewNovel(Novel*& arr, int& size)
{
	string titl;
	cout << "Write ranobe title: \nTitle (name without spaces! For example: NameOfTitle) ~~~ "; cin >> titl;
	bool hasSpaces = false;
	for (char c : titl)
	{
		if (c == ' ')
		{
			hasSpaces = true;
			return false;
		}
	}
	if (hasSpaces == false)
	{
		Novel* newArr = new Novel[size + 1];
		for (int i = 0; i < size; i++)
		{
			newArr[i] = arr[i];
		}
		newArr[size].title = titl;
		string command = "md RanobeLib\\" + newArr[size].title;
		if (system(command.c_str()) == 0)
		{
			cout << "Ok!" << endl;
			cout << "What is his rating? "; cin >> newArr[size].rating;
			cout << "How many volumes are there? "; cin >> newArr[size].volumes;
			cout << "Enter full name: "; cin.ignore(); getline(cin, newArr[size].FullName);
			cout << "What is the age rating of this anime? "; cin >> newArr[size].ageRating;
			cout << "What is the status of this anime? (ongoing, completed, frozen) "; cin >> newArr[size].status;
			cout << "What year did this anime start airing? "; cin >> newArr[size].releasedYear;
			cout << "Who is the author of this title? "; cin.ignore(); getline(cin, newArr[size].author);

			for (int i = 0; i < 30; i++)
			{
				system("cls");
				GenresPrint(); cout << endl;
				cout << "Enter the genre numbers (from the table above) and enter [0] when you finish entering!" << endl;

				cin >> newArr[size].genre[i];
				if (newArr[size].genre[i] == 0)
				{
					break;
				}
				else if (newArr[size].genre[i] > 35 || newArr[size].genre[i] < 1)
				{
					cout << "Incorrect genre number! Try a number between [1] and [35]!" << endl; system("pause");
				}
				for (int j = 0; j < 30; j++)
				{
					if (newArr[size].genre[i] == newArr[size].genre[j] && i != j)
					{
						cout << "You have already entered this genre try entering something else!" << endl; system("pause");
					}
				}
			}

			system("cls");
			cout << "Description of the anime storyline: ";
			cin.ignore(); getline(cin, newArr[size].description); bool check = false;

			for (int i = 0; i < size; i++)
			{
				if (newArr[i].ID == size)
				{
					newArr[size].ID = ++size; i = 0;
				}
			}

			delete[] arr;
			arr = newArr;
			size++;

			char chce;
			cout << "Do you want to add a new chapter?\n[Y] / [N]\n(0_0)? "; cin >> chce;
			if (chce == 'y' || chce == 'Y')
			{
				return true;
			}
			cout << "Ok! That's all!" << endl;
			return false;
		}
		else
		{
			cout << "Something went wrong :(" << endl;
		}
	}
	else
	{
		cout << "You were told not to use the space! \\(`o_`o#\\)" << endl; // Idiot -_-
	}
}
void Novel::ReadChapter(Novel novel, string chapter)
{
	string filePath = "RanobeLib\\" + novel.title + "\\" + chapter;
	wstring wFilePath(filePath.begin(), filePath.end());
	ShellExecuteW(nullptr, L"open", L"notepad.exe", wFilePath.c_str(), nullptr, SW_SHOWNORMAL);
}
bool Novel::DeleteChepter(Novel novel, string chapter)
{
	string filename = "RanobeLib\\" + novel.title + "\\" + chapter + ".txt";
	LPCSTR path = filename.c_str();

	BOOL result = DeleteFileA(path);

	if (result == FALSE)
	{
		cout << "Can't delete this file!" << endl; return false;
	}
	return true;
}
void Novel::RedactChapter(Novel novel, string chapter)
{
	string path = "RanobeLib\\" + novel.title + "\\" + chapter + ".txt";
	
	ifstream file(path);
	if (!file)
	{
		cout << "File not found: " << path << endl;
		return;
	}
	file.close();

	wstring wpath(path.begin(), path.end());
	LPCWSTR filePath = wpath.c_str();

	HINSTANCE result = ShellExecuteW(nullptr, L"open", L"notepad.exe", filePath, nullptr, SW_SHOW);
	if ((int)result <= 32)
	{
		cout << "Failed to open file in Notepad." << endl;
	}
}

// Prints
void Novel::Print()
{
	cout << "Title: " << FullName << "\nRating: " << rating << "\nVolumes: " << volumes
		<< "\nChapters: " << chapters << "\nAge rating: " << ageRating << "\nStatus: " << status
		<< "\nRelease year: " << releasedYear << "\nAuthor: " << author;
	cout << "\nDescription:\n" << description << endl;
}
void Novel::GenresPrint()
{
	cout << "[1] - Action" << "\t\t" << "[11] - Josei" << "\t\t" << "[21] - Sci-fi" << "\t\t" << "[31] - Xianxia" << endl
		<< "[2] - Adult" << "\t\t" << "[12] - Historical" << "\t" << "[22] - Seinen" << "\t\t" << "[32] - Xuanhuan" << endl
		<< "[3] - Adventure" << "\t\t" << "[13] - Horror" << "\t\t" << "[23] - Shoujo" << "\t\t" << "[33] - Wuxia" << endl
		<< "[4] - Comedy" << "\t\t" << "[14] - MartialArts" << "\t" << "[24] - Shounen" << "\t\t" << "[34] - Yaoi" << endl
		<< "[5] - Drama" << "\t\t" << "[15] - Mature" << "\t\t" << "[25] - SliceOfLife" << "\t" << "[35] - Yuri" << endl
		<< "[6] - Ecchi" << "\t\t" << "[16] - Mecha" << "\t\t" << "[26] - ShounenAi" << endl
		<< "[7] - Fantasy" << "\t\t" << "[17] - Mystery" << "\t\t" << "[27] - Sports" << endl
		<< "[8] - Game" << "\t\t" << "[18] - Psychological" << "\t" << "[28] - Supernatural" << endl
		<< "[9] - GenderBend" << "\t" << "[19] - Romance" << "\t\t" << "[29] - Smut" << endl
		<< "[10] - Harem" << "\t\t" << "[20] - SchoolLife" << "\t" << "[30] - Trageby" << endl;
}
void Novel::ChaptersPrint(string title)
{
	string path = "RanobeLib\\" + title;

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA((path + "\\*").c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "Invalid directory: " << path << endl;
		return;
	}
	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// Continue!
		}
		else
		{
			string filename = findData.cFileName;
			string extension = filename.substr(filename.find_last_of('.') + 1);
			if (extension == "txt")
			{
				cout << "Chapter: " << filename << endl;
			}
		}
	} while (FindNextFileA(hFind, &findData) != 0);

	FindClose(hFind);
}
void Novel::PrintAll(int size, Novel arr[])
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		arr[i].Print();
	}
}
void Novel::PrintGenreByNumber(int givenGenre)
{
	string genres[] =
	{
		"Action", "Adult", "Adventure", "Comedy", "Drama", "Ecchi", "Fantasy",
		"Game", "GenderBend", "Harem", "Josei", "Historical", "Horror",
		"MartialArts", "Mature", "Mecha", "Mystery", "Psychological",
		"Romance", "SchoolLife", "Sci-fi", "Seinen", "Shoujo", "Shounen",
		"SliceOfLife", "ShounenAi", "Sports", "Supernatural", "Smut", "Trageby"
	};

	if (givenGenre >= 1 && givenGenre <= 30)
	{
		cout << genres[givenGenre] << endl;
	}
}
void Novel::FullNovelPrint(int size, Novel arr[], int i)
{
	cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;
	cout << "     | " << arr[i].FullName << " |" << endl
		<< "Rating ~ " << arr[i].rating << "\nVolumes ~ " << arr[i].volumes
		<< "\nChapters ~ " << arr[i].chapters << "\nAge rating ~ " << arr[i].ageRating
		<< "\nStatus ~ " << arr[i].status << "\nRelease year ~ " << arr[i].releasedYear;
	for (int j = 0; j < size; j++)
	{
		if (arr[i].genre[j] != 0)
		{
			PrintGenreByNumber(arr[i].genre[j]);
		}
	}
	cout << " ~ ~ ~ ~ ~ ~ ~ Description ~ ~ ~ ~ ~ ~ ~ " << endl << arr[i].description << endl;
	cout << " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ " << endl;
}

// SEARCHES
int Novel::NameSearch(int size, Novel arr[])
{
	Novel temp;
	cout << "Enter title: "; cin.ignore(); getline(cin, temp.FullName);

	for (int i = 1; i < size; i++)
	{
		if (temp.FullName == arr[i].FullName)
		{
			cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
			arr[i].FullNovelPrint(size, arr, i);
			cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;

			return i;
		}
	}
	return -1;
}
int Novel::GenreSearch(int size, Novel arr[])
{
	GenresPrint(); cout << endl;
	int choicesArray[30] = {};
	int arraysize = 0;

	cout << "Enter the genre numbers (from the table above) and enter [0] when you finish entering!" << endl;

	for (int i = 0; i < 30; i++)
	{
		cin >> choicesArray[i];
		if (choicesArray[i] == 0)
		{
			i = 30;
			SearchNovelsByGenres(arr, size, choicesArray, arraysize);
		}
		else if (choicesArray[i] > 30 || choicesArray[i] < 1)
		{
			cout << "Incorrect genre number! Try a number between [1] and [30]!" << endl;
			i--;
		}
		for (int j = 0; j < 30; j++)
		{
			if (choicesArray[i] == choicesArray[j])
			{
				cout << "You have already entered this genre try entering something else!" << endl; i--;
			}
		}
	}
	return 0;
}
int Novel::RatingSearch(int size, Novel arr[])
{
	bool find = false; Novel temp;
	cout << "Enter anime rating: "; cin >> temp.rating;

	for (int i = 1; i < size; i++)
	{
		if (temp.rating == arr[i].rating)
		{
			cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
			arr[i].Print();
		}
	}
	cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;

	cout << "[0] - Exit\n[1] - Choose a novel\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter novel's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}
int Novel::VolumesSearch(int size, Novel arr[])
{
	Novel temp;
	cout << "Enter number of volumes: "; cin >> temp.volumes;

	for (int i = 1; i < size; i++)
	{
		if (temp.volumes == arr[i].volumes)
		{
			cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
			arr[i].Print();
		}
	}
	cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;

	cout << "[0] - Exit\n[1] - Choose a novel\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter novel's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}
int Novel::ChaptersSearch(int size, Novel arr[])
{
	Novel temp;
	cout << "Enter number of chapters: "; cin >> temp.chapters;

	for (int i = 1; i < size; i++)
	{
		if (arr[0].chapters == arr[i].chapters)
		{
			cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
			arr[i].Print();
		}
	}
	cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;

	cout << "[0] - Exit\n[1] - Choose a novel\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter novel's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}
int Novel::AgeRatingSearch(int size, Novel arr[])
{
	Novel temp;
	cout << "Enter title age rating: "; cin >> temp.ageRating;

	for (int i = 1; i < size; i++)
	{
		if (temp.ageRating == arr[i].ageRating)
		{
			cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
			arr[i].Print();
		}
	}
	cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
	cout << "[0] - Exit\n[1] - Choose a novel\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter novel's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}
void Novel::SearchNovelsByGenres(Novel* arr, int size, int* searchGenres, int searchSize)
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		bool found = true;
		for (int j = 0; j < searchSize; j++)
		{
			bool genreFound = false;
			for (int k = 0; k < 30; k++)
			{
				if (arr[i].genre[k] == searchGenres[j])
				{
					genreFound = true;
					break;
				}
			}
			if (!genreFound)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
			arr[i].Print();
		}
	}
}

// MENU
void Novel::UserMenu(int size, Novel arr[])
{
	for (int i = 0; i < size; i++)
	{
		arr[i].chapters = HowManyChapters(arr[i]);
	}
	system("cls");
	bool ex = false; int choice;
	while (ex == false)
	{
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;
		cout << "[0] - Go back\n[1] - Find title by...\n[2] - Print all ranobe list" << endl;
		cout << " (o_O)? "; cin >> choice;
		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Find title by...
			FindTitleByUserMenu(size, arr);
			break;
		case 2: // Print all ranobe list
			PrintAll(size, arr);
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}
void Novel::AdminMenu(int size, Novel arr[])
{
	for (int i = 0; i < size; i++)
	{
		arr[i].chapters = HowManyChapters(arr[i]);
	}
	system("cls");
	bool ex = false; int choice;
	while (ex == false)
	{
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;
		cout << "[0] - Go back\n[1] - Find title by...\n[2] - Print all ranobe list\n[3] - Add new novel" << endl;
		cout << " (o_O)? "; cin >> choice;
		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Find title by...
			FindTitleByAdminMenu(size, arr);
			break;
		case 2: // Print all ranobe list
			PrintAll(size, arr); system("pause");
			break;
		case 3:
			choice = NewNovel(arr, size); 
			if (choice == true)
			{
				NewChapter(arr[size - 1]);
			}
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}

}
void Novel::EditorMenu(int size, Novel arr[])
{
	for (int i = 0; i < size; i++)
	{
		arr[i].chapters = HowManyChapters(arr[i]);
	}
	system("cls");
	bool ex = false; int choice;
	while (ex == false)
	{
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;
		cout << "[0] - Go back\n[1] - Find title by...\n[2] - Print all ranobe list" << endl;
		cout << " (o_O)? "; cin >> choice;
		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Find title by...
			FindTitleByEditorMenu(size, arr);
			break;
		case 2: // Print all ranobe list
			PrintAll(size, arr);
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}

// "FIND TITLE" MENU
void Novel::FindTitleByUserMenu(int size, Novel arr[])
{
	int choice; int resultof = 0;
	cout << "Find title by:\n[1] - Name\n[2] - Genres\n[3] - Rating\n[4] - Number of volumes\n[5] - number of chapters\n[6] - Age rating\n[0] - Go back" << endl;
	cout << " (o_O)? "; cin >> choice;
	switch (choice)
	{
	case 0: break;
	case 1: // Name
		resultof = NameSearch(size, arr);
		resultof != -1 ? WorkWithNovelUser(size, arr, resultof) : void(0);
		break;
	case 2: // Genres
		resultof = GenreSearch(size, arr);
		resultof != -1 ? WorkWithNovelUser(size, arr, resultof) : void(0);
		break;
	case 3: // Rating
		resultof = RatingSearch(size, arr);
		resultof != -1 ? WorkWithNovelUser(size, arr, resultof) : void(0);
		break;
	case 4: // Volumes
		resultof = VolumesSearch(size, arr);
		resultof != -1 ? WorkWithNovelUser(size, arr, resultof) : void(0);
		break;
	case 5: // Chapters
		resultof = ChaptersSearch(size, arr);
		resultof != -1 ? WorkWithNovelUser(size, arr, resultof) : void(0);
		break;
	case 6: // Age rating
		resultof = AgeRatingSearch(size, arr);
		resultof != -1 ? WorkWithNovelUser(size, arr, resultof) : void(0);
		break;
	default:
		cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
		break;
	}
}
void Novel::FindTitleByAdminMenu(int size, Novel arr[])
{
	int choice; int resultof = 0;
	cout << "Find title by:\n[1] - Name\n[2] - Genres\n[3] - Rating\n[4] - Number of volumes\n[5] - number of chapters\n[6] - Age rating\n[0] - Go back" << endl;
	cout << " (o_O)? "; cin >> choice;
	switch (choice)
	{
	case 0: break;
	case 1: // Name
		resultof = NameSearch(size, arr);
		resultof != -1 ? WorkWithNovelAdmin(size, arr, resultof) : void(0);
		break;
	case 2: // Genres
		resultof = GenreSearch(size, arr);
		resultof != -1 ? WorkWithNovelAdmin(size, arr, resultof) : void(0);
		break;
	case 3: // Rating
		resultof = RatingSearch(size, arr);
		resultof != -1 ? WorkWithNovelAdmin(size, arr, resultof) : void(0);
		break;
	case 4: // Volumes
		resultof = VolumesSearch(size, arr);
		resultof != -1 ? WorkWithNovelAdmin(size, arr, resultof) : void(0);
		break;
	case 5: // Chapters
		resultof = ChaptersSearch(size, arr);
		resultof != -1 ? WorkWithNovelAdmin(size, arr, resultof) : void(0);
		break;
	case 6: // Age rating
		resultof = AgeRatingSearch(size, arr);
		resultof != -1 ? WorkWithNovelAdmin(size, arr, resultof) : void(0);
		break;
	default:
		cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
		break;
	}
}
void Novel::FindTitleByEditorMenu(int size, Novel arr[])
{
	int choice; int resultof = 0;
	cout << "Find title by:\n[1] - Name\n[2] - Genres\n[3] - Rating\n[4] - Number of volumes\n[5] - number of chapters\n[6] - Age rating\n[0] - Go back" << endl;
	cout << " (o_O)? "; cin >> choice;
	switch (choice)
	{
	case 0: break;
	case 1: // Name
		resultof = NameSearch(size, arr);
		resultof != -1 ? WorkWithNovelEditor(size, arr, resultof) : void(0);
		break;
	case 2: // Genres
		resultof = GenreSearch(size, arr);
		resultof != -1 ? WorkWithNovelEditor(size, arr, resultof) : void(0);
		break;
	case 3: // Rating
		resultof = RatingSearch(size, arr);
		resultof != -1 ? WorkWithNovelEditor(size, arr, resultof) : void(0);
		break;
	case 4: // Volumes
		resultof = VolumesSearch(size, arr);
		resultof != -1 ? WorkWithNovelEditor(size, arr, resultof) : void(0);
		break;
	case 5: // Chapters
		resultof = ChaptersSearch(size, arr);
		resultof != -1 ? WorkWithNovelEditor(size, arr, resultof) : void(0);
		break;
	case 6: // Age rating
		resultof = AgeRatingSearch(size, arr);
		resultof != -1 ? WorkWithNovelEditor(size, arr, resultof) : void(0);
		break;
	default:
		cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
		break;
	}
}

// WORK WITH NOVEL MENU
void Novel::WorkWithNovelUser(int size, Novel* arr, int i)
{
	bool ex = false; int choice; string chapter; bool check = false;
	while (ex == false)
	{
		cout << "[0] - Go back\n[1] - Chepters list\n[2] - Read" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Chepters list
			ChaptersPrint(arr[i].title);
			break;
		case 2: // Read
			ChaptersPrint(arr[i].title);
			cout << "Enter chepter name: "; cin >> chapter;
			check = ChapterNameCheck(chapter, arr[i].title);
			(check == true) ? ReadChapter(arr[i], chapter) : (void)printf("Wrong chapter name!\n");
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}
void Novel::WorkWithNovelAdmin(int size, Novel* arr, int i)
{
	bool ex = false; int choice; bool check = false; string chapter;
	while (ex == false)
	{
		cout << "[0] - Go back\n[1] - Chepters list\n[2] - Delete novel\n[3] - Change novel info\n[4] - Add new chepter\n[5] - Redact chepter\n[6] - Read" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Chepters list
			ChaptersPrint(arr[i].title);
			break;
		case 2: // Delete novel
			check = DeleteNovel(arr[i]);
			ex = (check == true) ? (cout << "Ok! The changes will be visible after the next login to the program" << endl, true) : (cout << "Something went wrong! >:(" << endl, false);
			break;
		case 3: // Change novel info
			RewriteInfo(arr[i]);
			break;
		case 4: // Add new chepter
			NewChapter(arr[i]);
			break;
		case 5: // Redact chepter
			ChaptersPrint(arr[i].title);
			cout << "Enter chepter name: "; cin >> chapter;
			check = ChapterNameCheck(chapter, arr[i].title);
			(check == true) ? RedactChapter(arr[i], chapter) : (void)printf("Wrong chapter name!\n");
			break;
		case 6: // Read
			ChaptersPrint(arr[i].title);
			cout << "Enter chepter name: "; cin >> chapter;
			check = ChapterNameCheck(chapter, arr[i].title);
			(check == true) ? ReadChapter(arr[i], chapter) : (void)printf("Wrong chapter name!\n");
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}
void Novel::WorkWithNovelEditor(int size, Novel* arr, int i)
{
	bool ex = false; int choice; string chapter; bool check = false;
	while (ex == false)
	{
		cout << "[0] - Go back\n[1] - Chepters list\n[2] - Add new chepter\n[3] - Redact chepter\n[4] - Read" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Chepters list
			ChaptersPrint(arr[i].title);
			break;
		case 2: // Add new chepter
			NewChapter(arr[i]);
			break;
		case 3: // Redact chepter
			ChaptersPrint(arr[i].title);
			cout << "Enter chepter name: "; cin >> chapter;
			check = ChapterNameCheck(chapter, arr[i].title);
			(check == true) ? RedactChapter(arr[i], chapter) : (void)printf("Wrong chapter name!\n");
			break;
		case 4: // Read
			ChaptersPrint(arr[i].title);
			cout << "Enter chepter name: "; cin >> chapter;
			check = ChapterNameCheck(chapter, arr[i].title);
			(check == true) ? ReadChapter(arr[i], chapter) : (void)printf("Wrong chapter name!\n");
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}