#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

bool is_pal(const string &s) {
    int n = s.size();
    for (int i = 0; i < n/2; i++)
        if (s[i] != s[n-1-i]) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for length bias
    vector<int> bias = {-2, -1, 0, 1, 2};
    int t_len = rnd.any(bias);
    int n = rnd.wnext(20, t_len) + 1;  // length in [1,20]

    // Hyper-parameter for alphabet size bias
    int t_alpha = rnd.any(bias);
    int k = rnd.wnext(26, t_alpha) + 1;  // number of distinct letters [1,26]
    char maxc = char('a' + k - 1);

    // Decide palindrome or not
    bool make_pal = rnd.next(0, 1) == 1;
    // If impossible to make non-palindrome, force palindrome
    if (n == 1 || k == 1) make_pal = true;

    string s(n, 'a');
    if (make_pal) {
        // build a palindrome
        for (int i = 0; i <= (n-1)/2; i++) {
            char c = rnd.next('a', maxc);
            s[i] = c;
            s[n-1-i] = c;
        }
    } else {
        // build a palindrome then introduce a mismatch
        for (int i = 0; i <= (n-1)/2; i++) {
            char c = rnd.next('a', maxc);
            s[i] = c;
            s[n-1-i] = c;
        }
        int pos = rnd.next(0, n-1);
        char orig = s[pos];
        char other;
        do {
            other = rnd.next('a', maxc);
        } while (other == orig);
        s[pos] = other;
    }

    // Output
    println(s);
    return 0;
}
