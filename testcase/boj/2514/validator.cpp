#include "testlib.h"

#include <array>
#include <cstdlib>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(30, 40, "M");
    inf.readEoln();
    int k = inf.readInt(1, 63, "K");
    inf.readEoln();

    array<array<int, 8>, 8> board{};
    array<int, 8> row_sum{};
    array<int, 8> col_sum{};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            board[i][j] = inf.readInt(1, 1000, "production");
            row_sum[i] += board[i][j];
            col_sum[j] += board[i][j];
        }
        inf.readEoln();
    }
    inf.readEof();

    array<array<int, 8>, 8> signature{};
    vector<pair<int, int>> occupied;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            signature[i][j] = row_sum[i] + col_sum[j] - board[i][j] - 15 * m;
            if (abs(signature[i][j]) % 2 == 1) {
                occupied.push_back({i, j});
            }
        }
    }

    ensuref((int)occupied.size() == k,
            "production grid implies %d sprayer cells, but K is %d",
            (int)occupied.size(), k);

    array<array<int, 8>, 8> all_fertilizer{};
    for (int i = 0; i < 8; ++i) {
        all_fertilizer[i].fill(m);
    }
    for (auto [r, c] : occupied) {
        for (int i = 0; i < 8; ++i) {
            ++all_fertilizer[i][c];
        }
        for (int j = 0; j < 8; ++j) {
            ++all_fertilizer[r][j];
        }
        --all_fertilizer[r][c];
    }

    array<int, 8> plus_row_sum{};
    array<int, 8> plus_col_sum{};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            plus_row_sum[i] += all_fertilizer[i][j];
            plus_col_sum[j] += all_fertilizer[i][j];
        }
    }

    array<array<int, 8>, 8> sprayer{};
    for (auto [r, c] : occupied) {
        int plus_signature = plus_row_sum[r] + plus_col_sum[c] - all_fertilizer[r][c] - 15 * m;
        sprayer[r][c] = abs(signature[r][c] - plus_signature) % 4 == 0 ? 1 : -1;
    }

    array<array<int, 8>, 8> reconstructed{};
    for (int i = 0; i < 8; ++i) {
        reconstructed[i].fill(m);
    }
    for (auto [r, c] : occupied) {
        int delta = sprayer[r][c];
        for (int i = 0; i < 8; ++i) {
            reconstructed[i][c] += delta;
        }
        for (int j = 0; j < 8; ++j) {
            reconstructed[r][j] += delta;
        }
        reconstructed[r][c] -= delta;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ensuref(reconstructed[i][j] == board[i][j],
                    "production grid is not realizable at cell (%d, %d): expected %d, reconstructed %d",
                    i + 1, j + 1, board[i][j], reconstructed[i][j]);
        }
    }
}
