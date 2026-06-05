#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string formatDuration(int minutes) {
    int hour = minutes / 60;
    int minute = minutes % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
    return string(buffer);
}

string makeName(int index) {
    string name;
    name.push_back(char('a' + index / 26));
    name.push_back(char('a' + index % 26));
    if (rnd.next(4) == 0) {
        int extra = rnd.next(1, 4);
        for (int i = 0; i < extra; ++i) {
            name.push_back(char('a' + rnd.next(26)));
        }
    }
    return name;
}

vector<int> splitTotal(int total) {
    int parts = rnd.next(1, min(5, total));
    vector<int> cuts;
    for (int i = 0; i < parts - 1; ++i) {
        cuts.push_back(rnd.next(1, total - 1));
    }
    cuts.push_back(0);
    cuts.push_back(total);
    sort(cuts.begin(), cuts.end());

    vector<int> pieces;
    for (int i = 1; i < (int)cuts.size(); ++i) {
        int piece = cuts[i] - cuts[i - 1];
        if (piece > 0) {
            pieces.push_back(piece);
        }
    }
    return pieces;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> targetTotals = {
        1, 10, 59, 60, 99, 100, 101, 149, 150, 151,
        199, 200, 201, 300, 719, 720, 1439
    };

    int studentCount = rnd.next(1, 8);
    vector<string> names;
    for (int i = 0; i < studentCount; ++i) {
        names.push_back(makeName(i));
    }
    shuffle(names.begin(), names.end());

    vector<pair<int, string>> records;
    for (int i = 0; i < studentCount; ++i) {
        int total;
        int mode = rnd.next(4);
        if (mode == 0) {
            total = rnd.any(targetTotals);
        } else if (mode == 1) {
            total = rnd.next(1, 180);
        } else if (mode == 2) {
            total = rnd.next(181, 600);
        } else {
            total = rnd.next(601, 1439);
        }

        vector<int> parts = splitTotal(total);
        for (int minutes : parts) {
            records.push_back({minutes, names[i]});
        }
    }

    shuffle(records.begin(), records.end());

    println((int)records.size());
    for (auto [minutes, name] : records) {
        println(formatDuration(minutes), name);
    }

    return 0;
}
