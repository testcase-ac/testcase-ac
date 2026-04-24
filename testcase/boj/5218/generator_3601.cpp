#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases, at least 3 to cover special cases
    int T = rnd.next(3, 10);
    vector<pair<string,string>> cases;
    cases.reserve(T);

    // 1) Identical words case
    {
        int L = rnd.next(4, 20);
        string s, t;
        for (int i = 0; i < L; i++) {
            char c = char('A' + rnd.next(0, 25));
            s.push_back(c);
            t.push_back(c);
        }
        cases.emplace_back(s, t);
    }

    // 2) Ascending-only distances (y >= x)
    {
        int L = rnd.next(4, 20);
        string s, t;
        for (int i = 0; i < L; i++) {
            int idx = rnd.next(0, 25);
            int offset = rnd.next(0, 25 - idx);
            s.push_back(char('A' + idx));
            t.push_back(char('A' + idx + offset));
        }
        cases.emplace_back(s, t);
    }

    // 3) Wrap-around-only distances (y < x)
    {
        int L = rnd.next(4, 20);
        string s, t;
        for (int i = 0; i < L; i++) {
            int idx = rnd.next(1, 25); // ensure idx >= 1 so we can go below
            int offset = rnd.next(0, idx - 1);
            s.push_back(char('A' + idx));
            t.push_back(char('A' + offset));
        }
        cases.emplace_back(s, t);
    }

    // Remaining mixed cases
    for (int k = 3; k < T; k++) {
        int L = rnd.next(4, 20);
        string s, t;
        for (int i = 0; i < L; i++) {
            int idx = rnd.next(0, 25);
            s.push_back(char('A' + idx));
            // If idx == 0, force ascending; else choose with prob 0.5
            if (idx == 0 || rnd.next() < 0.5) {
                int offset = rnd.next(0, 25 - idx);
                t.push_back(char('A' + idx + offset));
            } else {
                int offset = rnd.next(0, idx - 1);
                t.push_back(char('A' + offset));
            }
        }
        cases.emplace_back(s, t);
    }

    // Output all cases
    println(T);
    for (auto &pr : cases) {
        println(pr.first, pr.second);
    }
    return 0;
}
