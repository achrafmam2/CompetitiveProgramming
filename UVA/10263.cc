/// Railway
/// Compute the shortest distance of given point to segments given.
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

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
  double r = dot(b-a,b-a);
  if (fabs(r) < EPS) return a;
  r = dot(c-a, b-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

int main(void) {
  double x, y;
  while (scanf("%lf %lf", &x, &y) != EOF) {
    int n;
    scanf("%i", &n);
    vector<PT> points(n + 1);
    for (auto &p : points) {
      scanf("%lf %lf", &p.x, &p.y);
    }

    double best = 1e18;
    PT station;
    for (int i = 0; i < n; i++) {
      if (best > DistancePointSegment(points[i], points[i + 1], PT(x, y))) {
        best = DistancePointSegment(points[i], points[i + 1], PT(x, y));
        station = ProjectPointSegment(points[i], points[i + 1], PT(x, y));
      }
    }

    printf("%.4f\n%.4f\n", station.x, station.y);
  }
  return 0;
}

