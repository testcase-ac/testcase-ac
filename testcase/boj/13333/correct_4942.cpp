#include <stdio.h>
#include <stdlib.h>

int arr[10000];

int compare(const void* a, const void* b) {
	
	return *(int*)a-*(int*)b;
}

int main() {
	
	int n, k=0;
	scanf("%d", &n);
	for (int i=0; i<n; i++) {
		scanf("%d", arr+i);
	}
	
	qsort(arr, n, sizeof(int), compare);
	
	
	for (int i=0; i<=n; i++) {
		if (n - k == i) {
			printf("%d", i);
			return 0;
		}
		while (k < n && arr[k] <= i) {
			k++;
			if (n - k == i) {
				printf("%d", i);
				return 0;
			}
			
		}
		
	}
	printf("0");
}
