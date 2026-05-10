#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int Nmin = 5;
    const int Nmax = 1000;

    int N = inf.readInt(Nmin, Nmax, "N");
    inf.readEoln();

    vector<string> g(N);
    for (int i = 0; i < N; ++i) {
        g[i] = inf.readLine("[*_]{"+toString(N)+"}", "row");
        ensuref((int)g[i].size() == N, "Row %d must have exactly %d characters", i+1, N);
    }

    inf.readEof();

    // Now validate that the grid represents exactly one valid cookie as described.

    // Find heart: first row where there is any '*' and where head exists above it.
    int heartR = -1, heartC = -1;
    bool foundHeart = false;
    for (int i = 0; i < N && !foundHeart; ++i) {
        for (int j = 0; j < N; ++j) {
            if (g[i][j] == '*') {
                // candidate head? heart is below this cell
                int r = i + 1;
                int c = j;
                if (r < N && g[r][c] == '*') {
                    heartR = r;
                    heartC = c;
                    foundHeart = true;
                    break;
                }
            }
        }
    }
    ensuref(foundHeart, "No valid heart position found");

    // Check head: exactly one '*' directly above heart, and it's isolated vertically
    ensuref(heartR - 1 >= 0 && g[heartR-1][heartC] == '*',
            "Head must exist directly above heart");
    // head must not extend further up
    ensuref(heartR - 2 < 0 || g[heartR-2][heartC] == '_',
            "Head must have length exactly 1");
    // Heart itself must be '*'
    ensuref(g[heartR][heartC] == '*', "Heart cell must be '*'");

    // Count arms on heart row
    int leftArm = 0, rightArm = 0;
    // left arm: continuous '*' leftwards from heartC-1
    for (int j = heartC - 1; j >= 0 && g[heartR][j] == '*'; --j) {
        leftArm++;
    }
    // right arm: continuous '*' rightwards from heartC+1
    for (int j = heartC + 1; j < N && g[heartR][j] == '*'; ++j) {
        rightArm++;
    }

    ensuref(leftArm >= 1, "Left arm length must be at least 1");
    ensuref(rightArm >= 1, "Right arm length must be at least 1");

    // Verify no stray '*' on heart row except arms and heart
    for (int j = 0; j < N; ++j) {
        bool allowed = false;
        if (j == heartC) allowed = true;
        else if (j < heartC && j >= heartC - leftArm) allowed = true;
        else if (j > heartC && j <= heartC + rightArm) allowed = true;
        if (!allowed) {
            ensuref(g[heartR][j] == '_',
                    "Unexpected '*' on heart row at (%d,%d)", heartR+1, j+1);
        }
    }

    // Waist: continuous '*' downwards starting just below heart
    int waist = 0;
    int waistEndR = heartR;
    for (int i = heartR + 1; i < N && g[i][heartC] == '*'; ++i) {
        waist++;
        waistEndR = i;
    }
    ensuref(waist >= 1, "Waist length must be at least 1");

    // Legs start at waistEndR+1 at columns heartC-1 and heartC+1
    int startLegR = waistEndR + 1;
    ensuref(startLegR < N, "Legs must exist (grid too short below waist)");

    int leftLegC = heartC - 1;
    int rightLegC = heartC + 1;
    ensuref(leftLegC >= 0 && rightLegC < N,
            "Leg positions must be within grid");

    // First cells for legs must be '*'
    ensuref(g[startLegR][leftLegC] == '*',
            "Left leg must start immediately below-left of waist at (%d,%d)",
            startLegR+1, leftLegC+1);
    ensuref(g[startLegR][rightLegC] == '*',
            "Right leg must start immediately below-right of waist at (%d,%d)",
            startLegR+1, rightLegC+1);

    // Count leg lengths
    int leftLeg = 0, rightLeg = 0;
    for (int i = startLegR; i < N && g[i][leftLegC] == '*'; ++i) {
        leftLeg++;
    }
    for (int i = startLegR; i < N && g[i][rightLegC] == '*'; ++i) {
        rightLeg++;
    }
    ensuref(leftLeg >= 1, "Left leg length must be at least 1");
    ensuref(rightLeg >= 1, "Right leg length must be at least 1");

    // Now verify global shape: all '*' cells belong to exactly one of
    // {head, heart, arms, waist, legs}.

    vector<vector<bool>> used(N, vector<bool>(N, false));

    // mark head
    used[heartR-1][heartC] = true;
    // mark heart
    used[heartR][heartC] = true;
    // mark arms
    for (int j = heartC - leftArm; j < heartC; ++j) used[heartR][j] = true;
    for (int j = heartC + 1; j <= heartC + rightArm; ++j) used[heartR][j] = true;
    // mark waist
    for (int i = heartR + 1; i <= waistEndR; ++i) used[i][heartC] = true;
    // mark legs
    for (int i = startLegR; i < startLegR + leftLeg; ++i) used[i][leftLegC] = true;
    for (int i = startLegR; i < startLegR + rightLeg; ++i) used[i][rightLegC] = true;

    // Ensure no other '*' exist outside the body, and no disconnected parts/gaps
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (g[i][j] == '*') {
                ensuref(used[i][j],
                        "Unexpected body part at (%d,%d)", i+1, j+1);
            } else { // '_'
                ensuref(!used[i][j],
                        "Marked body part must be '*' at (%d,%d)", i+1, j+1);
            }
        }
    }

    // Additional structural checks: ensure no breaks along each 1-width segment.

    // Waist uninterrupted: already ensured by construction (continuous '*')
    // Legs uninterrupted: also by construction. Arms uninterrupted: by construction.

    return 0;
}
