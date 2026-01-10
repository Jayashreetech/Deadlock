/* File       : safety.c
   Purpose    : Implements the Safety Algorithm of Banker's Algorithm for Deadlock Avoidance
   Author     : Jayashree
   Description:
     This file contains the safety() function which checks whether the system is in a safe state given the allocation matrix, need matrix, and available resources.
*/

#include <stdio.h>

/* Function: print
   Prints a 2D matrix of size n x m.
   Parameters:
    x - the matrix to print
    n - number of rows
    m - number of columns
*/
void print(int x[][10], int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j < m; j++)
            printf("%d\t", x[i][j]);
    }
}

/* Function: safety
  Checks whether the system is in a safe state using the Banker's algorithm.

  Parameters:
    A  - Allocation matrix [n x m]
    N  - Need matrix [n x m]
    AV - Available resources matrix [1 x m]
    n  - Number of processes
    m  - Number of resources
    a  - Array to store safe sequence if system is safe

  Returns:
    1 - if system is in safe state
    0 - if system is unsafe
*/
int safety(int A[][10], int N[][10], int AV[10][10], int n, int m, int a[])
{
    int i, j, k, x = 0;
    int F[10];        // Finish array: 0 = not finished, 1 = finished
    int W[1][10];     // Work array to track available resources
    int pflag = 0;    // Count of processes safely completed
    int flag = 0;

    // Step 1: Initialize Finish array to 0 (all processes unfinished)
    for (i = 0; i < n; i++)
        F[i] = 0;

    // Step 2: Initialize Work = Available resources
    for (i = 0; i < m; i++)
        W[0][i] = AV[0][i];

    // Step 3: Try to find a safe sequence
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (F[i] == 0) // If process is unfinished
            {
                flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (N[i][j] > W[0][j])
                        flag = 1; // Cannot allocate resources yet
                }

                // If all needed resources are available
                if (flag == 0)
                {
                    // Simulate process completion: add allocated resources to Work
                    for (j = 0; j < m; j++)
                        W[0][j] += A[i][j];

                    F[i] = 1;           // Mark process finished
                    a[x++] = i;          // Add process to safe sequence
                    pflag++;             // Increment completed process count
                }
            }
        }

        // If all processes are finished, system is safe
        if (pflag == n)
            return 1;
    }

    // If not all processes finished, system is unsafe
    return 0;
}
