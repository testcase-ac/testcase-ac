#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the apple DNA string: length N, 1 ≤ N ≤ 10000, only A, C, G, T
    string s = inf.readLine("[ACGT]{1,10000}", "apple_dna");

    // Read the swine gene string: length M, 1 ≤ M ≤ 5000, only A, C, G, T
    string t = inf.readLine("[ACGT]{1,5000}", "swine_gene");

    // Read insertion costs for A, C, G, T in that order, each in [0,1000]
    int costA = inf.readInt(0, 1000, "cost_A");
    inf.readSpace();
    int costC = inf.readInt(0, 1000, "cost_C");
    inf.readSpace();
    int costG = inf.readInt(0, 1000, "cost_G");
    inf.readSpace();
    int costT = inf.readInt(0, 1000, "cost_T");
    inf.readEoln();

    // No further global constraints to check (inserting always allows embedding the gene)
    inf.readEof();
    return 0;
}
