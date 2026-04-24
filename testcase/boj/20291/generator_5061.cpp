#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Total files
    int N = rnd.next(1, 10);
    // Number of distinct extensions
    int K = rnd.next(1, min(N, 5));
    // Distribute counts: start with 1 each, then distribute N-K leftovers
    vector<int> cnt(K, 1);
    int rem = N - K;
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, K-1);
        cnt[idx]++;
    }
    // Generate unique extensions
    vector<string> exts;
    unordered_set<string> seen;
    for (int i = 0; i < K; i++) {
        string e;
        do {
            int L = rnd.next(1, 5);
            e.clear();
            for (int j = 0; j < L; j++) {
                char c = char('a' + rnd.next(0, 25));
                e.push_back(c);
            }
        } while (seen.count(e));
        seen.insert(e);
        exts.push_back(e);
    }
    // Generate file names
    vector<string> files;
    // Hyper-parameters for base name length
    int hi_base = rnd.next(3, 12);
    int t_base = rnd.next(-2, 2);
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            int Lb = rnd.wnext(hi_base, t_base) + 1;  // [1..hi_base]
            string s;
            s.reserve(Lb + 1 + exts[i].size());
            for (int x = 0; x < Lb; x++) {
                char c = char('a' + rnd.next(0, 25));
                s.push_back(c);
            }
            s.push_back('.');
            s += exts[i];
            files.push_back(s);
        }
    }
    // Shuffle file order for unpredictability
    shuffle(files.begin(), files.end());
    // Output
    println(N);
    for (auto &f : files) {
        println(f);
    }
    return 0;
}
