#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int patternType = rnd.next(0, 3);
    int N;
    string S;
    if (patternType == 0) {
        // Minimal case N=1
        N = 1;
        S.push_back(rnd.any(string("UDLR")));
    } else if (patternType == 1) {
        // Small N, net zero displacement
        N = rnd.next(2, 10);
        vector<char> seq;
        for (int i = 0; i < N - 1; ++i)
            seq.push_back(rnd.any(string("UDLR")));
        int dx = 0, dy = 0;
        for (char c : seq) {
            if (c == 'U') dy++;
            else if (c == 'D') dy--;
            else if (c == 'L') dx--;
            else dx++;
        }
        char last;
        if (dx > 0) last = 'L';
        else if (dx < 0) last = 'R';
        else if (dy > 0) last = 'D';
        else if (dy < 0) last = 'U';
        else last = rnd.any(string("UDLR"));
        seq.push_back(last);
        S = string(seq.begin(), seq.end());
    } else if (patternType == 2) {
        // Small N, net non-zero displacement
        do {
            N = rnd.next(2, 10);
            S.clear();
            for (int i = 0; i < N; ++i)
                S.push_back(rnd.any(string("UDLR")));
            int dx = 0, dy = 0;
            for (char c : S) {
                if (c == 'U') dy++;
                else if (c == 'D') dy--;
                else if (c == 'L') dx--;
                else dx++;
            }
            if (dx != 0 || dy != 0) break;
        } while (true);
    } else {
        // Larger random S
        N = rnd.next(20, 2000);
        S.clear();
        for (int i = 0; i < N; ++i)
            S.push_back(rnd.any(string("UDLR")));
    }
    // Choose K with varied scales
    int kType = rnd.next(0, 2);
    int K;
    if (kType == 0) {
        K = rnd.next(1, 5);
    } else if (kType == 1) {
        K = rnd.next(6, 1000000);
    } else {
        K = rnd.next(100000000, 1000000000);
    }
    println(N, K);
    printf("%s\n", S.c_str());
    return 0;
}
