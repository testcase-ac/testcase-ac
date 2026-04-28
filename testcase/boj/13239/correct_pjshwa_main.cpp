#include <cstdio>
#define LONG_MOD 1000000007LL

long long degree(long long a, long long k, long long p) {
  long long res = 1;
  long long cur = a;

  while (k) {
    if (k % 2) {
      res = (res * cur) % p;
    }
    k /= 2;
    cur = (cur * cur) % p;
  }
  return res;
}

int get_degree(long long n, long long p) { // returns the degree with which p is in n!
  int degree_num = 0;
  long long u = p;
  long long temp = n;

  while (u <= temp) {
    degree_num += temp / u;
    u *= p;
  }
  return degree_num;
}

long long combinations(int n, int k, long long p) {
  int num_degree = get_degree(n, p) - get_degree(n - k, p);
  int den_degree = get_degree(k, p);

  if (num_degree > den_degree) {
    return 0;
  }
  long long res = 1;
  for (long long i = n; i > n - k; --i) {
    long long ti = i;
    while(ti % p == 0) {
      ti /= p;
    }
    res = (res * ti) % p;
  }
  for (long long i = 1; i <= k; ++i) {
    long long ti = i;
    while(ti % p == 0) {
      ti /= p;
    }
    res = (res * degree(ti, p-2, p)) % p;
  }
  return res;
}

int power_of_2(int h){
	int answer = 1;
	for(int i = 0; i < h; i++){
		answer *= 2;
	}
	return answer;
}

int main(){
    int t;

    scanf("%d", &t);
    for(int i = 0; i < t; i++){
        int n,k;
        scanf("%d%d", &n,&k);
        printf("%lld\n", combinations(n,k,LONG_MOD));
    }
    
}