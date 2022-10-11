#include <stdio.h>

#define N 4

int gboard[N][N]; /* 0 is blank space, 1 is queen */

/* returns 1 if board[x][y] is a (currently) valid placement for a queen
 * returns 0 otherwise
 */
int can_place_queen(const int *board, int x, int y) {
  int i, xn, yn;
  for (i=0; i<N; i++) {
    if (board[x*N+i] || board[i*N+y])
      return 0;
    /* down and to the right */
    xn = x+i; yn = y+i;
    if ((xn >= 0) && (xn < N) && (yn >=0) && (yn < N) && board[xn*N+yn])
      return 0;
    /* down and to the left */
    xn = x-i; yn = y+i;
    if ((xn >= 0) && (xn < N) && (yn >=0) && (yn < N) && board[xn*N+yn])
      return 0;
    /* up and to the right */
    xn = x+i; yn = y-i;
    if ((xn >= 0) && (xn < N) && (yn >=0) && (yn < N) && board[xn*N+yn])
      return 0;
    /* up and to the left */
    xn = x-i; yn = y-i;
    if ((xn >= 0) && (xn < N) && (yn >=0) && (yn < N) && board[xn*N+yn])
      return 0;
  }
  return 1;
}

int count_queens(const int *board) {
  int i,j,sum;
  sum = 0;
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      sum += board[i*N+j];
  return sum;
}

/* If board is an solvable initial state, populates board with a complete
 *   solution and returns 1
 * If board is not a solvable initial state, does not modify board
 *   and returns 0
 * PRE: board must be a valid state
 */
int nqueens_rb(int *board) {
  int i, j;
  if (count_queens(board) == N) return 1;
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      if (can_place_queen(board, i, j)) {
	board[i*N+j] = 1;
	if (nqueens_rb(board))
	  return 1;
	board[i*N+j] = 0;
      }
    }
  }
  return 0;
}

int main() {
  int i, j;
  printf("Solver says %d\n", nqueens_rb(gboard));
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      printf("%d", gboard[i][j]);
    }
    printf("\n");
  }
  return 0;
}

