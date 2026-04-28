#include <stdio.h>
#include <iostream>
#include <utility>

#define MAX_N 5000
#define MAX_CALLS 70000

static int N;
static int realS[MAX_N];
static int realD[MAX_N];
static int inv[MAX_N];
static int num_calls;

int ES[5000], ED[5000];
std::pair<int, int> D2S[5000];

void answer(int S[], int D[]) {
    int i;
    int correct = 1;
    for (i = 0; i < N; ++i)
        if (S[i] != realS[i] || D[i] != realD[i]) {
            correct = 0;
            break;
        }

    if (correct)
        printf("CORRECT\n");
    else
        printf("INCORRECT\n");

    for (i = 0; i < N; ++i) {
        if (i > 0)
            printf(" ");
        printf("%d", S[i]);
    }
    printf("\n");

    for (i = 0; i < N; ++i) {
        if (i > 0)
            printf(" ");
        printf("%d", D[i]);
    }
    printf("\n");

    exit(0);
}

int tryCombination(int S[]) {
    int i;

    if (num_calls >= MAX_CALLS) {
        printf("INCORRECT\nToo many calls to tryCombination().\n");
        exit(0);
    }
    ++num_calls;

    for (i = 0; i < N; ++i)
        if (S[inv[i]] != realS[inv[i]])
            return i;
    return -1;
}

int init() {

  std::cin >> N;

  for (int i = 0; i < N; ++i) std::cin >> realS[i];
  for (int i = 0; i < N; ++i) {
    std::cin >> realD[i];
    inv[realD[i]] = i;
  }

  num_calls = 0;
  return N;
}

void findDoorX(int X, int N) {
  int opens;
  for (int i = 0; i < N; i++) ES[i] = 0;
  for (int i = 0; i < X; ++i) {
    auto[Si, So] = D2S[i];
    ES[Si] = So;
  }
  int res = tryCombination(ES);
  if (res == X) opens = 1;
  else opens = 0;

  int left = 0, right = N - 1;
  int mid = (left + right) / 2;

  while (left < right) {
    for (int i = 0; i < N; i++) ES[i] = (opens ^ 1);
    for (int i = left; i <= mid; i++) ES[i] = opens;
    for (int i = 0; i < X; ++i) {
      auto[Si, So] = D2S[i];
      ES[Si] = So;
    }
    int res = tryCombination(ES);
    if (res == X) left = mid + 1;
    else right = mid;
    mid = (left + right) / 2;
  }

  D2S[X] = {mid, opens};
}

void exploreCave(int N) {
  for (int i = 0; i < N; i++) findDoorX(i, N);
  for (int i = 0; i < N; i++) {
    auto[Si, So] = D2S[i];
    ES[Si] = So;
    ED[Si] = i;
  }
  answer(ES, ED);
}

int main() {
  int N = init();
	exploreCave(N);
	return 0;
}
