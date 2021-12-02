#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int make_account()
{
    ofstream login_data;
    string store;
    login_data.open("login_data.txt", ios::app);
    if (!login_data.is_open())
    {
        return 1;
    }

    cout << "Email" << endl;
    cin >> store;
    login_data << store << endl;

    cout << "Username" << endl;
    cin >> store;
    login_data << store << endl;

    cout << "Password\n";
    cin >> store;

    login_data << store << endl;

    login_data.close();
    return 0;
}

void login(string input_filename)
{

    bool found = false;
    ifstream fileInput;
    string line, pass, user;
    cin.clear();
    cout << "Username: ";
    cin >> user;

    cout << "Enter Password: ";
    cin >> pass;

    fileInput.open("login_data.txt");
    if (fileInput.is_open())
    {
        while (!fileInput.eof())
        {
            getline(fileInput, line);

            if (line == user)
            {
                getline(fileInput, line);
                if (line == pass)
                {
                    cout << "Welcome " << user << endl;
                    found = true;
                }
            }

        }
    }

    else
    {
        cout << "Unable to open file.";
    }
    if (found != true)
    {
        cout << "User not found. Please make sure you used the correct Username/Password.\n";
    }

    fileInput.close();
}

int main()
{
    int num;

    cout << "For making account, Press 1" << endl
         << "For login, Press 2" << endl;
    cin >> num;
    if (num == 1)
    {
        int check = make_account();
        if (check == 0)
        {
            cout << "You are registered" << endl;
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    if (num == 2)
    {

        login("login_data.txt");
    }
}
