#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of sentences
    int N = rnd.next(1, 10);
    println(N);

    const string alph = "abcdefghijklmnopqrstuvwxyz";
    const string pool = " .,!?'\"0123456789";

    for (int i = 0; i < N; i++) {
        bool is_pangram = rnd.next(0, 1) == 1;
        vector<char> v;

        if (is_pangram) {
            // include every letter once
            for (char c : alph) v.push_back(c);
        } else {
            // choose some letters to be missing
            int miss = rnd.next(1, 25);
            vector<int> idx(26);
            iota(idx.begin(), idx.end(), 0);
            shuffle(idx.begin(), idx.end());
            vector<bool> missing(26, false);
            for (int j = 0; j < miss; j++) {
                missing[idx[j]] = true;
            }
            for (int j = 0; j < 26; j++) {
                if (!missing[j]) v.push_back(alph[j]);
            }
        }

        // decide extra letters to pad up to some length
        int base = v.size();
        int extra_letters = rnd.next(0, 20);
        int Lmax = min(100, base + extra_letters);
        int Ltarget = rnd.next(base, Lmax);
        while ((int)v.size() < Ltarget) {
            v.push_back(rnd.any(alph));
        }

        // add some punctuation, digits, spaces
        int extra_sym = rnd.next(0, 20);
        for (int k = 0; k < extra_sym && (int)v.size() < 100; k++) {
            v.push_back(rnd.any(pool));
        }

        // shuffle all characters
        shuffle(v.begin(), v.end());

        // random capitalization
        for (auto &c : v) {
            if (c >= 'a' && c <= 'z' && rnd.next() < 0.5) {
                c = char('A' + (c - 'a'));
            }
        }

        // build and print the sentence
        string s(v.begin(), v.end());
        println(s);
    }

    return 0;
}
