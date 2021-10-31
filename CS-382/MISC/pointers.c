#include <stdio.h>
 
int main() {
    int a = 4;
    double b = 3.14;
    int* ptr = &a;
    printf("%d\n%p\n%p\n",a, ptr, &ptr); 
    
    return 0;
}
