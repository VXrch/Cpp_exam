#pragma once
#include<iostream>
#include <string>
#include <fstream>

using namespace std;

struct Person
{
	string name = " ";
	string email = " ";
	string username = " ";
	string password = " ";
	int ID;
	int accessLevel = 1;

	void Fill(Person& WhoIAm, int size, Person arr[]);
	void Print();
	int PrintAll(int size, Person arr[]);
	int Check(int size, Person arr[]);

	void Rewrite(int size, Person arr[], Person& WhoIAm, int WhatToDo = 0);
	void AddPerson(int& size, Person*& arr, Person& WhoIAm);
	void Register(int& size, Person*& arr, Person& WhoIAm);

	int ProfileMenuAdmin(int size, Person arr[], Person& WhoIAm);
	int ProfileMenuUser(int size, Person arr[], Person& WhoIAm);

	int FindUser(int size, Person arr[]);
	int FindEditor(int size, Person arr[]);
	int FindAdmin(int size, Person arr[]);
};