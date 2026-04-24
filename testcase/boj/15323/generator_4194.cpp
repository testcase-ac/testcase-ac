#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for small sizes
    int K = rnd.next(1, 10);      // number of words
    int N = rnd.next(1, 20);      // number of queries
    int P = rnd.next(1, min(K, 5)); // number of distinct starting letters

    // Choose P distinct starting letters
    vector<char> alpha;
    for (char c = 'a'; c <= 'z'; ++c) alpha.push_back(c);
    shuffle(alpha.begin(), alpha.end());
    vector<char> start_letters(alpha.begin(), alpha.begin() + P);

    // Generate K distinct words, ensuring coverage of each start letter
    set<string> wordset;
    // First ensure one word per starting letter
    for (char c : start_letters) {
        int len = rnd.next(1, 5);
        string w;
        w.push_back(c);
        for (int i = 1; i < len; i++) {
            w.push_back(char(rnd.next('a', 'z')));
        }
        wordset.insert(w);
    }
    // Fill up to K
    while ((int)wordset.size() < K) {
        char c = rnd.any(start_letters);
        int len = rnd.next(1, 5);
        string w;
        w.push_back(c);
        for (int i = 1; i < len; i++) {
            w.push_back(char(rnd.next('a', 'z')));
        }
        wordset.insert(w);
    }

    // Move to vector and shuffle order
    vector<string> words(wordset.begin(), wordset.end());
    shuffle(words.begin(), words.end());

    // Hyper-parameter for query distribution skew
    vector<int> tlist = {1, -1, 2, -2};
    int t = rnd.any(tlist);

    // Generate N queries (letters) using weighted next
    vector<char> queries;
    for (int i = 0; i < N; i++) {
        int idx = rnd.wnext(P, t);
        queries.push_back(start_letters[idx]);
    }

    // Output
    println(K, N);
    for (auto &w : words) println(w);
    for (char c : queries) println(c);

    return 0;
}
