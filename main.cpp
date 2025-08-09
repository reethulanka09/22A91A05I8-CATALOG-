#include <bits/stdc++.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

long long digitVal(char ch)
{
    if ('0' <= ch && ch <= '9')
        return ch - '0';
    if ('A' <= ch && ch <= 'Z')
        return ch - 'A' + 10;
    if ('a' <= ch && ch <= 'z')
        return ch - 'a' + 10;
    throw runtime_error("Invalid digit in value");
}

long long decodeBase(int base, const string &val)
{
    long long num = 0;
    for (char ch : val)
    {
        long long d = digitVal(ch);
        if (d >= base)
            throw runtime_error("Digit >= base");
        num = num * base + d;
    }
    return num;
}

// Lagrange interpolation at x = 0
long long lagrange_at_zero(const vector<long long> &X, const vector<long long> &Y, int k)
{
    long long result = 0;
    for (int i = 0; i < k; i++)
    {
        long double term = Y[i];
        for (int j = 0; j < k; j++)
        {
            if (i != j)
            {
                term *= (-X[j]) / (long double)(X[i] - X[j]);
            }
        }
        result += llround(term);
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in("input.json");
    if (!in.is_open())
    {
        cerr << "Failed to open input.json\n";
        return 1;
    }

    json j;
    in >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<long long> X, Y;
    for (auto &el : j.items())
    {
        if (el.key() == "keys")
            continue;
        long long x = stoll(el.key());
        int base = stoi(el.value()["base"].get<string>());
        string val = el.value()["value"];
        long long y = decodeBase(base, val);
        X.push_back(x);
        Y.push_back(y);
    }

    long long c = lagrange_at_zero(X, Y, k);
    cout << "Constant term c = " << c << "\n";

    return 0;
}
