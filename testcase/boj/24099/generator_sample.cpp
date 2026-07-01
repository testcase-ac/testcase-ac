#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int alphabetSize = rnd.next(1, 8);
    if (mode == 4) alphabetSize = 26;

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (mode != 4) {
        shuffle(alphabet.begin(), alphabet.end());
        alphabet.resize(alphabetSize);
        sort(alphabet.begin(), alphabet.end());
    }

    int l;
    string document;
    if (mode == 0) {
        l = 1;
        document.push_back(rnd.any(alphabet));
    } else if (mode == 1) {
        l = rnd.next(2, 40);
        document.assign(l, rnd.any(alphabet));
    } else if (mode == 2) {
        l = rnd.next(2, 60);
        char a = rnd.any(alphabet);
        char b = rnd.any(alphabet);
        for (int i = 0; i < l; ++i) document.push_back(i % 2 == 0 ? a : b);
    } else if (mode == 3) {
        l = rnd.next(1, 80);
        for (int i = 0; i < l; ++i) document.push_back(rnd.any(alphabet));
    } else if (mode == 4) {
        l = rnd.next(26, 80);
        for (int i = 0; i < l; ++i) document.push_back(alphabet[i % 26]);
        if (rnd.next(0, 1)) shuffle(document.begin(), document.end());
    } else {
        l = rnd.next(5, 70);
        for (int i = 0; i < l; ++i) {
            char base = alphabet[i % (int)alphabet.size()];
            document.push_back(rnd.next(0, 3) == 0 ? rnd.any(alphabet) : base);
        }
    }

    vector<pair<char, char>> allRules;
    for (char a = 'A'; a <= 'Z'; ++a) {
        for (char b = 'A'; b <= 'Z'; ++b) {
            allRules.push_back({a, b});
        }
    }
    shuffle(allRules.begin(), allRules.end());

    int maxRules;
    if (mode == 0) {
        maxRules = 3;
    } else if (mode == 4) {
        maxRules = 80;
    } else {
        maxRules = min(80, alphabetSize * alphabetSize + rnd.next(0, 20));
    }

    int m;
    if (rnd.next(0, 5) == 0) {
        m = 0;
    } else if (rnd.next(0, 3) == 0) {
        m = rnd.next(1, maxRules);
    } else {
        m = rnd.wnext(maxRules + 1, -2);
    }

    cout << l << '\n';
    cout << document << '\n';
    cout << m << '\n';
    for (int i = 0; i < m; ++i) {
        cout << allRules[i].first << ' ' << allRules[i].second << '\n';
    }

    return 0;
}
