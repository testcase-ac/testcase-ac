#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of numbers
    int N = rnd.next(1, 50);
    const string letters = "ABCDEFGHIJ";

    // Choose one letter that will never appear as first character (so it can map to 0)
    int dropIdx = rnd.next(0, 9);
    char dropC = letters[dropIdx];

    // Build list of allowed first letters
    string firstLetters;
    for (char c : letters)
        if (c != dropC)
            firstLetters.push_back(c);

    println(N);
    for (int i = 0; i < N; i++) {
        // Choose distribution type for length: -1 (min‐biased), 0 (uniform), +1 (max‐biased)
        int wtype = rnd.next(0, 2) - 1;
        int len = rnd.wnext(12, wtype) + 1;  // length in [1..12]

        // Build the string
        string s;
        s.push_back(rnd.any(firstLetters));  // first letter cannot be dropC

        // With some chance, make the string uniform to test repeats
        bool uniform = rnd.next(0.0, 1.0) < 0.2;
        if (uniform) {
            char c = rnd.any(firstLetters);
            for (int j = 1; j < len; j++)
                s.push_back(c);
        } else {
            for (int j = 1; j < len; j++)
                s.push_back(rnd.any(letters));
        }

        println(s);
    }

    return 0;
}
