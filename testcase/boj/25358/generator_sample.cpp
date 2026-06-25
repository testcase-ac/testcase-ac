#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, int alphabetSize) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('A' + rnd.next(alphabetSize)));
    }
    return s;
}

string reachableTarget(const string& s) {
    vector<int> keep;
    for (int i = 0; i < int(s.size()); ++i) {
        if (rnd.next(2) == 0) keep.push_back(i);
    }
    if (keep.empty()) keep.push_back(rnd.next(int(s.size())));

    vector<int> need(26, 0);
    for (int idx : keep) ++need[s[idx] - 'A'];

    string t;
    for (char c : s) {
        int x = c - 'A';
        if (need[x] == 0) continue;
        --need[x];
        t.push_back(c);
    }
    return t;
}

string subsequenceTarget(const string& s) {
    string t;
    for (char c : s) {
        if (rnd.next(2) == 0) t.push_back(c);
    }
    if (t.empty()) t.push_back(s[rnd.next(int(s.size()))]);
    return t;
}

string frequencyImpossibleTarget(const string& s, int alphabetSize) {
    string t = subsequenceTarget(s);
    char c = char('A' + rnd.next(alphabetSize));
    while (int(t.size()) < 30) {
        t.push_back(c);
        if (count(t.begin(), t.end(), c) > count(s.begin(), s.end(), c)) return t;
    }
    return string(30, char('A' + alphabetSize));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(20, 80);
    println(n);

    for (int tc = 0; tc < n; ++tc) {
        int mode = rnd.next(6);
        int alphabetSize = rnd.next(1, 8);
        int len = rnd.next(1, 30);
        string s;
        string t;

        if (mode == 0) {
            s = randomWord(len, alphabetSize);
            t = s;
        } else if (mode == 1) {
            s = randomWord(len, alphabetSize);
            t = reachableTarget(s);
        } else if (mode == 2) {
            alphabetSize = rnd.next(1, 3);
            s = randomWord(rnd.next(10, 30), alphabetSize);
            t = reachableTarget(s);
        } else if (mode == 3) {
            s = randomWord(len, alphabetSize);
            t = subsequenceTarget(s);
            if (t == reachableTarget(s)) {
                reverse(t.begin(), t.end());
            }
        } else if (mode == 4) {
            s = randomWord(len, alphabetSize);
            t = frequencyImpossibleTarget(s, alphabetSize);
        } else {
            alphabetSize = rnd.next(2, 6);
            len = rnd.next(2, 30);
            s = randomWord(len, alphabetSize);
            t = randomWord(rnd.next(1, 30), alphabetSize);
        }

        println(s, t);
    }

    return 0;
}
