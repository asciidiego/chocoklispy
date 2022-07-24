#include <stdio.h>

typedef struct {
  float x;
  float y;
} Point;

int main(int argc, char** argv) {
  Point p1 = {1, 2};

  printf("Point defined: [%f, %f]", p1.x, p1.y);

  return 0;
}
