#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string shuffledString(const vector<pair<char, int>>& counts) {
    string s;
    for (auto [ch, count] : counts) {
        s += string(count, ch);
    }
    shuffle(s.begin(), s.end());
    return s;
}

string distinctString(int n) {
    string letters = "abcdefghijklmnopqrstuvwxyz";
    shuffle(letters.begin(), letters.end());
    return letters.substr(0, n);
}

string randomSmallAlphabetString(int n, int alphabetSize) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += char('a' + rnd.next(alphabetSize));
    }
    return s;
}

string makeCase() {
    int mode = rnd.next(6);

    if (mode == 0) {
        return string(rnd.next(1, 8), char('a' + rnd.next(26)));
    }

    if (mode == 1) {
        int n = rnd.next(3, 25);
        int major = n / 2 + rnd.next(1, n - n / 2);
        vector<pair<char, int>> counts = {{'a', major}};
        for (int i = major; i < n; ++i) {
            counts.push_back({char('b' + rnd.next(25)), 1});
        }
        return shuffledString(counts);
    }

    if (mode == 2) {
        int half = rnd.next(1, 12);
        char a = char('a' + rnd.next(26));
        char b = char('a' + rnd.next(26));
        while (b == a) b = char('a' + rnd.next(26));
        return shuffledString({{a, half}, {b, half}});
    }

    if (mode == 3) {
        return distinctString(rnd.next(2, 20));
    }

    if (mode == 4) {
        int n = rnd.next(3, 28);
        int alphabetSize = rnd.next(2, 6);
        return randomSmallAlphabetString(n, alphabetSize);
    }

    int n = rnd.next(2, 28);
    vector<pair<char, int>> counts;
    int used = 0;
    for (char ch = 'a'; used < n && ch <= 'f'; ++ch) {
        int remaining = n - used;
        int count = rnd.next(1, min(remaining, max(1, n / 2)));
        counts.push_back({ch, count});
        used += count;
    }
    if (used < n) counts.push_back({'g', n - used});
    return shuffledString(counts);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 25);
    println(t);
    for (int i = 0; i < t; ++i) {
        println(makeCase());
    }

    return 0;
}
