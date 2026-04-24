#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters: score bounds
    int low = rnd.next(0, 70);
    int high = rnd.next(low + 1, 100);

    // Generate first student's scores
    vector<int> a(4), b(4);
    for (int i = 0; i < 4; i++) {
        a[i] = rnd.next(low, high);
    }
    int sumA = accumulate(a.begin(), a.end(), 0);
    int Smin = 4 * low;
    int Smax = 4 * high;

    // Decide relation between sumA and sumB
    double p = rnd.next(); // in [0,1)
    double pTie = 0.2, pLess = 0.6;
    if (p < pTie) {
        // Force tie
        b = a;
    } else if (p < pLess) {
        // Force sumB < sumA if possible, else > sumA
        if (sumA > Smin) {
            do {
                for (int i = 0; i < 4; i++)
                    b[i] = rnd.next(low, high);
            } while (accumulate(b.begin(), b.end(), 0) >= sumA);
        } else {
            // fallback to sumB > sumA
            do {
                for (int i = 0; i < 4; i++)
                    b[i] = rnd.next(low, high);
            } while (accumulate(b.begin(), b.end(), 0) <= sumA);
        }
    } else {
        // Force sumB > sumA if possible, else < sumA
        if (sumA < Smax) {
            do {
                for (int i = 0; i < 4; i++)
                    b[i] = rnd.next(low, high);
            } while (accumulate(b.begin(), b.end(), 0) <= sumA);
        } else {
            // fallback to sumB < sumA
            do {
                for (int i = 0; i < 4; i++)
                    b[i] = rnd.next(low, high);
            } while (accumulate(b.begin(), b.end(), 0) >= sumA);
        }
    }

    // Output two lines of scores
    println(a);
    println(b);
    return 0;
}
