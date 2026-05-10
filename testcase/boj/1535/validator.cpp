#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Number of people: at least 1, at most 20
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();
    
    // Energy costs L[i]: N integers, each between 0 and 100
    vector<int> L = inf.readInts(N, 0, 100, "L_i");
    inf.readEoln();
    
    // Joy values J[i]: N integers, each between 0 and 100
    vector<int> J = inf.readInts(N, 0, 100, "J_i");
    inf.readEoln();
    
    inf.readEof();
    return 0;
}
