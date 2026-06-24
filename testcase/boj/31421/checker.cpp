#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
string target;

struct Answer {
    bool impossible;
};

struct Fenwick {
    vector<int> tree;

    explicit Fenwick(int size) : tree(size + 2, 0) {}

    void add(int index, int value) {
        for (; index < (int)tree.size(); index += index & -index) {
            tree[index] += value;
        }
    }

    int sum(int index) const {
        int result = 0;
        for (; index > 0; index -= index & -index) {
            result += tree[index];
        }
        return result;
    }

    void flipRange(int left, int right) {
        add(left, 1);
        add(right + 1, -1);
    }
};

char colorAt(const Fenwick& flips, int index) {
    return flips.sum(index) % 2 == 0 ? 'W' : 'B';
}

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(-1, n, "K");

    if (k == -1) {
        stream.readEoln();
        stream.readEof();
        return {true};
    }

    stream.readEoln();

    if (n == 1 && k > 0) {
        stream.quitf(_wa, "positive operation count is impossible when N=1");
    }

    Fenwick flips(n);
    for (int i = 0; i < k; ++i) {
        int x = stream.readInt(1, n - 1, format("operation[%d]", i + 1).c_str());
        stream.readEoln();

        char leftColor = colorAt(flips, x);
        char rightColor = colorAt(flips, x + 1);
        if (leftColor != rightColor) {
            stream.quitf(_wa,
                         "operation %d chooses x=%d, but positions %d and %d have colors %c and %c",
                         i + 1, x, x, x + 1, leftColor, rightColor);
        }

        if (leftColor == 'W') {
            flips.flipRange(1, x);
        } else {
            flips.flipRange(x + 1, n);
        }
    }

    stream.readEof();

    for (int i = 1; i <= n; ++i) {
        char actual = colorAt(flips, i);
        if (actual != target[i - 1]) {
            stream.quitf(_wa,
                         "operations produce color %c at position %d instead of target %c",
                         actual, i, target[i - 1]);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    target = inf.readToken();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid sequence while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has a valid sequence");
    }

    quitf(_ok, "valid sequence");
}
