#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include <conio.h>
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
    char WorkPlace[10000];
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
    void ReadData()
    {
        int i = 0;
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

        while (ReadFile(hFile, (char*)&p, sizeof(p), &readedBytes, NULL))
        {
            if (readedBytes != 0)
            {
                p.Print();
                i++;
            }
            else break;
        }
        
        CloseHandle(hFile);
    }

    void ReadPerson(int i)
    {
        HANDLE hFile = CreateFile(
            L"base.dat",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            cout << "Wait for access" << endl;
            _getch();
            system("cls");
            Start();
        }
        else
        {
            SetFilePointer(hFile, sizeof(Person) * (i - 1), 0, FILE_BEGIN);
            Person p;
            DWORD bytesWritten;
            ReadFile(hFile,
                (char*)&p,
                sizeof(Person),
                &bytesWritten,
                nullptr);
            p.Print();
            cout << "Enter 1 if you want to see or edit other data" << endl;
            int param;
            cin >> param;
            if (param == 1)
            {
                CloseHandle(hFile);
                system("cls");
                Start();
            }
        }
    }

    void EditPerson(int i)
    {
        HANDLE hFile = CreateFile(
            L"base.dat",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            cout << "Wait for access" << endl;
            _getch();
            system("cls");
            Start();
        }
        else
        {
            Person p;
            DWORD bytesWritten;
            ReadFile(hFile,
                (char*)&p,
                sizeof(Person),
                &bytesWritten,
                nullptr);

            p.Print();
            cout << "Введите номер поля, которое вы хотите изменить: " << endl;
            int parameter;
            cin >> parameter;
            SetFilePointer(hFile, sizeof(Person) * (i - 1), 0, FILE_BEGIN);
            system("cls");
            switch(parameter)
            {
                case 1:
                {
                    cout << "Введите новое имя: " << endl;
                    string name_p;
                    cin >> name_p;
                    p.SetName(name_p);
                    break;
                }
                case 2:
                {
                    cout << "Введите новое значение возраста: " << endl;
                    int age_p;
                    cin >> age_p;
                    p.SetAge(age_p);
                    break;
                }
                case 3:
                {
                    cout << "Введите новое место работы: " << endl;
                    string wp_p;
                    cin >> wp_p;
                    p.SetWorkPlace(wp_p);
                    break;
                }
                case 4:
                {
                    cout << "Введите новую дату рождения: " << endl;
                    string birth_p;
                    cin >> birth_p;
                    p.SetBirth(birth_p);
                    break;
                }
                case 5:
                {
                    cout << "Введите новое значение з/п: " << endl;
                    int sal_p;
                    cin >> sal_p;
                    p.SetSalary(sal_p);
                    break;
                }
            }
            SetFilePointer(hFile, sizeof(Person) * (i - 1), 0, FILE_BEGIN);
            WriteFile(
                hFile,
                (char*)&p,
                sizeof(Person),
                &bytesWritten,
                nullptr);
            cout << "Enter 1 if you want to see or edit other data; 0 if u would like to edit else" << endl;
            int param;
            cin >> param;
            if (param == 1)
            {
                CloseHandle(hFile);
                system("cls");
                Start();
            }
            else
            {
                CloseHandle(hFile);
                system("cls");
                EditPerson(parameter);
            }
        }
    }
    void Start()
    {
        setlocale(LC_ALL, "ru");
        Command c;
        c.CreateFileBase();
        c.ReadData();
        cout << "Введите 1, если хотите прочесть анкету; Введите 2, если хотите редактировать анкету; Введите 3, если хотите добавить анкету." << endl;
        int command;
        cin >> command;
        switch (command)
        {
        case 1:
            system("cls");
            int id;
            cout << "Введите номер анкеты, которую вы хотите просмотреть." << endl;
            cin >> id;
            c.ReadPerson(id);
            break;
        case 2:
            system("cls");
            int id1;
            cout << "Введите номер анкеты, которую вы хотите редактировать." << endl;
            cin >> id1;
            c.EditPerson(id1);
            break;
        case 3:
            system("cls");
            c.CreateNewPerson();
            system("cls");
            c.Start();
            break;
        }
    };
};

int main()
{
    setlocale(LC_ALL, "ru");
    Command c;
   // c.CreateNewPerson();
    c.Start();
}

