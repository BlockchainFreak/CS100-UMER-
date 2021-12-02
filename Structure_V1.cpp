#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

using namespace std;

struct user
{
    string username, email, password;
    double coins[10];
};
struct transfer
{
    string sender, reciever;
    int ID;
    double amount;
};
struct conversion
{
    string user_ID;
    int old_coin, new_coin;
    double old_amount, new_amount;
};
class CoinClass
{
private:
    string abbrev_coin, name_coin;

public:
    double exchange_rate() const;
    void remove_coin(string s, int coin_ID);
    void set(string name, string abbrev)
    {
        name_coin = name;
        abbrev_coin = abbrev;
    }
    string get_abbrev()
    {
        return abbrev_coin;
    }
    string get_name()
    {
        return name_coin;
    }

} coin;
string FM(int n, string s)
{
    string str = "";
   for (int i =0; i<n ; i++ )
   {
       str += s;
   }
   return str;
}
void add_coin(int coin_ID)
{
    switch (coin_ID)
    {
    case 1:
        coin.set("Bitcoin", "BTC");
        break;
    case 2:
        coin.set("Ethereum", "ETH");
        break;
    case 3:
        coin.set("Dogecoin", "DOGE");
        break;
    case 4:
        coin.set("Polkadot", "DOT");
        break;
    case 5:
        coin.set("Solana", "SOL");
        break;
    case 6:
        coin.set("Chainlink", "LINK");
        break;
    case 7:
        coin.set("Thorchain", "RUNE");
        break;
    case 8:
        coin.set("Uniswap", "UNI");
        break;
    case 9:
        coin.set("Litecoin", "LTC");
        break;
    case 10:
        coin.set("Tether", "USDT");
        break;
    default:
        coin.set("**ERROR**", "ERROR!");
        break;
    }
}
void add_transfer(vector <transfer> &v,string Sender, string Reciever, int coin_ID, double Amount)
{
    transfer slot;
    slot.sender = Sender;
    slot.reciever = Reciever;
    slot.ID = coin_ID;
    slot.amount = Amount;
    v.push_back(slot);
}
void add_conversion(vector <conversion> &v,string current_user, int OLD_COIN, int NEW_COIN, double OLD_A , double NEW_A)
{
    conversion log;
    log.user_ID = current_user;
    log.old_coin = OLD_COIN;
    log.new_coin = NEW_COIN;
    log.old_amount = OLD_A;
    log.new_amount = NEW_A;
    v.push_back(log);
}
void add_data(vector<user> &v)
{
    user cred;
    cout << " \nEnter your username: ";
    cin.ignore();
    getline(cin, cred.username);
    cout << " \nEnter your email: ";
    getline(cin, cred.email);
    cout << " \nEnter your password: ";
    getline(cin, cred.password);
    cout<<endl;
    double deposit_amount;
    cout << " \nEnter your depositing amount: ";
    cin >> deposit_amount;
    while(cin.fail() || deposit_amount <= 0)
    {
        cin.clear();
        cin.ignore();
        cout << "\nEnter appropriate deposit amount: ";
        cin >> deposit_amount;
    }
// Initialize balance for the user.
    for (int i =0; i<9 ; i++ )
    {
        cred.coins[i] = 0;
    }
    cred.coins[9]=deposit_amount;

    v.push_back(cred);
    return;
}
void coin_index()
{
    cout << "------- COIN ID INDEX --------\n";
    cout << setw(18) << left << "COIN NAME" << "|COIN ID|\n";
    cout << FM(18," ") << "|\t  |\n";
    for (int i =1; i<=10 ; i++ )
    {
        add_coin(i);
        cout << setw(12) << left << coin.get_name()
             << setw(6)  << left << coin.get_abbrev()
             << "|   " << setw(2) << i << "  |" << endl;
    }
}
void print_wallet(vector <user> &v ,int login_index)
{
    system("CLS");
    cout << "***** WALLET INFORMATION *****\n";
    for (int i =0; i<10 ; i++ )
    {
        add_coin(i+1);
        cout << setw(10) << left << coin.get_name() << ": ";
        cout << setw(6) << left << v[login_index].coins[i]
             << coin.get_abbrev() << endl;
    }
}
void print_transfer_history(vector <transfer> v ,string login_username)
{
    for (int i =0; i<v.size() ; i++ )
    {
        if(v[i].reciever == login_username)
        {
        add_coin(v[i].ID);
        cout << v[i].sender << " sent you "
             << v[i].amount << " " << coin.get_name() << endl;
        }
        else if(v[i].sender == login_username)
        {
        add_coin(v[i].ID);
        cout << "You sent " << v[i].reciever << " "
             << v[i].amount << " " << coin.get_name() << endl;
        }
    }
}
void print_conversion_history(vector <conversion> v , string login_username)
{
    for (int i =0; i<v.size() ; i++ )
    {
        if(v[i].user_ID == login_username)
        {
            add_coin(v[i].old_coin);
            cout << "You swapped " << v[i].old_amount << " " << coin.get_name() << coin.get_abbrev();
            add_coin(v[i].new_coin);
            cout << " for " << v[i].new_amount << " " << coin.get_name() << coin.get_abbrev() << endl;
        }
    }
}
void save_file(vector <user> v, vector <transfer> t, vector <conversion> c)
{
    ofstream database;
    database.open("database.txt",ios::out);
    for (int i =0; i<v.size() ; i++ )
    {
        database << v[i].username << endl;
        database << v[i].email << endl;
        database << v[i].password << endl;
        for (int j =0; j<10 ; j++ )
        {
            database << v[i].coins[j] << endl;
        }
    }
    /****************************************/
    ofstream transfer_log;
    transfer_log.open("transfer_log.txt", ios::out);
    for (int j =0; j<t.size() ; j++ )
    {
        transfer_log << t[j].sender << endl;
        transfer_log << t[j].reciever << endl;
        transfer_log << t[j].ID << endl;
        transfer_log << t[j].amount << endl;
    }
    /*****************************************/
    ofstream conversion_log;
    conversion_log.open("conversion_log.txt", ios::out);
    for (int k =0; k<t.size() ; k++ )
    {
        conversion_log << c[k].user_ID << endl;
        conversion_log << c[k].old_coin << endl;
        conversion_log << c[k].old_amount << endl;
        conversion_log << c[k].new_coin << endl;
        conversion_log << c[k].new_amount << endl;
    }
}
void open_file(vector <user> &v, vector <transfer> &t, vector <conversion> &c)
{
    string line;
    int i=0, j=0 , int0;
    double doub;
    ifstream database;
    user cred;
    database.open("database.txt",ios::in);
    if(database.is_open())
   {
       while(getline(database,line))
       {
           if(j%13==0){cred.username=line;}
           else if(j%13==1){cred.email=line;}
           else if(j%13==2){cred.password=line;}
           else
           {
               doub = stod(line);
               cred.coins[(j%13)-3]=doub;
           }
           if(j%13==12){v.push_back(cred);}
           j++;
       }
   }
   /*************************************/
   ifstream transfer_log;
   transfer tran;
   transfer_log.open("transfer_log.txt",ios::in);
   if(transfer_log.is_open())
   {
       i = 0;
       while(getline(transfer_log,line))
       {
           if(i%4==0)     {tran.sender= line;}
           else if(i%4==1){tran.reciever = line;}
           else if(i%4==2)
           {
               int0 = stoi(line);
               tran.ID = int0;
           }
           else
           {
               doub = stod(line);
               tran.amount = doub;
               t.push_back(tran);
           }
       }
   }
   /*************************************/
   ifstream conversion_log;
   conversion conv;
   conversion_log.open("conversion_log.txt",ios::in);
   if(conversion_log.is_open())
   {
       i = 0;
       while(getline(conversion_log,line))
       {
           if(i%5==0){conv.user_ID = line;}
           else if(i%5==1)
           {
               int0 = stoi(line);
               conv.old_coin = int0;
           }
           else if(i%5==2)
           {
               doub = stod(line);
               conv.old_amount = doub;
           }
           else if(i%5==3)
           {
               int0 = stoi(line);
               conv.new_coin = int0;
           }
           else
           {
               doub = stod(line);
               conv.new_amount = doub;
               c.push_back(conv);
           }
       }
   }
}
void miner(vector <user> &v)
{
    string choice;
    while(1)
    {
        cout << "Select the coin you want to mine: \n";
        cout << "Press 1 for Bitcoin\n";
        cout << "Press 2 for Ethereum\n";
        cin >> choice;
        if(choice == "1" && choice == "2"){break;}
        cout << "Enter a valid number";
    }
    srand(time(0));
    int rand_hash = rand()%1000+657000;
    for (int i =656900; i!=rand_hash ; i++ )
    {
        cout << "________Hash Mining_______\n";
        cout << "________"<< i <<"________________\n";
        cout << "__________________________\n";
        system("CLS");
    }
    cout << "-----You mined a new block------\n";
}

