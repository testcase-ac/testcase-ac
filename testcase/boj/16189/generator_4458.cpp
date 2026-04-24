#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: length of s
    int n = rnd.next(1, 10);
    // Hyper-parameter: alphabet size (1 means only 'a', >1 allows non-palindromes)
    int alpha = rnd.next(1, 3);
    // Decide whether to make s palindrome
    bool make_pal = rnd.next() < 0.5;
    // Force palindrome when impossible to make non-palindrome
    if (n == 1 || alpha == 1) make_pal = true;

    string s(n, 'a');
    if (make_pal) {
        // Build a palindrome
        for (int i = 0; i <= (n - 1) / 2; i++) {
            char c = char('a' + rnd.next(0, alpha - 1));
            s[i] = c;
            s[n - 1 - i] = c;
        }
    } else {
        // Build a random non-palindrome
        auto is_pal = [&](const string& t) {
            for (int i = 0; i < n / 2; i++)
                if (t[i] != t[n - 1 - i])
                    return false;
            return true;
        };
        do {
            for (int i = 0; i < n; i++) {
                s[i] = char('a' + rnd.next(alpha));
            }
        } while (is_pal(s));
    }

    // Hyper-parameter for k
    long long k;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = rnd.next(2LL, 10LL);
    } else {
        // Large k near the upper bound
        k = rnd.next(100000000000000000LL, 1000000000000000000LL);
    }

    // Output the test case
    println(s);
    println(k);
    return 0;
}
