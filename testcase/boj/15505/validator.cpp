#include "testlib.h"
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    vector<vector<vector<long long>>> beauty(4,
        vector<vector<long long>>(N, vector<long long>(M)));

    for (int c = 0; c < 4; c++) {
        const char* name;
        if (c == 0) name = "red";
        else if (c == 1) name = "blue";
        else if (c == 2) name = "green";
        else name = "yellow";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                beauty[c][i][j] = inf.readLong(0LL, 1000000000LL,
                                               // name each entry as e.g. "red[2][3]"
                                               (string(name) +
                                                "[" + to_string(i) +
                                                "][" + to_string(j) + "]").c_str());
                if (j + 1 < M) inf.readSpace();
            }
            inf.readEoln();
        }
    }

    int height = N;
    int width = M;
    bool transposed = false;
    if (N < M) {
        height = M;
        width = N;
        transposed = true;
    }

    int mask_count = 1 << (2 * width);
    const long long NEG = -1;
    vector<vector<long long>> dp(width, vector<long long>(mask_count, NEG));
    vector<long long> next_dp(mask_count, NEG);

    auto cell_value = [&](int color, int line, int pos) {
        int i = transposed ? pos : line;
        int j = transposed ? line : pos;
        return beauty[color][i][j];
    };

    int first_shift = 2 * (width - 1);
    for (int color = 0; color < 4; color++) {
        dp[0][color << first_shift] = cell_value(color, 0, 0);
    }

    for (int line = 0; line < height; line++) {
        for (int pos = 0; pos < width; pos++) {
            if (line == 0 && pos == 0) {
                continue;
            }
            int shift = 2 * (width - 1 - pos);
            int previous_slot = (pos + width - 1) % width;
            fill(next_dp.begin(), next_dp.end(), NEG);
            for (int mask = 0; mask < mask_count; mask++) {
                int color = (mask >> shift) & 3;
                int left_color = pos > 0 ? ((mask >> (shift + 2)) & 3) : -1;
                if (color == left_color) {
                    continue;
                }
                for (int above_color = 0; above_color < 4; above_color++) {
                    if (line > 0 && color == above_color) {
                        continue;
                    }
                    int previous_mask =
                        (mask ^ (color << shift)) ^ (above_color << shift);
                    long long previous = dp[previous_slot][previous_mask];
                    if (previous < 0) {
                        continue;
                    }
                    next_dp[mask] =
                        max(next_dp[mask], previous + cell_value(color, line, pos));
                }
            }
            dp[pos].swap(next_dp);
        }
    }

    long long best = *max_element(dp[width - 1].begin(), dp[width - 1].end());
    ensuref(best <= 2100000000LL,
            "maximum beauty guarantee violated: best=%lld exceeds 2100000000",
            best);

    inf.readEof();
    return 0;
}
