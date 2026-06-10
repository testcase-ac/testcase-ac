#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class MaxSegmentTree {
public:
    explicit MaxSegmentTree(int n) {
        size_ = 1;
        while (size_ < n) {
            size_ *= 2;
        }
        tree_.assign(2 * size_, 0);
    }

    void update(int pos, int value) {
        int node = pos - 1 + size_;
        tree_[node] = max(tree_[node], value);
        for (node /= 2; node > 0; node /= 2) {
            tree_[node] = max(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    int query(int left, int right) const {
        int result = 0;
        int l = left - 1 + size_;
        int r = right - 1 + size_;
        while (l <= r) {
            if (l % 2 == 1) {
                result = max(result, tree_[l++]);
            }
            if (r % 2 == 0) {
                result = max(result, tree_[r--]);
            }
            l /= 2;
            r /= 2;
        }
        return result;
    }

private:
    int size_;
    vector<int> tree_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    string breeds = inf.readToken("[GH]{2,100000}", "breeds");
    ensuref((int)breeds.size() == n, "breed string length is %d, expected %d",
            (int)breeds.size(), n);
    inf.readEoln();

    vector<int> e(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        e[i] = inf.readInt(i, n, "E_i");
    }
    inf.readEoln();
    inf.readEof();

    vector<int> first(256, n + 1), last(256, 0), count(256, 0);
    for (int i = 1; i <= n; ++i) {
        unsigned char breed = breeds[i - 1];
        first[breed] = min(first[breed], i);
        last[breed] = max(last[breed], i);
        ++count[breed];
    }
    ensuref(count['G'] > 0, "there must be at least one Guernsey cow");
    ensuref(count['H'] > 0, "there must be at least one Holstein cow");

    vector<int> allHPrefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        bool coversAllH = breeds[i - 1] == 'H' && i == first['H'] && e[i] >= last['H'];
        allHPrefix[i] = allHPrefix[i - 1] + (coversAllH ? 1 : 0);
    }

    MaxSegmentTree activeH(n);
    bool hasPossiblePair = false;
    for (int i = 1; i <= n; ++i) {
        if (breeds[i - 1] == 'H' && !(i == first['H'] && e[i] >= last['H'])) {
            activeH.update(i, e[i]);
        }

        if (breeds[i - 1] != 'G') {
            continue;
        }

        bool coversAllG = i == first['G'] && e[i] >= last['G'];
        int left = coversAllG ? 1 : i;
        int right = coversAllG ? n : e[i];

        bool hasAllHCandidate = allHPrefix[right] - allHPrefix[left - 1] > 0;
        bool hasCoveringHCandidate = activeH.query(left, right) >= i;
        if (hasAllHCandidate || hasCoveringHCandidate) {
            hasPossiblePair = true;
            break;
        }
    }
    ensuref(hasPossiblePair, "statement guarantees at least one possible leader pair");
}
