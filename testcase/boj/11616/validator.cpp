#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 300000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    // Read the digit string
    // We read the entire line and then validate its length and contents
    string s = inf.readLine("[^]+", "s");
    ensuref((int)s.size() == n,
            "The length of the digit string s is %d but expected %d", (int)s.size(), n);
    for (int i = 0; i < n; i++) {
        char c = s[i];
        ensuref(c >= '0' && c <= '9',
                "Character s[%d] = '%c' is not a digit", i, c);
    }

    // No extra data after this line
    inf.readEof();
    return 0;
}
