#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

// Returns true if there exists a partition into 3 non-empty groups
// (upper, middle, lower) such that:
// - For any student in group X and any student in group Y, if X > Y
//   then student's (A,B) in X is strictly greater in both A and B than any in Y.
bool is_partition_possible(const vector<pair<int,int>>& students) {
    int N = students.size();
    // Sort students by (A, B)
    vector<pair<int,int>> sorted = students;
    sort(sorted.begin(), sorted.end());

    // Precompute prefix min/max and suffix min/max for both A and B
    vector<int> prefix_maxA(N), prefix_maxB(N), prefix_minA(N), prefix_minB(N);
    vector<int> suffix_minA(N), suffix_minB(N), suffix_maxA(N), suffix_maxB(N);

    prefix_maxA[0] = sorted[0].first;
    prefix_maxB[0] = sorted[0].second;
    prefix_minA[0] = sorted[0].first;
    prefix_minB[0] = sorted[0].second;
    for (int i = 1; i < N; ++i) {
        prefix_maxA[i] = max(prefix_maxA[i-1], sorted[i].first);
        prefix_maxB[i] = max(prefix_maxB[i-1], sorted[i].second);
        prefix_minA[i] = min(prefix_minA[i-1], sorted[i].first);
        prefix_minB[i] = min(prefix_minB[i-1], sorted[i].second);
    }
    suffix_minA[N-1] = sorted[N-1].first;
    suffix_minB[N-1] = sorted[N-1].second;
    suffix_maxA[N-1] = sorted[N-1].first;
    suffix_maxB[N-1] = sorted[N-1].second;
    for (int i = N-2; i >= 0; --i) {
        suffix_minA[i] = min(suffix_minA[i+1], sorted[i].first);
        suffix_minB[i] = min(suffix_minB[i+1], sorted[i].second);
        suffix_maxA[i] = max(suffix_maxA[i+1], sorted[i].first);
        suffix_maxB[i] = max(suffix_maxB[i+1], sorted[i].second);
    }

    // For all possible (i, j) with 0 < i < j < N, try to split into [0,i-1], [i,j-1], [j,N-1]
    // Each group must be non-empty
    for (int i = 1; i <= N-2; ++i) {
        for (int j = i+1; j <= N-1; ++j) {
            // Group 1: [0, i-1], Group 2: [i, j-1], Group 3: [j, N-1]
            // For group 1 (lower), group 2 (middle), group 3 (upper)
            // We need: minA_2 > maxA_1 && minB_2 > maxB_1
            //          minA_3 > maxA_2 && minB_3 > maxB_2
            int maxA_1 = prefix_maxA[i-1];
            int maxB_1 = prefix_maxB[i-1];
            int minA_2 = prefix_minA[j-1];
            int minB_2 = prefix_minB[j-1];
            int maxA_2 = prefix_maxA[j-1];
            int maxB_2 = prefix_maxB[j-1];
            if (i > 0) {
                minA_2 = prefix_minA[j-1];
                minB_2 = prefix_minB[j-1];
                if (i > 1) {
                    minA_2 = min(minA_2, prefix_minA[i]);
                    minB_2 = min(minB_2, prefix_minB[i]);
                }
            }
            int minA_3 = suffix_minA[j];
            int minB_3 = suffix_minB[j];
            if (minA_2 > maxA_1 && minB_2 > maxB_1 &&
                minA_3 > maxA_2 && minB_3 > maxB_2) {
                return true;
            }
        }
    }
    return false;
}

// More efficient: Instead of O(N^2), let's use a sweep line approach
// For all possible (A_cut, B_cut), try to split into 3 groups
// But for validator, we only need to check if possible at all, not minimal imbalance
// Let's use a more efficient approach: sort by A, then for each possible split point, maintain B's
bool is_partition_possible_fast(const vector<pair<int,int>>& students) {
    int N = students.size();
    // Sort by A, then by B
    vector<pair<int,int>> sorted = students;
    sort(sorted.begin(), sorted.end());

    // For each possible (i, j) with 0 < i < j < N, we want:
    // max(B in [0,i-1]) < min(B in [i,j-1]) < min(B in [j,N-1])
    // But we can do this efficiently by maintaining prefix/suffix min/max
    vector<int> B(N);
    for (int i = 0; i < N; ++i) B[i] = sorted[i].second;

    vector<int> prefix_maxB(N), prefix_minB(N), suffix_minB(N), suffix_maxB(N);
    prefix_maxB[0] = B[0];
    prefix_minB[0] = B[0];
    for (int i = 1; i < N; ++i) {
        prefix_maxB[i] = max(prefix_maxB[i-1], B[i]);
        prefix_minB[i] = min(prefix_minB[i-1], B[i]);
    }
    suffix_minB[N-1] = B[N-1];
    suffix_maxB[N-1] = B[N-1];
    for (int i = N-2; i >= 0; --i) {
        suffix_minB[i] = min(suffix_minB[i+1], B[i]);
        suffix_maxB[i] = max(suffix_maxB[i+1], B[i]);
    }

    // For each possible i, j (i: end of group 1, j: end of group 2)
    // We can fix i, then binary search j
    for (int i = 1; i <= N-2; ++i) {
        // Group 1: [0, i-1], Group 2: [i, j-1], Group 3: [j, N-1]
        // For group 2 to exist, i < j < N
        // For group 3 to exist, j < N
        // For group 2: B in [i, j-1], for group 3: B in [j, N-1]
        // We want min(B in group 2) > max(B in group 1)
        // and min(B in group 3) > max(B in group 2)
        int maxB1 = prefix_maxB[i-1];
        // For group 2, try all possible j
        for (int j = i+1; j <= N-1; ++j) {
            int minB2 = prefix_minB[j-1];
            int maxB2 = prefix_maxB[j-1];
            if (i > 0) {
                minB2 = min(minB2, prefix_minB[i]);
                maxB2 = max(maxB2, prefix_maxB[i]);
            }
            int minB3 = suffix_minB[j];
            if (minB2 > maxB1 && minB3 > maxB2) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    vector<pair<int,int>> students;
    students.reserve(N);

    for (int i = 0; i < N; ++i) {
        int A = inf.readInt(0, 1000000, "A_i");
        inf.readSpace();
        int B = inf.readInt(0, 1000000, "B_i");
        inf.readEoln();
        students.emplace_back(A, B);
    }

    // Check that all students are unique in (A,B) is NOT required by statement.

    // Validate that it is possible to assign grades according to the rules,
    // i.e., that there exists a partition into 3 non-empty groups such that
    // for any higher group, all (A,B) are strictly greater in both A and B
    // than any in lower group.
    // If not possible, the output should be -1, so input must allow for -1.
    // But the statement says: "만약 선생님이 조건에 맞게 등급을 부여하는 것이 불가능하다면, -1을 출력한다."
    // So, input can be impossible.

    // No global property to check except that all numbers are in range and N in range.

    inf.readEof();
}
