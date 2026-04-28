// C++ implementation of the approach 
#include <bits/stdc++.h> 
typedef long long ll;
using namespace std; 
const int MAX = 3e6;
  
// Ideally, we should not use global variables and large 
// constant-sized arrays, we have done it here for simplicity 
  
// To store segment tree 
ll tree[MAX] = { 0 }; 
  
// To store pending updates 
ll lazy[MAX] = { 0 }; 

ll arr[MAX];

void updateLazy(int si, int ss, int se) {
  // If lazy value is non-zero for current node of segment 
  // tree, then there are some pending updates. So we need 
  // to make sure that the pending updates are done before 
  // making new updates. Because this value may be used by 
  // parent after recursive calls (See last line of this 
  // function) 
   if (lazy[si] != 0) {

      // Make pending updates using value stored in lazy 
      // nodes 
      tree[si] += (se - ss + 1) * lazy[si];

      // Checking if it is not leaf node because if 
      // it is leaf node then we cannot go further 
      if (ss != se) {

        // We can postpone updating children we don't 
        // need their new values now. 
        // Since we are not yet updating children of si, 
        // we need to set lazy flags for the children
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }

      // Set the lazy value for current node as 0 as it 
      // has been updated 
      lazy[si] = 0;
  }
}
  
// si -> index of current node in segment tree 
// ss and se -> Starting and ending indexes of 
// elements for which current nodes stores sum 
// us and ue -> starting and ending indexes of update query 
// diff -> which we need to add in the range us to ue 
void updateRange(int si, int ss, int se, int us, int ue, ll diff) 
{ 
    updateLazy(si, ss, se);

    // Out of range 
    if (ss > se || ss > ue || se < us) return; 
  
    // Current segment is fully in range 
    if (ss >= us && se <= ue) { 
        // Add the difference to current node 
        tree[si] += diff * (se - ss + 1); 
  
        // Same logic for checking leaf node or not 
        if (ss != se) { 
            // This is where we store values in lazy nodes, 
            // rather than updating the segment tree itelf 
            // Since we don't need these updated values now 
            // we postpone updates by storing values in lazy[] 
            lazy[si * 2 + 1] += diff; 
            lazy[si * 2 + 2] += diff; 
        } 
        return; 
    } 
  
    // If not completely in range, but overlaps 
    // recur for children 
    int mid = (ss + se) / 2; 
    updateRange(si * 2 + 1, ss, mid, us, ue, diff); 
    updateRange(si * 2 + 2, mid + 1, se, us, ue, diff); 
  
    // And use the result of children calls 
    // to update this node 
    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2]; 
} 
  
// A recursive function to get the sum of values in given 
// a range of the array. The following are the parameters 
// for this function 
// si --> Index of the current node in the segment tree 
// Initially, 0 is passed as root is always at index 0 
// ss & se --> Starting and ending indexes of the 
// segment represented by current node 
// i.e., tree[si] 
// qs & qe --> Starting and ending indexes of query 
// range 
ll getSum(int ss, int se, int qs, int qe, int si) 
{ 
  
    updateLazy(si, ss, se);

  
    // Out of range 
    if (ss > se || ss > qe || se < qs) 
        return 0; 
  
    // At this point, we are sure that pending lazy updates 
    // are done for current node. So we can return value 
    // (same as it was for a query in our previous post) 
  
    // If this segment lies in range 
    if (ss >= qs && se <= qe) 
        return tree[si]; 
  
    // If a part of this segment overlaps with the given 
    // range 
    int mid = (ss + se) / 2; 
    return getSum(ss, mid, qs, qe, 2 * si + 1) +
           getSum(mid + 1, se, qs, qe, 2 * si + 2); 
} 
  
// A recursive function that constructs Segment Tree for 
// array[ss..se]. si is index of current node in segment 
// tree st. 
void constructSTUtil(ll arr[], int ss, int se, int si) 
{ 
    // out of range as ss can never be greater than se 
    if (ss > se) 
        return; 
  
    // If there is one element in array, store it in 
    // current node of segment tree and return 
    if (ss == se) { 
        tree[si] = arr[ss]; 
        return; 
    } 
  
    // If there are more than one elements, then recur 
    // for left and right subtrees and store the sum 
    // of values in this node 
    int mid = (ss + se) / 2; 
    constructSTUtil(arr, ss, mid, si * 2 + 1); 
    constructSTUtil(arr, mid + 1, se, si * 2 + 2); 
  
    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2]; 
} 
  
// Function to construct a segment tree from a given array 
// This function allocates memory for segment tree and 
// calls constructSTUtil() to fill the allocated memory 
void constructST(ll arr[], int n) 
{ 
    // Fill the allocated memory st 
    constructSTUtil(arr, 0, n - 1, 0); 
} 
  
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

// Driver code 
int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  m += k;

  for (int i = 0; i < n; i++) cin >> arr[i];

  // Build segment tree from given array 
  constructST(arr, n); 

  ll a, b, c, d;
  while (m--) {
    cin >> a >> b >> c;
    if (a == 1) {
      cin >> d;
      updateRange(0, 0, n - 1, b - 1, c - 1, d); 
    }
    else cout << getSum(0, n - 1, b - 1, c - 1, 0) << '\n';
  }
} 

// https://www.geeksforgeeks.org/lazy-propagation-in-segment-tree-set-2/
