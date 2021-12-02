#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;
// for finding hcf, it helps me determine if the 2 arguments passed are co-prime with each other or not.
// If they are, b will be = 1 and if they are not b will be something other than 1.
int hcf(int a, int b)
{
    int temp;
    while (1)
    {
        temp = a % b;
        if (temp == 0)
        {
            return b;
        }
        a = b;
        b = temp;
    }
}
void RSA(string input_filename, bool encryption, bool decryption)
{
    // select two random prime numbers
    int p = 29;
    int q = 23;
    long long int n = p * q;               // calculate n
    long long int phi = (p - 1) * (q - 1); // calculate phi(n)
    // making public key
    // e is for encryption
    double e = 8;

    // check that 1 < e < phi(n) and hcf(e, phi(n)) = 1 (meaning e and phi(n) are co-prime with each other)
    while (e < phi)
    {
        long long int flag = hcf(e, phi);
        if (flag == 1)
        {
            break;
        }
        else
        {
            e++;
        }
    }
    // making private key
    // d is for decryption
    // choose d such that it satisfies d*e = 1*(mod phi(n))
    double d_temp = 1 / e;
    double d = fmod(d_temp, phi);
    // Reading from file and encrypting, writing to file and decrypting
    ifstream in_file(input_filename);
    ofstream encrypted;
    if(encryption == true)
    {  
       encrypted.open("encrypted.txt");
    }
    ofstream decrypted;
    
    if(decryption == true)
    {
       decrypted.open("decrypted.txt");
    }

    if (in_file.fail())
    {
        return;
    }
    
    char ch;
    
    while (in_file.get(ch))
    {
        int message = ch;

        long long int c = pow(message, e); // encrypt the message
        long long int m = pow(c, d);
        c = fmod(c, n);
        m = fmod(m, n);
        if (decryption == true)
        {
             char k = m + 1;
             decrypted << k;
        }
        if(encryption == true)
        {
            encrypted << c;
        }
    }

    in_file.close();
    encrypted.close();
    decrypted.close();
    remove("test.txt");
}
int main()
{
    bool encryption = true;
    bool decryption = true;
    RSA("test.txt", encryption, decryption);
}
