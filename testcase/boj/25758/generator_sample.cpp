#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string gene(char first, char second) {
    string s;
    s += first;
    s += second;
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> genes;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(2, 5);
        char a = char('A' + rnd.next(0, 25));
        char b = char('A' + rnd.next(0, 25));
        for (int i = 0; i < n; ++i) {
            genes.push_back(gene(a, b));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 12);
        char first = char('A' + rnd.next(0, 25));
        for (int i = 0; i < n; ++i) {
            char second = char('A' + rnd.next(0, 25));
            genes.push_back(gene(first, second));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 12);
        char second = char('A' + rnd.next(0, 25));
        for (int i = 0; i < n; ++i) {
            char first = char('A' + rnd.next(0, 25));
            genes.push_back(gene(first, second));
        }
    } else if (mode == 3) {
        int limit = rnd.next(2, 10);
        for (int i = 0; i < limit; ++i) {
            char c = char('A' + i);
            genes.push_back(gene(c, char('A' + rnd.next(0, limit - 1))));
        }
        for (int i = 0; i < limit; ++i) {
            char c = char('A' + i);
            genes.push_back(gene(char('A' + rnd.next(0, limit - 1)), c));
        }
        shuffle(genes.begin(), genes.end());
        genes.resize(rnd.next(2, (int)genes.size()));
    } else if (mode == 4) {
        int n = rnd.next(2, 30);
        int lo = rnd.next(0, 20);
        int hi = rnd.next(lo, 25);
        for (int i = 0; i < n; ++i) {
            genes.push_back(gene(char('A' + rnd.next(lo, hi)), char('A' + rnd.next(lo, hi))));
        }
    } else {
        int n = rnd.next(2, 80);
        int alphabet = rnd.next(2, 26);
        vector<string> pool;
        for (int i = 0; i < alphabet; ++i) {
            for (int j = 0; j < alphabet; ++j) {
                if (rnd.next(0, 3) != 0) {
                    pool.push_back(gene(char('A' + i), char('A' + j)));
                }
            }
        }
        if (pool.empty()) {
            pool.push_back("AA");
        }
        for (int i = 0; i < n; ++i) {
            genes.push_back(rnd.any(pool));
        }
    }

    println((int)genes.size());
    println(genes);

    return 0;
}
