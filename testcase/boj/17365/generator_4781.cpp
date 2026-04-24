#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int N = rnd.next(1, 10);                    // total dictionary size
    int A = rnd.next(1, min(4, N));             // alphabet size
    int maxWordLen = rnd.next(1, 3);            // maximum distinct word length

    // build alphabet
    vector<char> letters;
    for (char c = 'a'; c <= 'z'; ++c) letters.push_back(c);
    shuffle(letters.begin(), letters.end());
    letters.resize(A);

    // generate all possible words up to length maxWordLen
    vector<string> possible;
    function<void(string,int)> dfs = [&](string pref, int rem) {
        if (rem == 0) return;
        for (char c : letters) {
            string t = pref + c;
            possible.push_back(t);
            dfs(t, rem - 1);
        }
    };
    dfs("", maxWordLen);

    // choose number of distinct words
    int maxK = min((int)possible.size(), N);
    int K = rnd.next(1, maxK);

    // sample distinct words
    shuffle(possible.begin(), possible.end());
    vector<string> distinct(possible.begin(), possible.begin() + K);

    // build dictionary with duplicates
    vector<string> dictWords = distinct;
    while ((int)dictWords.size() < N) {
        dictWords.push_back(rnd.any(distinct));
    }
    shuffle(dictWords.begin(), dictWords.end());

    // decide feasibility
    bool feasible = rnd.next(0, 1);

    // build target string
    string target;
    const int maxTargetLen = 20;
    if (feasible) {
        int segs = rnd.next(1, 5);
        for (int i = 0; i < segs; ++i) {
            string w = rnd.any(distinct);
            int take = rnd.next(1, (int)w.size());
            if ((int)target.size() + take > maxTargetLen) break;
            target += w.substr(0, take);
        }
        if (target.empty()) {
            string w = distinct[0];
            int take = rnd.next(1, (int)w.size());
            target = w.substr(0, take);
        }
    } else {
        int L = rnd.next(1, maxTargetLen);
        for (int i = 0; i < L; ++i)
            target.push_back(rnd.any(letters));
    }

    // output
    println(N);
    for (auto &w : dictWords) println(w);
    println(target);

    return 0;
}
