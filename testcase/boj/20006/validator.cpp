#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of players p and room capacity m
    int p = inf.readInt(1, 300, "p");
    inf.readSpace();
    int m = inf.readInt(1, 300, "m");
    inf.readEoln();

    // Read each player's level and nickname, ensuring uniqueness and format
    set<string> seenNames;
    for (int i = 0; i < p; i++) {
        int level = inf.readInt(1, 500, "level");
        inf.readSpace();
        string name = inf.readToken("[a-z]{1,16}", "nickname");
        inf.readEoln();
        ensuref(seenNames.insert(name).second,
                "Duplicate nickname detected: %s", name.c_str());
    }

    inf.readEof();
    return 0;
}
