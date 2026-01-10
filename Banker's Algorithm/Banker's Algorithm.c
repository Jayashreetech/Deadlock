/* =====================================================
   File       : bankers.c
   Purpose    : Implements the Banker's Algorithm
                to determine if the system is in a safe state
   Author     : Jayashree

   Description:
     This file contains the banker() function which calls the safety() function to determine whether a safe sequence exists and prints it.
   ===================================================== */

#include <stdio.h>
#include "safety.c"  

/* 
  Function: banker
  ----------------
  Implements Banker's algorithm. Calls the safety() function and prints the safe sequence if available.

  Parameters:
    A - Allocation matrix [n x m]
    N - Need matrix [n x m]
    W - Available matrix [1 x m]
    n - Number of processes
    m - Number of resources

  Returns:
    1 - if a safe sequence is found
    0 - if the system is unsafe
*/
int banker(int A[][10], int N[][10], int W[1][10], int n, int m)
{
    int a[10];  // Array to store safe sequence
    int j = safety(A, N, W, n, m, a); // Call safety algorithm

    if (j != 0)
    {
        int i;
        printf("\n\nSafe Sequence Detected: ");
        for (i = 0; i < n; i++)
            printf("P%d ", a[i]);
        printf("\nSystem is in a safe state.\n");
        return 1;
    }
    else
    {
        printf("\nSystem is NOT in a safe state.\n");
        return 0;
    }
}
