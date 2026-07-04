#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int readProbabilityToken(const string& name, bool allowZero) {
    string token = inf.readToken("[0-9]\\.[0-9]{6}", name);
    int whole = token[0] - '0';
    int frac = 0;
    for (int i = 2; i < 8; ++i) {
        frac = frac * 10 + (token[i] - '0');
    }
    int scaled = whole * 1000000 + frac;
    ensuref(scaled <= 1000000, "%s must be at most 1.000000: %s",
            name.c_str(), token.c_str());
    ensuref(allowZero || scaled > 0, "%s must be positive: %s",
            name.c_str(), token.c_str());
    return scaled;
}

vector<int> readProbabilityLine(int n, const string& baseName, bool allowZero) {
    vector<int> values;
    values.reserve(n);

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = readProbabilityToken(baseName + "_" + to_string(i + 1), allowZero);
        values.push_back(value);
        sum += value;
    }
    inf.readEoln();

    ensuref(sum == 1000000, "%s values must sum to 1.000000, got %.6f",
            baseName.c_str(), sum / 1000000.0);
    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    readProbabilityLine(n, "q", true);
    readProbabilityLine(n, "r", false);

    inf.readEof();
}
