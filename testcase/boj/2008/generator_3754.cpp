#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N to get small, medium, large
    double r = rnd.next();
    int N;
    if (r < 0.20)          N = rnd.next(1, 3);
    else if (r < 0.60)     N = rnd.next(4, 7);
    else if (r < 0.90)     N = rnd.next(8, 10);
    else                   N = rnd.next(1, 10);

    // Compute maximum possible horizontal lines (but cap to 10)
    int limitM = 0;
    if (N > 1) {
        limitM = min(N * (N - 1) / 2, 10);
    }

    // Hyper-parameter for M
    int M;
    if (limitM == 0) {
        M = 0;
    } else {
        double r2 = rnd.next();
        if (r2 < 0.20)             M = 0;
        else if (r2 < 0.40)        M = 1;
        else if (r2 < 0.60)        M = rnd.next(1, min(3, limitM));
        else if (r2 < 0.80)        M = rnd.next(max(0, limitM - 3), limitM);
        else                       M = rnd.next(0, limitM);
    }

    // Start and end columns
    int a = rnd.next(1, N);
    int b = rnd.next(1, N);

    // Costs X (delete) and Y (add), with cases X=Y, X>Y, X<Y
    int X, Y;
    double r3 = rnd.next();
    if (r3 < 0.33) {
        X = rnd.next(0, 500);
        Y = X;
    } else if (r3 < 0.66) {
        X = rnd.next(0, 500);
        Y = rnd.next(0, X);
    } else {
        Y = rnd.next(0, 500);
        X = rnd.next(0, Y);
    }

    // Generate existing horizontal lines
    vector<int> p;
    p.reserve(M);
    for (int i = 0; i < M; i++) {
        double t = rnd.next();
        int val;
        if (t < 0.20)           val = rnd.wnext(N - 1, -1) + 1;  // bias left
        else if (t < 0.40)      val = rnd.wnext(N - 1, 1) + 1;   // bias right
        else                    val = rnd.next(1, N - 1);       // uniform
        p.push_back(val);
    }

    // Shuffle the order of lines (heights)
    shuffle(p.begin(), p.end());

    // Output
    println(N, M);
    println(a, b, X, Y);
    for (int v : p) {
        println(v);
    }

    return 0;
}
