#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

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

void add_coin(int coin_ID)
{
    switch (coin_ID)
    {
    case 1:
        coin.set("Bitcoin  ", "(BTC) ");
        break;
    case 2:
        coin.set("Ethereum ", "(ETH) ");
        break;
    case 3:
        coin.set("Dogecoin ", "(DOGE)");
        break;
    case 4:
        coin.set("Polkadot ", "(DOT) ");
        break;
    case 5:
        coin.set("Solana   ", "(SOL) ");
        break;
    case 6:
        coin.set("Chainlink", "(LINK)");
        break;
    case 7:
        coin.set("Thorchain", "(RUNE)");
        break;
    case 8:
        coin.set("Uniswap  ", "(UNI) ");
        break;
    case 9:
        coin.set("Litecoin ", "(LTC) ");
        break;
    case 10:
        coin.set("Tether   ", "(USDT)");
        break;
    default:
        coin.set("**ERROR**", "ERROR!");
        break;
    }
}
void add_history(vector <transfer> &v,string current_login,string Reciever, int coin_ID, double Amount)
{
    transfer slot;
    slot.sender = current_login;
    slot.reciever = Reciever;
    slot.ID = coin_ID;
    slot.amount = Amount;
    v.push_back(slot);
}
void add_conversion(vector <conversion> &v,string current_login, int OLD_COIN, int NEW_COIN, double OLD_A , double NEW_A)
{
    conversion log;
    log.user_ID = current_login;
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
void print_wallet(vector <user> &v ,int login_index)
{
    for (int i =0; i<10 ; i++ )
    {
        add_coin(i+1);
        cout << coin.get_name() << coin.get_abbrev() << ": $";
        cout<< v[login_index].coins[i] << endl;
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
void print_conversion_history(vector <conversion> v , string current_login)
{
    for (int i =0; i<v.size() ; i++ )
    {
        if(v[i].user_ID == current_login)
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
    database.open("database.txt",ios::app);
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
    transfer_log.open("transfer_log.txt", ios::app);
    for (int j =0; j<t.size() ; j++ )
    {
        transfer_log << t[j].sender << endl;
        transfer_log << t[j].reciever << endl;
        transfer_log << t[j].ID << endl;
        transfer_log << t[j].amount << endl;
    }
    /*****************************************/
    ofstream conversion_log;
    conversion_log.open("conversion_log.txt", ios::app);
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
int main()
{
    string coin_name, coin_abbrev;
    vector <user> details;
    vector <transfer> Transfer;
    vector <conversion> Conversion;
//    add_data(details);

//    save_file(details);
    open_file(details,Transfer,Conversion);
    print_wallet(details,0);
//    for (int i =0; i<details.size() ; i++ )
//    {
//    cout << details[i].username << endl;
//    cout << details[i].email << endl;
//    cout << details[i].password << endl;
//    for (int j =0; j<10 ; j++ )
//    {
//        cout << details[i].coins[j] << endl;
//    }
//    }


}
