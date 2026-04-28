#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = 2e5;
  int M = 2e5;
  printf("%d %d\n", N, M);

  vector<int> nums(10 * N);
  for (int i = 0; i < 5 * N; ++i) nums[i] = 1;
  for (int i = 5 * N; i < 10 * N; ++i) nums[i] = rnd.next(2, M);
  shuffle(nums.begin(), nums.end());

  // randomly choose the number N times
  for (int i = 0; i < N; i++) {
    int K = 10;
    printf("%d ", K);

    printf("%d ", nums.back()); nums.pop_back();
    for (int j = 1; j < K - 1; j++) {
      printf("%d ", rnd.next(1, M));
    }
    printf("%d\n", nums.back()); nums.pop_back();
  }
}
