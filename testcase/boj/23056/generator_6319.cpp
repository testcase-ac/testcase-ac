#include "testlib.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose even number of classes N
    vector<int> Ns = {2, 4, 6, 8, 10};
    int N = rnd.any(Ns);
    int M = rnd.next(1, 10);

    // Determine number of registrations K
    int maxExtra = rnd.next(0, N);
    int maxPossible = N * M + maxExtra;
    int maxK = min(maxPossible, 30);
    int K = rnd.next(0, maxK);

    // Hyper-parameters for class selection and name lengths
    int t_class = rnd.next(-3, 3);
    int maxLen = rnd.next(1, 15);

    vector<pair<int, string>> regs;
    vector<unordered_set<string>> used(N + 1);

    for (int i = 0; i < K; i++) {
        int c = rnd.wnext(N, t_class) + 1;
        int t_len = rnd.next(-2, 2);
        int len = rnd.wnext(maxLen, t_len) + 1;
        string s;
        do {
            s.clear();
            for (int j = 0; j < len; j++) {
                char ch = char('a' + rnd.next(0, 25));
                s.push_back(ch);
            }
        } while (used[c].count(s));
        used[c].insert(s);
        regs.emplace_back(c, s);
    }

    // Output block and termination
    println(N, M);
    for (auto &p : regs) {
        println(p.first, p.second);
    }
    println(0, 0);

    return 0;
}
