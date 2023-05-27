#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <Shellapi.h>
#include "NOVEL.h"

using namespace std;


// Novel work
void Novel::NewNovel()
{
	cout << "Write ranobe title: \nTitle (name without spaces! For example: NameOfTitle) ~~~ "; cin >> title;
	bool hasSpaces = false;
	for (char c : title)
	{
		if (c == ' ')
		{
			hasSpaces = true;
			break;
		}
	}
	if (hasSpaces == false)
	{
		string command = "md RanobeLib\\" + title;
		if (system(command.c_str()) == 0)
		{
			cout << "Ok!" << endl;
			cout << "What is his rating? "; cin >> rating;
			cout << "How many volumes are there? "; cin >> volumes;
			cout << "How many chapters are there? "; cin >> chapters;
			cout << "Enter full name: "; cin.ignore(); getline(cin, FullName);
			cout << "What is the age rating of this anime? "; cin >> ageRating;
			cout << "What is the status of this anime? (ongoing, completed, frozen) "; cin >> status;
			cout << "What year did this anime start airing? "; cin >> releasedYear;

			GenresPrint(); cout << endl;

			cout << "Enter the genre numbers (from the table above) and enter [0] when you finish entering!" << endl;

			for (int i = 0; i < 30; i++)
			{
				cin >> genre[i];
				if (genre[i] == 0)
				{
					i = 30;
				}
				else if (genre[i] > 30 || genre[i] < 1)
				{
					cout << "Incorrect genre number! Try a number between [1] and [30]!" << endl;
				}
				for (int j = 0; j < 30; j++)
				{
					if (genre[i] == genre[j])
					{
						cout << "You have already entered this genre try entering something else!" << endl;
					}
				}
			}

			system("cls");
			cout << "Description of the anime storyline: ";
			cin.ignore(); getline(cin, description);

			char chce;
			cout << "Do you want to add a new chapter?\n[Y] / [N]\n(0_0)? "; cin >> chce;
			if (chce == 'y' || chce == 'Y')
			{
				
			}
			cout << "Ok! That's all!" << endl;
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
void Novel::RewriteInfo(Novel& novel)
{
	bool ex = false; int option;
	while (ex == false)
	{
		cout << "___---___---___---___---___---___---___" << endl;
		cout << "What do you want to change?\n[0] - Go back\n[1] - Title\n[2] - Rating\n[3] - Volumes\n[4] - Chapters\n[5] - Full name\n[6] - Age rating\n[7] - Status\n[8] - Released year\n[9] - Genres\n[10] - Description" << endl;
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
			cout << "Enter the new description of the anime storyline: ";
			cin.ignore(); getline(cin, novel.description); break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause"); break;
		}
	}
}


// Prints
void Novel::Print()
{
	cout << "Title: " << FullName << "\nRating: " << rating << "\nVolumes: " << volumes
		<< "\nChapters: " << chapters << "\nAge rating: " << ageRating
		<< "\nStatus: " << status << "\nRelease year: " << releasedYear;
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
void Novel::PrintAll(int size, Novel arr[])
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		cout << arr[i].FullName << "  ~~~  title rating - " << arr[i].rating << "  ~  chapters - " << arr[i].chapters << "  ~  age rating - " << arr[i].ageRating << "  ~  ID - " << arr[i].ID << endl;
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
			arr[i].Print();
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
	bool ex = false; int choice;
	system("cls");
	while (ex == false)
	{
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;
		cout << "[[0] - Go back\n[1] - Find title by...\n[2] - Print all ranobe list" << endl;
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
	bool ex = false; int choice;
	system("cls");
	while (ex == false)
	{
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;
		cout << "[[0] - Go back\n[1] - Find title by...\n[2] - Print all ranobe list\n[3] - Add new novel" << endl;
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
			NewNovel(); break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}

}
void Novel::EditorMenu(int size, Novel arr[])
{
	bool ex = false; int choice;
	system("cls");
	while (ex == false)
	{
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;
		cout << "[[0] - Go back\n[1] - Find title by...\n[2] - Print all ranobe list" << endl;
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
	bool ex = false; int choice;
	while (ex == false)
	{
		cout << "[0] - Go back\n[1] - Chepters list" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Chepters list

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
		cout << "[0] - Go back\n[1] - Chepters list\n[2] - Delete novel\n[3] - Change novel info\n[4] - Add new chepter\n[5] - Redact chepter" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Chepters list

			break;
		case 2: // Delete novel

			ex = (check == false) ? (cout << "Ok! The changes will be visible after the next login to the program" << endl, true) : (cout << "Something went wrong! >:(" << endl, false);
			break;
		case 3: // Change novel info
			chapter = "NOVEL_INFO";
			RewriteInfo(arr[i]);

			break;
		case 4: // Add new chepter

			break;
		case 5: // Redact chepter

			cout << "Enter chepter name: "; cin >> chapter;

			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}
void Novel::WorkWithNovelEditor(int size, Novel* arr, int i)
{
	bool ex = false; int choice; string chapter;
	while (ex == false)
	{
		cout << "[0] - Go back\n[1] - Chepters list\n[2] - Add new chepter\n[3] - Redact chepter" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 0: // Go back
			ex = true;
			break;
		case 1: // Chepters list

			break;
		case 2: // Add new chepter

			break;
		case 3: // Redact chepter

			cout << "Enter chepter name: "; cin >> chapter;

			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}