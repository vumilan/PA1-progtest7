#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int max ( int num1, int num2 ) {
    return (num1 > num2 ) ? num1 : num2;
}

int min ( int num1, int num2 ) {
    return (num1 > num2 ) ? num2 : num1;
}

int minimax ( int * array, int player, int alpha, int beta, int array_left, int array_right, int extra_moveP1, int extra_moveP2, int * new_arrayA, int * new_arrayB, int * specialA, int * specialB, int depth ) {
  int best_value;
  int child_value;
  ++depth;

  if ( array_left == array_right ) {
    if ( player == 1 ){

      new_arrayA[depth] = array_right;
      specialA[depth] = 1;
      best_value = array[array_right];
    }
    else{

      new_arrayB[depth] = array_right;
      specialB[depth] = 1;
      best_value = -array[array_right];
    }
  }
  else if ( player == 1 ) {
    best_value = alpha;
    if ( extra_moveP1 == 0 && array_right - 2 >= array_left ) {

      for ( int i = 0; i < 5; ++i ) {

        switch (i) {
          case 0:
            child_value = minimax( array, 0, alpha, beta, array_left + 1, array_right, 0, extra_moveP2, new_arrayA, new_arrayB, specialA, specialB, depth ) + array[array_left];
            if ( child_value > best_value ) {
              best_value = child_value;
              new_arrayA[depth] = array_left;
              specialA[depth] = 1;
            }
            break;
          case 1:
            child_value = minimax( array, 0, alpha, beta, array_left, array_right - 1, 0, extra_moveP2, new_arrayA, new_arrayB, specialA, specialB, depth ) + array[array_right];
            if ( child_value > best_value ) {
              best_value = child_value;
              new_arrayA[depth] = array_right;
              specialA[depth] = 1;
            }
            break;
          case 2:
            child_value = minimax( array, 0, alpha, beta, array_left + 1, array_right - 1, 1, extra_moveP2, new_arrayA, new_arrayB, specialA, specialB, depth ) + array[array_left] + array[array_right];
            if ( child_value > best_value ) {
              best_value = child_value;
              new_arrayA[depth] = array_left;
              new_arrayA[depth+1] = array_right;
              specialA[depth] = 2;
            }
            break;
          case 3:
            child_value = minimax( array, 0, alpha, beta, array_left + 2, array_right, 1, extra_moveP2, new_arrayA, new_arrayB, specialA, specialB, depth ) + array[array_left] + array[array_left+1];
            if ( child_value > best_value ) {
              best_value = child_value;
              new_arrayA[depth] = array_left;
              new_arrayA[depth+1] = array_left + 1;
              specialA[depth] = 2;
            }
            break;
          case 4:
            child_value = minimax( array, 0, alpha, beta, array_left, array_right - 2, 1, extra_moveP2, new_arrayA, new_arrayB, specialA, specialB, depth ) + array[array_right] + array[array_right-1];
            if ( child_value > best_value ) {
              best_value = child_value;
              new_arrayA[depth] = array_right;
              new_arrayA[depth+1] = array_right - 1;
              specialA[depth] = 2;
            }
            break;
        }
      }
    }
    else {
      for ( int i = 0; i < 2; ++i ) {

        switch (i) {
          case 0:
            child_value = minimax( array, 0, alpha, beta, array_left + 1, array_right, 0, extra_moveP2, new_arrayA, new_arrayB, specialA, specialB, depth ) + array[array_left];
            if ( child_value > best_value ) {
              best_value = child_value;
              new_arrayA[depth] = array_left;
              specialA[depth] = 1;
            }
            break;
          case 1:
            child_value = minimax( array, 0, alpha, beta, array_left, array_right - 1, 0, extra_moveP2, new_arrayA, new_arrayB, specialA, specialB, depth ) + array[array_right];
            if ( child_value > best_value ) {
              best_value = child_value;
              new_arrayA[depth] = array_right;
              specialA[depth] = 1;
            }
            break;
        }
      }
    }
  }
  else {
    best_value = beta;
    if ( extra_moveP2 == 0 && array_right - 2 >= array_left ) {

      for ( int i = 0; i < 5; ++i ) {

        switch (i) {
          case 0:
            child_value = minimax( array, 1, alpha, beta, array_left + 1, array_right, extra_moveP1, 0, new_arrayA, new_arrayB, specialA, specialB, depth )  - array[array_left];
            if ( child_value < best_value ) {
              best_value = child_value;
              new_arrayB[depth] = array_left;
              specialB[depth] = 1;
            }
            break;
          case 1:
            child_value = minimax( array, 1, alpha, beta, array_left, array_right - 1, extra_moveP1, 0, new_arrayA, new_arrayB, specialA, specialB, depth ) - array[array_right];
            if ( child_value < best_value ) {
              best_value = child_value;
              new_arrayB[depth] = array_right;
              specialB[depth] = 1;
            }
            break;
          case 2:
            child_value = minimax( array, 1, alpha, beta, array_left + 1, array_right - 1, extra_moveP1, 1, new_arrayA, new_arrayB, specialA, specialB, depth ) - (array[array_left]+array[array_right]);
            if ( child_value < best_value ) {
              best_value = child_value;
              new_arrayB[depth] = array_left;
              new_arrayB[depth+1] = array_right;
              specialB[depth] = 2;
            }
            break;
          case 3:
            child_value = minimax( array, 1, alpha, beta, array_left + 2, array_right, extra_moveP1, 1, new_arrayA, new_arrayB, specialA, specialB, depth ) - (array[array_left]+array[array_left+1]);
            if ( child_value < best_value ) {
              best_value = child_value;
              new_arrayB[depth] = array_left;
              new_arrayB[depth+1] = array_left + 1;
              specialB[depth] = 2;
            }
            break;
          case 4:
            child_value = minimax( array, 1, alpha, beta, array_left, array_right - 2, extra_moveP1, 1, new_arrayA, new_arrayB, specialA, specialB, depth ) - (array[array_right]+array[array_right-1]);
            if ( child_value < best_value ) {
              best_value = child_value;
              new_arrayB[depth] = array_right;
              new_arrayB[depth+1] = array_right - 1;
              specialB[depth] = 2;
            }
            break;
        }

      }
    }
    else {

      for ( int i = 0; i < 2; ++i ) {

        switch (i) {
          case 0:
            child_value = minimax( array, 1, alpha, beta, array_left + 1, array_right, extra_moveP1, 0, new_arrayA, new_arrayB, specialA, specialB, depth ) - array[array_left];
            if ( child_value < best_value ) {
              best_value = child_value;
              new_arrayB[depth] = array_left;
              specialB[depth] = 1;
            }
            break;
          case 1:
            child_value = minimax( array, 1, alpha, beta, array_left, array_right - 1, extra_moveP1, 0, new_arrayA, new_arrayB, specialA, specialB, depth )  - array[array_right];
            if ( child_value < best_value ) {
              best_value = child_value;
              new_arrayB[depth] = array_right;
              specialB[depth] = 1;
            }
            break;
        }

      }
    }
  }

  return best_value;
}

