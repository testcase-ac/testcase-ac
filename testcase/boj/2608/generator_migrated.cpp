#include <bits/stdc++.h>
using namespace std;

vector<pair<int, string>> roman_numerals = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

string toRoman(int num) {
    string result = "";
    for (auto& rn : roman_numerals) {
        while (num >= rn.first) {
            result += rn.second;
            num -= rn.first;
        }
    }
    return result;
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 2000);
    int num1 = dist(gen);
    int num2 = dist(gen);
    cout<<toRoman(num1)<<"\n"<<toRoman(num2);
}
