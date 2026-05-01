#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N small to medium for manual verification
    int N = rnd.next(1, 30);

    // Generate A's schedule with hyper-parameter variety
    string A(N, '0'), B(N, '0');
    int typeA = rnd.next(0, 3);
    if (typeA == 0) {
        // random density
        double d = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++)
            if (rnd.next() < d) A[i] = '1';
    } else if (typeA == 1) {
        // single continuous block
        int len = rnd.next(1, N);
        int st = rnd.next(0, N - len);
        for (int i = st; i < st + len; i++) A[i] = '1';
    } else if (typeA == 2) {
        // two blocks
        int len1 = rnd.next(1, N), len2 = rnd.next(1, N);
        int st1 = rnd.next(0, N - len1), st2 = rnd.next(0, N - len2);
        for (int i = st1; i < st1 + len1; i++) A[i] = '1';
        for (int i = st2; i < st2 + len2; i++) A[i] = '1';
    } else {
        // alternating pattern
        int start0 = rnd.next(0, 1);
        for (int i = 0; i < N; i++)
            A[i] = ((i + start0) % 2) ? '1' : '0';
    }

    // Generate B's schedule similarly
    int typeB = rnd.next(0, 3);
    if (typeB == 0) {
        double d = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++)
            if (rnd.next() < d) B[i] = '1';
    } else if (typeB == 1) {
        int len = rnd.next(1, N);
        int st = rnd.next(0, N - len);
        for (int i = st; i < st + len; i++) B[i] = '1';
    } else if (typeB == 2) {
        int len1 = rnd.next(1, N), len2 = rnd.next(1, N);
        int st1 = rnd.next(0, N - len1), st2 = rnd.next(0, N - len2);
        for (int i = st1; i < st1 + len1; i++) B[i] = '1';
        for (int i = st2; i < st2 + len2; i++) B[i] = '1';
    } else {
        int start0 = rnd.next(0, 1);
        for (int i = 0; i < N; i++)
            B[i] = ((i + start0) % 2) ? '1' : '0';
    }

    // Generate ticket prices with different relative orderings
    int p1, p3, p5, p_pair;
    int typeP = rnd.next(0, 3);
    if (typeP == 0) {
        // non-decreasing 1-day,3-day,5-day
        p1 = rnd.next(1, 1000);
        p3 = p1 + rnd.next(0, 1000);
        p5 = p3 + rnd.next(0, 1000);
        p_pair = rnd.next(1, 1000);
    } else if (typeP == 1) {
        // non-increasing 1-day,3-day,5-day
        p1 = rnd.next(2001, 3000);
        p3 = rnd.next(1001, 2000);
        p5 = rnd.next(1, 1000);
        p_pair = rnd.next(1001, 2000);
    } else if (typeP == 2) {
        // pair ticket cheapest
        p_pair = rnd.next(1, 100);
        p1 = rnd.next(p_pair, p_pair + 1000);
        p3 = rnd.next(p_pair, p_pair + 1000);
        p5 = rnd.next(p_pair, p_pair + 1000);
    } else {
        // fully random
        p1 = rnd.next(1, 10000);
        p3 = rnd.next(1, 10000);
        p5 = rnd.next(1, 10000);
        p_pair = rnd.next(1, 10000);
    }

    // Output the test case
    println(N);
    printf("%s\n", A.c_str());
    printf("%s\n", B.c_str());
    println(p1, p3, p5, p_pair);

    return 0;
}
