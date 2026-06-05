#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string memberName(int index) {
    string name;
    do {
        name.push_back(char('A' + (index % 26)));
        index /= 26;
    } while (index > 0);
    reverse(name.begin(), name.end());
    return name;
}

void addLike(vector<vector<int>>& likes, int friendIndex, int memberIndex) {
    vector<int>& row = likes[friendIndex];
    if (find(row.begin(), row.end(), memberIndex) == row.end()) {
        row.push_back(memberIndex);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);
    vector<vector<int>> likes(n);

    if (mode == 0) {
        m = max(m, n);
        for (int i = 0; i < n; ++i) {
            addLike(likes, i, i);
        }
        for (int i = 0; i < n; ++i) {
            int extra = rnd.next(0, min(m - 1, 4));
            while ((int)likes[i].size() < extra + 1) {
                addLike(likes, i, rnd.next(m));
            }
        }
    } else if (mode == 1) {
        int limited = rnd.next(1, min(m, max(1, n - 1)));
        for (int i = 0; i < n; ++i) {
            int k = rnd.next(1, limited);
            set<int> chosen;
            while ((int)chosen.size() < k) {
                chosen.insert(rnd.next(limited));
            }
            likes[i] = vector<int>(chosen.begin(), chosen.end());
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int k = rnd.next(max(1, m / 2), m);
            set<int> chosen;
            while ((int)chosen.size() < k) {
                chosen.insert(rnd.next(m));
            }
            likes[i] = vector<int>(chosen.begin(), chosen.end());
        }
    } else {
        m = max(m, n);
        for (int i = 0; i < n; ++i) {
            addLike(likes, i, i);
            if (i + 1 < m) {
                addLike(likes, i, i + 1);
            }
            if (i > 0 && rnd.next(2) == 0) {
                addLike(likes, i, i - 1);
            }
        }
        if (rnd.next(2) == 0) {
            likes.back().clear();
            addLike(likes, n - 1, rnd.next(n - 1));
        }
    }

    vector<string> names;
    for (int i = 0; i < m; ++i) {
        names.push_back(memberName(i));
    }

    for (auto& row : likes) {
        shuffle(row.begin(), row.end());
    }

    println(n, m);
    for (const string& name : names) {
        println(name);
    }
    for (const vector<int>& row : likes) {
        printf("%d", (int)row.size());
        for (int memberIndex : row) {
            printf(" %s", names[memberIndex].c_str());
        }
        printf("\n");
    }

    return 0;
}
