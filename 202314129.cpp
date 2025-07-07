#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1000;


class symbolinfo
{
public:
    string name;
    string type;

    symbolinfo() {}
    symbolinfo(string n, string t) : name(n), type(t) {}
};

class symboltable
{
public:
    vector<symbolinfo> table[SIZE];
    int hash(string s)
    {                                              /// ID = 202314129
        int n = 2 + 0 + 2 + 3 + 1 + 4 + 1 + 2 + 9; // Sum of digits in ID
        int sLen = s.length();
        ;
        int sum = 0;
        if (sLen < 2)
        {
            for (int i = 0; i < sLen; i++)
            {
                sum = sum + (int)s[i];
            }
        }
        if (sLen == 3)
        {
            sum = s[0] + s[1] + s[2];
        }
        if (sLen >= 4)
        {
            sum = s[0] + s[1];
            for (int i = sLen - 2; i < sLen; i++)
            {
                sum = sum + s[i];
            }
        }
        return ((sum << 5) * n) % SIZE;
    }

    void insert(symbolinfo sym)
    {
        int index = hash(sym.name);
        for (const auto &s : table[index])
        {
            if (s.name == sym.name)
            {
                cout << "Symbol already exists: " << sym.name << endl;
                return; // Symbol already exists
            }
        }
        table[index].push_back(sym);
        cout << "Symbol inserted: " << sym.name << ", Type: " << sym.type << endl;
    }

    bool LOOKUP(string name, bool insert = false)
    {
        int index = hash(name);
        int column = -1;
        for (int i = 0; i < table[index].size(); i++)
        {
            if (table[index][i].name == name)
            {
                column = i;
                break;
            }
        }
        if (insert == true && column == -1)
        {
            cout << "Symbol not found: " << name << endl;
            return false; // Symbol not found
        }
        else if (column != -1)
        {
            cout << "Symbol found: " << table[index][column].name << ", Type: " << table[index][column].type << endl;
            return true; // Symbol found
        }
    }

    void delete_symbol(string name)
    {
        int index = hash(name);
        for (int i = 0; i < table[index].size(); i++)
        {
            if (table[index][i].name == name)
            {
                table[index].erase(table[index].begin() + i);
                cout << "Symbol deleted: " << name << endl;
                return;
            }
        }
        cout << "Symbol not found for deletion: " << name << endl;
    }

    void print_table()
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (!table[i].empty())
            {
                cout << "Index " << i << ": ";
                for (const auto &sym : table[i])
                {
                    cout << sym.name << " (" << sym.type << ") ";
                }
                cout << endl;
            }
        }
    }
};

int main()
{
    symboltable symtab;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char op;
    while(cin>>op)
    {
        string name, type;


        if (op == 'I')
        {
            cin >> name >> type;
            symtab.insert(symbolinfo(name, type));
        }
        else if (op == 'L')
        {
            cin >> name;
            symtab.LOOKUP(name, true);
        }
        else if (op == 'D')
        {
            cin >> name;
            symtab.delete_symbol(name);
        }
        else if (op == 'P')
        {
            cout << "Printing symbol table:" << endl;
            symtab.print_table();
        }
    }
}