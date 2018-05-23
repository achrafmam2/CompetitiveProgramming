#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int main(void) {
  int r, h;
  scanf("%i %i", &r, &h);

  int count =
    floor(double(h) / double(r) * 2) + floor(double(h % r) / double(r) + 0.15) + 1;
  printf("%i\n", count);

  return 0;
}

