#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of original words
    int N = rnd.next(5, 12);
    set<string> sigs;
    vector<string> words;
    // Generate N unique words with distinct (first, last, sorted interior) signatures
    while ((int)words.size() < N) {
        int len = rnd.next(1, 8);
        char first = rnd.next('a', 'z');
        char last = rnd.next('a', 'z');
        string interior = "";
        if (len >= 2) {
            int ilen = len - 2;
            for (int i = 0; i < ilen; i++) {
                interior += char(rnd.next('a', 'z'));
            }
        }
        if (len == 1) {
            string w(1, first);
            string sig = w;
            if (sigs.insert(sig).second) {
                words.push_back(w);
            }
        } else {
            string sorted_int = interior;
            sort(sorted_int.begin(), sorted_int.end());
            string sig;
            sig += first;
            sig += last;
            sig += sorted_int;
            if (sigs.insert(sig).second) {
                string w;
                w += first;
                w += interior;
                w += last;
                words.push_back(w);
            }
        }
    }
    // Number of words in the sentence
    int M = rnd.next(1, N * 2);
    vector<string> sentence;
    // Build the mangled sentence
    for (int i = 0; i < M; i++) {
        string w = rnd.any(words);
        int len = w.size();
        if (len > 3) {
            string interior = w.substr(1, len - 2);
            shuffle(interior.begin(), interior.end());
            string mw;
            mw += w[0];
            mw += interior;
            mw += w[len - 1];
            sentence.push_back(mw);
        } else {
            // len 1,2,3: no effective interior permutation
            sentence.push_back(w);
        }
    }
    // Output
    println(N);
    for (auto &w : words) println(w);
    println(M);
    println(sentence);
    return 0;
}
