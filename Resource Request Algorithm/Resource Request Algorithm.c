/* =====================================================
   File       : resource_request.c
   Purpose    : Implements the Resource Request Algorithm for Banker's Algorithm
   Author     : Jayashree
   Description:
     This file contains the res_request() function which handles additional resource requests from processes, updates Allocation, Need, and Available matrices and checks for errors.
   ===================================================== */

#include <stdio.h>
#include <stdlib.h>  // Needed for exit()

/* 
  Function: res_request
  --------------------
  Handles additional resource request for a process.

  Parameters:
    A   - Allocation matrix [n x m]
    N   - Need matrix [n x m]
    AV  - Available matrix [1 x m]
    pid - Process ID making the request
    m   - Number of resources
*/
void res_request(int A[10][10], int N[10][10], int AV[10][10], int pid, int m)
{
    int reqmat[1][10];
    int i;

    // Input resource request from user
    printf("\nEnter additional request for process P%d:\n", pid);
    for (i = 0; i < m; i++)
    {
        printf("Request for resource %d: ", i);
        scanf("%d", &reqmat[0][i]);
    }

    // Check if request exceeds the need
    for (i = 0; i < m; i++)
    {
        if (reqmat[0][i] > N[pid][i])
        {
            printf("\nError: Requested more than needed.\n");
            exit(0);
        }
    }

    // Update Available, Allocation, and Need matrices
    for (i = 0; i < m; i++)
    {
        AV[0][i] -= reqmat[0][i];
        printf("Available after request: %d\n", AV[0][i]);

        A[pid][i] += reqmat[0][i];
        printf("Allocation after request: %d\n", A[pid][i]);

        N[pid][i] -= reqmat[0][i];
        printf("Remaining Need: %d\n", N[pid][i]);
    }
}
