#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string emoji = inf.readLine("[a-z_:]{7,32}", "emoji");

    ensuref(emoji.rfind(":chino", 0) == 0, "emoji must start with ':chino'");
    ensuref(emoji.back() == ':', "emoji must end with ':'");

    for (int i = 1; i + 1 < (int)emoji.size(); ++i) {
        char c = emoji[i];
        ensuref(('a' <= c && c <= 'z') || c == '_',
                "emoji body contains invalid character at index %d: %c", i, c);
    }

    inf.readEof();
}
