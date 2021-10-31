#include <stdio.h>

double area(double side) {
    return side * side;
}

int main (){
    double x = area(2);
    printf("%f\n", x);
    return 0;
}
