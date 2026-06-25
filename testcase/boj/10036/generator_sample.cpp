#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<int> makePositions(int n) {
    vector<int> positions;

    int mode = rnd.next(0, 3);
    if (mode == 0) {
        int start = rnd.next(0, 100);
        int gap = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) positions.push_back(start + i * gap);
    } else if (mode == 1) {
        int start = rnd.next(0, 1000);
        int cur = start;
        for (int i = 0; i < n; ++i) {
            positions.push_back(cur);
            cur += rnd.next(1, 1000);
        }
    } else if (mode == 2) {
        set<int> used;
        while ((int)positions.size() < n) {
            int x = rnd.next(0, 1000000);
            if (used.insert(x).second) positions.push_back(x);
        }
        sort(positions.begin(), positions.end());
    } else {
        set<int> used;
        used.insert(0);
        if (n > 1) used.insert(1000000000);
        while ((int)used.size() < n) used.insert(rnd.next(1, 999999999));
        positions.assign(used.begin(), used.end());
    }

    return positions;
}

vector<char> makeBreeds(int n) {
    vector<char> breeds(n);
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        char breed = rnd.any(string("GH"));
        fill(breeds.begin(), breeds.end(), breed);
    } else if (mode == 1) {
        char first = rnd.any(string("GH"));
        for (int i = 0; i < n; ++i) breeds[i] = (i % 2 == 0 ? first : (first == 'G' ? 'H' : 'G'));
    } else if (mode == 2) {
        char first = rnd.any(string("GH"));
        int run = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            bool flip = (i / run) % 2 == 1;
            breeds[i] = (flip ? (first == 'G' ? 'H' : 'G') : first);
        }
    } else if (mode == 3) {
        int split = rnd.next(0, n - 1);
        char left = rnd.any(string("GH"));
        for (int i = 0; i < n; ++i) breeds[i] = (i <= split ? left : (left == 'G' ? 'H' : 'G'));
    } else if (mode == 4) {
        int targetG = rnd.next(0, n);
        fill(breeds.begin(), breeds.begin() + targetG, 'G');
        fill(breeds.begin() + targetG, breeds.end(), 'H');
        shuffle(breeds.begin(), breeds.end());
    } else {
        char common = rnd.any(string("GH"));
        int threshold = rnd.next(55, 85);
        for (int i = 0; i < n; ++i) {
            breeds[i] = (rnd.next(1, 100) <= threshold ? common : (common == 'G' ? 'H' : 'G'));
        }
    }

    return breeds;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 6) {
        n = rnd.next(2, 18);
    } else {
        n = rnd.next(19, 45);
    }

    vector<int> positions = makePositions(n);
    vector<char> breeds = makeBreeds(n);

    vector<pair<int, char>> cows;
    for (int i = 0; i < n; ++i) cows.push_back({positions[i], breeds[i]});

    if (rnd.next(0, 99) < 70) shuffle(cows.begin(), cows.end());

    println(n);
    for (auto cow : cows) println(cow.first, cow.second);

    return 0;
}