int main ( void ) {

  int * chip_array = (int *) malloc(100*sizeof(int));
  int * new_arrayA = (int *) malloc(100*sizeof(int));
  int * new_arrayB = (int *) malloc(100*sizeof(int));
  int * specialA = (int *) malloc(100*sizeof(int));
  int * specialB = (int *) malloc(100*sizeof(int));
  int chip_count = 0;
  int array_width;

  printf("Zetony:\n");

  while ( 1 ) {

    if ( chip_count > 99 || scanf(" %d", &chip_array[chip_count]) != 1 ) {
      printf("Nespravny vstup.\n");
      free(chip_array);
      return 0;
    }

    ++chip_count;

    if ( getchar() == '\n' ) {
      break;
    }

  }


  printf("%d\n", minimax ( chip_array, 1, -1000, 1000, 0, chip_count - 1, 0, 0, new_arrayA, new_arrayB, specialA, specialB, -1));

  for ( int i = 0; i < chip_count; ++i ) {
    printf("%d ", chip_array[i]);
  }

  for ( int i = 0; i < chip_count; ++i ) {

    if ( specialA[i] == 1 )
      printf("A [%d]: %d\n", new_arrayA[i], chip_array[new_arrayA[i]]);
    if ( specialA[i] == 2 )
      printf("A: [%d], [%d]: %d + %d\n", new_arrayA[i], new_arrayA[i+1], chip_array[new_arrayA[i]], chip_array[new_arrayA[i+1]]);
    if ( specialB[i] == 1 )
      printf("B [%d]: %d\n", new_arrayB[i], chip_array[new_arrayB[i]]);
    if ( specialB[i] == 2 )
      printf("B: [%d], [%d]: %d + %d\n", new_arrayB[i], new_arrayB[i+1], chip_array[new_arrayB[i]], chip_array[new_arrayB[i+1]]);
  }

  free(new_arrayA);
  free(new_arrayB);
  free(specialA);
  free(specialB);
  free(chip_array);
  return 0;
}
