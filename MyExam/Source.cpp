#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <Shellapi.h>
#include"PERSON.h";
#include"NOVEL.h";

//#define MyDebug

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainMenu();
Novel* FindNovels(int& size);
int LogInMenu(int size, Person arr[]);
void WriteNovelToFile(Novel novel, int size);
void SmoothPhrase(const string& phrase, int delay);
void TheRightSize(const string& directory, int& size);
Person* ReadFromFile(const string& filename, int& size);
void WriteToFile(const string& filename, Person* arr, int size);
void ReadNovelInfoFromFile(const string& filePath, Novel& novel);
void RecursiveFindNovels(const string& directory, Novel* novels, int& size);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string filename = "ALLUSERS.txt"; const string directory = "RanobeLib";
string phrase; int delay = 60; // Smooth phrase options 
Person WhoIAm; int choice; bool ex;
Person tempPerson; Novel tempNovel; // TEMPS
Person* usersArray = nullptr; int usersSize = 0; // Users array
Novel* novelsArray = nullptr; int novelSize = 0; // Novels array


////////////////////////////////////////////////////////////////////////////////////////////////////////////
void START()
{
    usersArray = ReadFromFile(filename, usersSize); // Reading data from a file into an array
    
    for (int i = 0; i < novelSize; i++)
    {
        TheRightSize(directory, novelSize);
    }
    novelsArray = FindNovels(novelSize);

    ex = false;
    while (ex == false) // log in
    {
        ex = LogInMenu(usersSize, usersArray);
    }
}

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

// NOVEL FILES
void WriteNovelToFile(Novel novel, int size)
{
    string filePath = "RanobeLib\\" + novel.title + "\\NOVEL_INFO.txt";
    ofstream file(filePath);
    if (file.is_open()) 
    {
        for (int i = 0; i < size; i++)
        {
            file << novel.title << endl;
            file << novel.rating << endl;
            file << novel.volumes << endl;
            file << novel.chapters << endl;
            file << novel.FullName << endl;
            file << novel.ageRating << endl;
            file << novel.status << endl;
            file << novel.releasedYear << endl;
            file << novel.ID << endl;
            file << novel.author << endl;
            for (int j = 0; j < 30; j++)
            {
                file << novel.genre[j] << " ";
            }
            file << endl;
            file << novel.description << endl;
        }
        file.close();
    }
    else 
    {
        cout << "Failed to open the file." << endl;
    }
}
Novel* FindNovels(int& size)
{
    const string rootDirectory = "RanobeLib";
    Novel* novels = new Novel[size];

    RecursiveFindNovels(rootDirectory, novels, size);

    return novels;
}
void RecursiveFindNovels(const string& directory, Novel* novels, int& size)
{
    WIN32_FIND_DATAA findData;
    const string searchPath = directory + "\\*";
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Failed to find files in directory: " << directory << endl;
        return;
    }

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            string subDirectory = findData.cFileName;
            if (subDirectory != "." && subDirectory != "..")
            {
                string subDirectoryPath = directory + "\\" + subDirectory;
                RecursiveFindNovels(subDirectoryPath, novels, size);
            }
        }
        else
        {
            string fileName = findData.cFileName;
            if (fileName == "NOVEL_INFO.txt")
            {
                string filePath = directory + "\\" + fileName;
                ReadNovelInfoFromFile(filePath, novels[size]);
                size++;
            }
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);
}
void ReadNovelInfoFromFile(const string& filePath, Novel& novel)
{
    ifstream file(filePath);
    if (file.is_open())
    {
        getline(file, novel.title);
        getline(file, novel.rating);
        getline(file, novel.volumes);
        getline(file, novel.chapters);
        getline(file, novel.FullName);
        getline(file, novel.ageRating);
        getline(file, novel.status);
        file >> novel.releasedYear;
        file >> novel.ID;
        file.ignore();

        for (int i = 0; i < 30; i++)
        {
            file >> novel.genre[i];
        }

        file.ignore();
        getline(file, novel.description);

        file.close();
    }
    else
    {
        cout << "I can't open this file!" << endl;
    }
}
void TheRightSize(const string& directory, int& size)
{
    WIN32_FIND_DATAA fileData;
    string searchPath = directory + "\\*.*";
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &fileData);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                string subDirectory = fileData.cFileName;
                if (subDirectory != "." && subDirectory != "..")
                {
                    string subDirectoryPath = directory + "\\" + subDirectory;
                    TheRightSize(subDirectoryPath, size);
                }
            }
            else
            {
                string fileName = fileData.cFileName;
                if (fileName == "NOVEL_INFO.txt")
                {
                    size++;
                }
            }
        } while (FindNextFileA(hFind, &fileData) != 0);

        FindClose(hFind);
    }
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