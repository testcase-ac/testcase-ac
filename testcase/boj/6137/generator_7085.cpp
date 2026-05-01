#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of the string S
    int N = rnd.next(1, 30);
    vector<char> s(N);

    // Different generation scenarios for diversity
    vector<string> types = {
        "uniform",    // all same character
        "inc",        // non-decreasing sequence
        "dec",        // non-increasing sequence
        "pal",        // palindrome
        "rand_small", // random with small alphabet
        "rand_large"  // random with full alphabet
    };
    string type = rnd.any(types);

    if (type == "uniform") {
        char c = char(rnd.next('A', 'Z'));
        for (int i = 0; i < N; i++) s[i] = c;
    }
    else if (type == "inc") {
        for (int i = 0; i < N; i++) s[i] = char(rnd.next('A', 'Z'));
        sort(s.begin(), s.end());
    }
    else if (type == "dec") {
        for (int i = 0; i < N; i++) s[i] = char(rnd.next('A', 'Z'));
        sort(s.begin(), s.end(), greater<char>());
    }
    else if (type == "pal") {
        for (int i = 0; i < N/2; i++) {
            char c = char(rnd.next('A', 'Z'));
            s[i] = s[N-1-i] = c;
        }
        if (N % 2 == 1) {
            s[N/2] = char(rnd.next('A', 'Z'));
        }
    }
    else if (type == "rand_small") {
        int K = rnd.next(1, 3);
        char maxc = char('A' + K - 1);
        for (int i = 0; i < N; i++) {
            s[i] = char(rnd.next('A', maxc));
        }
    }
    else { // rand_large
        for (int i = 0; i < N; i++) {
            s[i] = char(rnd.next('A', 'Z'));
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%c\n", s[i]);
    }

    return 0;
}
