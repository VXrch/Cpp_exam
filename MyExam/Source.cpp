#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <Shellapi.h>
#include"PERSON.h";
#include"NOVEL.h";

#define MyDebug

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string filename = "ALLUSERS.txt";
string phrase; int delay = 60; // Smooth phrase options 
Person WhoIAm; int choice; bool ex;
Person tempPerson; Novel tempNovel; // TEMPS
Person* usersArray = nullptr; int usersSize = 0; // Users array
Novel* novelsArray = nullptr; int novelSize = 0; // Novels array

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WriteToFile(const string& filename, Person* arr, int size);
Person* ReadFromFile(const string& filename, int& size);
void SmoothPhrase(const string& phrase, int delay);
int LogInMenu(int size, Person arr[]);
void MainMenu();

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
    usersArray = ReadFromFile(filename, usersSize); // Reading data from a file into an array
    ex = false;
    while (ex == false) // log in
    {
        ex = LogInMenu(usersSize, usersArray);
    }
    ex = false;
    while (ex == false) // Menu
    {
        MainMenu();
        if (WhoIAm.accessLevel == 1) // USER  ////////////////////////////////////////////////////////////////
        {
            if (choice == 1)  // Profile
            {
                tempPerson.ProfileMenuUser(usersSize, usersArray, WhoIAm);
            }
            else if (choice == 2) // Ranobaes
            {
                tempNovel.UserMenu(novelSize, novelsArray);
            }
            else if (choice == 0)
            {
                system("cls");
                cout << "Bye-bye!" << endl; ex = true;
            }
            else
            {
                cout << "Wrong choice. Maybe you should try again." << endl;
            }
        }
        else if (WhoIAm.accessLevel == 2) // EDITOR ////////////////////////////////////////////////////////////////
        {
            if (choice == 1) // Profile
            {
                tempPerson.ProfileMenuUser(usersSize, usersArray, WhoIAm);
            }
            else if (choice == 2)// Ranobaes
            {
                tempNovel.EditorMenu(novelSize, novelsArray);
            }
            else if (choice == 0)
            {
                system("cls");
                cout << "Bye-bye!" << endl; ex = true;
            }
            else
            {
                cout << "Wrong choice. Maybe you should try again." << endl;
            }
        }
        else if (WhoIAm.accessLevel == 3) // ADMIN ////////////////////////////////////////////////////////////////
        {
            if (choice == 1) // Profile
            {
                tempPerson.ProfileMenuAdmin(usersSize, usersArray, WhoIAm);
            }
            else if (choice == 2) // Ranobaes
            {
                tempNovel.AdminMenu(novelSize, novelsArray);
            }
            else if (choice == 0)
            {
                system("cls");
                cout << "Bye-bye!" << endl; ex = true;
            }
            else
            {
                cout << "Wrong choice. Maybe you should try again." << endl;
            }
        }
    }

    WriteToFile(filename, usersArray, usersSize);
    delete[] usersArray; delete[] novelsArray;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainMenu()
{
    system("cls");
    cout << " [Profile] | [Ranobes] | [Exit]\n   [1]     |    [2]    |  [0]\n\n (o_o)? ";
    cin >> choice;
}
int LogInMenu(int size, Person arr[])
{
    char loginto; system("cls");
    cout << " Log in [L] || [R] Register" << endl; cin >> loginto;

    if (loginto == 'L' || loginto == 'l') // Login to account
    {
        Person temp; system("cls");
        cout << " Enter your username: "; cin >> temp.username;
        cout << " Enter password: "; cin >> temp.password;
        for (int i = 0; i < size; i++)
        {
            if (arr[i].username == temp.username && arr[i].password == temp.password)
            {
                system("cls");
                cout << endl << "\t"; phrase = " Login successful!"; SmoothPhrase(phrase, delay);
                system("cls");

                WhoIAm = arr[i];
                return 1;
            }
        }
        cout << endl << "\t"; phrase = " Wrong login or password! Please try again!"; SmoothPhrase(phrase, delay);
    }
    else if (loginto == 'R' || loginto == 'r') // Register on account
    {
        usersArray[0].Register(usersSize, usersArray, WhoIAm);
        return 1;
    }
    return 0;
}
void SmoothPhrase(const string& phrase, int delay)
{
    int length = phrase.length();
    for (int i = 0; i <= length; i++) {
        string substring = phrase.substr(0, i);
        cout << substring << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
        cout << "\r";
    }
    this_thread::sleep_for(chrono::milliseconds(1100));
}


// PERSON FILES
Person* ReadFromFile(const string& filename, int& size)
{
    Person* data = nullptr;
    ifstream file(filename);
    if (!file)
    {
        cout << "Something went wrong >:(" << endl;
        return data;
    }

    string line;
    while (getline(file, line))
    {
        size++;
    }

    size /= 6;

    file.clear();
    file.seekg(0, ios::beg);

    data = new Person[size];

    for (int i = 0; i < size; i++)
    {
        getline(file, data[i].name);
        getline(file, data[i].email);
        getline(file, data[i].username);
        getline(file, data[i].password);
        file >> data[i].ID;
        file >> data[i].accessLevel;
        file.ignore();
    }

//////////////////////////////////////////////
#ifdef MyDebug
    for (int i = 0; i < size; i++)
    {
        cout << " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
        cout << "name ~ " << data[i].name << endl;
        cout << "email ~ " << data[i].email << endl;
        cout << "username ~ " << data[i].username << endl;
        cout << "password ~ " << data[i].password << endl;
        cout << "ID ~ " << data[i].ID << endl;
        cout << "accessLevel ~ " << data[i].accessLevel << endl;
    }
//////////////////////////////////////////////

    system("pause");
#endif // MyDebug

    file.close(); return data;
}
void WriteToFile(const string& filename, Person* arr, int size)
{
    ofstream file(filename, ios::trunc);
    if (!file)
    {
        cout << "Something went wrong >:(" << endl;
        return;
    }
    for (int i = 0; i < size; i++)
    {
        file << arr[i].name << endl;
        file << arr[i].email << endl;
        file << arr[i].username << endl;
        file << arr[i].password << endl;
        file << arr[i].ID << endl;
        file << arr[i].accessLevel << endl;
    }
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////