#include "testlib.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int N, K, A, B;
vector<string> codes;

// compute Hamming distance between two binary strings of length K
int hamming(const string &a, const string &b) {
    int cnt = 0;
    for (int i = 0; i < K; i++)
        if (a[i] != b[i])
            cnt++;
    return cnt;
}

// Reads one answer (either from jury or participant), validates it,
// and returns the number of vertices in the path, or -1 if "-1".
int readAns(InStream &stream) {
    // Make sure there's something to read
    if (stream.seekEof())
        stream.quitf(_wa, "unexpected end of output");

    // Read the entire next line
    string line = stream.readLine();
    // Trim leading/trailing spaces
    while (!line.empty() && isspace(line.back())) line.pop_back();
    int pos = 0;
    while (pos < (int)line.size() && isspace(line[pos])) pos++;
    if (pos > 0) line = line.substr(pos);

    if (line.empty())
        stream.quitf(_wa, "empty line in output");

    istringstream iss(line);
    vector<int> path;
    int x;
    if (!(iss >> x))
        stream.quitf(_wa, "cannot read first token");

    // case: no path
    if (x == -1) {
        // ensure no extra tokens
        if (iss >> x)
            stream.quitf(_wa, "extra tokens after -1");
        return -1;
    }

    // otherwise it's a path
    path.push_back(x);
    while (iss >> x) {
        path.push_back(x);
    }

    // path must have at least 2 vertices (A != B)
    if ((int)path.size() < 2)
        stream.quitf(_wa, "path too short: length = %d", (int)path.size());

    // check vertex IDs and no repeats
    vector<bool> used(N, false);
    for (int v : path) {
        if (v < 1 || v > N)
            stream.quitf(_wa, "vertex id %d out of range [1..%d]", v, N);
        if (used[v - 1])
            stream.quitf(_wa, "vertex %d is visited twice", v);
        used[v - 1] = true;
    }

    // check start and end
    if (path.front() != A)
        stream.quitf(_wa, "path should start at %d but starts at %d", A, path.front());
    if (path.back() != B)
        stream.quitf(_wa, "path should end at %d but ends at %d", B, path.back());

    // check each adjacent pair has Hamming distance == 1
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        int u = path[i] - 1, v = path[i + 1] - 1;
        if (hamming(codes[u], codes[v]) != 1)
            stream.quitf(_wa, "codes %d and %d are not adjacent", path[i], path[i+1]);
    }

    // return number of vertices
    return (int)path.size();
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // read input
    N = inf.readInt();
    K = inf.readInt();
    codes.resize(N);
    for (int i = 0; i < N; i++)
        codes[i] = inf.readToken();
    A = inf.readInt();
    B = inf.readInt();

    // read jury and participant answers
    int jans = readAns(ans);
    int pans = readAns(ouf);

    // compare
    if (jans == -1) {
        // no path exists
        if (pans == -1)
            quitf(_ok, "correctly reports no path");
        else
            quitf(_wa, "found a path, but none exists");
    } else {
        // path exists
        if (pans == -1)
            quitf(_wa, "reports no path, but a path of length %d exists", jans);
        if (pans > jans)
            quitf(_wa, "path too long: expected length %d, found %d", jans, pans);
        if (pans < jans)
            quitf(_fail, "participant found shorter path than jury: jury %d, participant %d", jans, pans);
        // pans == jans
        quitf(_ok, "correct, path length = %d", pans);
    }
    return 0;
}