int authenticate(bool &status,string input, vector <user> v)
{
    status = false;
    int i=0;
    while(i<v.size())
    {
        if(v[i].username == input)
        {
            status = true;
            break;
        }
        i++;
    }
    return i;
}

void transfer_menu(int current_user, vector <user> &v, vector <transfer> &t)
{
    string user, choice = "1";
    int coin_ID;
    double amount;
    bool status;
    while(choice == "1")
    {
        system("CLS");
        cout << "Enter the username of person you want to transfer funds:\n";
        getline(cin, user);
        int user_pos = authenticate(status,user,v);
        if(!status)
        {
            system("CLS");
            cout << "User not found!\n";
            cout << "Press 0 to return back.";
            cout << "Press 1 to retry.";
            getline (cin, choice);
        }
        else
        {
            choice = "0";
            cout << "Enter the coin ID you want to transfer:\n";
            cin >> coin_ID;
            coin_ID--;
            while(cin.fail() || coin_ID < 0 || coin_ID > 9)
            {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                system("CLS");
                cout << "----------------------\n";
                cout << "Enter a valid coin ID.\n";
                cout << "----------------------\n\n";
                cout << "Enter the coin ID you want to transfer:\n";
                cin >> coin_ID;
            }
            system("CLS");
            cout << "Enter the amount you want to transfer:\n";
            cin >> amount;
            while(cin.fail())
            {
                cin.clear();
                cin.ignore();
                system("CLS");
                cout << "----------------------\n";
                cout << "Enter a valid input\n";
                cout << "----------------------\n";
                cout << "Enter the amount you want to transfer:\n";
                cin >> amount;
            }
            while(amount < v[current_user].coins[coin_ID])
            {
                cin.clear();
                cin.ignore();
                system("CLS");
                cout << "----------------------\n";
                cout << "You do not have enough funds.\n";
                cout << "----------------------\n";
                cout << "Enter the amount you want to transfer:\n";
                cin >> amount;
            }
                v[current_user].coins[coin_ID] -= amount;
                v[user_pos].coins[coin_ID] += amount;
                string dummy = v[current_user].username;
                add_transfer(t,dummy,user,coin_ID,amount);
        }
    }
}
void conversion_menu(vector <user> &v, vector <conversion> &c)
{
    string choice;
    int old_coin, new_coin;
    double old_amount , new_amount;
    cout << "Enter the coin ID:\n";

//    ID_validation(old_coin ,"From: ");
//    ID_validation(new_coin ,"To: ");
    add_coin(old_coin);
    cout << "How many " << coin.get_abbrev() << " do you want to swap: ";
//    old_amount = amount_validation("");
//    // new_amount = floater();
//    add_conversion(v,old_coin,new_coin,old_amount,new_amount);
}
void prompt(string str)
{
    cin.clear();
    cin.ignore();
    cout << "----------------------";
    cout << "Invalid " << str << "!!!\n";
    cout << "Enter a valid " << str << ".\n";
    cout << "----------------------";
}
void ID_validation(int &ID,string question)
{
    while(1)
    {
        cout << question;
        cin >> ID;
        ID--; // adjusts value for index
        if(cin.fail() || ID < 0 || ID > 9)
        {
            prompt("coin_ID");
        }
        else {break;}
    }
}
double amount_validation(string question)
{
    double amount;
    while(1)
    {
        cout << question;
        cin >> amount;
        amount--; // adjusts value for index
        if(cin.fail())
        {
            prompt("amount");
        }
        else {break;}
    }
    return amount;
}
void log_in(vector <user> v)
{

}

int main()
{
    int current_user; // keeps track of user index
    char choice;
    bool Exit = false;
    string coin_name, coin_abbrev;
    vector <user> details;
    vector <transfer> Transfer;
    vector <conversion> Conversion;
//    add_data(details);

//    save_file(details);
//    open_file(details,Transfer,Conversion);
    while(!Exit)
    {

        cout << "Press 0 to Exit.\n";
        cout << "Press 1 to Make a new account.\n";
        cout << "Press 2 to Log In.\n";
        cin  >> choice;
        switch (choice)
        {
        case '0':  Exit = true;  break;
        case '1':  add_data(details);  break;
        case '2':  log_in(details);  break;
        default :
            system("CLS");
            cout << "Please enter a valid input" << endl;
            break;
        }
    }


}
