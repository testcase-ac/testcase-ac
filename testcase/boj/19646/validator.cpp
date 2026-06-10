#include "testlib.h"

#include <vector>

using namespace std;

class Fenwick {
public:
    explicit Fenwick(int n) : tree(n + 1, 0) {}

    void add(int index, int value) {
        for (int i = index; i < static_cast<int>(tree.size()); i += i & -i) {
            tree[i] += value;
        }
    }

    int kth(int target) const {
        int index = 0;
        int bit = 1;
        while ((bit << 1) < static_cast<int>(tree.size())) {
            bit <<= 1;
        }

        for (; bit > 0; bit >>= 1) {
            int next = index + bit;
            if (next < static_cast<int>(tree.size()) && tree[next] < target) {
                index = next;
                target -= tree[next];
            }
        }
        return index + 1;
    }

private:
    vector<int> tree;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    vector<int> w(n + 1);
    Fenwick remaining(n);
    int total = 0;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        w[i] = inf.readInt(1, 1000, "w_i");
        remaining.add(i, w[i]);
        total += w[i];
    }
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int p = inf.readInt(1, total, "p_i");
        int chosen = remaining.kth(p);
        remaining.add(chosen, -w[chosen]);
        total -= w[chosen];
    }
    inf.readEoln();
    inf.readEof();
}
