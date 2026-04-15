#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

/*------------------- PHONEBOOK CLASS -------------------*/
class PhoneBook
{
public:
    string name;
    long long number; 
    string email;

    void input()
    {
        cout << "Enter Name: ";
        cin >> name;

string num;
do
{
    cout << "Enter 10-digit Number: ";
    cin >> num;

    if (num.length() != 10)
    {
        cout << "Invalid! Number must be exactly 10 digits.\n";
    }
    else
    {
        bool valid = true;
        for (char c : num)
        {
            if (!isdigit(c))
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            cout << "Invalid! Only digits allowed.\n";
            num = "";
        }
    }

} while (num.length() != 10);

number = stoll(num);   
        do
        {
            cout << "Enter Email: ";
            cin >> email;

            if (email.find('@') == string::npos)
            {
                cout << "Invalid! Email must contain '@'.\n";
            }

        } while (email.find('@') == string::npos);
    }

    void display()
    {
        cout << "\n--------- Contact Details ---------\n";
        cout << "Name   : " << name << endl;
        cout << "Number : " << number << endl;
        cout << "Email  : " << email << endl;
    }
};

/*------------------- MANAGEMENT CLASS -------------------*/
class ManagePhoneBook
{
private:
    PhoneBook p[100];
    int n = 0;

public:
    void loadFromFile()
    {
        ifstream file("contact_records.txt");
        n = 0;

        while (file >> p[n].number >> p[n].name >> p[n].email)
        {
            n++;
        }
        file.close();
    }

    void appendToFile(PhoneBook pb)
    {
        ofstream file("contact_records.txt", ios::app);
        file << pb.number << " " << pb.name << " " << pb.email << endl;
        file.close();
    }

    void saveAllToFile()
    {
        ofstream file("contact_records.txt");

        for (int i = 0; i < n; i++)
        {
            file << p[i].number << " "
                 << p[i].name << " "
                 << p[i].email << endl;
        }
        file.close();
    }

    void insertContact()
    {
        int count;
        cout << "\nEnter number of contacts to add: ";
        cin >> count;

        for (int i = 0; i < count; i++)
        {
            cout << "\nEnter details " << n + 1 << ":\n";

            PhoneBook temp;
            temp.input();

            p[n] = temp;
            appendToFile(p[n]);
            n++;

            cout << "\nContact added successfully!\n";
        }
    }

    void displayAll()
    {
        if (n == 0)
        {
            cout << "\nNo contacts available!\n";
            return;
        }

        for (int i = 0; i < n; i++)
        {
            p[i].display();
        }
    }

    void searchByName()
    {
        string searchName;
        cout << "\nEnter Name to Search: ";
        cin >> searchName;

        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (p[i].name == searchName)
            {
                cout << "\nContact Found:\n";
                p[i].display();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nContact Not Found!\n";
    }

    void updateContact()
    {
        string name;
        cout << "\nEnter Contact Name to update: ";
        cin >> name;

        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (p[i].name == name)
            {
                cout << "\nEnter New Details:\n";
                p[i].input();

                found = true;
                cout << "\nContact Updated Successfully!\n";
                break;
            }
        }

        if (!found)
            cout << "\nContact Not Found!\n";

        saveAllToFile();
    }

    void deleteContact()
    {
        string name;
        cout << "\nEnter Contact Name to delete: ";
        cin >> name;

        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (p[i].name == name)
            {
                for (int j = i; j < n - 1; j++)
                {
                    p[j] = p[j + 1];
                }

                n--;
                found = true;

                cout << "\nContact Deleted Successfully!\n";
                break;
            }
        }

        if (!found)
            cout << "\nContact Not Found!\n";

        saveAllToFile();
    }

    void menu()
    {
        loadFromFile();
        int choice;

        do
        {
            cout << "\n------ PHONEBOOK MANAGEMENT SYSTEM ------";
            cout << "\n1. Insert Contact";
            cout << "\n2. Display All Contacts";
            cout << "\n3. Search Contact by Name";
            cout << "\n4. Update Contact";
            cout << "\n5. Delete Contact";
            cout << "\n6. Exit";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1: insertContact(); break;
                case 2: displayAll(); break;
                case 3: searchByName(); break;
                case 4: updateContact(); break;
                case 5: deleteContact(); break;
                case 6:
                    cout << "\nExiting program...\n";
                    saveAllToFile();
                    break;
                default:
                    cout << "\nInvalid Choice! Try again.\n";
            }

        } while (choice != 6);
    }
};

/*------------------- MAIN FUNCTION -------------------*/
int main()
{
    ManagePhoneBook obj;
    obj.menu();
    return 0;
}