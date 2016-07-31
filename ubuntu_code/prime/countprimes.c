#include <stdio.h>
#include <malloc.h>

int countPrimes(int n) {
    int count = 0;
    int i,j,limit;
    char* pflags = (char*)malloc(n+1);
    if (n <= 2) return 0;

    pflags[2] = 1;
    for (i = 3; i < n; ++i) {
        pflags[i] = 1;
        i++;
        pflags[i] = 0;
    }
    
    limit = n / 2 + 1;
    for (i = 3; i < limit; ++i) {
        if (0 == pflags[i]) continue;
        for (j = i*2; j < n; j += i) {
            pflags[j] = 0;
        }
    }
    
    for (i = 2; i < n; ++i) {
        if (pflags[i] == 1) count++;
    }
    
    free(pflags);
    
    return count;
}

void main() {
  int count;
  count = countPrimes(1000000);
  printf("count:%d\n", count); 
}
