#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string genDyck(int n) {
    if (n == 1) return "ab";
    // decide whether to wrap or to concatenate
    if (rnd.next() < 0.5) {
        string s = genDyck(n - 1);
        return "a" + s + "b";
    } else {
        int k = rnd.next(1, n - 1);
        return genDyck(k) + genDyck(n - k);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int i = 0; i < T; i++) {
        // choose sizes n1 and n2 (number of pairs)
        int n1 = rnd.next(1, 5);
        bool useSameLen = rnd.next() < 0.8;  // 80% same length
        int n2;
        if (useSameLen) {
            n2 = n1;
        } else {
            // ensure different
            do {
                n2 = rnd.next(1, 5);
            } while (n2 == n1);
        }
        // generate A
        string A = genDyck(n1);
        // generate B
        string B;
        if (useSameLen && rnd.next() < 0.2) {
            // 20% chance B == A to test zero operations
            B = A;
        } else {
            B = genDyck(n2);
        }
        println(A, B);
    }
    return 0;
}
