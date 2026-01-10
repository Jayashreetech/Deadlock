/*  File       : main.c
   Purpose    : Main program for Deadlock Avoidance using Banker's Algorithm
   Author     : Jayashree
  
   Description:
     This is the main driver program that:
       1. Accepts number of processes, resources, and matrices
       2. Computes the available resources and Need matrix
       3. Calls the Banker's algorithm to check for a safe state
       4. Handles additional resource requests from processes */

#include <stdio.h>
#include <stdlib.h>
#include "safety.c"          // Safety algorithm
#include "bankers.c"         // Banker's algorithm
#include "resource_request.c" // Resource request algorithm

/* Accepts the number of processes, number of resources, Allocation matrix, Maximum matrix, and calculates the Available and Need matrices.

  Parameters:
    A  - Allocation matrix [n x m]
    N  - Need matrix [n x m]
    M  - Maximum matrix [n x m]
    W  - Available matrix [1 x m]
    n  - Pointer to number of processes
    m  - Pointer to number of resources */
void accept(int A[][10], int N[][10], int M[10][10], int W[1][10], int *n, int *m)
{
    int i, j, h, z[10]; // z stores total instances of each resource

    printf("\nEnter total number of processes: ");
    scanf("%d", n);

    printf("Enter total number of resources: ");
    scanf("%d", m);

    // Accept total instances of each resource
    for (h = 0; h < *m; h++)
    {
        printf("Enter total instances of resource R%d: ", h + 1);
        scanf("%d", &z[h]);
    }

    // Accept Allocation and Maximum matrices
    for (i = 0; i < *n; i++)
    {
        printf("\nProcess P%d\n", i);
        for (j = 0; j < *m; j++)
        {
            printf("Allocation for resource R%d: ", j + 1);
            scanf("%d", &A[i][j]);

            printf("Maximum for resource R%d: ", j + 1);
            scanf("%d", &M[i][j]);
        }
    }

    // Calculate Available matrix: W = total instances - sum of allocations
    for (j = 0; j < *m; j++)
    {
        int sum = 0;
        for (i = 0; i < *n; i++)
            sum += A[i][j];
        W[0][j] = z[j] - sum;
    }

    printf("\nAvailable Resources: ");
    for (j = 0; j < *m; j++)
        printf("%d ", W[0][j]);
    printf("\n");

    // Calculate Need matrix: N = Maximum - Allocation
    for (i = 0; i < *n; i++)
        for (j = 0; j < *m; j++)
            N[i][j] = M[i][j] - A[i][j];

    // Print all matrices
    printf("\nAllocation Matrix:");
    print(A, *n, *m);

    printf("\nMaximum Matrix:");
    print(M, *n, *m);

    printf("\nNeed Matrix:");
    print(N, *n, *m);
}

/*  Main function */
int main()
{
    int A[10][10], M[10][10], N[10][10], W[1][10];
    int n, m;       // Number of processes and resources
    int pid, ch;    // Process ID and choice for additional request
    int ret;

    printf("=== DEADLOCK AVOIDANCE USING BANKER'S ALGORITHM ===\n");

    // Step 1: Accept process and resource information
    accept(A, N, M, W, &n, &m);

    // Step 2: Run Banker's algorithm to check initial safe state
    ret = banker(A, N, W, n, m);

    // Step 3: If system is safe, ask user for additional resource requests
    if (ret != 0)
    {
        printf("\nDo you want to make an additional request? (1=Yes | 0=No): ");
        scanf("%d", &ch);

        if (ch == 1)
        {
            printf("Enter process number: ");
            scanf("%d", &pid);

            // Process the additional resource request
            res_request(A, N, W, pid, m);

            // Re-run Banker's algorithm to check for safe state
            ret = banker(A, N, W, n, m);

            if (ret == 0)
            {
                printf("\nSystem became unsafe after the request. Exiting.\n");
                exit(0);
            }
        }
    }
    else
    {
        printf("\nSystem is not in a safe state initially. Exiting.\n");
        exit(0);
    }

    printf("\nProgram completed successfully.\n");
    return 0;
}
