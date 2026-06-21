#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int beadCount(const string& s) {
    int count = 0;
    for (char c : s) {
        count += c == 'O';
    }
    return count;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 30);
    int q = rnd.next(1, 45);
    string s(n, 'X');

    if (mode == 0) {
        int beads = rnd.next(1, min(n, 4));
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < beads; ++i) {
            s[pos[i]] = 'O';
        }
    } else if (mode == 1) {
        int empties = rnd.next(0, min(n - 1, 5));
        s.assign(n, 'O');
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < empties; ++i) {
            s[pos[i]] = 'X';
        }
    } else if (mode == 2) {
        int len = rnd.next(1, n);
        int start = rnd.next(0, n - len);
        for (int i = start; i < start + len; ++i) {
            s[i] = 'O';
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            s[i] = (i % 2 == rnd.next(2) ? 'O' : 'X');
        }
        if (beadCount(s) == 0) {
            s[rnd.next(n)] = 'O';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 35) {
                s[i] = 'O';
            }
        }
        if (beadCount(s) == 0) {
            s[rnd.next(n)] = 'O';
        }
    }

    string initial = s;
    string state = s;
    vector<int> queries;
    int beads = beadCount(state);
    for (int i = 0; i < q; ++i) {
        vector<int> candidates;
        for (int j = 0; j < n; ++j) {
            if (state[j] == 'X' || beads > 1) {
                candidates.push_back(j);
            }
        }

        int k;
        if (i > 0 && rnd.next(100) < 30) {
            int previous = queries.back() - 1;
            if (state[previous] == 'X' || beads > 1) {
                k = previous;
            } else {
                k = rnd.any(candidates);
            }
        } else {
            k = rnd.any(candidates);
        }

        if (state[k] == 'O') {
            state[k] = 'X';
            --beads;
        } else {
            state[k] = 'O';
            ++beads;
        }
        queries.push_back(k + 1);
    }

    println(n);
    println(initial);
    println(q);
    for (int k : queries) {
        println(k);
    }

    return 0;
}
