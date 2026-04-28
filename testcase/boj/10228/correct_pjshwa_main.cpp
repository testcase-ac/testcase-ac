#include "grader.h"
#include "memory.h"
#include <vector>

void play() {
  std::vector<int> B[256];
  for (int i = 1; i <= 50; ++i) B[faceup(i)].push_back(i);
  for (int j = 0; j < 256; ++j) for (int i : B[j]) faceup(i);
}
