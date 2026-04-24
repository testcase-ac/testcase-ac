#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cases
    int T = rnd.next(5, 15);
    println(T);
    for (int i = 0; i < T; i++) {
        // First case: trivial 0+0
        if (i == 0) {
            println("0", "0");
            continue;
        }
        // Last case: maximal carry chain
        if (i == T - 1) {
            string s8(8, '1');
            println(s8, s8);
            continue;
        }
        // General cases
        // Random lengths up to 8
        int lenA = rnd.next(1, 8);
        int lenB = rnd.next(1, 8);
        // Bias for ones
        double p1_A = rnd.next(0.0, 1.0);
        double p1_B = rnd.next(0.0, 1.0);
        // Occasionally all zeros or all ones
        bool allZeroA = (rnd.next(0, 9) == 0);
        bool allOneA  = (!allZeroA && rnd.next(0, 9) == 0);
        bool allZeroB = (rnd.next(0, 9) == 0);
        bool allOneB  = (!allZeroB && rnd.next(0, 9) == 0);
        // Build strings
        string a, b;
        for (int j = 0; j < lenA; j++) {
            char c;
            if (allZeroA)      c = '0';
            else if (allOneA)  c = '1';
            else               c = (rnd.next() < p1_A ? '1' : '0');
            a.push_back(c);
        }
        for (int j = 0; j < lenB; j++) {
            char c;
            if (allZeroB)      c = '0';
            else if (allOneB)  c = '1';
            else               c = (rnd.next() < p1_B ? '1' : '0');
            b.push_back(c);
        }
        // Randomly add leading zeros
        if (rnd.next(0, 1) == 0) {
            int L = rnd.next(0, 3);
            a = string(L, '0') + a;
        }
        if (rnd.next(0, 1) == 0) {
            int L = rnd.next(0, 3);
            b = string(L, '0') + b;
        }
        println(a, b);
    }
    return 0;
}
