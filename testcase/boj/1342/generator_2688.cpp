#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // length of the string: 1 to 10
    int L = rnd.next(1, 10);
    // alphabet size: 1 to min(5, L)
    int A = rnd.next(1, min(5, L));
    vector<char> alph;
    for (int i = 0; i < A; ++i) {
        alph.push_back(char('a' + i));
    }

    string s;
    // 20% chance to generate a fully distinct string (if possible)
    if (rnd.next() < 0.2 && A >= L) {
        shuffle(alph.begin(), alph.end());
        s = string(alph.begin(), alph.begin() + L);
    } else {
        // otherwise build string with some randomness and occasional repeats
        for (int i = 0; i < L; ++i) {
            if (!s.empty() && rnd.next() < 0.2) {
                // repeat the previous character to introduce runs
                s.push_back(s.back());
            } else {
                // pick one from the alphabet
                s.push_back(rnd.any(alph));
            }
        }
    }

    // sometimes shuffle the whole string to mix repeats
    if (rnd.next() < 0.3) {
        shuffle(s.begin(), s.end());
    }

    // output the generated string
    println(s);
    return 0;
}
