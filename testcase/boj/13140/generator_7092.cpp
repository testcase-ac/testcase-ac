#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    bool solvable = rnd.next(0, 1) == 0;
    if (solvable) {
        // Generate a valid mapping for HELLO + WORLD = N
        vector<int> nonzero;
        for (int i = 1; i <= 9; ++i) nonzero.push_back(i);
        shuffle(nonzero.begin(), nonzero.end());
        int h = nonzero[0], w = nonzero[1];

        vector<int> rem;
        for (int i = 0; i <= 9; ++i)
            if (i != h && i != w)
                rem.push_back(i);
        shuffle(rem.begin(), rem.end());
        int e = rem[0], l = rem[1], o = rem[2], r = rem[3], d = rem[4];

        long long hello = h*10000 + e*1000 + l*100 + l*10 + o;
        long long world = w*10000 + o*1000 + r*100 + l*10 + d;
        long long N = hello + world;
        println(N);
    } else {
        // Generate an N with no solution: outside possible sum range [20000,199998]
        bool small = rnd.next(0, 1) == 0;
        int N;
        if (small) {
            N = rnd.next(1, 19999);
        } else {
            N = rnd.next(200000, 999999);
        }
        println(N);
    }

    return 0;
}
