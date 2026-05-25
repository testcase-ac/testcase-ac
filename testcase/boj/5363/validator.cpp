#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only says positive N; 100000 keeps total input around
    // the practical 10 MB scale from the validator-authoring policy.
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string sentence = inf.readLine();
        ensuref(!sentence.empty(), "sentence %d is empty", i);
        ensuref((int)sentence.size() <= 100,
                "sentence %d has length %d, maximum is 100",
                i, (int)sentence.size());
        ensuref(sentence.front() != ' ', "sentence %d has leading space", i);
        ensuref(sentence.back() != ' ', "sentence %d has trailing space", i);

        int words = 1;
        for (int j = 0; j < (int)sentence.size(); ++j) {
            unsigned char ch = static_cast<unsigned char>(sentence[j]);
            if (ch == ' ') {
                ensuref(j > 0 && sentence[j - 1] != ' ',
                        "sentence %d has repeated spaces", i);
                ++words;
            } else {
                ensuref(33 <= ch && ch <= 126,
                        "sentence %d contains non-printable or non-ASCII character at position %d",
                        i, j + 1);
            }
        }

        ensuref(words >= 3, "sentence %d has %d words, minimum is 3", i, words);
    }

    inf.readEof();
}
