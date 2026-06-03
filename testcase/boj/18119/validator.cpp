#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string word = inf.readToken("[a-z]{1,1000}", "word");
        inf.readEoln();
    }

    vector<bool> remembered(26, true);
    for (int i = 0; i < m; ++i) {
        int o = inf.readInt(1, 2, "o");
        inf.readSpace();
        string token = inf.readToken("[a-z]", "x");
        inf.readEoln();

        char x = token[0];
        int index = x - 'a';
        ensuref(!isVowel(x), "query %d uses vowel %c, but vowels are never forgotten", i + 1, x);

        if (o == 1) {
            ensuref(remembered[index], "query %d forgets already forgotten letter %c", i + 1, x);
            remembered[index] = false;
        } else {
            ensuref(!remembered[index], "query %d remembers already remembered letter %c", i + 1, x);
            remembered[index] = true;
        }
    }

    inf.readEof();
}
