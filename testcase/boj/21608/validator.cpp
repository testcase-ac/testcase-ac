#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 20, "N");
    inf.readEoln();

    int total = N * N;
    vector<bool> seen_student(total + 1, false);

    // For each of the N^2 students
    for (int i = 0; i < total; i++) {
        // Line index for error messages (first student line is line 2)
        int lineno = i + 2;

        // Read student id
        int sid = inf.readInt(1, total, "student_id");
        inf.readSpace();
        ensuref(!seen_student[sid],
                "Duplicate student id %d at input line %d", sid, lineno);
        seen_student[sid] = true;

        // Read 4 liked students
        vector<int> likes = inf.readInts(4, 1, total, "like");
        inf.readEoln();

        // Check liked students constraints
        // 1) All four must be distinct
        // 2) None equals sid
        // 3) No duplicates among the four
        {
            set<int> st;
            for (int j = 0; j < 4; j++) {
                int x = likes[j];
                ensuref(x != sid,
                        "Student %d (line %d) cannot like themselves",
                        sid, lineno);
                ensuref(!st.count(x),
                        "Duplicate liked student %d for student %d at line %d",
                        x, sid, lineno);
                st.insert(x);
            }
        }
    }

    // Ensure all student IDs 1..N^2 appeared exactly once
    for (int id = 1; id <= total; id++) {
        ensuref(seen_student[id],
                "Missing student id %d in input", id);
    }

    inf.readEof();
    return 0;
}
