#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> randomComposition(int sum, int parts) {
    vector<int> cuts;
    for (int i = 1; i < sum; ++i) {
        cuts.push_back(i);
    }
    shuffle(cuts.begin(), cuts.end());
    cuts.resize(parts - 1);
    sort(cuts.begin(), cuts.end());

    vector<int> result;
    int previous = 0;
    for (int cut : cuts) {
        result.push_back(cut - previous);
        previous = cut;
    }
    result.push_back(sum - previous);
    return result;
}

static vector<int> makeShuffle(int mode) {
    vector<int> right;
    vector<int> left;

    if (mode == 0) {
        right = {14};
        left = {13};
    } else if (mode == 1) {
        right.assign(14, 1);
        left.assign(13, 1);
    } else if (mode == 2) {
        right = {rnd.next(1, 13)};
        right.push_back(14 - right[0]);
        left = {rnd.next(1, 12)};
        left.push_back(13 - left[0]);
    } else if (mode == 3) {
        int rightParts = rnd.next(2, 7);
        int leftParts = rightParts - rnd.next(0, 1);
        right = randomComposition(14, rightParts);
        left = randomComposition(13, leftParts);
    } else if (mode == 4) {
        int rightParts = rnd.next(7, 14);
        int leftParts = rightParts == 14 ? 13 : rightParts - rnd.next(0, 1);
        right = randomComposition(14, rightParts);
        left = randomComposition(13, leftParts);
    } else {
        int rightParts = rnd.next(1, 4);
        int leftParts = rightParts;
        right = randomComposition(14, rightParts);
        left = randomComposition(13, leftParts);
        if (rnd.next(0, 1)) {
            sort(right.begin(), right.end());
            reverse(right.begin(), right.end());
            sort(left.begin(), left.end());
        }
    }

    vector<int> line;
    for (int i = 0; i < (int)right.size(); ++i) {
        line.push_back(right[i]);
        if (i < (int)left.size()) {
            line.push_back(left[i]);
        }
    }
    return line;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(13, 40);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        int mode;
        if (i == 0 && rnd.next(0, 3) == 0) {
            mode = rnd.next(0, 1);
        } else {
            mode = rnd.next(0, 5);
        }
        println(makeShuffle(mode));
    }

    return 0;
}
