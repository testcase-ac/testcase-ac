#include "testlib.h"

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

int n;
vector<long long> a;

struct Claim {
    vector<int> color;
};

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.color.resize(n);

    vector<vector<long long>> groups(61);
    for (int i = 0; i < n; ++i) {
        int color = stream.readInt(1, 60, format("b[%d]", i + 1).c_str());
        claim.color[i] = color;
        groups[color].push_back(a[i]);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after b[%d]", n);
    }

    for (int color = 1; color <= 60; ++color) {
        auto& values = groups[color];
        sort(values.begin(), values.end());

        unordered_set<long long> seen(values.begin(), values.end());

        for (int i = 0; i < (int)values.size(); ++i) {
            for (int j = i; j < (int)values.size(); ++j) {
                if (values[i] > 1000000000000000000LL - values[j]) {
                    break;
                }

                long long sum = values[i] + values[j];
                auto it = seen.find(sum);
                if (it != seen.end()) {
                    stream.quitf(_wa,
                                 "color %d is not anti-closed: a value %lld plus a value %lld equals %lld",
                                 color,
                                 values[i],
                                 values[j],
                                 sum);
                }
            }
        }
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong();
    }

    readClaim(ans);
    readClaim(ouf);

    quitf(_ok, "valid anti-closed partition");
}
