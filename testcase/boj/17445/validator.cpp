#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static long long readCanonicalBoundedInt(const string& token, int index) {
    ensuref(!token.empty(), "argument %d is empty", index);

    int pos = 0;
    bool negative = false;
    if (token[0] == '-') {
        negative = true;
        pos = 1;
        ensuref(pos < (int)token.size(), "argument %d has no digits", index);
    }

    for (int i = pos; i < (int)token.size(); ++i) {
        ensuref('0' <= token[i] && token[i] <= '9',
                "argument %d contains a non-digit character", index);
    }

    if (token[pos] == '0') {
        ensuref(pos + 1 == (int)token.size(),
                "argument %d has leading zeroes", index);
        ensuref(!negative, "argument %d uses -0, but zero must be written as 0", index);
    }

    long long value = 0;
    for (int i = pos; i < (int)token.size(); ++i) {
        value = value * 10 + (token[i] - '0');
        ensuref(value <= 1000000000LL,
                "argument %d is too large in absolute value", index);
    }
    if (negative) {
        value = -value;
    }

    ensuref(-1000000000LL < value && value < 1000000000LL,
            "argument %d is outside the allowed range", index);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string text = inf.readToken("[(),\\-0-9aegnr]+", "range");
    inf.readEoln();
    inf.readEof();

    const string prefix = "range(";
    ensuref(text.size() >= prefix.size() + 2, "range expression is too short");
    ensuref(text.rfind(prefix, 0) == 0, "input must start with range(");
    ensuref(text.back() == ')', "input must end with )");

    string inside = text.substr(prefix.size(), text.size() - prefix.size() - 1);
    vector<string> args;
    size_t start = 0;
    while (true) {
        size_t comma = inside.find(',', start);
        if (comma == string::npos) {
            args.push_back(inside.substr(start));
            break;
        }
        args.push_back(inside.substr(start, comma - start));
        start = comma + 1;
    }

    ensuref(1 <= (int)args.size() && (int)args.size() <= 3,
            "range must have one, two, or three arguments");

    vector<long long> values;
    values.reserve(args.size());
    for (int i = 0; i < (int)args.size(); ++i) {
        values.push_back(readCanonicalBoundedInt(args[i], i + 1));
    }

    if (values.size() == 3) {
        ensuref(values[2] != 0, "third argument must be nonzero");
    }
}
