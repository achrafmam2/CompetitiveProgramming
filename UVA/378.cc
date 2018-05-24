#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

double INF = 1e100;
double EPS = 1e-12;

struct PT {
  double x, y;
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")";
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }
PT RotateCCW(PT p, double t) {
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}

bool LinesParallel(PT a, PT b, PT c, PT d) {
  return fabs(cross(b-a, c-d)) < EPS;
}

bool LinesCollinear(PT a, PT b, PT c, PT d) {
  return LinesParallel(a, b, c, d)
  && fabs(cross(a-b, a-c)) < EPS
  && fabs(cross(c-d, c-a)) < EPS;
}

PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}

int main(void) {
  int T;
  scanf("%i", &T);

  puts("INTERSECTING LINES OUTPUT");

  while (T--) {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    scanf("%i %i %i %i %i %i %i %i", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);

    PT p1 = PT(x1, y1);
    PT p2 = PT(x2, y2);
    PT p3 = PT(x3, y3);
    PT p4 = PT(x4, y4);

    if (LinesCollinear(p1, p2, p3, p4)) {
      puts("LINE");
    } else if (LinesParallel(p1, p2, p3, p4)) {
      puts("NONE");
    } else {
      PT q = ComputeLineIntersection(p1, p2, p3, p4);
      printf("POINT %.2f %.2f\n", q.x, q.y);
    }
  }

  puts("END OF OUTPUT");

  return 0;
}

