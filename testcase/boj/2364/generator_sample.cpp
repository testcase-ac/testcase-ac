#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

void triangulate(int left, int right, vector<vector<int>>& faces) {
    if (right - left + 1 == 3) {
        faces.push_back({left, left + 1, right});
        return;
    }

    int split = rnd.next(left + 1, right - 1);
    faces.push_back({left, split, right});

    if (split - left + 1 >= 3) {
        triangulate(left, split, faces);
    }
    if (right - split + 1 >= 3) {
        triangulate(split, right, faces);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 4);
    if (sizeMode == 0) {
        n = 3;
    } else if (sizeMode == 1) {
        n = rnd.next(4, 7);
    } else if (sizeMode == 2) {
        n = rnd.next(8, 14);
    } else {
        n = rnd.next(15, 24);
    }

    vector<vector<int>> faces;
    triangulate(1, n, faces);

    int m = (int)faces.size() + 1;
    int l = rnd.next(1, min(30, n));

    vector<int> towns(n);
    iota(towns.begin(), towns.end(), 1);
    shuffle(towns.begin(), towns.end());
    towns.resize(l);
    sort(towns.begin(), towns.end());

    println(m);
    println(n);
    println(l);
    println(towns);

    shuffle(faces.begin(), faces.end());
    for (const auto& face : faces) {
        println((int)face.size());
        println(face);
    }

    vector<int> outer(n);
    for (int i = 0; i < n; ++i) {
        outer[i] = n - i;
    }
    println(n);
    println(outer);

    return 0;
}
