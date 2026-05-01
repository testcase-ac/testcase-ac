#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Allowed characters except period
    string AL = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,";
    int caseType = rnd.next(0, 2);
    int N;
    string S;
    if (caseType == 0) {
        // Short case: N <= 25, output S directly
        N = rnd.next(2, 25);
        S.reserve(N);
        for (int i = 1; i < N; i++) {
            S += rnd.any(AL);
        }
        S += '.';
    } else if (caseType == 1) {
        // Long single-sentence case: N > 25, no internal periods (rule 2 applies)
        N = rnd.next(26, 50);
        S.reserve(N);
        for (int i = 1; i < N; i++) {
            S += rnd.any(AL);
        }
        S += '.';
    } else {
        // Long multi-sentence with a period in the cut region (rule 3 applies)
        N = rnd.next(26, 50);
        // Choose a period position p in [12, N-11]
        int p = rnd.next(12, N - 11);
        // First sentence length = p (including period), second = N-p
        int len1 = p;
        int len2 = N - p;
        S.reserve(N);
        // Build first sentence
        for (int i = 1; i < len1; i++) {
            S += rnd.any(AL);
        }
        S += '.';
        // Build second sentence
        for (int i = 1; i < len2; i++) {
            S += rnd.any(AL);
        }
        S += '.';
    }
    println(N);
    // Print the string S
    printf("%s\n", S.c_str());
    return 0;
}
