#include "testlib.h"

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

namespace {

constexpr int kMaxN = 50000;
constexpr int kMaxTargetLength = 150000;
constexpr int kMaxSourceLength = 20;

bool canSynthesize(const string& target, const unordered_set<string>& sources) {
    const int z = static_cast<int>(target.size());
    vector<char> reachable(z, false);

    for (int start = 0; start < z; ++start) {
        string current;
        bool hasPreviousOverlap = false;
        for (int len = 1; len <= kMaxSourceLength && start + len <= z; ++len) {
            current.push_back(target[start + len - 1]);
            if (sources.count(current) && (start == 0 || hasPreviousOverlap)) {
                reachable[start + len - 1] = true;
            }
            hasPreviousOverlap = hasPreviousOverlap || reachable[start + len - 1];
        }
    }

    return reachable.back();
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, kMaxN, "N");
    inf.readEoln();

    string target = inf.readToken("[ATGC]{1,150000}", "target");
    ensuref(static_cast<int>(target.size()) <= kMaxTargetLength,
            "target length is too large: %d", static_cast<int>(target.size()));
    inf.readEoln();

    unordered_set<string> sources;
    sources.reserve(static_cast<size_t>(n) * 2);
    for (int i = 1; i <= n; ++i) {
        string source = inf.readToken("[ATGC]{1,20}", "source");
        ensuref(static_cast<int>(source.size()) <= kMaxSourceLength,
                "source %d length is too large: %d", i,
                static_cast<int>(source.size()));
        ensuref(sources.insert(source).second, "duplicate source string at index %d: %s",
                i, source.c_str());
        inf.readEoln();
    }

    ensuref(canSynthesize(target, sources),
            "target cannot be synthesized from the given source strings");

    inf.readEof();
}
