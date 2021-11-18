#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

class CoinClass
{
private:
    string abbrev_coin, name_coin;
    int coin_ID;

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
        coin.set("Bitcoin", "(BTC)");
        break;
    case 2:
        coin.set("Ethereum", "(ETH)");
        break;
    case 3:
        coin.set("Dogecoin", "(DOGE)");
        break;
    case 4:
        coin.set("Polkadot", "(DOT)");
        break;
    case 5:
        coin.set("Solana", "(SOL)");
        break;
    case 6:
        coin.set("Chainlink", "(LINK)");
        break;
    case 7:
        coin.set("Thorchain", "(RUNE)");
        break;
    case 8:
        coin.set("Uniswap", "(UNI )");
        break;
    case 9:
        coin.set("Litecoin", "(LTC)");
        break;
    case 10:
        coin.set("Tether", "(USDT)");
        break;
    default:
        coin.set("**ERROR**", "ERROR!");
        break;
    }
}

int main()
{
    int ID;
    cout << "Enter ID: " <<endl;
    cin >> ID;
    add_coin(ID);
    cout << coin.get_name() << " " << coin.get_abbrev() << endl;
}
