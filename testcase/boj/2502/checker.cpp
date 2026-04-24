#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

// We read D, K from the input file (inf).
// Then we'll read solutions from ans (jury's output) and ouf (contestant's output).

// This function reads A, B from stream, checks correctness (T_D == K), and returns nothing.
// If the solution is invalid, stream.quitf will produce either _fail (if it's jury's ans)
// or _wa (if it's contestant's output).
void readAns(InStream &stream, int D, int K)
{
    // Read A, B. We allow A, B up to 100,000 arbitrarily here, since K <= 100,000.
    // It's safe to set upper bounds a bit generously or you can set them even higher,
    // as the problem only states 1 ≤ A ≤ B, but not an explicit upper limit.
    int A = stream.readInt(1, 100000, "A");
    int B = stream.readInt(A, 100000, "B"); // B >= A

    // Build the T array up to T_D
    // T_1 = A, T_2 = B, T_n = T_{n-2} + T_{n-1}.
    vector<int> T(D + 1);
    T[1] = A;
    T[2] = B;
    for (int i = 3; i <= D; i++)
    {
        // We'll do it in int, which is safe here because:
        // - The problem constraints (D <= 30, K <= 100,000) keep us well within int range.
        T[i] = T[i - 1] + T[i - 2];
    }

    // Check if T_D == K
    if (T[D] != K)
        stream.quitf(_wa,
                     "Wrong answer: T[%d] != %d (got %d instead).",
                     D, K, T[D]);
}

int main(int argc, char *argv[])
{
    registerTestlibCmd(argc, argv);

    // Read the input from inf
    int D = inf.readInt();  // 3 ≤ D ≤ 30
    int K = inf.readInt();  // 10 ≤ K ≤ 100000

    // First, check the jury's solution from ans (official output)
    // If the jury's solution is invalid, we produce _fail
    readAns(ans, D, K);

    // Now, check the contestant's solution from ouf
    // If invalid, that triggers _wa, otherwise we accept
    readAns(ouf, D, K);

    // If we reached here, both solutions are valid
    quitf(_ok, "Accepted: participant's output is a valid solution.");
}
