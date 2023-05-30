#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <Shellapi.h>
#include"PERSON.h"
#include"NOVEL.h"

//#define MyDebug

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string filename1 = "ALLUSERS.txt"; const string filename2 = "NOVELS_INFO.txt";
string phrase; int delay = 60; // Smooth phrase options 
Person WhoIAm; int choice; bool ex;
Person tempPerson; Novel tempNovel; // TEMPS
int usersSize = 0; Person* usersArray = new Person[usersSize]; // Users array
int novelSize = 0; Novel* novelsArray = new Novel[novelSize]; // Novels array

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void START();
void MainMenu();
bool LogInMenu(int size, Person arr[]);
void WriteNovelsToFile(Novel*& novels, int& size);
void SmoothPhrase(const string& phrase, int delay);
Person* ReadFromFile(const string& filename, int& size);
Novel* ReadNovelsFromFile(const string& filename, int& size);
void WriteToFile(const string& filename, Person* arr, int size);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
    START();
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

    WriteToFile(filename1, usersArray, usersSize);
    WriteNovelsToFile(novelsArray, novelSize);
    delete[] usersArray; delete[] novelsArray;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void START()
{
    usersArray = ReadFromFile(filename1, usersSize); // Reading data from a file into an array
    novelsArray = ReadNovelsFromFile(filename2, novelSize); // Reading data from a file into an array

    ex = false;
    while (ex == false) // log in
    {
        ex = LogInMenu(usersSize, usersArray);
    }
}

void MainMenu()
{
    system("cls");
    cout << " [Profile] | [Ranobes] | [Exit]\n   [1]     |    [2]    |  [0]\n\n (o_o)? ";
    cin >> choice;
}
bool LogInMenu(int size, Person arr[])
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
                return true;
            }
        }
        cout << endl << "\t"; phrase = " Wrong login or password! Please try again!"; SmoothPhrase(phrase, delay);
    }
    else if (loginto == 'R' || loginto == 'r') // Register on account
    {
        tempPerson.Register(usersSize, usersArray, WhoIAm);
        return true;
    }
    return false;
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

// NOVEL FILES
void WriteNovelsToFile(Novel*& novels, int& size)
{
    ofstream outputFile("NOVELS_INFO.txt");
    if (outputFile.is_open())
    {
        for (int i = 0; i < size; ++i)
        {
            outputFile << novels[i].title << endl;
            outputFile << novels[i].author << endl;
            outputFile << novels[i].rating << endl;
            outputFile << novels[i].volumes << endl;
            outputFile << novels[i].chapters << endl;
            outputFile << novels[i].FullName << endl;
            outputFile << novels[i].ageRating << endl;
            outputFile << novels[i].status << endl;
            outputFile << novels[i].language << endl;
            outputFile << novels[i].releasedYear << endl;
            outputFile << novels[i].ID << endl;
            for (int j = 0; j < 10; ++j)
            {
                outputFile << novels[i].genre[j] << endl;
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Successfull!" << endl;
    }
    else
    {
        cout << "NOPE" << endl;
    }
}
Novel* ReadNovelsFromFile(const string& filename, int& size)
{
    Novel* data = nullptr;
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

    size /= 21;

    file.clear();
    file.seekg(0, ios::beg);

    data = new Novel[size];

    for (int i = 0; i < size; i++)
    {
        getline(file, data[i].title);
        getline(file, data[i].author);
        getline(file, data[i].rating);
        getline(file, data[i].volumes);
        getline(file, data[i].chapters);
        getline(file, data[i].FullName);
        getline(file, data[i].ageRating);
        getline(file, data[i].status);
        getline(file, data[i].language);
        file >> data[i].releasedYear;
        file >> data[i].ID;
        file.ignore();

        for (int j = 0; j < 10; j++)
        {
            file >> data[i].genre[j];
        }
        file.ignore();
    }

#ifdef MyDebug
    for (int i = 0; i < size; i++)
    {
        cout << " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
        cout << "title ~ " << data[i].title << endl;
        cout << "author ~ " << data[i].author << endl;
        cout << "rating ~ " << data[i].rating << endl;
        cout << "volumes ~ " << data[i].volumes << endl;
        cout << "chapters ~ " << data[i].chapters << endl;
        cout << "FullName ~ " << data[i].FullName << endl;
        cout << "ageRating ~ " << data[i].ageRating << endl;
        cout << "status ~ " << data[i].status << endl;
        cout << "language ~ " << data[i].language << endl;
        cout << "releasedYear ~ " << data[i].releasedYear << endl;
        cout << "ID ~ " << data[i].ID << endl;
        cout << "genre ~ ";
        for (int j = 0; j < 10; j++)
        {
            cout << data[i].genre[j] << " ";
        }
        cout << endl;
    }

    system("pause");
#endif // MyDebug

    file.close();
    return data;
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
    system("pause"); system("cls");
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
    system("pause"); system("cls");
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////