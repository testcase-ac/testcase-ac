#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 6000, "n");
    inf.readEoln();

    const string alphabet = "abcdefghi";
    for (int i = 0; i < n; ++i) {
        string word = inf.readToken("[a-i]{9}", "word");
        string sorted = word;
        sort(sorted.begin(), sorted.end());
        ensuref(sorted == alphabet, "word %d is not a permutation of %s: %s",
                i + 1, alphabet.c_str(), word.c_str());
        inf.readEoln();
    }

    inf.readEof();
}
