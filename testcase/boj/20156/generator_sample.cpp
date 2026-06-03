#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    int m = rnd.next(0, 18);
    int k = rnd.next(4, 20);

    vector<int> mentor(n + 1, -1);

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            mentor[i] = i + 1;
        }
    } else if (mode == 1) {
        int root = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != root) {
                mentor[i] = root;
            }
        }
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());

        for (int pos = 1; pos < n; ++pos) {
            if (rnd.next(100) < (mode == 2 ? 70 : mode == 3 ? 45 : 85)) {
                int mentorPos = rnd.next(0, pos - 1);
                mentor[order[pos]] = order[mentorPos];
            }
        }
    }

    vector<int> rounds;
    rounds.reserve(m);
    for (int i = 0; i < m; ++i) {
        if (i > 0 && rnd.next(100) < 35) {
            rounds.push_back(rounds.back());
        } else if (rnd.next(100) < 65) {
            vector<int> candidates;
            for (int v = 1; v <= n; ++v) {
                if (mentor[v] != -1) {
                    candidates.push_back(v);
                }
            }
            rounds.push_back(candidates.empty() ? rnd.next(1, n) : rnd.any(candidates));
        } else {
            rounds.push_back(rnd.next(1, n));
        }
    }

    vector<int> notable;
    for (int v = 1; v <= n; ++v) {
        notable.push_back(v);
        if (mentor[v] != -1) {
            notable.push_back(mentor[v]);
        }
    }

    println(n, m, k);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            putchar(' ');
        }
        printf("%d", mentor[i]);
    }
    putchar('\n');

    for (int x : rounds) {
        println(x);
    }

    for (int i = 0; i < k; ++i) {
        int a;
        if (m == 0) {
            a = 0;
        } else if (i < 3) {
            a = i == 0 ? 0 : rnd.next(1, m);
        } else {
            a = rnd.next(0, m);
        }

        int b = rnd.any(notable);
        int c;
        if (rnd.next(100) < 25) {
            c = b;
        } else if (mentor[b] != -1 && rnd.next(100) < 55) {
            c = mentor[b];
        } else {
            c = rnd.any(notable);
        }
        println(a, b, c);
    }

    return 0;
}
