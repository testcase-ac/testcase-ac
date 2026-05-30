#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<pair<int, int>> faces = {
        {1, 2},   {1, 3},   {1, 4},   {1, 5},
        {2, 6},   {2, 7},   {2, 8},   {3, 6},
        {3, 9},   {3, 10},  {4, 7},   {4, 9},
        {4, 11},  {5, 8},   {5, 10},  {5, 11},
        {6, 12},  {6, 13},  {7, 12},  {7, 14},
        {8, 13},  {8, 14},  {9, 12},  {9, 15},
        {10, 13}, {10, 15}, {11, 14}, {11, 15},
        {12, 16}, {13, 16}, {14, 16}, {15, 16},
    };

    int N = inf.readInt(0, 32, "N");
    inf.readEoln();

    set<pair<int,int>> seen;

    for (int i = 0; i < N; ++i) {
        int a = inf.readInt(1, 16, "a");
        inf.readSpace();
        int b = inf.readInt(1, 16, "b");
        inf.readEoln();

        ensuref(a < b,
                "Line %d after N: must satisfy 1 <= a < b <= 16, got a=%d, b=%d",
                i + 2, a, b);

        pair<int,int> e = {a, b};
        ensuref(faces.count(e), "tetrahedra %d and %d do not share a face", a, b);
        ensuref(!seen.count(e),
                "Duplicate face (%d, %d) on line %d",
                a, b, i + 2);
        seen.insert(e);
    }

    inf.readEof();
}
