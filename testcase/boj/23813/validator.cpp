#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[1-9]{1,9}", "N");
    inf.readEoln();

    ensuref(n <= "987654321", "N exceeds 987654321: %s", n.c_str());

    array<bool, 10> seen = {};
    for (int i = 0; i < (int)n.size(); ++i) {
        int digit = n[i] - '0';
        ensuref(!seen[digit], "duplicate digit %d at position %d", digit, i + 1);
        seen[digit] = true;
    }

    inf.readEof();
}
