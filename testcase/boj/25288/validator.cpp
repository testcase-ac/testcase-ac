#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    string alphabet = inf.readToken("[a-z]{1,26}", "alphabet");
    vector<bool> seen(26, false);
    for (int i = 0; i < (int)alphabet.size(); ++i) {
        int c = alphabet[i] - 'a';
        ensuref(!seen[c], "alphabet contains duplicate character '%c' at position %d", alphabet[i], i + 1);
        seen[c] = true;
    }
    inf.readEoln();

    inf.readEof();
}
