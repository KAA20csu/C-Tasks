#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
using namespace std;
using std::string;
using std::cin;
using std::cout;

const char* fname1 = "test1.txt";
class Person
{
public:

    char Name[50];
    int Age;
    char WorkPlace[100];
    char DateOfBirth[16];
    double Salary;
    void Print()
    {
        cout << "Имя: " << Name << endl;
        cout << "Возраст: " << Age << endl;
        cout << "Место работы: " << WorkPlace << endl;
        cout << "Дата рождения: " << DateOfBirth << endl;
        cout << "Зарплата: " << Salary << endl;
        cout << "\n" << endl;
    }
    void SetName(string name)
    {
        strcpy(this->Name, name.c_str());
    };
    void SetAge(int age)
    {
        this->Age = age;
    };
    void SetWorkPlace(string wp)
    {
        strcpy(this->WorkPlace, wp.c_str());
    };
    void SetBirth(string birth)
    {
        strcpy(this->DateOfBirth, birth.c_str());
    };
    void SetSalary(double sal)
    {
        this->Salary = sal;
    };

};

class Command
{
public:
    void CreateFileBase()
    {
        
       HANDLE hFile = CreateFile(
            L"base.dat",
            GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

       CloseHandle(hFile);
    }
    void CreateNewPerson()
    {
        HANDLE hFile = CreateFile(
            L"base.dat",
            GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);


        Person newPerson;

        cout << "Введите имя: ";
        string name;
        cin >> name;
        cout << "Введите возраст: ";
        int age;
        cin >> age;
        cout << "Введите место работы: ";
        string wp;
        cin >> wp;
        cout << "Введите дату рождения в формате dd/mm/yyyy: ";
        string birth;
        cin >> birth;
        cout << "Введите зарплату: ";
        double sal;
        cin >> sal;

        newPerson.SetName(name);
        newPerson.SetAge(age);
        newPerson.SetWorkPlace(wp);
        newPerson.SetBirth(birth);
        newPerson.SetSalary(sal);
        SetFilePointer(hFile, 0, NULL, FILE_END);
        DWORD bytesWritten;
        WriteFile(
            hFile,
            (char*)&newPerson,
            sizeof(Person),
            &bytesWritten,
            nullptr);
        CloseHandle(hFile);
        
    };
    void ReadPerson()
    {
        Person p;
        HANDLE hFile = CreateFile(
            L"base.dat",
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL, 
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,  
            NULL);
        DWORD readedBytes;

        if (ReadFile(
            hFile,
            (char*)&p,
            sizeof(p), 
            &readedBytes,
            NULL
        )) {
            p.Print();
        }
        CloseHandle(hFile);
    }
};
int main()
{
    setlocale(LC_ALL, "ru");
    Command c;
    c.CreateFileBase();
    //c.CreateNewPerson();
    c.ReadPerson();
}

