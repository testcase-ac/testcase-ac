#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small, hand-checkable length
    int N = rnd.next(1, 10);

    // Hyper-parameter for vowel probability (0.0 to 1.0, biased extremes or center)
    int t = rnd.next(-2, 2);
    int vp = rnd.wnext(11, t); // integer in [0,10], biased by t
    double p = vp / 10.0;

    // Prepare vowel and consonant pools
    const vector<char> vowels = {'a','e','i','o','u'};
    const string consonants = "bcdfghjklmnpqrstvwxyz";

    // Generation mode: 0 = random by p, 1 = alternating, 2 = block-wise
    int mode = rnd.next(0, 2);
    string s;
    s.reserve(N);

    if (mode == 0) {
        // Pure random each position
        for (int i = 0; i < N; i++) {
            if (rnd.next() < p)
                s.push_back(rnd.any(vowels));
            else
                s.push_back(consonants[rnd.next((int)consonants.size())]);
        }
    } else if (mode == 1) {
        // Alternating pattern
        bool startVowel = rnd.next(0, 1);
        for (int i = 0; i < N; i++) {
            bool wantV = (i % 2 == 0) ? startVowel : !startVowel;
            if (wantV)
                s.push_back(rnd.any(vowels));
            else
                s.push_back(consonants[rnd.next((int)consonants.size())]);
        }
    } else {
        // Block-wise: random block sizes of vowels/consonants
        bool curVowel = rnd.next(0, 1);
        int i = 0;
        while (i < N) {
            int maxBlock = max(1, N / 2);
            int bsz = rnd.next(1, maxBlock);
            for (int j = 0; j < bsz && i < N; j++, i++) {
                if (curVowel)
                    s.push_back(rnd.any(vowels));
                else
                    s.push_back(consonants[rnd.next((int)consonants.size())]);
            }
            curVowel = !curVowel;
        }
    }

    // Output the single test case
    println(s);
    return 0;
}
