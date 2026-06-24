#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_A = (1LL << 31) - 1;

int n, targetK;

struct Output {
    bool impossible;
    vector<int> a;
};

struct SegmentTree {
    explicit SegmentTree(int size) : size(size), minLast(4 * size + 4, 0), maxLast(4 * size + 4, 0) {}

    void update(int value, int position) {
        update(1, 0, size - 1, value, position);
    }

    int countAtLeast(int queryLeft, int queryRight, int lowerBound) const {
        if (queryLeft > queryRight) {
            return 0;
        }
        return countAtLeast(1, 0, size - 1, queryLeft, queryRight, lowerBound);
    }

private:
    int size;
    vector<int> minLast;
    vector<int> maxLast;

    void update(int node, int left, int right, int value, int position) {
        if (left == right) {
            minLast[node] = maxLast[node] = position;
            return;
        }

        int mid = (left + right) / 2;
        if (value <= mid) {
            update(node * 2, left, mid, value, position);
        } else {
            update(node * 2 + 1, mid + 1, right, value, position);
        }

        minLast[node] = min(minLast[node * 2], minLast[node * 2 + 1]);
        maxLast[node] = max(maxLast[node * 2], maxLast[node * 2 + 1]);
    }

    int countAtLeast(int node, int left, int right, int queryLeft, int queryRight, int lowerBound) const {
        if (right < queryLeft || queryRight < left || maxLast[node] < lowerBound) {
            return 0;
        }
        if (queryLeft <= left && right <= queryRight && minLast[node] >= lowerBound) {
            return right - left + 1;
        }
        if (left == right) {
            return maxLast[node] >= lowerBound ? 1 : 0;
        }

        int mid = (left + right) / 2;
        return countAtLeast(node * 2, left, mid, queryLeft, queryRight, lowerBound)
             + countAtLeast(node * 2 + 1, mid + 1, right, queryLeft, queryRight, lowerBound);
    }
};

Output readOutput(InStream& stream) {
    long long first = stream.readLong(-1, MAX_A, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    vector<int> a(n);
    a[0] = (int)first;
    for (int i = 1; i < n; ++i) {
        a[i] = (int)stream.readLong(0, MAX_A, format("A[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }
    return {false, a};
}

int computeMexMex(const vector<int>& a) {
    vector<vector<int>> positions(n + 1);
    for (int i = 0; i < n; ++i) {
        if (0 <= a[i] && a[i] <= n) {
            positions[a[i]].push_back(i + 1);
        }
    }

    vector<vector<pair<int, int>>> gapsByRight(n + 1);
    for (int mex = 0; mex <= n; ++mex) {
        int previous = 0;
        for (int pos : positions[mex]) {
            int left = previous + 1;
            int right = pos - 1;
            if (left <= right) {
                gapsByRight[right].push_back({mex, left});
            }
            previous = pos;
        }
        int left = previous + 1;
        int right = n;
        if (left <= right) {
            gapsByRight[right].push_back({mex, left});
        }
    }

    vector<char> possible(n + 1, false);
    SegmentTree latest(n + 1);
    vector<int> lastSeen(n + 1, 0);

    for (int right = 1; right <= n; ++right) {
        int value = a[right - 1];
        if (0 <= value && value <= n) {
            lastSeen[value] = right;
            latest.update(value, right);
        }

        for (auto [mex, left] : gapsByRight[right]) {
            int distinctValues = latest.countAtLeast(0, mex - 1, left);
            if (distinctValues == mex) {
                possible[mex] = true;
            }
        }
    }

    for (int mexmex = 0; mexmex <= n; ++mexmex) {
        if (!possible[mexmex]) {
            return mexmex;
        }
    }
    return n + 1;
}

void validateSequence(InStream& stream, const Output& output) {
    if (output.impossible) {
        return;
    }

    int mexmex = computeMexMex(output.a);
    if (mexmex != targetK) {
        stream.quitf(_wa, "MEXMEX is %d, expected %d", mexmex, targetK);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    targetK = inf.readInt();

    Output jury = readOutput(ans);
    validateSequence(ans, jury);

    Output participant = readOutput(ouf);
    if (participant.impossible) {
        if (jury.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_wa, "participant claims impossible, but jury has a construction");
    }

    int participantMexMex = computeMexMex(participant.a);
    if (participantMexMex != targetK) {
        quitf(_wa, "participant MEXMEX is %d, expected %d", participantMexMex, targetK);
    }

    if (jury.impossible) {
        quitf(_fail, "participant found a valid construction while jury claims impossible");
    }
    quitf(_ok, "valid construction with MEXMEX %d", participantMexMex);
}
