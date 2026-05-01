#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N between 1 and 30
    int N = rnd.next(1, 30);
    vector<int> a(N);
    // Choose a scenario for distribution
    int type = rnd.next(0, 4);
    if (type == 0) {
        // Mostly small positives, few negatives
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.8) a[i] = rnd.next(1, 10);
            else a[i] = rnd.next(-10, -1);
        }
    } else if (type == 1) {
        // Mostly small negatives, few positives
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.8) a[i] = rnd.next(-10, -1);
            else a[i] = rnd.next(1, 10);
        }
    } else if (type == 2) {
        // Wide uniform range
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(-10000, 10000);
        }
    } else if (type == 3) {
        // Mix with zeros and medium values
        for (int i = 0; i < N; i++) {
            double p = rnd.next();
            if (p < 0.1) a[i] = 0;
            else if (p < 0.55) a[i] = rnd.next(1, 100);
            else a[i] = rnd.next(-100, -1);
        }
    } else {
        // Alternating large positives and negatives
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) a[i] = rnd.next(5000, 10000);
            else a[i] = rnd.next(-10000, -5000);
        }
    }
    // Output
    println(N);
    println(a);
    return 0;
}
