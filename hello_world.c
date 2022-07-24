#include <stdio.h>

int main(int argc, char** argv) {
  struct point {
    float x;
    float y;
  };
  struct point p1;
  p1.x = 1;
  p1.y = 2;
  printf("Point defined: [%f, %f]", p1.x, p1.y);
  return 0;
}
