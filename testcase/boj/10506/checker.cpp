#include "testlib.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int T;
vector<int> n_list;
vector<vector<int>> sequences;

int currentTestCase = -1;

enum Verdict { NO, VALID };

struct Answer {
    Verdict verdict;
    string choices;
};

// Simulates the merging process according to the participant's choices
bool simulateMerging(const vector<int>& blocks, const string& choices) {
    vector<int> sequence;
    int n = blocks.size();
    // Initialize the sequence with the first block
    sequence.push_back(blocks[0]);
    for (int i = 1; i < n; ++i) {
        int block = blocks[i];
        char choice = choices[i];
        if (choice == 'l') {
            sequence.insert(sequence.begin(), block);
        } else if (choice == 'r') {
            sequence.push_back(block);
        } else {
            return false; // Invalid character
        }
        // Now merge adjacent blocks as per the rules
        bool merged;
        do {
            merged = false;
            for (int j = 0; j < (int)sequence.size() - 1; ++j) {
                if (sequence[j] == sequence[j + 1]) {
                    sequence[j] *= 2;
                    sequence.erase(sequence.begin() + j + 1);
                    merged = true;
                    break; // Restart merging from the beginning
                }
            }
        } while (merged);
    }
    // Check if we have a single block at the end
    return sequence.size() == 1;
}

Answer readAns(InStream& stream, int n, const vector<int>& blocks) {
    string s = stream.readLine();
    s = trim(s);  // Use the trim function from testlib.h

    if (s == "no") {
        return {NO, ""};
    } else {
        if ((int)s.length() != n) {
            stream.quitf(_pe, "Expected a string of length %d, but got length %d", n, (int)s.length());
        }
        for (char c : s) {
            if (c != 'l' && c != 'r') {
                stream.quitf(_pe, "Invalid character '%c' in the choices, expected 'l' or 'r'", c);
            }
        }
        // Simulate the merging process
        bool success = simulateMerging(blocks, s);
        if (success) {
            return {VALID, s};
        } else {
            stream.quitf(_wa, "The choices do not lead to a single block in test case %d", currentTestCase + 1);
        }
    }
    // Should not reach here
    return {NO, ""};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    T = inf.readInt();
    n_list.resize(T);
    sequences.resize(T);

    for (int testCase = 0; testCase < T; ++testCase) {
        inf.readEoln();
        int n = inf.readInt();
        n_list[testCase] = n;
        vector<int> blocks(n);
        inf.readEoln();
        for (int i = 0; i < n; ++i) {
            blocks[i] = inf.readInt();
            if (i != n - 1) inf.readSpace();
            if (blocks[i] <= 0 || (blocks[i] & (blocks[i] - 1)) != 0) {
                quitf(_fail, "Invalid block length %d, not a power of two", blocks[i]);
            }
        }
        sequences[testCase] = blocks;
    }

    for (int testCase = 0; testCase < T; ++testCase) {
        currentTestCase = testCase;
        int n = n_list[testCase];
        const vector<int>& blocks = sequences[testCase];

        // Read jury's answer
        Answer juryAns = readAns(ans, n, blocks);

        // Read participant's answer
        Answer contAns = readAns(ouf, n, blocks);

        // Compare the answers
        if (juryAns.verdict == NO) {
            if (contAns.verdict == NO) {
                // Both say 'no', accept
                continue;
            } else {
                // Participant found a valid solution, but jury said 'no'
                quitf(_fail, "Participant found a valid solution, but jury said 'no' in test case %d", testCase + 1);
            }
        } else {
            if (contAns.verdict == NO) {
                // Participant says 'no', but a solution exists
                quitf(_wa, "Participant says 'no', but a solution exists in test case %d", testCase + 1);
            } else {
                // Both provided valid solutions
                continue;
            }
        }
    }

    // All test cases passed
    quitf(_ok, "All test cases passed");
}
