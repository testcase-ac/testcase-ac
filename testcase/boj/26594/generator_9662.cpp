#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We will generate a string formed by K distinct uppercase letters,
    // each appearing exactly N times consecutively.
    // Total length kept reasonably small for manual checking.

    int scenario = rnd.next(0, 5); // 6 different styles: 0..5

    int N = 1; // repetition count
    int K = 1; // number of distinct letters

    vector<char> letters;
    for (char c = 'A'; c <= 'Z'; ++c) letters.push_back(c);

    vector<char> chosen;

    if (scenario == 0) {
        // Very small, simple, contiguous letters from 'A'
        N = rnd.next(1, 3);
        K = rnd.next(1, 5);
        int start = rnd.next(0, 26 - K);
        for (int i = 0; i < K; ++i)
            chosen.push_back(char('A' + start + i));
    } else if (scenario == 1) {
        // Medium size, contiguous letters
        N = rnd.next(2, 10);
        int maxK = min(20, 200 / N);
        if (maxK < 2) maxK = 2;
        K = rnd.next(2, maxK);
        int start = rnd.next(0, 26 - K);
        for (int i = 0; i < K; ++i)
            chosen.push_back(char('A' + start + i));
    } else if (scenario == 2) {
        // N = 1, many distinct letters (edge: no repetition per letter)
        N = 1;
        K = rnd.next(1, 26);
        int start = rnd.next(0, 26 - K);
        for (int i = 0; i < K; ++i)
            chosen.push_back(char('A' + start + i));
    } else if (scenario == 3) {
        // Single letter repeated many times (edge: only one run)
        K = 1;
        N = rnd.next(1, 200);
        char c = rnd.any(letters);
        chosen.push_back(c);
    } else if (scenario == 4) {
        // Random subset of letters in random order, small to medium N
        N = rnd.next(2, 8);
        int maxK = min(15, 200 / N);
        if (maxK < 1) maxK = 1;
        K = rnd.next(1, maxK);
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < K; ++i)
            chosen.push_back(letters[i]);
    } else if (scenario == 5) {
        // Longer but still readable: many distinct letters, moderate N
        K = rnd.next(10, 26);
        int maxN = max(2, 480 / K); // ensure total length <= 480
        N = rnd.next(2, maxN);
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < K; ++i)
            chosen.push_back(letters[i]);
    }

    // Build the final string
    string s;
    s.reserve(N * K);
    for (char c : chosen) {
        for (int i = 0; i < N; ++i)
            s.push_back(c);
    }

    // Safety: ensure not exceeding around 500 chars (problem requirement hint)
    if ((int)s.size() > 500) {
        // Fallback to a small simple case
        s.clear();
        N = 3;
        chosen.clear();
        chosen.push_back('Z');
        chosen.push_back('O');
        chosen.push_back('A');
        chosen.push_back('C'); // example-like "ZZZOOOAAACCC"
        for (char c : chosen)
            for (int i = 0; i < N; ++i)
                s.push_back(c);
    }

    println(s);

    return 0;
}
