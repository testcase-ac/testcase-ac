#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
// 체
using namespace std;

char *isPrime;
void calcIsPrimeTo(int size) {
	isPrime = (char *)malloc(size);
	memset(isPrime, 1, sizeof(char) * size);
	isPrime[0] = 0;
	isPrime[1] = 0;
	int p=2;
	while(p * p <= size) {
		for(int i=p*2; i<=size; i+=p)
			isPrime[i] = 0;
		p++;
		while(!isPrime[p])
			p++;
	}
} 

int main() {
	int T, n, nmax=0;
	cin >> T;
	int nArr[T];
	for(int i=0;i<T;i++){
		cin >> n;
		if(n > nmax)
			nmax = n;
		nArr[i] = n;
	}
	calcIsPrimeTo(nmax);
	for(int i=0; i<T; i++) {
		n = nArr[i];
		for(int j=n/2;;j--) { // assume conjecture is true by not putting terminating cond....??????? -> at least it should be true in int range, so whatever
			int k = n-j;
			if(isPrime[j] && isPrime[k]) {
				printf("%d %d\n", j, k);
				break;
			}
		}
	}
}
