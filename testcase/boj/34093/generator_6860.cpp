#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 9);
    println(T);
    vector<string> types = {"random", "sorted", "rev", "rotated"};
    for (int tc = 0; tc < T; tc++) {
        int N = rnd.next(2, 12);
        int t = rnd.next(1, N);
        int minOps = N - 1;
        int a, b;
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            a = 0;
            b = minOps;
        } else if (mode == 1) {
            a = minOps;
            b = 0;
        } else {
            a = rnd.next(0, minOps);
            b = rnd.next(max(0, minOps - a), minOps);
        }
        println(N, t, a, b);
        vector<int> A(N);
        for (int i = 0; i < N; i++) A[i] = i + 1;
        string tp = rnd.any(types);
        if (tp == "sorted") {
            // already sorted
        } else if (tp == "rev") {
            reverse(A.begin(), A.end());
        } else if (tp == "rotated") {
            int rot = rnd.next(0, N - 1);
            rotate(A.begin(), A.begin() + rot, A.end());
        } else {
            shuffle(A.begin(), A.end());
        }
        println(A);
    }
    return 0;
}
