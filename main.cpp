#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

struct user
{
    string username, email, password;
    double coins[10]={0};
};
void coin_naming(int coin_ID,string &coin_name, string &coin_abbrev)
{
    switch (coin_ID)
    {
    case 1:
        coin_name = "Bitcoin  ";
        coin_abbrev = "(BTC) ";
        break;
    case 2:
        coin_name = "Ethereum ";
        coin_abbrev = "(ETH) ";
        break;
    case 3:
        coin_name = "Dogecoin ";
        coin_abbrev = "(DOGE)";
        break;
    case 4:
        coin_name = "Polkadot ";
        coin_abbrev = "(DOT) ";
        break;
    case 5:
        coin_name = "Solana   ";
        coin_abbrev = "(SOL) ";
        break;
    case 6:
        coin_name = "Chainlink";
        coin_abbrev = "(LINK)";
        break;
    case 7:
        coin_name = "Thorchain";
        coin_abbrev = "(RUNE)";
        break;
    case 8:
        coin_name = "Uniswap  ";
        coin_abbrev = "(UNI )";
        break;
    case 9:
        coin_name = "Litecoin ";
        coin_abbrev = "(LTC) ";
        break;
    case 10:
        coin_name = "Tether   ";
        coin_abbrev = "(USDT)";
        break;

    default:
        coin_name = "**ERROR**";
        coin_abbrev = "ERROR!";
        break;
    }
}

void add_data(vector<user> &v)
{
    user cred;
    string arbit;
    double deposit_amount;
    cout << " \nEnter your username: ";
    cin.ignore();
    getline(cin, cred.username);
    cout << " \nEnter your email: ";
    getline(cin, cred.email);
    cout << " \nEnter your password: ";
    getline(cin, cred.password);
    cout<<endl;
    cout << " \nEnter your depositing amount: ";
    cin >> deposit_amount;
    while(cin.fail() || deposit_amount <= 0)
    {
        cin.clear();
        cin.ignore();
        cout << "\nEnter appropriate deposit amount: ";
        cin >> deposit_amount;
    }

    cred.coins[9]=deposit_amount;

    v.push_back(cred);
    return;
}

void print_wallet(vector <user> &v ,int login_index)
{
    string coin_name, coin_abbrev;
    for (int i =0; i<10 ; i++ )
    {
        coin_naming(i+1,coin_name,coin_abbrev);
        cout << coin_name << coin_abbrev << ": $";
        cout<< v[login_index].coins[i] << endl;
    }
}
void save_file(vector <user> v)
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

void open_file(vector <user> &v)
{
    ifstream database;
    user cred;
   database.open("database.txt",ios::in);
   if(database.is_open())
   {
       string line;
       int i=0, j=0;
       double price;
       while(getline(database,line))
       {
           if(j%13==0){cred.username=line;}
           else if(j%13==1){cred.email=line;}
           else if(j%13==2){cred.password=line;}
           else
           {
               price = stod(line);
               cred.coins[(j%13)-3]=price;
           }
           if(j%13==12){v.push_back(cred);}
           j++;
       }
   }
}
int main()
{
    string coin_name, coin_abbrev;
    vector <user> details;
//    add_data(details);
//    print_wallet(details,0);

//    save_file(details);
    open_file(details);
    for (int i =0; i<details.size() ; i++ )
    {
    cout << details[i].username << endl;
    cout << details[i].email << endl;
    cout << details[i].password << endl;
    for (int j =0; j<10 ; j++ )
    {
        cout << details[i].coins[j] << endl;
    }
    }


}
