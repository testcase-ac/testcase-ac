#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 15) {
        n = rnd.next(1, 3);
    } else {
        n = rnd.next(4, 18);
    }

    string grades;
    grades.reserve(n);
    for (int grade = 1; grade <= 3 && (int)grades.size() < n; ++grade) {
        if (rnd.next(100) < 75) {
            grades.push_back(char('0' + grade));
        }
    }
    while ((int)grades.size() < n) {
        grades.push_back(char('1' + rnd.next(3)));
    }
    shuffle(grades.begin(), grades.end());

    vector<string> dislikes(n, string(n, 'N'));
    vector<pair<int, int>> crossGradePairs;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (grades[i] != grades[j]) {
                crossGradePairs.push_back({i, j});
            }
        }
    }

    int mode = rnd.next(5);
    if (mode == 0) {
        int threshold = rnd.next(5, 35);
        for (auto [i, j] : crossGradePairs) {
            if (rnd.next(100) < threshold) {
                dislikes[i][j] = dislikes[j][i] = 'Y';
            }
        }
    } else if (mode == 1) {
        int threshold = rnd.next(45, 85);
        for (auto [i, j] : crossGradePairs) {
            if (rnd.next(100) < threshold) {
                dislikes[i][j] = dislikes[j][i] = 'Y';
            }
        }
    } else if (mode == 2) {
        int a = rnd.next(1, 3);
        int b = rnd.next(1, 3);
        while (b == a) {
            b = rnd.next(1, 3);
        }
        for (auto [i, j] : crossGradePairs) {
            bool chosenGradePair =
                (grades[i] == char('0' + a) && grades[j] == char('0' + b)) ||
                (grades[i] == char('0' + b) && grades[j] == char('0' + a));
            if (chosenGradePair && rnd.next(100) < 90) {
                dislikes[i][j] = dislikes[j][i] = 'Y';
            } else if (!chosenGradePair && rnd.next(100) < 15) {
                dislikes[i][j] = dislikes[j][i] = 'Y';
            }
        }
    } else if (mode == 3) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int x = 0; x + 1 < n; ++x) {
            int i = order[x], j = order[x + 1];
            if (grades[i] != grades[j]) {
                dislikes[i][j] = dislikes[j][i] = 'Y';
            }
        }
        for (auto [i, j] : crossGradePairs) {
            if (rnd.next(100) < 10) {
                dislikes[i][j] = dislikes[j][i] = 'Y';
            }
        }
    } else {
        shuffle(crossGradePairs.begin(), crossGradePairs.end());
        int take = crossGradePairs.empty() ? 0 : rnd.next(0, (int)crossGradePairs.size());
        for (int k = 0; k < take; ++k) {
            int i = crossGradePairs[k].first;
            int j = crossGradePairs[k].second;
            dislikes[i][j] = dislikes[j][i] = 'Y';
        }
    }

    println(n);
    println(grades);
    for (const string& row : dislikes) {
        println(row);
    }

    return 0;
}
