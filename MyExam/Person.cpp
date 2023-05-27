#include "Person.h";
#include <iostream>
#include<string>
#include <fstream>

using namespace std;

void Person::Fill(Person& WhoIAm, int size, Person arr[])
{
	Person temp; bool again; bool ex = false;
	while (ex == false)
	{
		again = false;
		cout << "Enter name: "; cin >> name;
		cout << "Enter email: "; cin >> temp.email;
		for (int i = 0; i < size; i++)
		{
			again = (arr[i].email == temp.email) ? (cout << "This email is already exist! Try entering another one!" << endl, true) : false;
		}
		if (again == false)
		{
			email = temp.email;
			cout << "Enter username: "; cin >> temp.username;
			for (int i = 0; i < size; i++)
			{
				again = (arr[i].username == temp.username) ? (cout << "This username is already exist! Try entering another one!" << endl, true) : false;
			}
		}
		if (again == false)
		{
			username = temp.username;
			cout << "Enter password: "; cin >> password; ex = true;
		}
		if (WhoIAm.accessLevel == 3)
		{
			ex = false;
			cout << "Enter access level: "; cin >> temp.accessLevel;
			ex = (accessLevel == 1 || accessLevel == 2 || accessLevel == 3) ? true : (cout << "Wrong access level! Enter something between 1 and 3!" << endl, false);
		}
	}
}

void Person::Print()
{
	cout << "Name: " << name << "\nEmail: " << email << "\nAccess level: " << accessLevel
		<< "\nUsername: " << username << "\nPassword: " << password << "\nID: " << ID << endl;
}

int Person::Check(int size, Person arr[])
{
	Person temp;
	cout << "Enter worker`s ID: "; cin >> temp.ID;

	for (int i = 0; i < size; i++) // Search
	{
		if (temp.ID == arr[i].ID)
		{
			system("cls");
			char choice1 = '\n';
			cout << "___---___---___---___---___---___---___" << endl;
			cout << "Worker found:" << endl; arr[i].Print();
			cout << "___---___---___---___---___---___---___" << endl;
			cout << "\nIs this that user?\n[Y]/[N]\nYour choice: "; cin >> choice1;
			if (choice1 == 'Y' || choice1 == 'y')
			{
				return i;
			}
			else
			{
				cout << "Ok..." << endl;
			}
		}
	}
	cout << "User not found. Try again later!" << endl;
	return -1;
}

void Person::Rewrite(int size, Person arr[], Person& WhoIAm, int WhatToDo)
{
	char ch; int option; bool ex = false; bool check = false; string newUsername; bool ext;
	if (WhatToDo == 0)
	{
		int choice = Check(size, arr);
		if (choice != 0)
		{
			while (ex == false)
			{
				cout << "___---___---___---___---___---___---___" << endl;
				cout << "What do you want to change?\n[0] - Go back\n[1] - Name\n[2] - Email\n[3] - Username\n[4] - Password\n" << endl;
				cout << "Your choice  (/`^_^)/'  "; cin >> option;
				cout << "___---___---___---___---___---___---___" << endl;

				switch (option)
				{
				case 0: ex = true; break;
				case 1: // name
					cout << "Enter new name: "; cin >> arr[choice].name;
					cout << "___---___---___---___---___---___---___" << endl;
					ex = true;
					break;
				case 2: // email
					cout << "Enter new email: "; cin >> arr[choice].email;
					cout << "___---___---___---___---___---___---___" << endl;
					ex = true;
					break;
				case 3: // username
					while (ext = false)
					{
						cout << "Enter new username (or [0] to exit): "; cin >> newUsername;
						for (int i = 0; i < size; i++)
						{
							if (arr[i].username == newUsername)
							{
								cout << "This username is alredy exist" << endl;
								check = false;
							}
							else if (newUsername == "0")
							{
								ext = true;
							}
						}
						if (check == true)
						{
							arr[choice].username == newUsername;
						}
						cout << "___---___---___---___---___---___---___" << endl;
						ex = true;
					}
					break;
				case 4: // password
					cout << "Enter new password: "; cin >> arr[choice].password;
					cout << "___---___---___---___---___---___---___" << endl;
					ex = true;
					break;
				default:
					cout << "You entered a wrong number! ._(°w°)_." << endl;
					break;
				}
			}
		}
	}
	else if (WhatToDo == 1)
	{
		cout << "___---___---___---___---___---___---___" << endl;
		cout << "What do you want to change?\n[0] - Go back\n[1] - Name\n[2] - Email\n[3] - Username\n[4] - Password\n" << endl;
		cout << "Your choice  (/`^_^)/'  "; cin >> option;
		cout << "___---___---___---___---___---___---___" << endl;

		int iterator = 0;
		for (int i = 0; i < size; i++)
		{
			if (WhoIAm.ID == arr[i].ID)
			{
				iterator = i;
			}
		}
		switch (option)
		{
		case 0: ex = true; break;
		case 1: // name
			cout << "Enter new name: "; cin >> arr[iterator].name;
			cout << "___---___---___---___---___---___---___" << endl;
			ex = true; system("pause"); system("cls");
			break;
		case 2: // email
			cout << "Enter new email: "; cin >> arr[iterator].email;
			cout << "___---___---___---___---___---___---___" << endl;
			ex = true; system("pause"); system("cls");
			break;
		case 3: // username
			cout << "Enter new username: "; cin >> arr[iterator].username;
			cout << "___---___---___---___---___---___---___" << endl;
			ex = true; system("pause"); system("cls");
			break;
		case 4: // password
			cout << "Enter new password: "; cin >> arr[iterator].password;
			cout << "___---___---___---___---___---___---___" << endl;
			ex = true; system("pause"); system("cls");
			break;
		default:
			cout << "You entered a wrong number! ._(°w°)_." << endl; system("pause"); system("cls");
			break;
		}
		WhoIAm = arr[iterator];
	}
}

