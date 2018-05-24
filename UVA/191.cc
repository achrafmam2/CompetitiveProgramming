#include <iostream>
#include <cstdio>
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
  PT(int x, int y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
  return fabs(cross(b-a, c-d)) < EPS;
}

bool LinesCollinear(PT a, PT b, PT c, PT d) {
  return LinesParallel(a, b, c, d)
  && fabs(cross(a-b, a-c)) < EPS
  && fabs(cross(c-d, c-a)) < EPS;
}

// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
        dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}

bool PointInPolygon(const vector<PT> &p, PT q) {
  bool c = 0;
  for (int i = 0; i < p.size(); i++){
    int j = (i+1)%p.size();
    if ((p[i].y <= q.y && q.y < p[j].y ||
         p[j].y <= q.y && q.y < p[i].y) &&
        q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}

int main(void) {
  int T;
  scanf("%i", &T);

  while (T--) {
    int x, y;
    scanf("%i %i", &x, &y);
    PT l = PT(x, y);
    scanf("%i %i", &x, &y);
    PT r = PT(x, y);

    int xl, yt, xr, yb;
    scanf("%i %i %i %i", &xl, &yt, &xr, &yb);

    vector<PT> rectangle = {PT(xl, yt), PT(xr, yt), PT(xr, yb), PT(xl, yb)};

    if (SegmentsIntersect(l, r, PT(xl, yt), PT(xl, yb)) ||
        SegmentsIntersect(l, r, PT(xl, yt), PT(xr, yt)) ||
        SegmentsIntersect(l, r, PT(xr, yt), PT(xr, yb)) ||
        SegmentsIntersect(l, r, PT(xr, yb), PT(xl, yb)) ||
        PointInPolygon(rectangle, l) || PointInPolygon(rectangle, r)) {
      puts("T");
    } else {
      puts("F");
    }
  }

  return 0;
}
