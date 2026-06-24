#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> targetProducts;

struct Claim {
    bool possible;
    vector<int> values;
};

TResult verdictFor(const InStream& stream) {
    return (&stream == &ouf) ? _wa : _fail;
}

Claim readClaim(InStream& stream) {
    string verdict = lowerCase(stream.readToken("[A-Za-z]+", "verdict"));
    if (verdict == "no") {
        if (!stream.seekEof()) {
            stream.quitf(verdictFor(stream), "extra output after No");
        }
        return {false, {}};
    }
    if (verdict != "yes") {
        stream.quitf(verdictFor(stream),
                     "verdict must be Yes or No, found '%s'",
                     verdict.c_str());
    }

    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = stream.readInt(1, 100, format("a[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(verdictFor(stream), "extra output after array");
    }

    vector<int> products;
    products.reserve(n - 1);
    for (int i = 0; i + 1 < n; ++i) {
        products.push_back(values[i] * values[i + 1]);
    }
    sort(products.begin(), products.end());
    if (products != targetProducts) {
        stream.quitf(verdictFor(stream),
                     "adjacent product multiset does not match input");
    }

    return {true, values};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 18, "n");
    targetProducts.resize(n - 1);
    for (int i = 0; i + 1 < n; ++i) {
        targetProducts[i] = inf.readInt(1, 10000, format("b[%d]", i + 1).c_str());
    }
    sort(targetProducts.begin(), targetProducts.end());

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.possible) {
        if (!participant.possible) {
            quitf(_ok, "both outputs claim No");
        }
        quitf(_fail, "participant provided a valid array while jury says No");
    }

    if (!participant.possible) {
        quitf(_wa, "jury has a valid array but participant says No");
    }

    quitf(_ok, "participant provided a valid array");
}
