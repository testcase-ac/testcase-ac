#include "testlib.h"
#include <cctype>
#include <cstdio>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of scenarios
    int ts = inf.readInt(1, 100000, "number_of_scenarios");
    inf.readEoln();

    for (int tc = 1; tc <= ts; tc++) {
        // Top face (3 lines, each with 6 leading spaces and 3 tokens)
        for (int i = 0; i < 3; i++) {
            char name[50];
            sprintf(name, "top_line_%d", i+1);
            string line = inf.readLine("[^]+", name);
            // Expected exact length: 6 spaces + 3 chars + 2 spaces between them = 11
            ensuref((int)line.size() == 11,
                    "Line %d of top side: expected length 11, got %d", i+1, (int)line.size());
            // Check indent
            for (int k = 0; k < 6; k++)
                ensuref(line[k] == ' ',
                        "Line %d of top side: expected space at position %d", i+1, k);
            // Check tokens and separators
            ensuref(!isspace(line[6]),
                    "Line %d of top side: expected color at position 6", i+1);
            ensuref(line[7] == ' ',
                    "Line %d of top side: expected space at position 7", i+1);
            ensuref(!isspace(line[8]),
                    "Line %d of top side: expected color at position 8", i+1);
            ensuref(line[9] == ' ',
                    "Line %d of top side: expected space at position 9", i+1);
            ensuref(!isspace(line[10]),
                    "Line %d of top side: expected color at position 10", i+1);
        }

        // Middle 4 faces in 3 lines: each line has 4 groups of 3 tokens,
        // groups and tokens separated by single spaces: total length = 12 chars + 11 spaces = 23.
        for (int i = 0; i < 3; i++) {
            char name[50];
            sprintf(name, "middle_line_%d", i+1);
            string line = inf.readLine("[^]+", name);
            ensuref((int)line.size() == 23,
                    "Middle line %d: expected length 23, got %d", i+1, (int)line.size());
            for (int j = 0; j < 23; j++) {
                if (j % 2 == 0) {
                    // token position
                    ensuref(!isspace(line[j]),
                            "Middle line %d: expected color at position %d", i+1, j);
                } else {
                    // must be single space
                    ensuref(line[j] == ' ',
                            "Middle line %d: expected space at position %d", i+1, j);
                }
            }
        }

        // Bottom face (same format as top)
        for (int i = 0; i < 3; i++) {
            char name[50];
            sprintf(name, "bottom_line_%d", i+1);
            string line = inf.readLine("[^]+", name);
            ensuref((int)line.size() == 11,
                    "Line %d of bottom side: expected length 11, got %d", i+1, (int)line.size());
            for (int k = 0; k < 6; k++)
                ensuref(line[k] == ' ',
                        "Line %d of bottom side: expected space at position %d", i+1, k);
            ensuref(!isspace(line[6]),
                    "Line %d of bottom side: expected color at position 6", i+1);
            ensuref(line[7] == ' ',
                    "Line %d of bottom side: expected space at position 7", i+1);
            ensuref(!isspace(line[8]),
                    "Line %d of bottom side: expected color at position 8", i+1);
            ensuref(line[9] == ' ',
                    "Line %d of bottom side: expected space at position 9", i+1);
            ensuref(!isspace(line[10]),
                    "Line %d of bottom side: expected color at position 10", i+1);
        }

        // Number of turns
        int t = inf.readInt(1, 1000000000, "t");
        inf.readEoln();
        // Each turn: side s in [0,5], direction d in {-1,1}
        for (int i = 0; i < t; i++) {
            int s = inf.readInt(0, 5, "s");
            inf.readSpace();
            int d = inf.readInt(-1, 1, "d");
            ensuref(d == 1 || d == -1,
                    "Direction must be 1 or -1, got %d at turn %d", d, i+1);
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
