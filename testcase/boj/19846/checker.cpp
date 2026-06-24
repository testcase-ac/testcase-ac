#include "testlib.h"

#include <array>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, m, q;
vector<pair<int, int>> intervals;

struct Answer {
    string text;
};

Answer readAnswer(InStream& stream) {
    string text = stream.readToken("[a-z]+", "answer string");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer string");
    }

    if ((int)text.size() != m) {
        stream.quitf(_wa, "answer length is %d, expected %d", (int)text.size(), m);
    }

    array<int, 26> used{};
    int distinct = 0;
    for (char ch : text) {
        int c = ch - 'a';
        if (used[c] == 0) {
            ++distinct;
        }
        ++used[c];
    }
    if (distinct != n) {
        stream.quitf(_wa, "answer uses %d distinct letters, expected %d", distinct, n);
    }

    vector<array<int, 26>> prefix(m + 1);
    prefix[0].fill(0);
    for (int i = 0; i < m; ++i) {
        prefix[i + 1] = prefix[i];
        ++prefix[i + 1][text[i] - 'a'];
    }

    for (int i = 0; i < q; ++i) {
        int left = intervals[i].first;
        int right = intervals[i].second;
        int present = 0;
        int odd = 0;
        for (int c = 0; c < 26; ++c) {
            int count = prefix[right][c] - prefix[left - 1][c];
            if (count > 0) {
                ++present;
            }
            if (count % 2 == 1) {
                ++odd;
            }
        }

        if (present != n) {
            stream.quitf(_wa,
                         "interval %d contains %d distinct letters, expected %d",
                         i + 1,
                         present,
                         n);
        }
        if (odd != 1) {
            stream.quitf(_wa,
                         "interval %d has %d letters with odd frequency, expected 1",
                         i + 1,
                         odd);
        }
    }

    return {text};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    q = inf.readInt();
    intervals.resize(q);
    for (int i = 0; i < q; ++i) {
        int s = inf.readInt();
        int e = inf.readInt();
        intervals[i] = {s, e};
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid construction");
}
