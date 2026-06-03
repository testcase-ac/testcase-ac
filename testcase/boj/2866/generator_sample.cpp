#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int length, int alphabetSize) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(char('a' + rnd.next(alphabetSize)));
    }
    return result;
}

vector<string> makeUniqueColumns(int r, int c, int alphabetSize) {
    vector<string> columns;
    columns.reserve(c);
    while ((int)columns.size() < c) {
        string candidate = randomString(r, alphabetSize);
        if (find(columns.begin(), columns.end(), candidate) == columns.end()) {
            columns.push_back(candidate);
        }
    }
    return columns;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int r = rnd.next(2, 28);
    int c = rnd.next(2, min(28, r * 2 + 8));
    int alphabetSize = rnd.next(6, 10);

    vector<string> columns;
    if (mode == 0) {
        columns = makeUniqueColumns(r, c, alphabetSize);
    } else {
        int answer = 0;
        if (r >= 3) {
            if (mode == 1) {
                answer = 0;
            } else if (mode == 2) {
                answer = rnd.next(1, r - 2);
            } else {
                answer = r - 2;
            }
        }

        int sharedSuffixLen = r - answer - 1;
        string sharedSuffix = randomString(sharedSuffixLen, alphabetSize);

        columns.assign(c, string());
        columns[0] = string(answer + 1, 'a') + sharedSuffix;
        columns[1] = string(answer, 'a') + "b" + sharedSuffix;

        for (int col = 2; col < c; ++col) {
            while (true) {
                string candidate = randomString(r, alphabetSize);
                bool ok = true;
                for (int prev = 0; prev < col; ++prev) {
                    if (candidate == columns[prev] ||
                        candidate.substr(answer) == columns[prev].substr(answer)) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    columns[col] = candidate;
                    break;
                }
            }
        }

        shuffle(columns.begin(), columns.end());
    }

    println(r, c);
    for (int row = 0; row < r; ++row) {
        string line;
        line.reserve(c);
        for (int col = 0; col < c; ++col) {
            line.push_back(columns[col][row]);
        }
        println(line);
    }

    return 0;
}
