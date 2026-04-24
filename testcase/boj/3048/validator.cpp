#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the sizes of the two ant groups
    int N1 = inf.readInt(1, 26, "N1");
    inf.readSpace();
    int N2 = inf.readInt(1, 26, "N2");
    inf.readEoln();

    // Read the first group's string
    string s1 = inf.readToken("[A-Z]+", "s1");
    ensuref((int)s1.size() == N1,
            "Length of first group string should be %d, but found %d",
            N1, (int)s1.size());
    inf.readEoln();

    // Read the second group's string
    string s2 = inf.readToken("[A-Z]+", "s2");
    ensuref((int)s2.size() == N2,
            "Length of second group string should be %d, but found %d",
            N2, (int)s2.size());
    inf.readEoln();

    // Ensure all letters are uppercase A-Z and unique
    bool used1[26] = {false};
    for (int i = 0; i < N1; i++) {
        char c = s1[i];
        int idx = c - 'A';
        ensuref(0 <= idx && idx < 26,
                "Invalid character '%c' in first group at position %d", c, i);
        ensuref(!used1[idx],
                "Duplicate ant label '%c' in first group at position %d", c, i);
        used1[idx] = true;
    }

    bool used2[26] = {false};
    for (int i = 0; i < N2; i++) {
        char c = s2[i];
        int idx = c - 'A';
        ensuref(0 <= idx && idx < 26,
                "Invalid character '%c' in second group at position %d", c, i);
        ensuref(!used2[idx],
                "Duplicate ant label '%c' in second group at position %d", c, i);
        ensuref(!used1[idx],
                "Ant label '%c' appears in both groups (at second group position %d)", c, i);
        used2[idx] = true;
    }

    // Read time T
    int T = inf.readInt(0, 50, "T");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
