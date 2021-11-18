#include <iostream>
#include <vector>

using namespace std;


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

struct transfers
{
    string sender, reciever;
    int ID;
    double amount;
};

void print_transfer_history(vector <transfers> v ,string login_username)
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

void add_history(vector <transfers> &v)
{
    transfers slot;
    slot.sender = "Kachra_rani71";
    slot.reciever = "Bagla1972";
    slot.ID = 5;
    slot.amount = 52.36;
    v.push_back(slot);

    slot.sender = "Davidson83";
    slot.reciever = "Kachra_rani71";
    slot.ID = 3;
    slot.amount = 459.5;
    v.push_back(slot);

    slot.sender = "Bagla1972";
    slot.reciever = "Davidson83";
    slot.ID = 5;
    slot.ID = 10;
    slot.amount = 563.5;
    v.push_back(slot);
}

int main()
{
    vector <transfers> transfer;
    add_history(transfer);
    string current_login = "Kachra_rani71";
    print_transfer_history(transfer,current_login);
    current_login = "Davidson83";
    print_transfer_history(transfer,current_login);
    current_login = "Bagla1972";
    print_transfer_history(transfer,current_login);
}
