#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases T between 1 and 5
    int T = rnd.next(1, 5);
    println(T);

    const string ALPH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int tc = 0; tc < T; tc++) {
        // Choose how many distinct letters appear in S
        int distinct_cnt = rnd.next(1, 26);

        // Sample distinct letters
        vector<char> letters(ALPH.begin(), ALPH.end());
        shuffle(letters.begin(), letters.end());
        letters.resize(distinct_cnt);

        // Determine string length L between distinct_cnt and at most distinct_cnt+5 (cap at 26)
        int max_extra = min(5, 26 - distinct_cnt);
        int L = rnd.next(distinct_cnt, distinct_cnt + max_extra);

        // Build the string S by picking from the distinct letters (to allow repeats)
        string S;
        S.reserve(L);
        for (int i = 0; i < L; i++) {
            S.push_back(rnd.any(letters));
        }
        // Shuffle to mix repeats
        shuffle(S.begin(), S.end());

        // Output the string
        println(S);
    }

    return 0;
}
