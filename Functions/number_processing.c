#include <stdio.h>

int multByTwo(int original) {
    int ans;
    ans = original *2;
    return ans;
}

int isFirstBigger(int first, int second) {
    if (first < second) {
        return 0;
    }
    return 1;
}

float addVat(float original) {
    float ans = original *1.2;
    return ans;
}

int main() {
    int ans = multByTwo(4);
    printf("%d\n", ans);
    ans = isFirstBigger(8,3);
    printf("%d\n", ans); 
    float ansVat = addVat(4000);
    printf("%f\n", ansVat);
}