void Person::AddPerson(int& size, Person*& arr, Person& WhoIAm)
{
	Person* temparr = new Person[size + 1];

	for (int i = 0; i < size; i++)
	{
		temparr[i] = arr[i];
	}

	temparr[size].Fill(WhoIAm, size, arr);
	temparr[size].ID = size;

	for (int i = 0; i < size; i++)
	{
		if (arr[i].ID == temparr[size].ID)
		{
			temparr[size].ID++;
		}
	}

	delete[] arr;
	arr = temparr;
	size++;
}

void Person::Register(int& size, Person*& arr, Person& WhoIAm)
{
	Person* temparr = new Person[size + 1];

	for (int i = 0; i < size; i++)
	{
		temparr[i] = arr[i];
	}


	temparr[size].Fill(WhoIAm, size, arr);
	temparr[size].ID = size;

	for (int i = 0; i < size; i++)
	{
		if (arr[i].ID == temparr[size].ID)
		{
			temparr[size].ID++;
		}
	}

	WhoIAm = temparr[size];
	delete[] arr;
	arr = temparr;
	size++;
}

int Person::ProfileMenuAdmin(int size, Person arr[], Person& WhoIAm)
{
	bool ex = false;
	while (ex == false)
	{
		int choice; Person temp;
		system("cls");
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
		WhoIAm.Print();
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;

		cout << "[1] - Change profile\n[2] - Find user\n[3] - Go back" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 1: // Change the profile
			WhoIAm.Rewrite(size, arr, WhoIAm, 1);
			break;
		case 2: // Find user
			int ch; system("cls");
			cout << "[1] - Show the whole list\n[2] - Find a user\n[3] - Find an editor\n[4] - Find an administrator\n[5] - Go back" << endl;
			cout << " (o_O)? "; cin >> ch;
			switch (ch)
			{
			case 1: // Show the whole list
				temp.PrintAll(size, arr);
				break;
			case 2: // Find a user
				temp.FindUser(size, arr);
				break;
			case 3: // Find an editor
				temp.FindEditor(size, arr);
				break;
			case 4: // Find an administrator
				temp.FindAdmin(size, arr);
				break;
			case 5: // Go back
				system("cls"); ex = true;
				break;
			default:
				cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
				break;
			}
			break;
		case 3: // Go back
			system("cls"); return 1;
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}
int Person::ProfileMenuUser(int size, Person arr[], Person& WhoIAm)
{
	bool ex = false;
	while (ex == false)
	{
		int choice; system("cls");
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
		WhoIAm.Print();
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl << endl;

		cout << "[1] - Change the profile\n[2] - Go back" << endl;
		cout << " (o_O)? "; cin >> choice;

		switch (choice)
		{
		case 1: // Change the profile
			WhoIAm.Rewrite(size, arr, WhoIAm, 1);
			break;
		case 2: // Go back
			system("cls"); return 1;
			break;
		default:
			cout << "Wrong choice. Maybe you should try again?" << endl; system("pause");
			break;
		}
	}
}

int Person::FindUser(int size, Person arr[])
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].accessLevel == 1)
		{
			arr[i].Print();
		}
	}
	cout << "[0] - Exit\n[1] - Select a user\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter user's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}
int Person::FindEditor(int size, Person arr[])
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].accessLevel == 2)
		{
			arr[i].Print();
		}
	}
	cout << "[0] - Exit\n[1] - Select a user\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter user's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}
int Person::FindAdmin(int size, Person arr[])
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].accessLevel == 3)
		{
			arr[i].Print();
		}
	}
	cout << "[0] - Exit\n[1] - Select a user\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter user's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}

int Person::PrintAll(int size, Person arr[])
{
	cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
	for (int i = 0; i < size; i++)
	{
		arr[i].Print();
		cout << "__--__--__--__--__--__--__--__--__--__--__--__" << endl;
	}
	cout << "[0] - Exit\n[1] - Select a user\n"; int choice; cout << " (o_O)? "; cin >> choice;
	if (choice == 1)
	{
		cout << "Eneter user's ID: "; cin >> choice;
		return choice;
	}
	else
	{
		return -1;
	}
}