#include <bits/stdc++.h>
// #include "202314129.cpp"
using namespace std;
/// mod val 12
ofstream out("output.txt", ios_base::out);
bool idOrkey(char ch)
{
    if ((ch >= '0' && ch <= '9') || (ch == '_') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    else
        return false;
}
bool digit(string a)
{
    int cnt = 0;
    int n = a.size();
    if (a[0] != '-' && !(a[0] >= '0' && a[0] <= '9') && a[0] != '.')
        return false;
    if (a[0] == '.')
        cnt++;
    for (int i = 1; i < n; i++)
    {
        if (!(a[i] >= '0' && a[i] <= '9') && (a[i] != '.'))
            return false;
        {
            if (a[i] == '.')
                cnt++;
        }
        if (cnt > 1)
            return false;
        return true;
    }
}

bool id(string a)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (!idOrkey(a[i]))
            return false;
    }
    if (a.size() > 0)
        if (a[0] >= '0' && a[0] <= '9')
            return false;

    if (a.size() == 0)
        return false;
    return true;
}

bool op(string ch)
{
    vector<string> op = {"+", "-", "*", "%", "&&", "||", "&", "|", "<<", ">>", "=", "+=", "/=",
                         "%=", "!", "!=", "-=", "==", ">", "<", "!"};
    if (find(op.begin(), op.end(), ch) != op.end())
        return true;
    else
        return false;
}

bool spc(char ch)
{
    if (ch == ' ' || ch == '\n' || ch == '\t')
        return true;
    return false;
}
bool punct(char ch)
{
    vector<char> punc = {',', '.', ';', '?', ':'};
    if (find(punc.begin(), punc.end(), ch) != punc.end())
        return true;
    else
        return false;
}
bool keyword(string a)
{
    vector<string> key = {"if", "else", "else if", "for", "while", "do", "break", "int",
                          "char", "float", "double", "unsigned", "const", "return", "include"};
    if (find(key.begin(), key.end(), a) != key.end())
        return true;
    else
        return false;
}
bool interrupt(char ch)
{
    vector<char> bracket = {'(', ')', '{', '}', '[', ']', ',', '.', ';', '?', ':'};
    if (find(bracket.begin(), bracket.end(), ch) != bracket.end())
        return true;
    else
        return false;
}

class SymbolInfo
{
    string symbol, type;

public:
    SymbolInfo(string sym, string typ) : symbol(sym), type(typ) {}
    string getSymbol() const { return symbol; }
    string getType() const { return type; }
    void setSymbol(const string &sym) { symbol = sym; }
    void setType(const string &typ) { type = typ; }
};

class SymbolTable
{
    vector<SymbolInfo> table[12];

public:
    bool lookup(string symbol)
    {
        int hashVal = hashFunction(symbol);
        bool b = false;
        for (int j = 0; j < table[hashVal].size(); j++)
        {
            if (table[hashVal][j].getSymbol() == symbol)
            {
                out << "Found at " << hashVal << "," << j << endl;
                b = true;
            }
        }
        return b;
    }

    void print()
    {
        for (int i = 0; i < 12; i++)
        {
            out << i << " -> ";
            for (int j = 0; j < table[i].size(); j++)
            {
                out << "<" << table[i][j].getSymbol() << ","
                    << table[i][j].getType() << "> ";
            }
            out << endl;
        }
    }

    int hashFunction(const string &symbol)
    {
        int sum = 0;
        if (symbol.length() >= 1)
            sum += symbol[0];
        if (symbol.length() >= 2)
            sum += symbol[1];
        if (symbol.length() >= 3)
            sum += symbol[2];
        return ((sum * 2) % 12);
    }
    void insertVal(string symbol, string symbolType)
    {
        bool b = lookup(symbol);
        if (b == false)
        {
            SymbolInfo obj = SymbolInfo(symbol, symbolType);
            int hashVal = hashFunction(symbol);
            table[hashVal].push_back(obj);
            int pos = table[hashVal].size();
            out << "Inserted at position " << hashVal << "," << pos - 1 << endl;
            print();
        }
        else
        {
            out << "Value already exists" << endl;
        }
    }
};

int main()
{
    string symbol, symbolType;
    SymbolTable ob;
    ifstream input;
    ofstream key("output1_keyword.txt");
    ofstream func("output1_function.txt");
    ofstream identifier("output1_id.txt");
    ofstream operat("output1_oper.txt");
    ofstream num("output1_number.txt");
    ofstream liter("output1_literal.txt");
    input.open("sample_input1.txt");
    string s = "";
    int line = 1;
    while (getline(input, s))
    {
        int n = s.size();
        string token = "", temp = "", lit = "";
        bool literal = false, op_pattern = false, str_pattern = false;
        for (int i = 0; i < n; i++)
        {
            temp = "";
            if (s[i] == '"')
            {
                if (literal)
                {
                    lit += s[i];
                    liter << lit << " " << line << endl;
                    literal = false;
                }
                else
                {
                    literal = true;
                    /// continue;
                }
            }
            if (literal)
            {
                lit += s[i];
            }
            if (idOrkey(s[i]) && !literal)
            {
                token += s[i];
            }
            else
            {
                if (!interrupt(s[i]) && !literal && !spc(s[i]))
                {
                    temp = s[i];
                    if (op(temp))
                    {
                        string y = temp + s[i + 1];
                        if (op(y))
                        {
                            operat << y << " " << line << endl;
                            i++;
                            ob.insertVal(y, "Operator");
                        }
                        else
                        {
                            operat << temp << " " << line << endl;
                            ob.insertVal(temp, "Operator");
                        }
                        op_pattern = true;
                    }
                    else
                        op_pattern = false;
                }
                if (keyword(token))
                {
                    key << token << " " << line << endl;
                    ob.insertVal(token, "Keyword");
                    str_pattern = true;
                }
                else if (id(token))
                {
                    if (s[i] == '(')
                    {
                        func << token << " " << line << endl;
                        ob.insertVal(token, "Function");
                    }
                    else
                    {
                        identifier << token << " " << line << endl;
                        ob.insertVal(token, "Identifier");
                    }
                    str_pattern = true;
                }
                else if (digit(token))
                {
                    num << token << " " << line << endl;
                    ob.insertVal(token, "Number");
                    str_pattern = true;
                }
                else
                {
                    str_pattern = false;
                }
                if (((token.size() && str_pattern == false) || (temp.size() && op_pattern == false)) && !literal || interrupt(s[i]))
                {
                    cout << "Lexical error at line " << line << " and error is: " << s[i] << endl;
                }
                token = "";
            }
            str_pattern = op_pattern = false;
        }
        line++;
    }
    input.close();
    return 0;
}