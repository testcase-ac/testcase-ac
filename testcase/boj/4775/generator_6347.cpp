#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

string genWord(int maxLen, double punctProb) {
    int len = rnd.next(1, maxLen);
    string w;
    static const string puncts = "-'";
    for (int i = 0; i < len; i++) {
        if (i > 0 && i < len - 1 && rnd.next() < punctProb) {
            w += puncts[rnd.next(0, (int)puncts.size() - 1)];
        } else {
            w += char('a' + rnd.next(0, 25));
        }
    }
    return w;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int D = rnd.next(1, 10);            // dictionary size
    int maxLen = rnd.next(1, 8);        // max word length
    double punctProb = rnd.next(0.0, 1.0);  // punctuation probability
    int E = rnd.next(1, 5);             // number of emails
    double unknownProb = rnd.next(0.0, 1.0); // prob of unknown word in email

    // Generate dictionary
    set<string> dictSet;
    vector<string> dict;
    while ((int)dict.size() < D) {
        string w = genWord(maxLen, punctProb);
        if (!dictSet.count(w)) {
            dictSet.insert(w);
            dict.push_back(w);
        }
    }

    // Output dictionary
    println(D);
    for (auto &w : dict) println(w);

    // Generate emails
    println(E);
    for (int ei = 0; ei < E; ei++) {
        int Nw = rnd.next(1, 8);  // words in this email
        for (int i = 0; i < Nw; i++) {
            if (rnd.next() < unknownProb) {
                // generate unknown word
                string w;
                do {
                    w = genWord(maxLen, punctProb);
                } while (dictSet.count(w));
                println(w);
            } else {
                // pick from dictionary
                println(dict[rnd.next(0, D - 1)]);
            }
        }
        // end of email marker
        println("-1");
    }

    return 0;
}
