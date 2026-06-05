#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> poses = {
        ".omln",
        "owln.",
        "..oLn",
    };

    int mode = rnd.next(0, 4);
    int width = 1;
    if (mode == 0) {
        width = rnd.next(1, 4);
    } else if (mode == 1) {
        width = rnd.next(5, 12);
    } else if (mode == 2) {
        width = rnd.next(8, 24);
    } else if (mode == 3) {
        width = rnd.next(12, 30);
    } else {
        width = rnd.next(20, 45);
    }

    vector<int> columns;
    columns.reserve(width);

    if (mode == 0) {
        int pose = rnd.next(0, 2);
        for (int i = 0; i < width; ++i) {
            if (rnd.next(0, 3) == 0) pose = rnd.next(0, 2);
            columns.push_back(pose);
        }
    } else if (mode == 1) {
        for (int i = 0; i < width; ++i) {
            columns.push_back(i % 3);
        }
        if (rnd.next(0, 1)) {
            int shift = rnd.next(0, 2);
            for (int& pose : columns) pose = (pose + shift) % 3;
        }
    } else if (mode == 2) {
        int first = rnd.next(0, 2);
        int second = rnd.next(0, 2);
        while (second == first) second = rnd.next(0, 2);
        for (int i = 0; i < width; ++i) {
            columns.push_back((i % 2 == 0) ? first : second);
        }
    } else if (mode == 3) {
        while ((int)columns.size() < width) {
            int pose = rnd.next(0, 2);
            int run = rnd.next(1, 6);
            while (run-- > 0 && (int)columns.size() < width) {
                columns.push_back(pose);
            }
        }
    } else {
        array<int, 3> weights = {
            rnd.next(1, 8),
            rnd.next(1, 8),
            rnd.next(1, 8),
        };
        int total = weights[0] + weights[1] + weights[2];
        for (int i = 0; i < width; ++i) {
            int pick = rnd.next(1, total);
            if (pick <= weights[0]) {
                columns.push_back(0);
            } else if (pick <= weights[0] + weights[1]) {
                columns.push_back(1);
            } else {
                columns.push_back(2);
            }
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(columns.begin(), columns.end());
    }

    vector<string> rows(5, string(width, '.'));
    for (int col = 0; col < width; ++col) {
        const string& pose = poses[columns[col]];
        for (int row = 0; row < 5; ++row) {
            rows[row][col] = pose[row];
        }
    }

    for (const string& row : rows) {
        println(row);
    }

    return 0;
}
