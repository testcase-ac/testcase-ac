#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string element(int a, int b) {
    return "a" + to_string(a) + "b" + to_string(b);
}

int pickExponent(int limit) {
    vector<int> edges = {0, 1, limit - 1};
    if (limit > 3) edges.push_back(limit / 2);

    if (rnd.next(0, 2) == 0) return rnd.any(edges);
    return rnd.next(0, limit - 1);
}

int pickModulus(int mode) {
    if (mode == 0) return 2;
    if (mode == 1) return rnd.next(2, 12);
    if (mode == 2) return rnd.next(13, 80);
    if (mode == 3) return rnd.any(vector<int>{97, 101, 499, 997, 1000});
    return rnd.next(2, 1000);
}

string problemId(int index) {
    vector<string> prefixes = {"C", "T", "Set", "P", "Mix"};
    return rnd.any(prefixes) + to_string(index);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int setCount = rnd.next(1, mode == 3 ? 4 : 3);

    for (int tc = 1; tc <= setCount; ++tc) {
        int m = pickModulus(mode);
        int n = pickModulus(rnd.next(0, 4));
        int p = rnd.next(1, mode == 3 ? 12 : 7);

        println(problemId(tc), m, n, p);

        for (int i = 0; i < p; ++i) {
            int a1 = pickExponent(m);
            int b1 = pickExponent(n);
            int a2 = pickExponent(m);
            int b2 = pickExponent(n);

            if (mode == 0 && i < 2) {
                a1 = i % m;
                b1 = i % n;
                a2 = (m - 1 + i) % m;
                b2 = (n - 1 + i) % n;
            } else if (mode == 1 && i % 3 == 0) {
                b1 = n - 1;
                a2 = rnd.next(1, m - 1);
            } else if (mode == 2 && i % 2 == 0) {
                a1 = rnd.any(vector<int>{0, m - 1});
                b2 = rnd.any(vector<int>{0, n - 1});
            }

            println(element(a1, b1), element(a2, b2));
        }
    }

    println("ZZ", 0, 0, 0);
    return 0;
}
