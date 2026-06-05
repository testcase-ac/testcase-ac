#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> relabel(vector<int> colors, int k) {
    vector<int> labels(k);
    for (int i = 0; i < k; ++i) labels[i] = i + 1;
    shuffle(labels.begin(), labels.end());

    for (int& color : colors) color = labels[color - 1];
    return colors;
}

static void printCase(const vector<int>& colors, int k) {
    println(static_cast<int>(colors.size()), k);
    for (int color : colors) println(color);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = rnd.next(1, 10);
    vector<int> colors;

    if (mode == 0) {
        // Every color appears once, so no double rainbow can exist.
        colors.resize(k);
        for (int i = 0; i < k; ++i) colors[i] = i + 1;
        shuffle(colors.begin(), colors.end());
    } else if (mode == 1) {
        // Two copies per color, with the two rainbows often separated cleanly.
        colors.reserve(2 * k);
        for (int pass = 0; pass < 2; ++pass) {
            vector<int> block(k);
            for (int i = 0; i < k; ++i) block[i] = i + 1;
            shuffle(block.begin(), block.end());
            colors.insert(colors.end(), block.begin(), block.end());
        }
    } else if (mode == 2) {
        // Long runs stress windows that must shrink across repeated colors.
        for (int color = 1; color <= k; ++color) {
            int run = rnd.next(1, 5);
            colors.insert(colors.end(), run, color);
        }
        for (int color = k; color >= 1; --color) {
            int run = rnd.next(1, 5);
            colors.insert(colors.end(), run, color);
        }
    } else if (mode == 3) {
        // A complete rainbow appears in the middle, with random outside support.
        int side = rnd.next(k, 3 * k);
        colors.reserve(2 * side + k);
        for (int i = 0; i < side; ++i) colors.push_back(rnd.next(1, k));
        for (int color = 1; color <= k; ++color) colors.push_back(color);
        for (int i = 0; i < side; ++i) colors.push_back(rnd.next(1, k));
    } else if (mode == 4) {
        // Small random instance, repaired to include every color.
        int n = rnd.next(k, min(80, max(k, 8 * k)));
        colors.resize(n);
        for (int i = 0; i < n; ++i) colors[i] = rnd.next(1, k);
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int color = 1; color <= k; ++color) colors[positions[color - 1]] = color;
    } else {
        // Larger hand-checkable case near the validator's shape, but still compact.
        k = rnd.next(5, 20);
        int n = rnd.next(2 * k, min(120, 6 * k));
        colors.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 65) {
                colors[i] = 1 + (i % k);
            } else {
                colors[i] = rnd.next(1, k);
            }
        }
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int color = 1; color <= k; ++color) colors[positions[color - 1]] = color;
    }

    if (rnd.next(0, 1) == 1) shuffle(colors.begin(), colors.end());
    colors = relabel(colors, k);
    printCase(colors, k);

    return 0;
}
