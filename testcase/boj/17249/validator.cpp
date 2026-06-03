#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[@=()^0]{1,1000}", "s");

    const string face = "(^0^)";
    size_t face_pos = s.find(face);
    ensuref(face_pos != string::npos, "face is missing");
    ensuref(s.find(face, face_pos + 1) == string::npos, "face appears more than once");

    string left = s.substr(0, face_pos);
    string right = s.substr(face_pos + face.size());
    ensuref(!left.empty(), "left afterimage is missing");
    ensuref(!right.empty(), "right afterimage is missing");

    int left_count = 0;
    for (size_t i = 0; i < left.size();) {
        ensuref(left[i] == '@', "left afterimage %d must start with @", left_count + 1);
        ++i;
        size_t start = i;
        while (i < left.size() && left[i] == '=') {
            ++i;
        }
        ensuref(i > start, "left afterimage %d has no = trail", left_count + 1);
        ++left_count;
    }

    int right_count = 0;
    for (size_t i = 0; i < right.size();) {
        size_t start = i;
        while (i < right.size() && right[i] == '=') {
            ++i;
        }
        ensuref(i > start, "right afterimage %d has no = trail", right_count + 1);
        ensuref(i < right.size() && right[i] == '@',
                "right afterimage %d must end with @", right_count + 1);
        ++i;
        ++right_count;
    }

    inf.readEof();
}
