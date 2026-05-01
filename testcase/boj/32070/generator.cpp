#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 2);
    if (scenario == 0) {
        // Trivial: all pairs already matched
        int N = rnd.next(1, 5);
        println(N);
        for (int i = 1; i <= N; i++)
            println(i, i);
    } else if (scenario == 1) {
        // Impossible: pick one color c with both in bottom
        int N = rnd.next(2, 8);
        vector<int> cols(N);
        iota(cols.begin(), cols.end(), 1);
        int c = rnd.any(cols);
        vector<int> others;
        for (int x : cols) if (x != c) others.push_back(x);
        int d = rnd.any(others);
        // Build bottom list: two c's and one of each other except d
        vector<int> B;
        B.push_back(c);
        B.push_back(c);
        for (int x : cols) if (x != c && x != d) B.push_back(x);
        // Build top list: two d's and one of each other except c
        vector<int> A;
        A.push_back(d);
        A.push_back(d);
        for (int x : cols) if (x != c && x != d) A.push_back(x);
        shuffle(A.begin(), A.end());
        shuffle(B.begin(), B.end());
        println(N);
        for (int i = 0; i < N; i++) {
            println(A[i], B[i]);
        }
    } else {
        // Solvable random: one top and one bottom per color
        int N = rnd.next(1, 8);
        vector<int> cols(N);
        iota(cols.begin(), cols.end(), 1);
        vector<int> A = cols, B = cols;
        shuffle(A.begin(), A.end());
        shuffle(B.begin(), B.end());
        println(N);
        for (int i = 0; i < N; i++)
            println(A[i], B[i]);
    }

    return 0;
}
