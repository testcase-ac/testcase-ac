#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static string shifted(string name, int amount) {
    for (char& ch : name) {
        ch = char('a' + (ch - 'a' + amount) % 26);
    }
    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> prefixes = {
        "northlondo",
        "branksomeh",
        "koreainter",
        "stjohnsbur",
    };

    const int mode = rnd.next(0, 3);
    const string prefix = rnd.any(prefixes);

    int amount = 0;
    if (mode == 0) {
        amount = 0;
    } else if (mode == 1) {
        amount = rnd.any(vector<int>{1, 25});
    } else if (mode == 2) {
        amount = rnd.any(vector<int>{13, 24, 25});
    } else {
        amount = rnd.next(0, 25);
    }

    println(shifted(prefix, amount));
    return 0;
}
