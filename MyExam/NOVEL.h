#pragma once
#include<iostream>
#include <fstream>
#include<string>
#include <Windows.h>
#include <Shellapi.h>

using namespace std;

struct Novel
{
	string title;
	string rating;
	string volumes;
	string chapters;
	string FullName;
	string ageRating;
	string status;
	int releasedYear;
	int ID;
	int genre[30] = {};
	string description;



	// OTHER
	bool ChapterNameCheck(string chapter, string title);

	// PRINTS
	void Print();
	void GenresPrint();
	void PrintAll(int size, Novel arr[]);
	void ChaptersPrint(string title);
	void PrintGenreByNumber(int givenGenre);
	void FullNovelPrint(int size, Novel arr[], int i);

	// WORK WITH NOVEL
	void NewChapter(Novel novel);
	bool DeleteNovel(Novel novel);
	void RewriteInfo(Novel& novel);
	bool NewNovel(Novel*& arr, int& size);
	void ReadChapter(Novel novel, string chapter);
	bool DeleteChepter(Novel novel, string chapter);
	void RedacrChapter(Novel novel, string chapter);

	// SEARCHES
	int NameSearch(int size, Novel arr[]);
	int GenreSearch(int size, Novel arr[]);
	int RatingSearch(int size, Novel arr[]);
	int VolumesSearch(int size, Novel arr[]);
	int ChaptersSearch(int size, Novel arr[]);
	int AgeRatingSearch(int size, Novel arr[]);
	void SearchNovelsByGenres(Novel* arr, int size, int* searchGenres, int searchSize);

	// MENU	
	void UserMenu(int size, Novel arr[]);
	void AdminMenu(int size, Novel arr[]);
	void EditorMenu(int size, Novel arr[]);

	// "FIND TITLE" MENU
	void FindTitleByUserMenu(int size, Novel arr[]);
	void FindTitleByAdminMenu(int size, Novel arr[]);
	void FindTitleByEditorMenu(int size, Novel arr[]);

	//  WORK WITH NOVEL
	void WorkWithNovelUser(int size, Novel* arr, int i);
	void WorkWithNovelAdmin(int size, Novel* arr, int i);
	void WorkWithNovelEditor(int size, Novel* arr, int i);
};