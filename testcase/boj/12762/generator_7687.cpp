#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N small enough for manual check, up to 20
    int N = rnd.next(1, 20);
    vector<int> a;

    // Select a pattern type for variability
    int t = rnd.next(0, 7);

    if (t == 0) {
        // Completely random heights
        a.resize(N);
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, 10000);
    } else if (t == 1) {
        // Strictly increasing
        int step = rnd.next(1, 10);
        int maxStart = 10000 - step * (N - 1);
        if (maxStart < 1) {
            step = 1;
            maxStart = 10000 - (N - 1);
        }
        int startH = rnd.next(1, maxStart);
        a.resize(N);
        for (int i = 0; i < N; i++)
            a[i] = startH + i * step;
    } else if (t == 2) {
        // Strictly decreasing
        int step = rnd.next(1, 10);
        int minStart = 1 + step * (N - 1);
        if (minStart > 10000) {
            step = 1;
            minStart = N;
        }
        int startH = rnd.next(minStart, 10000);
        a.resize(N);
        for (int i = 0; i < N; i++)
            a[i] = startH - i * step;
    } else if (t == 3) {
        // V-shape: decreasing then increasing
        int Ldec = rnd.next(1, N);
        int Linc = N - Ldec + 1;
        // decreasing part
        int stepDec = rnd.next(1, 5);
        int minStart = 1 + (Ldec - 1) * stepDec;
        if (minStart > 10000) {
            stepDec = 1;
            minStart = Ldec;
        }
        int startH = rnd.next(minStart, 10000);
        int base = startH - (Ldec - 1) * stepDec;
        // increasing step
        int stepInc = 1;
        if (Linc > 1) {
            int maxStep = (10000 - base) / (Linc - 1);
            if (maxStep < 1) maxStep = 1;
            stepInc = rnd.next(1, min(5, maxStep));
        }
        a.resize(N);
        for (int i = 0; i < Ldec; i++)
            a[i] = startH - i * stepDec;
        for (int j = 1; j < Linc; j++)
            a[Ldec - 1 + j] = base + j * stepInc;
    } else if (t == 4) {
        // Mountain: increasing then decreasing
        int Linc = rnd.next(1, N);
        int Ldec = N - Linc + 1;
        // increasing part
        int stepInc = rnd.next(1, 5);
        int maxStart = 10000 - stepInc * (Linc - 1);
        if (maxStart < 1) {
            stepInc = 1;
            maxStart = 10000 - (Linc - 1);
        }
        int startH = rnd.next(1, maxStart);
        int peak = startH + (Linc - 1) * stepInc;
        // decreasing step
        int stepDec = 1;
        if (Ldec > 1) {
            int maxStep = (peak - 1) / (Ldec - 1);
            if (maxStep < 1) maxStep = 1;
            stepDec = rnd.next(1, min(5, maxStep));
        }
        a.resize(N);
        for (int i = 0; i < Linc; i++)
            a[i] = startH + i * stepInc;
        for (int j = 1; j < Ldec; j++)
            a[Linc - 1 + j] = peak - j * stepDec;
    } else if (t == 5) {
        // Sawtooth: alternating high and low
        int lowH = rnd.next(1, 5000);
        int highH = rnd.next(lowH + 1, 10000);
        bool startHigh = rnd.next(0, 1) == 0;
        a.resize(N);
        for (int i = 0; i < N; i++) {
            bool isHigh = ((i % 2) == 0) == startHigh;
            a[i] = isHigh ? highH : lowH;
        }
    } else if (t == 6) {
        // Many duplicates
        a.resize(N);
        for (int i = 0; i < N; i++) {
            if (i > 0 && rnd.next() < 0.7)
                a[i] = a[i - 1];
            else
                a[i] = rnd.next(1, 10000);
        }
    } else {
        // All same
        int v = rnd.next(1, 10000);
        a.assign(N, v);
    }

    // Output
    println(N);
    println(a);

    return 0;
}
