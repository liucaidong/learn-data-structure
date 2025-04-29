#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

int F[100]; /* 斐波那契数列 */

// 提前计算斐波那契数列，避免在main函数中重复计算
void initFibonacci() {
    F[0]=0;
    F[1]=1;
    for(int i = 2; i < 100; i++) { 
        F[i] = F[i-1] + F[i-2];  
    } 
}

/* 无哨兵顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字 */
int Sequential_Search(int *a, int n, int key) {
    for(int i = 1; i <= n; i++) {
        if (a[i] == key) {
            return i;
        }
    }
    return 0;
}

/* 有哨兵顺序查找 */
int Sequential_Search2(int *a, int n, int key) {
    a[0] = key;
    int i = n;
    while(a[i] != key) {
        i--;
    }
    return i;
}

/* 折半查找 */
int Binary_Search(int *a, int n, int key) {
    int low = 1, high = n, mid;
    while(low <= high) {
        // 避免整数溢出
        mid = low + ((high - low) >> 1); 
        if (key < a[mid]) {
            high = mid - 1;
        } else if (key > a[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return 0;
}

/* 插值查找 */
int Interpolation_Search(int *a, int n, int key) {
    int low = 1, high = n, mid;
    while(low <= high && key >= a[low] && key <= a[high]) {
        mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]); 
        if (key < a[mid]) {
            high = mid - 1;
        } else if (key > a[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return 0;
}

/* 斐波那契查找 */
int Fibonacci_Search(int *a, int n, int key) {
    int low = 1, high = n, mid, i, k = 0;
    while(n > F[k] - 1) {
        k++;
    }
    int temp[MAXSIZE + F[k] - n];
    for(i = 0; i < n; i++) {
        temp[i] = a[i];
    }
    for(i = n; i < F[k] - 1; i++) {
        temp[i] = a[n - 1];
    }
    while(low <= high) {
        mid = low + F[k - 1] - 1;
        if (key < temp[mid]) {
            high = mid - 1;
            k = k - 1;
        } else if (key > temp[mid]) {
            low = mid + 1;
            k = k - 2;
        } else {
            return (mid < n) ? mid : n;
        }
    }
    return 0;
}

int main(void) {    
    int a[MAXSIZE + 1], i, result;
    int arr[MAXSIZE] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};
    
    // 初始化斐波那契数列
    initFibonacci();

    for(i = 0; i <= MAXSIZE; i++) {
        a[i] = i;
    }

    result = Sequential_Search(a, MAXSIZE, MAXSIZE);
    printf("Sequential_Search:%d \n", result);
    result = Sequential_Search2(a, MAXSIZE, 1);
    printf("Sequential_Search2:%d \n", result);

    result = Binary_Search(arr, 10, 62);
    printf("Binary_Search:%d \n", result);

    result = Interpolation_Search(arr, 10, 62);
    printf("Interpolation_Search:%d \n", result);

    result = Fibonacci_Search(arr, 10, 62);
    printf("Fibonacci_Search:%d \n", result);
    
    return 0;
}
