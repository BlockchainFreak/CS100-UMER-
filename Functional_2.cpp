#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <unistd.h>
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
    double rate_coin;
public:
    void remove_coin(string s, int coin_ID);
    void set(string name, string abbrev ,double rate)
    {
        name_coin = name;
        abbrev_coin = abbrev;
        rate_coin = rate;
    }
    string get_abbrev()
    {
        return abbrev_coin;
    }
    string get_name()
    {
        return name_coin;
    }
    double get_rate()
    {
        return rate_coin;
    }
} coin;
void print_asterisk()
{
   for (int i =0; i<25 ; i++ )
   {
       cout << "*";
   }
   cout << "\n";
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
void add_coin(int coin_ID)
{
    switch (coin_ID)
    {
    case 1:
        coin.set("Bitcoin", "BTC",56000);
        break;
    case 2:
        coin.set("Ethereum", "ETH",4400);
        break;
    case 3:
        coin.set("Dogecoin", "DOGE",1.4);
        break;
    case 4:
        coin.set("Polkadot", "DOT",52);
        break;
    case 5:
        coin.set("Solana", "SOL",232);
        break;
    case 6:
        coin.set("Chainlink", "LINK",28);
        break;
    case 7:
        coin.set("Thorchain", "RUNE",14);
        break;
    case 8:
        coin.set("Uniswap", "UNI",35);
        break;
    case 9:
        coin.set("Litecoin", "LTC",215);
        break;
    case 10:
        coin.set("Tether", "USDT",1);
        break;
    default:
        coin.set("**ERROR**", "ERROR!",1);
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
void add_data(vector <user> &v)
{
    user cred;
    string dummy;
    bool check;
    system("CLS");
    cout << "Enter your username: ";
    getline(cin, dummy);
    authenticate(check,dummy,v);
    while(check)
    {
        system("CLS");
        cout << "There is already a username with " << dummy;
        cout << "\nsuggested usernames:\n";
        cout << "<23" << dummy << "> ";
        cout << "<" << dummy << "_5618> ";
        cout << "<045" << dummy << "op> \n";
        cout << "Try another one:\n";
        getline(cin, dummy);
        authenticate(check,dummy,v);
    }
    cred.username = dummy;
    cout << " \nEnter your email: ";
    getline(cin, dummy);
    int special_sign = 0;
    for (int i =0; i<dummy.size() ; i++ )
    {
        char c = dummy[i];
        if(c =='@'){special_sign++;}
        if(c==' ' || c =='/'){special_sign+=100;}
    }
    while(special_sign!=1)
    {
        special_sign = 0;
        system("CLS");
        cout << "Invalid email format.\n";
        getline(cin, dummy);
        special_sign=0;
        for (int i =0; i<dummy.size() ; i++ )
        {
            char c = dummy[i];
            if(c =='@'){special_sign++;}
            if(c==' ' || c =='/'){special_sign+=100;}
        }
    }
    cred.email = dummy;
    dummy.clear();
    cout << " \nEnter your password: \n";
    getline(cin, dummy);
    int s = dummy.size();
    while(s<6)
    {
        system("CLS");
        cout << "Password must be at least 6 characters.\n";
        getline(cin, dummy);
        s = dummy.size();
    }
    cred.password = dummy;
    cout<<"\n";
    double deposit_amount;
    cout << " \nEnter your depositing amount: ";
    cin >> deposit_amount;
    while(cin.fail() || deposit_amount <= 0)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
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
    cout << "\t\t  " << "|\t  |\n";
    for (int i =1; i<=10 ; i++ )
    {
        add_coin(i);
        cout << setw(12) << left << coin.get_name()
             << setw(6)  << left << coin.get_abbrev()
             << "|   " << setw(2) << i << "  |" << endl;
    }
    cout << "------------------------------\n";
}
void print_wallet(vector <user> &v ,int login_index)
{
    system("CLS");
    cout << "***** WALLET INFORMATION *****\n";
    for (int i =0; i<10 ; i++ )
    {
        add_coin(i+1);
        cout << setw(10) << left << coin.get_name() << ": ";
        cout << setw(10) << left << v[login_index].coins[i]
             << setw(4) << coin.get_abbrev() << "  |$"
             << setw(6) << coin.get_rate() << "|" << endl;
    }
    cout << "******************************\n";
    char temp;
    cin >> temp;
}
void print_transfer_history(vector <transfer> v ,string login_username)
{
    system("CLS");
    for (int i =0; i<v.size() ; i++ )
    {
        if(v[i].reciever == login_username)
        {
            add_coin(v[i].ID+1);
            cout << v[i].sender << " sent you "
                 << v[i].amount << " " << coin.get_name() << endl;
        }
        else if(v[i].sender == login_username && i>5)
        {
            add_coin(v[i].ID+1);
            cout << "You sent " << v[i].reciever << " "
                 << v[i].amount << " " << coin.get_name() << endl;
        }
        else if(v[i].sender == login_username && i<=5)
        {
            add_coin(v[i].ID+1);
            cout << "You paid " << v[i].reciever << " "
                 << v[i].amount << " " << coin.get_name() << endl;
        }
    }
    char temp;
    cin >> temp;
}
void print_conversion_history(vector <conversion> v , string login_username)
{
    char temp;
    system("CLS");
    for (int i =0; i<v.size() ; i++ )
    {
        if(v[i].user_ID == login_username)
        {
            add_coin(v[i].old_coin+1);
            cout << "You swapped " << v[i].old_amount << " "
                 << coin.get_name() << " (" << coin.get_abbrev();
            add_coin(v[i].new_coin+1);
            cout << ") for " << v[i].new_amount << " " << coin.get_name()
            << " (" << coin.get_abbrev() << ")\n";
        }
    }
    cin >> temp;
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
    transfer_log.open("transfer_log.txt",ios::out);
    for (int j =0; j<t.size() ; j++ )
    {
        transfer_log << t[j].sender << endl;
        transfer_log << t[j].reciever << endl;
        transfer_log << t[j].ID << endl;
        transfer_log << t[j].amount << endl;
    }
    /*****************************************/
    ofstream conversion_log;
    conversion_log.open("conversion_log.txt",ios::out);
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
    int i=0, int0;
    double doub;
    ifstream database;
    user cred;
    database.open("database.txt",ios::in);
    if(database.is_open())
   {
       while(getline(database,line))
       {
           if(i%13==0){cred.username=line;}
           else if(i%13==1){cred.email=line;}
           else if(i%13==2){cred.password=line;}
           else
           {
               doub = stod(line);
               cred.coins[(i%13)-3]=doub;
           }
           if(i%13==12){v.push_back(cred);}
           i++;
       }
   }
   database.close();
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
           i++;
       }
   }
   transfer_log.close();
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
           i++;
       }
   }
   conversion_log.close();
}
void miner(int current_user, vector <user> &v)
{
    static const char pool[] = {"0123456789abcdef"};
    string choice;
    string Hash = "";
    char temp;
    srand(time(NULL));
    while(1)
    {
        cout << "Select the coin you want to mine: \n";
        cout << "Press 1 for Bitcoin\n";
        cout << "Press 2 for Ethereum\n";
        cin >> choice;
        if(choice == "1" || choice == "2"){break;}
        cout << "Enter a valid number";
    }
    for (int i =0; i<30 ; i++ )
    {
        cout << "\t\t Mining Blocks\n";
        cout << "\t\t estimated time: " << 15-(i/2) << "s\n\n" ;
        for (int j =0; j<18 ; j++ )
        {
            for (int k =0; k<50 ; k++ )
            {
                temp = pool[rand()%16];
                Hash += temp;
            }
            usleep(1000);
            cout << "\t\t" << Hash << "\n";
            Hash = "";
        }
        usleep(10000);
        system("CLS");
    }
    cout << "-----You mined a new block------\n";
    if(choice=="1")
    {
        v[current_user].coins[0]+=2.5;
        cout << "Congrats! You have got 2.5 BTC as reward.\n";
    }
    else if(choice=="2")
    {
        v[current_user].coins[1]+=12;
        cout << "Congrats! You have got 12 ETH as reward.\n";
    }
    usleep(2*1000000);
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
            cout << "Press 0 to return back.\n";
            cout << "Press 1 to retry.\n";
            getline (cin, choice);
        }
        else
        {
            choice = "0";
            system("CLS");
            coin_index();
            cout << "Enter the coin ID you want to transfer:\n";
            cin >> coin_ID;
            while(cin.fail() || coin_ID < 1 || coin_ID > 10)
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
            coin_ID--;
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
            while(amount > v[current_user].coins[coin_ID])
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
                if(amount!=0)
                {
                    add_transfer(t,dummy,user,coin_ID,amount);
                }
                cout << "--------------------------------------\n";
                cout << "Transaction is successful.\n";
                cout << "--------------------------------------\n";
                usleep(1*1000000);
                add_coin(coin_ID+1);
                print_asterisk();
                cout << "\nYou successfully transfered " << amount << " "
                << coin.get_abbrev() << " to " << user << ".\n";
                print_asterisk();
                usleep(2*1000000);
        }
    }
}
void conversion_menu(int current_user, vector <user> &v, vector <conversion> &c)
{
    string choice;
    int old_coin, new_coin;
    double old_amount , new_amount;
    system("CLS");
    coin_index();
    cout << "Enter the coin ID of old asset:\n";
    cin >> old_coin;
    while(cin.fail() || old_coin < 1 || old_coin > 10)
        {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("CLS");
            cout << "----------------------\n";
            cout << "Enter a valid coin ID.\n";
            cout << "----------------------\n\n";
            cout << "Enter the coin ID:\n";
            cin >> old_coin;
        }
    cout << "Enter the coin ID of new asset:\n";
    cin >> new_coin;
    while(cin.fail() || new_coin < 1 || new_coin > 10 || old_coin==new_coin)
        {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("CLS");
            cout << "----------------------\n";
            cout << "Enter a valid coin ID.\n";
            cout << "----------------------\n\n";
            cout << "Enter the coin ID:\n";
            cin >> new_coin;
        }
    system("CLS");
    add_coin(old_coin);
    cout << "How many " << coin.get_abbrev() << " do you want to swap: \n";
    cin >> old_amount;
    add_coin(old_coin);
    double rate_old = coin.get_rate();
    add_coin(new_coin);
    double rate_new = coin.get_rate();
    new_amount = (old_amount*rate_old)/rate_new*(1.000001);
    old_coin--;
    new_coin--;
    while(cin.fail() || v[current_user].coins[old_coin] < old_amount)
        {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("CLS");
            cout << "----------------------\n";
            cout << "Invalid Input or Insufficient balance!\n";
            cout << "----------------------\n\n";
            cout << "How many " << coin.get_abbrev() << " do you want to swap: \n";
            cin >> old_amount;
        }
    system("CLS");
    string user_n = v[current_user].username;
    add_conversion(c,user_n,old_coin,new_coin,old_amount,new_amount);
    v[current_user].coins[old_coin] -= old_amount;
    v[current_user].coins[new_coin] += new_amount;
    cout << "--------------------------------------\n";
    cout << "Assets have been successfully swapped.\n";
    cout << "--------------------------------------\n";
    usleep(1500000);
}
void log_in(vector <user> v ,int &current_user)
{
    system("CLS");
    string username;
    string pass;
    bool status = false;
    cout << "Enter you username:\n";
    getline(cin, username);
    current_user = authenticate(status, username, v);
    while(!status)
    {
        system("CLS");
        cout << "No account exist with such username!\n";
        cout << "Try again\n";
        cout << "Enter you username:\n";
        getline(cin, username);
        current_user = authenticate(status, username, v);
    }
    cout << "\nEnter your password: ";
    getline(cin, pass);
    while(v[current_user].password!=pass)
    {
        system("CLS");
        cout << "Wrong password!!!!\n";
        cout << "Press 0 and Enter to Return back.\n";
        cout << "Enter your password: \n";
        getline(cin, pass);
        if(pass=="0")
        {
            current_user = -1;
            break;
        }
    }
}
void payment_window(int current_user, vector <user> &v, vector <transfer> &t)
{
    bool Exit = false;
    unsigned int coin_ID, pos;
    double amount;
    system("CLS");
    while(!Exit)
    {
        cout << "Press 1 to pay PDC(Pepsi Dining Centre.\n";
        cout << "Press 2 to pay Zakir Tikka.\n";
        cout << "Press 3 to pay Subway.\n";
        cout << "Press 4 to pay Bunker.\n";
        cout << "Press 5 to pay Superstore.\n";
        cout << "Press 6 to pay Khokha store.\n";
        cout << "Press 0 to Exit.\n";
        cin >> pos;
        while(cin.fail() || pos < 0 || pos > 6)
        {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("CLS");
            cout << "----------------------\n";
            cout << "Enter a valid option.\n";
            cout << "----------------------\n\n";
            cin >> pos;
        }
        if(pos==0)
        {
            Exit = true;
        }
        else if(pos>=0 && pos<=5)
        {
            system("CLS");
            coin_index();
            cout << "Enter the coin ID you want to transfer:\n";
            cin >> coin_ID;
            while(cin.fail() || coin_ID < 1 || coin_ID > 10)
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
            coin_ID--;
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
            v[pos-1].coins[coin_ID] += amount;
            string dummy1 = v[current_user].username;
            string dummy2 = v[pos].username;
            add_transfer(t,dummy1,dummy2,coin_ID,amount);
            cout << "--------------------------------------\n";
            cout << "Transaction is Successful!.\n";
            cout << "--------------------------------------\n";
            usleep(1500000);
        }
    }
}
void change_pass(int current_user,vector <user> &v)
{
    string input, real, update;
    system("CLS");
    print_asterisk();
    cout << "Enter you previous password:\n";
    getline(cin, input);
    real = v[current_user].password;
    while(real!=input && input!="0")
    {
        system("CLS");
        print_asterisk();
        cout << "!!!!!Wrong Password. Try again!!\n";
        cout << "or Press 0 to leave.\n";
        getline(cin, input);
    }
    if(input!="0")
    {
        system("CLS");
        cout << "Enter your new password:\n";
        getline(cin, update);
        while(update.size() <6)
        {
            system("CLS");
            cout << "Password must be at least 6 characters.\n";
            getline(cin, update);
        }
        if(input!="0")
        {
            v[current_user].password = update;
            print_asterisk();
            cout << "Password changed succesfully.\n";
            print_asterisk();
            usleep(1500000);
            system("CLS");
        }
    }
}
void main_menu(int current_user,vector <user> &v,vector <transfer> &t, vector <conversion> &c)
{
    string choice;
    char temp;
    bool End =false;
    system("CLS");
    while(!End)
    {
        system("CLS");
        cout << "Press 0 to Exit.\n";
        cout << "Press 1 to view you assets.\n";
        cout << "Press 2 to convert assets.\n";
        cout << "Press 3 to transfer assets.\n";
        cout << "Press 4 to change you password.\n";
        cout << "Press 5 to mine coins.\n";
        cout << "Press 6 to open payment window.\n";
        cout << "Press 7 to print conversion history.\n";
        cout << "Press 8 to print transfer history.\n";
        getline(cin, choice);
        string login_username = v[current_user].username;
        switch (choice[0])
        {
        case '0' :
            End = true;
            break;
        case '1' :
            print_wallet(v,current_user);
            break;
        case '2' :
            conversion_menu(current_user,v,c);
            break;
        case '3' :
            transfer_menu(current_user,v,t);
            break;
        case '4' :
            change_pass(current_user,v);
            break;
        case '5' :
            miner(current_user,v);
            break;
        case '6' :
            payment_window(current_user,v,t);
            break;
        case '7' :
            print_conversion_history(c,login_username);
            break;
        case '8' :
            print_transfer_history(t,login_username);
            break;
        default :
            cout << "Enter a valid choice.\n";
            cout << "*********************\n";
            break;
        }
    }
}

int main()
{
    int current_user; // keeps track of user index
    string choice;
    bool Exit = false;
    vector <user> details;
    vector <transfer> Transfer;
    vector <conversion> Conversion;
    open_file(details,Transfer,Conversion);
    while(!Exit)
    {
        system("CLS");
        cout << "Welcome to Cryptocurrency Exchange\n";
        cout << "**********************************\n";
        cout << "Press 0 to Exit.\n";
        cout << "Press 1 to Make a new account.\n";
        cout << "Press 2 to Log In.\n";
        getline(cin, choice);
        switch (choice[0])
        {
        case '0' :
            Exit = true;
            break;
        case '1' :
            add_data(details);
            break;
        case '2' :
            log_in(details,current_user);
            if(current_user>=0)
            {
                main_menu(current_user,details,Transfer,Conversion);
            }
            break;

        default:
            system("CLS");
            cout << "Please enter a valid input" << endl;
            break;
        }
    }
    save_file(details,Transfer,Conversion);
}
