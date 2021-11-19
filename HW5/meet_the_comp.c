#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


void print_result(int* arr, int N)
{
    printf("name%d", arr[0]);
    for (int i = 1; i < N; ++i)
        printf(" -> name%d", arr[i]);
    printf("\n");
}

void current_state(int* state, int psize)
{
    int* done_processes = state;
    int* remaining_processes = state + psize;

    state[2 * psize] = 0;
    state[2 * psize + 1] = psize;

    for (int i = 0; i < psize; ++i)
    {
        remaining_processes[i] = i;
    }
}

int state_next(int* state, int prank, int psize)
{
    int* done_processes = state;
    int* remaining_processes = state + psize;

    int n_done = state[2 * psize];
    int n_remaining = state[2 * psize + 1];

    done_processes[n_done] = prank;
    state[2 * psize] = ++n_done;

    int i;
    for (i = 0; i < n_remaining; ++i)
    {
        if (prank == remaining_processes[i])
        {
            break;
        }
    }

    remaining_processes[i] = remaining_processes[n_remaining - 1];
    state[2 * psize + 1] = --n_remaining;

    int send_to_rank = -1;
    if (n_remaining > 0)
        send_to_rank = remaining_processes[rand() % n_remaining];

    return send_to_rank;
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int psize;
    MPI_Comm_size(MPI_COMM_WORLD, &psize);

    int prank;
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    int* state = (int*)malloc((2 * psize + 2) * sizeof(int));
    current_state(state, psize);

    if (prank == 0)
    {
        int send_to = state_next(state, prank, psize);
        MPI_Ssend(state, 2 * psize + 2, MPI_INT, send_to, 99, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(state, 2 * psize + 2, MPI_INT, MPI_ANY_SOURCE, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int send_to = state_next(state, prank, psize);

        if (send_to > 0)
        {
            MPI_Ssend(state, 2 * psize + 2, MPI_INT, send_to, 99, MPI_COMM_WORLD);
        }
        else
        {
            print_result(state, psize);
        }
    }

    free(state);
    MPI_Finalize();
    return 0;
}