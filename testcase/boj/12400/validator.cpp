#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string g = inf.readLine();
        ensuref(!g.empty(), "G must contain at least one character");
        ensuref((int)g.size() <= 100, "G must contain at most 100 characters");
        ensuref(g.front() != ' ', "G must not start with a space");
        ensuref(g.back() != ' ', "G must not end with a space");

        for (int i = 0; i < (int)g.size(); ++i) {
            ensuref(g[i] == ' ' || ('a' <= g[i] && g[i] <= 'z'),
                    "G contains invalid character at position %d", i + 1);
        }

        for (int i = 0; i + 1 < (int)g.size(); ++i) {
            ensuref(!(g[i] == ' ' && g[i + 1] == ' '),
                    "G must have exactly one space between consecutive words");
        }
    }

    inf.readEof();
}
