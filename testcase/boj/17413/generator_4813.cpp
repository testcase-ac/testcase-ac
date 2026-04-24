#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int T = rnd.next(0, 3);             // number of tags
    bool startWithTag = (T > 0 && rnd.next(2) == 0);
    double letterProb = rnd.next();     // prob to pick letter in words
    double tagSpaceProb = rnd.next();   // prob to pick space inside tags
    char maxWordChar = 'a' + rnd.next(0, 25);

    vector<bool> isTag;
    if (!startWithTag) {
        // TEXT, TAG, TEXT, TAG, ..., TEXT
        for (int i = 0; i < 2 * T + 1; i++) {
            isTag.push_back(i % 2 == 1);
        }
    } else {
        // TAG, TEXT, TAG, TEXT, ..., TEXT
        for (int i = 0; i < 2 * T; i++) {
            isTag.push_back(i % 2 == 0);
        }
    }

    string S;
    for (bool tag : isTag) {
        if (tag) {
            // generate a tag: "<...>"
            int lenC = rnd.next(1, 5);
            string content;
            for (int i = 0; i < lenC; i++) {
                if (rnd.next() < tagSpaceProb) {
                    content.push_back(' ');
                } else {
                    char c = 'a' + rnd.next(0, 25);
                    content.push_back(c);
                }
            }
            S.push_back('<');
            S += content;
            S.push_back('>');
        } else {
            // generate a text segment: one or more words
            int W = rnd.next(1, 3);
            for (int w = 0; w < W; w++) {
                int L = rnd.next(1, 5);
                for (int i = 0; i < L; i++) {
                    if (rnd.next() < letterProb) {
                        char c = rnd.next((int)'a', (int)maxWordChar);
                        S.push_back(c);
                    } else {
                        char d = '0' + rnd.next(0, 9);
                        S.push_back(d);
                    }
                }
                if (w + 1 < W) {
                    S.push_back(' ');
                }
            }
        }
    }

    // Output the single test string
    println(S);
    return 0;
}
