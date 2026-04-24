#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int alphaSize = rnd.next(2, 26);            // alphabet size
    double hitProb = rnd.next(30, 70) / 100.0;  // probability query exists
    int N = rnd.next(2, 10);                    // number of dictionary words
    int Q = rnd.next(1, 10);                    // number of queries

    // Build alphabet
    string alphabet;
    for (int i = 0; i < alphaSize; i++) alphabet.push_back('a' + i);

    // Length distribution modes: 0 = uniform, 1 = weighted toward small
    int lenMode = rnd.next(0, 1);

    auto genLen = [&]() {
        if (lenMode == 0) {
            return rnd.next(1, 10);
        } else {
            // weighted: more small lengths
            return rnd.wnext(10, -2) + 1;
        }
    };

    // Generate unique dictionary
    set<string> dict;
    while ((int)dict.size() < N) {
        int L = genLen();
        string w;
        for (int i = 0; i < L; i++)
            w.push_back(rnd.any(alphabet));
        dict.insert(w);
    }
    vector<string> words(dict.begin(), dict.end());

    // Output dictionary
    println(N);
    for (auto &w : words) println(w);

    // Generate queries
    println(Q);
    for (int i = 0; i < Q; i++) {
        string q;
        if (rnd.next() < hitProb && !words.empty()) {
            // pick existing
            q = rnd.any(words);
        } else {
            // new word, ensure not in dict
            do {
                int L = genLen();
                q.clear();
                for (int j = 0; j < L; j++)
                    q.push_back(rnd.any(alphabet));
            } while (dict.count(q));
        }
        println(q);
    }

    return 0;
}
