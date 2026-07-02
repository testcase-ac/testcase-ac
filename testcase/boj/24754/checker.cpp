#include "testlib.h"

#include <unordered_map>
#include <vector>

using namespace std;

int n;
vector<long long> a;
vector<long long> b;

struct Answer {
    int groups;
};

void addDiff(unordered_map<long long, int>& diff, vector<long long>& touched, long long value, int delta) {
    auto it = diff.find(value);
    if (it == diff.end()) {
        diff[value] = delta;
        touched.push_back(value);
    } else {
        it->second += delta;
    }
}

bool sameMultisetInSegment(int left, int right) {
    unordered_map<long long, int> diff;
    vector<long long> touched;
    diff.reserve((right - left + 1) * 2 + 1);

    for (int i = left; i <= right; ++i) {
        addDiff(diff, touched, a[i], 1);
        addDiff(diff, touched, b[i], -1);
    }
    for (long long value : touched) {
        if (diff[value] != 0) {
            return false;
        }
    }
    return true;
}

Answer readAnswer(InStream& stream) {
    vector<string> tokens;
    while (!stream.seekEof()) {
        tokens.push_back(stream.readToken());
    }

    int groups = 1;
    int segmentStart = 0;
    int itemIndex = 0;

    for (int tokenIndex = 0; tokenIndex < int(tokens.size()); ++tokenIndex) {
        if (itemIndex == n) {
            stream.quitf(_wa, "extra token after item[%d]: %s", n, tokens[tokenIndex].c_str());
        }

        string token = tokens[tokenIndex];
        if (token == "#") {
            stream.quitf(_wa, "divider appears where item[%d] is expected", itemIndex + 1);
        }
        long long value = stringToLongLong(stream, token);
        if (value != b[itemIndex]) {
            stream.quitf(_wa, "item[%d] is %lld, expected %lld", itemIndex + 1, value, b[itemIndex]);
        }

        if (tokenIndex + 1 < int(tokens.size()) && tokens[tokenIndex + 1] == "#") {
            if (itemIndex + 1 == n) {
                stream.quitf(_wa, "divider appears after the final item");
            }
            if (!sameMultisetInSegment(segmentStart, itemIndex)) {
                stream.quitf(_wa, "segment [%d, %d] is not a rearrangement of the original segment",
                             segmentStart + 1, itemIndex + 1);
            }
            ++groups;
            segmentStart = itemIndex + 1;
            ++tokenIndex;
        }
        ++itemIndex;
    }

    if (itemIndex != n) {
        stream.quitf(_wa, "output has %d items, expected %d", itemIndex, n);
    }

    if (!sameMultisetInSegment(segmentStart, n - 1)) {
        stream.quitf(_wa, "segment [%d, %d] is not a rearrangement of the original segment",
                     segmentStart + 1, n);
    }
    return {groups};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong();
    }
    for (int i = 0; i < n; ++i) {
        b[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.groups < jury.groups) {
        quitf(_wa, "jury has more groups: jury=%d participant=%d", jury.groups, participant.groups);
    }
    if (participant.groups > jury.groups) {
        quitf(_fail, "participant has more groups than jury: jury=%d participant=%d",
              jury.groups, participant.groups);
    }
    quitf(_ok, "groups=%d", participant.groups);
}
