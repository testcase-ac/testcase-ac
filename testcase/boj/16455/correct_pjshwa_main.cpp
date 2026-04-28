#include <bits/stdc++.h>

// int kth(std::vector<int> &a, int k) {
//   int n = a.size();
//   int start = 0, end = n - 1;

//   while (start < end) {
//     int i = start;
//     int j = end;
//     int mid = a[(i + j)/2];
 
//     while (i < j) {
//       if (a[i] >= mid) {
//         int tmp = a[j];
//         a[j] = a[i];
//         a[i] = tmp;
//         j--;
//       }
//       else i++;
//     }

//     if (a[i] > mid) i--;

//     if (k - 1 <= i) end = i;
//     else start = i + 1;
//   }

//   return a[k - 1];
// }

int kth(std::vector<int> &a, int k) {
  std::nth_element(a.begin(), a.begin() + k - 1, a.end());
  return a[k - 1];
}

// int main() {
//   std::vector<int> a{2,1,4,3,5};
//   std::cout << kth(a, 4) << '\n';
// }
