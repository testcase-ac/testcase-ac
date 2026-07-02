#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

using boost::multiprecision::cpp_int;
using namespace std;

int n;
vector<int> a;

struct Claim {
    bool impossible;
    cpp_int selectedProduct;
    cpp_int otherProduct;
};

Claim readClaim(InStream& stream) {
    string first = stream.readToken("[A-Za-z0-9+-]+", "answer type or count");

    if (first == "Impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after Impossible");
        }
        return {true, 0, 0};
    }

    int count;
    try {
        size_t pos = 0;
        count = stoi(first, &pos);
        if (pos != first.size()) {
            stream.quitf(_wa, "answer count is not an integer: %s", first.c_str());
        }
    } catch (...) {
        stream.quitf(_wa, "answer count is not an integer: %s", first.c_str());
    }

    if (count < 1 || count > n) {
        stream.quitf(_wa, "answer count %d is outside [1, %d]", count, n);
    }

    vector<int> used(n, 0);
    for (int i = 0; i < count; ++i) {
        int index = stream.readInt(1, n, format("index[%d]", i + 1).c_str()) - 1;
        if (used[index]) {
            stream.quitf(_wa, "index %d is repeated", index + 1);
        }
        used[index] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after subset");
    }

    cpp_int selected = 1;
    cpp_int other = 1;
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            selected *= a[i];
        } else {
            other *= a[i];
        }
    }

    if (selected <= other) {
        stream.quitf(_wa, "selected product is not greater than unselected product");
    }

    return {false, selected, other};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 1000, "n");
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt(-100, 100, format("a[%d]", i + 1).c_str());
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers are Impossible");
        }
        quitf(_fail, "participant found a valid subset while jury says Impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid subset but participant says Impossible");
    }

    quitf(_ok, "valid subset");
}
