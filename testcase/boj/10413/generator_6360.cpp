#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Full and lowercase alphabets
    const string alphaLower = "abcdefghijklmnopqrstuvwxyz";
    const string alphaUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string alphaAll = alphaLower + alphaUpper;
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int tp = rnd.next(0, 5);
        string s;
        if (tp == 0) {
            // Random string from full alphabet
            int n = rnd.next(1, 20);
            for (int i = 0; i < n; i++)
                s += rnd.any(alphaAll);
        } else if (tp == 1) {
            // All same character
            int n = rnd.next(1, 20);
            char c = rnd.any(alphaLower);
            s = string(n, c);
        } else if (tp == 2) {
            // Alternating two distinct characters
            int n = rnd.next(1, 20);
            char c1 = rnd.any(alphaLower);
            char c2;
            do { c2 = rnd.any(alphaLower); } while (c2 == c1);
            for (int i = 0; i < n; i++)
                s += (i % 2 == 0 ? c1 : c2);
        } else if (tp == 3) {
            // Repeated block pattern
            int p = rnd.next(1, 5);
            string block;
            for (int i = 0; i < p; i++)
                block += rnd.any(alphaLower);
            int n = rnd.next(1, 20);
            while ((int)s.size() < n)
                s += block;
            s.resize(n);
        } else if (tp == 4) {
            // All distinct characters (no repeats)
            int n = rnd.next(1, min(26, 20));
            for (int i = 0; i < n; i++)
                s += alphaLower[i];
        } else {
            // Palindromic string
            int n = rnd.next(1, 20);
            int half = n / 2;
            string left;
            for (int i = 0; i < half; i++)
                left += rnd.any(alphaLower);
            s = left;
            if (n % 2 == 1)
                s += rnd.any(alphaLower);
            reverse(left.begin(), left.end());
            s += left;
        }
        println(s);
    }
    return 0;
}
