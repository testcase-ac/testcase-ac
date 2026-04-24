#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of measures
    int M = rnd.next(3, 5);
    // Scenario: 0 = minor wins, 1 = major wins, 2 = tie→A-minor, 3 = tie→C-major
    int scenario = rnd.next(0, 3);
    const string minorCent = "ADE";
    const string majorCent = "CFG";

    // Decide first notes of each measure
    vector<char> firstnotes(M);
    if (scenario < 2) {
        // Non-tie: bias probabilities to ensure win
        double p_minor, p_major;
        if (scenario == 0) {
            p_minor = rnd.next(0.6, 0.9);
            p_major = rnd.next(0.0, 1.0 - p_minor);
        } else {
            p_major = rnd.next(0.6, 0.9);
            p_minor = rnd.next(0.0, 1.0 - p_major);
        }
        double p_neu = 1 - p_minor - p_major;

        int cntM, cntm;
        do {
            cntM = cntm = 0;
            for (int i = 0; i < M; i++) {
                double r = rnd.next();
                if (r < p_minor) {
                    firstnotes[i] = rnd.any(minorCent);
                    cntm++;
                } else if (r < p_minor + p_major) {
                    firstnotes[i] = rnd.any(majorCent);
                    cntM++;
                } else {
                    firstnotes[i] = 'B';
                }
            }
        } while ((scenario == 0 && cntm <= cntM) || (scenario == 1 && cntM <= cntm));
    } else {
        // Tie scenario: equal counts of minor & major, plus neutrals
        int maxX = M / 2;
        int X = rnd.next(0, maxX);
        int neutrals = M - 2 * X;
        vector<char> tmp;
        tmp.reserve(M);
        for (int i = 0; i < X; i++) tmp.push_back(rnd.any(minorCent));
        for (int i = 0; i < X; i++) tmp.push_back(rnd.any(majorCent));
        for (int i = 0; i < neutrals; i++) tmp.push_back('B');
        shuffle(tmp.begin(), tmp.end());
        firstnotes = tmp;
    }

    // Generate measure lengths, ensure last measure >1 in tie so we can override last note
    vector<int> lens(M);
    for (int i = 0; i < M; i++) {
        lens[i] = rnd.next(1, 3);
    }
    if (scenario >= 2 && lens[M-1] == 1) {
        lens[M-1] = rnd.next(2, 3);
    }

    // Build measures
    vector<string> measures(M);
    for (int i = 0; i < M; i++) {
        measures[i].resize(lens[i]);
        measures[i][0] = firstnotes[i];
        for (int j = 1; j < lens[i]; j++) {
            measures[i][j] = rnd.any(string("ABCDEFG"));
        }
    }
    // In tie scenarios, override the last note to break the tie
    if (scenario >= 2) {
        if (scenario == 2) {
            // tie → A-minor
            measures[M-1][lens[M-1] - 1] = rnd.any(minorCent);
        } else {
            // tie → C-major
            measures[M-1][lens[M-1] - 1] = rnd.any(majorCent);
        }
    }

    // Join and output
    string s;
    for (int i = 0; i < M; i++) {
        if (i > 0) s.push_back('|');
        s += measures[i];
    }
    println(s);

    return 0;
}
