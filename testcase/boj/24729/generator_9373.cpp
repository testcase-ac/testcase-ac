#include "testlib.h"
using namespace std;

void genYesTwoValues(vector<int>& a, int& N) {
    int k = rnd.next(1, 15); // N in [2,30], even
    N = 2 * k;
    int A = rnd.next(1, 50);
    int B = A + 1;
    a.clear();
    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0) a.push_back(A);
        else a.push_back(B);
    }
    shuffle(a.begin(), a.end());
}

void genYesThreeValues(vector<int>& a, int& N) {
    int k = rnd.next(1, 7); // N in [4,28], multiple of 4
    N = 4 * k;
    int A = rnd.next(1, 48); // A, A+1, A+2 <= 50
    a.clear();
    // base pattern: A, A+1, A+2, A+1 is a valid cycle of length 4
    for (int i = 0; i < k; ++i) {
        a.push_back(A);
        a.push_back(A + 1);
        a.push_back(A + 2);
        a.push_back(A + 1);
    }
    shuffle(a.begin(), a.end());
}

void genYesClosedWalk(vector<int>& a, int& N) {
    // General closed walk on integer line with step +/-1, forming a cycle
    int L = 2 * rnd.next(1, 15); // even length in [2,30]
    N = L;

    vector<int> step(L);
    int half = L / 2;
    for (int i = 0; i < L; ++i)
        step[i] = (i < half ? 1 : -1);
    shuffle(step.begin(), step.end());

    vector<int> x(L);
    x[0] = 0;
    for (int i = 1; i < L; ++i)
        x[i] = x[i - 1] + step[i - 1];
    // step[L-1] is used for the closing edge back to x[0], sum of all step = 0

    int mn = x[0], mx = x[0];
    for (int v : x) {
        if (v < mn) mn = v;
        if (v > mx) mx = v;
    }

    int shift = rnd.next(1, 50) - mn; // ensures all values >= 1 and small
    a.resize(L);
    for (int i = 0; i < L; ++i)
        a[i] = x[i] + shift;

    shuffle(a.begin(), a.end()); // multiset unchanged, still YES
}

void genNoAllEqual(vector<int>& a, int& N) {
    N = rnd.next(1, 30);
    int x = rnd.next(1, 100000);
    a.assign(N, x);
}

void genNoGapTwoApart(vector<int>& a, int& N) {
    N = rnd.next(2, 30);
    int A = rnd.next(1, 99998); // A+2 <= 100000
    int B = A + 2;
    a.clear();
    for (int i = 0; i < N; ++i) {
        a.push_back(rnd.next(0, 1) == 0 ? A : B);
    }
}

void genRandomSmall(vector<int>& a, int& N) {
    N = rnd.next(1, 30);
    a.clear();
    for (int i = 0; i < N; ++i)
        a.push_back(rnd.next(1, 20));
}

void genRandomLargeValues(vector<int>& a, int& N) {
    N = rnd.next(2, 25);
    a.clear();
    int base = rnd.next(50000, 99980);
    for (int i = 0; i < N; ++i)
        a.push_back(base + rnd.next(0, 20)); // stay <= 100000
}

void genSingleElement(vector<int>& a, int& N) {
    N = 1;
    a.clear();
    a.push_back(rnd.next(1, 100000));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int N = 0;

    int type = rnd.next(1, 8); // choose scenario type 1..8

    switch (type) {
        case 1:
            genYesTwoValues(a, N);
            break;
        case 2:
            genYesThreeValues(a, N);
            break;
        case 3:
            genYesClosedWalk(a, N);
            break;
        case 4:
            genNoAllEqual(a, N);
            break;
        case 5:
            genNoGapTwoApart(a, N);
            break;
        case 6:
            genRandomSmall(a, N);
            break;
        case 7:
            genRandomLargeValues(a, N);
            break;
        case 8:
        default:
            genSingleElement(a, N);
            break;
    }

    println(N);
    println(a);

    return 0;
}
