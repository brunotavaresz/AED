#include <stdio.h>


int verify_progession_geom(int array[], int n) {
    double r;

    if (n < 3) {
        return 0; 
    }
    
    r = array[1] / array [0];
    
    for (int i = 1; i < n; i++) {
        if (array[i] != r * array[i - 1]) {
            return 1;
        }
    }
    
    return 0;
}


int main() {

    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n1 = sizeof(array1) / sizeof(array1[0]); 

    int array2[] = {1, 2, 4, 4, 5, 6, 7, 8, 9, 10};
    int n2 = sizeof(array2) / sizeof(array2[0]); 

    int array3[] = {1, 2, 4, 8, 5, 6, 7, 8, 9, 10};
    int n3 = sizeof(array3) / sizeof(array3[0]); 

    int array4[] = {1, 2, 4, 8, 16, 6, 7, 8, 9, 10};
    int n4 = sizeof(array4) / sizeof(array4[0]); 

    int array5[] = {1, 2, 4, 8, 16, 32, 7, 8, 9, 10};
    int n5 = sizeof(array5) / sizeof(array5[0]);

    int array6[] = {1, 2, 4, 8, 16, 32, 64, 8, 9, 10};
    int n6 = sizeof(array6) / sizeof(array6[0]);

    int array7[] = {1, 2, 4, 8, 16, 32, 64, 128, 9, 10};
    int n7 = sizeof(array7) / sizeof(array7[0]);

    int array8[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 10};
    int n8 = sizeof(array8) / sizeof(array8[0]);


    int array9[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    int n9 = sizeof(array9) / sizeof(array9[0]);

    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array1, n1));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array2, n2));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array3, n3));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array4, n4));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array5, n5));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array6, n6));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array7, n7));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array8, n8));
    printf("Progressão geométrica (0 - V ; 1 - F) %d\n", verify_progession_geom(array9, n9));

    return 0;
}

    