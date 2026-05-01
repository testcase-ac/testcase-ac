#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of lines
    int N = rnd.next(1, 10);
    // Partition into pure-letter, pure-digit, and mixed lines
    int num_letters = rnd.next(0, N);
    int num_digits = rnd.next(0, N - num_letters);
    int num_mixed = N - num_letters - num_digits;

    vector<string> lines;
    // Pure-letter lines
    for (int i = 0; i < num_letters; i++) {
        int L = rnd.next(1, 20);
        string s;
        for (int j = 0; j < L; j++)
            s += char('a' + rnd.next(0, 25));
        lines.push_back(s);
    }
    // Pure-digit lines
    for (int i = 0; i < num_digits; i++) {
        int L = rnd.next(1, 20);
        string s;
        for (int j = 0; j < L; j++)
            s += char('0' + rnd.next(0, 9));
        lines.push_back(s);
    }
    // Mixed lines
    for (int i = 0; i < num_mixed; i++) {
        int k = rnd.next(1, 3); // number of digit segments
        bool start_digit = rnd.next(0, 1);
        int total_segments = start_digit ? (2*k - 1) : (2*k);
        string s;
        for (int seg = 0; seg < total_segments; seg++) {
            bool is_digit_seg = (seg % 2 == 0) ? start_digit : !start_digit;
            if (is_digit_seg) {
                // maybe prefix zeros
                int pz = (rnd.next(0, 9) < 3 ? rnd.next(1, 3) : 0);
                for (int z = 0; z < pz; z++) s += '0';
                int dlen = rnd.next(1, 9);
                for (int d = 0; d < dlen; d++)
                    s += char('0' + rnd.next(0, 9));
            } else {
                int llen = rnd.next(1, 5);
                for (int c = 0; c < llen; c++)
                    s += char('a' + rnd.next(0, 25));
            }
        }
        lines.push_back(s);
    }

    // Shuffle lines to randomize order
    shuffle(lines.begin(), lines.end());

    // Output
    println(N);
    for (auto &l : lines)
        println(l);
    return 0;
}
