#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

long long parseNumber(const string& s) {
    long long value = 0;
    for (char ch : s) value = value * 10 + (ch - '0');
    return value;
}

string randomPositiveDigits(int len) {
    string s;
    s += char('1' + rnd.next(9));
    for (int i = 1; i < len; ++i) s += char('0' + rnd.next(10));
    return s;
}

string insertDigits(string base, vector<char> extra) {
    shuffle(extra.begin(), extra.end());
    for (char ch : extra) {
        int pos = rnd.next(int(base.size()) + 1);
        if (pos == 0 && ch == '0') pos = 1;
        base.insert(base.begin() + pos, ch);
    }
    return base;
}

void printReduced(long long a, long long b) {
    long long g = gcd(a, b);
    println(a, b, a / g, b / g);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);

    if (mode == 0) {
        long long den = rnd.next(2, 999);
        long long num = rnd.next(1LL, den - 1);
        long long g = gcd(num, den);
        num /= g;
        den /= g;

        vector<char> removed;
        int removedCount = rnd.next(1, 5);
        for (int i = 0; i < removedCount; ++i) removed.push_back(char('0' + rnd.next(10)));

        string a = insertDigits(to_string(num), removed);
        string b = insertDigits(to_string(den), removed);
        println(parseNumber(a), parseNumber(b), num, den);
        return 0;
    }

    if (mode == 1) {
        vector<pair<string, string>> bases = {
            {"1", "2"}, {"13", "39"}, {"87", "261"}, {"123", "456"}
        };
        auto base = rnd.any(bases);
        vector<char> removed;
        int removedCount = rnd.next(2, 6);
        for (int i = 0; i < removedCount; ++i) {
            removed.push_back(rnd.any(string("00112233445566778899")));
        }

        string a = insertDigits(base.first, removed);
        string b = insertDigits(base.second, removed);
        printReduced(parseNumber(a), parseNumber(b));
        return 0;
    }

    if (mode == 2) {
        long long a = rnd.next(1LL, 999999999LL);
        long long b = rnd.next(1LL, 999999999LL);
        printReduced(a, b);
        return 0;
    }

    if (mode == 3) {
        string a = randomPositiveDigits(rnd.next(12, 18));
        string b = randomPositiveDigits(rnd.next(12, 18));
        string c = randomPositiveDigits(rnd.next(12, 18));
        string d = randomPositiveDigits(rnd.next(12, 18));
        println(parseNumber(a), parseNumber(b), parseNumber(c), parseNumber(d));
        return 0;
    }

    if (mode == 4) {
        long long a = rnd.next(1LL, 999999LL);
        long long b = rnd.next(1LL, 999999LL);
        long long c = rnd.next(1LL, 999999LL);
        long long d = rnd.next(1LL, 999999LL);
        if ((__int128)a * d == (__int128)b * c) ++d;
        println(a, b, c, d);
        return 0;
    }

    long long scale = rnd.next(1LL, 1000000LL);
    long long c = rnd.next(1LL, 1000000LL);
    long long d = rnd.next(1LL, 1000000LL);
    println(c * scale, d * scale, c, d);
    return 0;
}
