#include "testlib.h"

#include <array>
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    array<string, 3> strings;
    int minLength = 17;

    for (int i = 0; i < 3; ++i) {
        strings[i] = inf.readToken("[a-z]{1,17}", format("s_%d", i + 1));
        inf.readEoln();

        set<char> seen;
        for (char c : strings[i]) {
            ensuref(seen.insert(c).second,
                    "s_%d contains duplicate character '%c'", i + 1, c);
        }
        minLength = min(minLength, static_cast<int>(strings[i].size()));
    }

    inf.readInt(1, minLength, "k");
    inf.readEoln();
    inf.readEof();
}
