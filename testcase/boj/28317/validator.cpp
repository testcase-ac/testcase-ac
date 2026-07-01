#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    int m = n - k + 1;
    vector<int> sms(m);
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        sms[i] = inf.readInt(0, k, "sms_i");
    }
    inf.readEoln();
    inf.readEof();

    vector<int> min_offset(k, 0);
    vector<int> max_offset(k, 0);
    vector<int> offset(k, 0);

    for (int i = 0; i + 1 < m; ++i) {
        int delta = sms[i + 1] - sms[i];
        ensuref(-1 <= delta && delta <= 1,
                "adjacent SMS values differ by %d at index %d", delta, i + 1);

        int residue = i % k;
        offset[residue] += delta;
        min_offset[residue] = min(min_offset[residue], offset[residue]);
        max_offset[residue] = max(max_offset[residue], offset[residue]);
    }

    int min_first_window = 0;
    int max_first_window = 0;
    for (int residue = 0; residue < k; ++residue) {
        bool can_zero = min_offset[residue] >= 0 && max_offset[residue] <= 1;
        bool can_one = min_offset[residue] >= -1 && max_offset[residue] <= 0;
        ensuref(can_zero || can_one,
                "no binary assignment is possible for residue %d", residue + 1);

        if (!can_zero) {
            ++min_first_window;
        }
        if (can_one) {
            ++max_first_window;
        }
    }

    ensuref(min_first_window <= sms[0] && sms[0] <= max_first_window,
            "first SMS value %d is outside feasible range [%d, %d]",
            sms[0], min_first_window, max_first_window);
}
