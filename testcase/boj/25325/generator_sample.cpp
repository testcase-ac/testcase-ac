#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

string nameFromIndex(int index) {
    string name;
    do {
        name.push_back(char('a' + index % 26));
        index = index / 26 - 1;
    } while (index >= 0);
    reverse(name.begin(), name.end());
    return name;
}

vector<int> pickLikedStudents(int n, int self, int mode) {
    vector<int> candidates;
    for (int i = 0; i < n; ++i) {
        if (i != self) {
            candidates.push_back(i);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int count = 1;
    if (mode == 0) {
        count = 1;
    } else if (mode == 1) {
        count = rnd.next(1, min(n - 1, 2));
    } else if (mode == 2) {
        count = rnd.next(max(1, n / 2), n - 1);
    } else if (mode == 3) {
        count = n - 1;
    } else {
        count = rnd.next(1, n - 1);
    }

    candidates.resize(count);
    sort(candidates.begin(), candidates.end());
    return candidates;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, mode == 2 || mode == 3 ? 18 : 10);

    vector<string> names;
    for (int i = 0; i < n; ++i) {
        names.push_back(nameFromIndex(i));
    }
    shuffle(names.begin(), names.end());

    println(n);
    println(names);

    for (int i = 0; i < n; ++i) {
        vector<int> liked = pickLikedStudents(n, i, mode);

        if (mode == 4 && rnd.next(0, 3) == 0) {
            shuffle(liked.begin(), liked.end());
        }

        for (int j = 0; j < (int)liked.size(); ++j) {
            if (j > 0) {
                cout << ' ';
            }
            cout << names[liked[j]];
        }
        cout << '\n';
    }

    return 0;
}
