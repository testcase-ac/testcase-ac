#include "testlib.h"

#include <string>

using namespace std;

long long readFixed9Decimal(const string& name) {
    string token = inf.readToken("-?[0-4][.][0-9]{9}", name);

    int pos = 0;
    bool negative = false;
    if (token[pos] == '-') {
        negative = true;
        ++pos;
    }

    long long scaled = token[pos] - '0';
    ++pos;
    ensuref(token[pos] == '.', "%s must contain a decimal point", name.c_str());
    ++pos;

    for (int i = 0; i < 9; ++i) {
        scaled = scaled * 10 + (token[pos + i] - '0');
    }
    if (negative) {
        scaled = -scaled;
    }

    ensuref(-4000000000LL <= scaled && scaled <= 4000000000LL,
            "%s is outside [-4, 4]: %s", name.c_str(), token.c_str());
    ensuref(!negative || scaled != 0, "%s has non-canonical negative zero", name.c_str());

    return scaled;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        readFixed9Decimal("A");
        inf.readSpace();
        readFixed9Decimal("B");
        inf.readEoln();
    }

    inf.readEof();
}
