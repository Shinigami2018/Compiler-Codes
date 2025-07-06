#include <bits/stdc++.h>
#define table_size 20
using namespace std;

int hash_func(string value)
{
    int ans = 0;
    for (int i = 0; i < 3; i++)
        ans += value[i];
    cout << ans << endl;
    return (ans * 202314113) % 20;
}

class symbolinfo
{
public:
    string symbol;
    string type;
};

class symboltable
{
public:
    vector<symbolinfo> table[100];
    int hash_func(string value);
    int sum = 0;
};
for (int i = 0; i < value.size(), i++)
{
    sum += value[i] << 2;
}

// int hash_(string value , int n)
// {
//     int ans = 0;
//     for(auto x : value )
//         ans += x << n;
//     return ans % 100;
// }

int main()
{
    string s1 = "var_1";
    // cout << hash_func(s1);
    // cout << hash_("int", 3);
    return 0;
}