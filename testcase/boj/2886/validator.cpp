#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 100, "R");
    inf.readSpace();
    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    vector<pair<int, int>> people;
    vector<pair<int, int>> seats;

    for (int i = 0; i < r; ++i) {
        string row = inf.readToken("[.XL]{1,100}", "row");
        inf.readEoln();
        ensuref((int)row.size() == c, "row %d length is %d, expected %d", i + 1, (int)row.size(), c);

        for (int j = 0; j < c; ++j) {
            if (row[j] == 'X') {
                people.push_back({i, j});
            } else if (row[j] == 'L') {
                seats.push_back({i, j});
            }
        }
    }

    ensuref(!people.empty(), "there must be at least one X");
    ensuref(!seats.empty(), "there must be at least one L");

    for (int i = 0; i < (int)people.size(); ++i) {
        vector<bool> seen(2 * 99 * 99 + 1, false);
        for (int j = 0; j < (int)seats.size(); ++j) {
            int dr = people[i].first - seats[j].first;
            int dc = people[i].second - seats[j].second;
            int dist2 = dr * dr + dc * dc;
            ensuref(!seen[dist2],
                    "person %d has at least two seats at squared distance %d",
                    i + 1,
                    dist2);
            seen[dist2] = true;
        }
    }

    inf.readEof();
}
