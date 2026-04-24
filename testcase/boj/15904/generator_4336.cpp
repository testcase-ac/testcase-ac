#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    bool good = rnd.next(0, 1) == 1;
    int N = rnd.next(1, 10);
    if (good && N < 4) N = 4;
    vector<string> words(N);

    const string lows = "abcdefghijklmnopqrstuvwxyz";
    const string ups = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (good) {
        // choose positions for 'U','C','P','C'
        vector<int> pos(4);
        pos[0] = rnd.next(0, N - 4);
        pos[1] = rnd.next(pos[0] + 1, N - 3);
        pos[2] = rnd.next(pos[1] + 1, N - 2);
        pos[3] = rnd.next(pos[2] + 1, N - 1);
        char tgt[4] = {'U','C','P','C'};
        // fill words
        for (int i = 0; i < N; i++) {
            int L = rnd.next(1, 7);
            string w;
            w.reserve(L);
            int idx = -1;
            for (int k = 0; k < 4; k++) {
                if (pos[k] == i) { idx = k; break; }
            }
            int ins = -1;
            if (idx != -1) {
                ins = rnd.next(0, L - 1);
            }
            for (int j = 0; j < L; j++) {
                if (j == ins) {
                    w.push_back(tgt[idx]);
                } else {
                    // random letter, random case
                    if (rnd.next(0,1) == 1) {
                        w.push_back(rnd.any(ups));
                    } else {
                        w.push_back(rnd.any(lows));
                    }
                }
            }
            words[i] = w;
        }
    } else {
        // hate case: only lowercase, no uppercase => cannot form UCPC
        for (int i = 0; i < N; i++) {
            int L = rnd.next(1, 7);
            string w;
            w.reserve(L);
            for (int j = 0; j < L; j++) {
                w.push_back(rnd.any(lows));
            }
            words[i] = w;
        }
    }

    // join with single spaces, no leading/trailing
    string s;
    for (int i = 0; i < N; i++) {
        s += words[i];
        if (i + 1 < N) s += ' ';
    }
    println(s);
    return 0;
}
