/**
 * @file 2-7.c
 * @author Gavin Hua
 * @brief 2-7: Write a function invert(x,p,n) that returns x with the n bits 
 * that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 */

#include<math.h>
#include<stdio.h>

int invert(int, int, int);

int main(){
    printf("%d", invert(0b1000, 2, 1));
    return 0;
}

/**
 * @brief Changes some bits of x.
 * 
 * @param x 
 * @param p 
 * @param n 
 * @return x with the n bits that begin at position p inverted (i.e., 1 changed 
 * into 0 and vice versa) and the others unchanged
 */
int invert(int x, int p, int n){
    int inversion_mask = pow(2, n)-1;
    inversion_mask <<= p-n;
    return (x^inversion_mask);
}