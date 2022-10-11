#include <stdio.h>

/* Moves N disks numbered 1..N from from-pole to the to-pole, possibly
 * using the via-pole. Follows the rules a) moves one disk at a time,
 * and b) disks are increasing in size
 * PRE: 1..N are on pole from
 *      (No disks smaller than N are on any of the to, via poles)
 *      Any disks larger N are in increasing size on any pole they inhabit.
 * POST: Outputs the sequence of moves to move 1..N to pole "to"
 */
void hanoi(int N, int from, int to, int via) {
  if (!N) return; /* Base case (step 3) */
  hanoi(N-1, from, via, to);
  printf("Move disk of size %d from %d to %d\n", N, from, to);
  hanoi(N-1, via, to, from);
}

int main() {
  hanoi(7, 1, 3, 2);
}
