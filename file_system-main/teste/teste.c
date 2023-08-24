#include <stdio.h>

void swapWithoutTemp(int *a, int *b) {
    *a = *a + *b;  // Soma os valores de a e b e armazena em a
    *b = *a - *b;  // Subtrai o valor original de b de a e armazena em b (agora contém o valor original de a)
    *a = *a - *b;  // Subtrai o valor original de a de b (agora contém o valor original de b)
}

int main() {
    int x = 5, y = 10;
    
    printf("Antes da troca: x = %d, y = %d\n", x, y);
    
    swapWithoutTemp(&x, &y);
    
    printf("Após a troca: x = %d, y = %d\n", x, y);
    
    return 0;
}




