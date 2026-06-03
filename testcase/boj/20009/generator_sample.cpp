#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

string makeName(char prefix, int index) {
    string digits = to_string(index);
    while (digits.size() < 3) {
        digits = "0" + digits;
    }
    return string(1, prefix) + digits;
}

vector<int> identityOrder(int n) {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    return order;
}

vector<int> preferenceOrder(int n, int owner, int mode) {
    vector<int> order = identityOrder(n);

    if (mode == 0) {
        return order;
    }
    if (mode == 1) {
        reverse(order.begin(), order.end());
        return order;
    }
    if (mode == 2) {
        rotate(order.begin(), order.begin() + owner % n, order.end());
        return order;
    }
    if (mode == 3) {
        int split = max(1, n / 2);
        shuffle(order.begin(), order.begin() + split);
        shuffle(order.begin() + split, order.end());
        if (owner % 2 == 1) {
            rotate(order.begin(), order.begin() + split, order.end());
        }
        return order;
    }

    shuffle(order.begin(), order.end());
    return order;
}

void printNameLine(const vector<string>& names) {
    println(names);
}

void printPreferenceRows(const vector<string>& owners,
                         const vector<string>& choices,
                         int mode,
                         bool reverseOwners) {
    int n = static_cast<int>(owners.size());
    vector<int> rowOrder = identityOrder(n);
    if (reverseOwners) {
        reverse(rowOrder.begin(), rowOrder.end());
    }
    if (rnd.next(2) == 1) {
        shuffle(rowOrder.begin(), rowOrder.end());
    }

    for (int owner : rowOrder) {
        vector<string> row;
        row.reserve(n + 1);
        row.push_back(owners[owner]);

        vector<int> order = preferenceOrder(n, owner, mode);
        for (int choice : order) {
            row.push_back(choices[choice]);
        }
        println(row);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sizes = {1, 2, 3, 4, 5, 6, 8, 10, 12, 16};
    int n = rnd.any(sizes);
    if (rnd.next(5) == 0) {
        n = rnd.next(1, 25);
    }

    vector<string> men;
    vector<string> women;
    men.reserve(n);
    women.reserve(n);
    for (int i = 0; i < n; ++i) {
        men.push_back(makeName('m', i));
        women.push_back(makeName('w', i));
    }

    int menMode = rnd.next(0, 4);
    int womenMode = rnd.next(0, 4);

    println(n);
    printNameLine(men);
    printNameLine(women);
    printPreferenceRows(men, women, menMode, false);
    printPreferenceRows(women, men, womenMode, true);
}
