#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // QWERTY keyboard layout as per problem (3 rows)
    // Row 1: q w e r t y u i o p
    // Row 2: a s d f g h j k l
    // Row 3: z x c v b n m

    // Set of valid lowercase letters
    set<char> valid_letters;
    for (char c = 'a'; c <= 'z'; ++c) valid_letters.insert(c);

    // Read first line: s_L and s_R
    string sL = inf.readToken("[a-z]", "s_L");
    inf.readSpace();
    string sR = inf.readToken("[a-z]", "s_R");
    inf.readEoln();

    ensuref(sL.size() == 1 && valid_letters.count(sL[0]), "s_L must be a single lowercase letter");
    ensuref(sR.size() == 1 && valid_letters.count(sR[0]), "s_R must be a single lowercase letter");

    // Read second line: string to type
    string S = inf.readToken("[a-z]{1,100}", "S");
    inf.readEoln();

    ensuref(!S.empty(), "S must not be empty");
    ensuref(S.size() <= 100, "S must be at most 100 characters");

    for (size_t i = 0; i < S.size(); ++i) {
        ensuref(valid_letters.count(S[i]), "S[%zu] = '%c' is not a lowercase letter", i, S[i]);
    }

    inf.readEof();
}
