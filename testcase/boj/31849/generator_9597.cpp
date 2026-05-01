#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 5);

    // Hand-crafted interesting case with ties and asymmetric distances
    if (type == 5) {
        int N = 7, M = 7, R = 5, C = 3;
        println(N, M, R, C);
        // rooms: (a, b, p)
        println(1, 1, 10);
        println(7, 7, 2);
        println(4, 4, 1);
        println(3, 5, 3);
        println(5, 2, 2);
        // stores: (c, d)
        println(2, 2);
        println(6, 6);
        println(2, 6);
        return 0;
    }

    int N, M;
    const int K_CAP = 35; // keep total lines small enough

    if (type == 0) {
        // Tiny grid
        N = rnd.next(2, 5);
        M = rnd.next(2, 5);
    } else if (type == 1) {
        // Asymmetric: tall or wide
        if (rnd.next(0, 1) == 0) {
            N = rnd.next(8, 20);
            M = rnd.next(2, 6);
        } else {
            N = rnd.next(2, 6);
            M = rnd.next(8, 20);
        }
    } else if (type == 2) {
        // Medium grid, relatively dense objects (but capped)
        N = rnd.next(5, 15);
        M = rnd.next(5, 15);
    } else if (type == 3) {
        // Few stores, many rooms
        N = rnd.next(5, 25);
        M = rnd.next(5, 25);
    } else { // type == 4
        // Few rooms, many stores
        N = rnd.next(5, 25);
        M = rnd.next(5, 25);
    }

    int maxK = min(K_CAP, N * M);
    if (maxK < 2) maxK = 2; // just in case, though N,M>=2 guarantees NM>=4

    int R, C, K;

    if (type == 0 || type == 1 || type == 2) {
        // Generic split
        int upperK;
        if (type == 0) {
            upperK = min(maxK, 8);
            if (upperK < 2) upperK = 2;
            K = rnd.next(2, upperK);
        } else if (type == 1) {
            K = rnd.next(2, maxK);
        } else { // type == 2: relatively dense
            int delta = max(1, maxK / 3);
            K = max(2, maxK - rnd.next(0, delta));
        }
        R = rnd.next(1, K - 1);
        C = K - R;
    } else if (type == 3) {
        // Few stores
        int maxStores = min(3, maxK - 1);
        C = rnd.next(1, maxStores);
        K = rnd.next(C + 1, maxK);
        R = K - C;
    } else { // type == 4
        // Few rooms
        int maxRooms = min(3, maxK - 1);
        R = rnd.next(1, maxRooms);
        K = rnd.next(R + 1, maxK);
        C = K - R;
    }

    // Collect all cells and choose R+C distinct positions
    vector<pair<int,int>> cells;
    cells.reserve(N * M);
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());

    vector<pair<int,int>> rooms(cells.begin(), cells.begin() + R);
    vector<pair<int,int>> stores(cells.begin() + R, cells.begin() + R + C);

    // Choose a rent distribution mode for this test
    int rentMode = rnd.next(0, 2); // 0: uniform, 1: low-biased, 2: high-biased

    auto genRent = [&]() -> int {
        if (rentMode == 0) {
            return rnd.next(1, 100);
        } else if (rentMode == 1) {
            // Biased to low values
            return rnd.wnext(100, -3) + 1; // in [1,100]
        } else {
            // Biased to high values
            return rnd.wnext(100, 3) + 1; // in [1,100], skewed high
        }
    };

    println(N, M, R, C);
    for (int i = 0; i < R; ++i) {
        int a = rooms[i].first;
        int b = rooms[i].second;
        int p = genRent();
        println(a, b, p);
    }
    for (int j = 0; j < C; ++j) {
        int c = stores[j].first;
        int d = stores[j].second;
        println(c, d);
    }

    return 0;
}
