#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int R = rnd.next(1, 12);
    int C = rnd.next(1, 12);
    int N = rnd.next(1, 40);

    if (mode == 1) {
        R = rnd.any(vector<int>{1, 2, rnd.next(20, 100000)});
        C = rnd.next(20, 100000);
        N = rnd.next(4, 30);
    } else if (mode == 2) {
        R = rnd.next(3, 30);
        C = rnd.next(3, 30);
        N = rnd.next(6, 50);
    } else if (mode == 3) {
        R = rnd.next(1, 100000);
        C = rnd.next(1, 100000);
        N = rnd.next(1, 80);
    } else if (mode == 4) {
        if (rnd.next(0, 1) == 0) {
            R = 1;
            C = rnd.next(1, 100000);
        } else {
            R = rnd.next(1, 100000);
            C = 1;
        }
        N = rnd.next(1, 60);
    } else if (mode == 5) {
        R = rnd.next(2, 20);
        C = rnd.next(2, 20);
        N = rnd.next(10, 70);
    }

    vector<tuple<int, int, int>> pieces;
    auto addPiece = [&](int id, int row, int col) {
        pieces.emplace_back(id, row, col);
    };

    if (mode == 0) {
        int row = rnd.next(1, R);
        int col = rnd.next(1, C);
        int idCount = rnd.next(1, N);
        for (int i = 0; i < N; ++i) {
            addPiece(rnd.next(1, idCount), row, col);
        }
    } else if (mode == 1) {
        int target = rnd.next(1, N);
        addPiece(target, 1, 1);
        addPiece(target, R, C);
        while ((int)pieces.size() < N) {
            int id = rnd.next(1, N);
            int row = rnd.next(1, R);
            int col = rnd.next(1, C);
            if (id == target && rnd.next(0, 2) == 0) {
                row = rnd.any(vector<int>{1, R});
                col = rnd.any(vector<int>{1, C});
            }
            addPiece(id, row, col);
        }
    } else if (mode == 2) {
        int idA = 1;
        int idB = 2;
        int top = rnd.next(1, R - 2);
        int left = rnd.next(1, C - 2);
        int height = rnd.next(2, R - top + 1);
        int width = rnd.next(2, C - left + 1);
        addPiece(idA, top, left);
        addPiece(idA, top + height - 1, left + width - 1);
        addPiece(idB, top, left + width - 1);
        addPiece(idB, top + height - 1, left);
        while ((int)pieces.size() < N) {
            addPiece(rnd.next(1, N), rnd.next(1, R), rnd.next(1, C));
        }
    } else if (mode == 3) {
        for (int i = 1; i <= N; ++i) {
            addPiece(i, rnd.next(1, R), rnd.next(1, C));
        }
        int extraUpdates = rnd.next(0, N / 2);
        for (int i = 0; i < extraUpdates; ++i) {
            int pos = rnd.next(0, N - 1);
            pieces[pos] = make_tuple(rnd.next(1, N), rnd.next(1, R), rnd.next(1, C));
        }
    } else if (mode == 4) {
        int favored = rnd.next(1, N);
        for (int i = 0; i < N; ++i) {
            int id = (rnd.next(0, 3) == 0 ? favored : rnd.next(1, N));
            addPiece(id, rnd.next(1, R), rnd.next(1, C));
        }
    } else {
        int clusterRow = rnd.next(1, R);
        int clusterCol = rnd.next(1, C);
        for (int i = 0; i < N; ++i) {
            int row = rnd.next(0, 3) == 0 ? rnd.next(1, R) : clusterRow;
            int col = rnd.next(0, 3) == 0 ? rnd.next(1, C) : clusterCol;
            addPiece(rnd.next(1, N), row, col);
        }
    }

    shuffle(pieces.begin(), pieces.end());

    println(R, C);
    println(N);
    for (auto [id, row, col] : pieces) {
        println(id, row, col);
    }

    return 0;
}
