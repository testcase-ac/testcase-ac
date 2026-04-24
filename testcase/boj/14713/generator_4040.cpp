#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of parrots/sentences
    int N = rnd.next(1, 10);

    // Generate unique words pool
    set<string> used;
    auto genUniqueWord = [&]() {
        while (true) {
            int len = rnd.next(1, 5);
            string w;
            for (int i = 0; i < len; i++)
                w += char('a' + rnd.next(0, 25));
            if (!used.count(w)) {
                used.insert(w);
                return w;
            }
        }
    };

    // Generate each sentence S_i
    vector<vector<string>> S(N);
    for (int i = 0; i < N; i++) {
        // sentence length varied
        int slen = rnd.next(1, 5);
        for (int j = 0; j < slen; j++) {
            S[i].push_back(genUniqueWord());
        }
    }

    // Build a possible interleaving L
    vector<string> L;
    vector<vector<string>> copyS = S;
    while (true) {
        vector<int> nonempty;
        for (int i = 0; i < N; i++)
            if (!copyS[i].empty())
                nonempty.push_back(i);
        if (nonempty.empty()) break;
        int which = rnd.any(nonempty);
        L.push_back(copyS[which].front());
        copyS[which].erase(copyS[which].begin());
    }

    // Randomly decide to break the sequence to make it impossible
    bool makeImpossible = rnd.next(0, 1) == 0;
    if (makeImpossible) {
        // insert a completely new word not in any S_i
        string bad;
        do {
            int len = rnd.next(1, 5);
            bad.clear();
            for (int i = 0; i < len; i++)
                bad += char('a' + rnd.next(0, 25));
        } while (used.count(bad));
        int pos = rnd.next(0, (int)L.size());
        L.insert(L.begin() + pos, bad);
    }

    // Output
    println(N);
    for (auto &sent : S) {
        println(sent);
    }
    println(L);

    return 0;
}
