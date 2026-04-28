#include <iostream>
#include <set>

using namespace std;

struct RatioComp {
  bool operator() (const pair<long long int, long long int>& A, const pair<long long int, long long int>& B) {
    if (A.first * B.second < A.second * B.first) {
      return true;
    } else if (A.first * B.second == A.second * B.first) {
      return A.first < B.first;
    } else {
      return false;
    }
  }
};

int main() {
  long long int B, N;
  while (cin >> B >> N) {
    if (B == 0 && N == 0) {
      break;
    }
    set<pair<long long int, long long int>, RatioComp> answers;
    long long N2 = (long long int)N*(long long int)N;
    for (int M = 1; M <= 2*N; ++M) {
      if (M == N) {
        continue;
      }
      long long int prod = (long long int)B*(long long int)M*(long long int)(2*N - M);
      if (prod % N2 == 0) {
        int A = (int)(prod / N2);
        answers.insert(make_pair(A, M));
      }
    }
    set<pair<long long int, long long int> >::const_iterator itr_end = answers.end();
    for (set<pair<long long int, long long int> >::const_iterator itr = answers.begin();
         itr != itr_end; ++itr) {
      if (itr != answers.begin()) {
        cout << " ";
      }
      cout << itr->first << "/" << itr->second;
    }
    cout << endl;
  }
}
