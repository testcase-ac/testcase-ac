#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of books sold today
    int N = rnd.next(1, 10);

    // Choose a small custom alphabet
    int alphSize = rnd.next(1, 5);
    vector<char> alphabet;
    string all = "abcdefghijklmnopqrstuvwxyz";
    shuffle(all.begin(), all.end());
    for (int i = 0; i < alphSize; i++) {
        alphabet.push_back(all[i]);
    }

    // Number of distinct titles
    int D = rnd.next(1, min(N, 5));

    // Generate D unique titles
    set<string> seen;
    vector<string> titles;
    while ((int)titles.size() < D) {
        int len = rnd.next(1, 5);
        string s;
        for (int i = 0; i < len; i++) {
            s += alphabet[rnd.next(0, alphSize - 1)];
        }
        if (!seen.count(s)) {
            seen.insert(s);
            titles.push_back(s);
        }
    }

    // Generate the sold list by sampling titles
    vector<string> sold;
    sold.reserve(N);
    for (int i = 0; i < N; i++) {
        sold.push_back(rnd.any(titles));
    }
    // Shuffle to randomize order
    shuffle(sold.begin(), sold.end());

    // Output
    println(N);
    for (auto &s : sold) {
        println(s);
    }

    return 0;
}
