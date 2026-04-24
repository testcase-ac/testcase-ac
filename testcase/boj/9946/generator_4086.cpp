#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    // Probability of same-case
    double pSame = rnd.next(0.0, 1.0);
    // Alphabet size hyperparameter
    int K = rnd.next(1, 26);
    string alphabet;
    for (int i = 0; i < K; i++)
        alphabet += char('a' + i);

    for (int tc = 0; tc < T; tc++) {
        // Generate original word length 1 to 10
        int L = rnd.next(1, 10);
        string s;
        for (int i = 0; i < L; i++)
            s += rnd.any(alphabet);

        // Decide whether the recovered multiset is same
        bool same = rnd.next() < pSame;
        string t = s;
        if (same) {
            // Shuffle to create a permutation
            shuffle(t.begin(), t.end());
        } else {
            // Choose allowable operations: 0=deletion,1=insertion,2=substitution
            vector<int> ops;
            if ((int)t.size() > 1) ops.push_back(0);
            ops.push_back(1);
            ops.push_back(2);
            int op = rnd.any(ops);
            if (op == 0) {
                // deletion, safe because t.size() > 1
                int pos = rnd.next(0, (int)t.size() - 1);
                t.erase(pos, 1);
            } else if (op == 1) {
                // insertion
                char c = rnd.any(alphabet);
                int pos = rnd.next(0, (int)t.size());
                t.insert(t.begin() + pos, c);
            } else {
                // substitution
                int pos = rnd.next(0, (int)t.size() - 1);
                char c;
                // if alphabet size >1, ensure change
                do {
                    c = rnd.any(alphabet);
                } while (K > 1 && c == t[pos]);
                t[pos] = c;
            }
        }
        // Output this test case
        println(s);
        println(t);
    }
    // End markers
    println("END");
    println("END");
    return 0;
}
