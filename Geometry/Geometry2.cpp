//get_dist, get_area, get_equation, get_intersection can't have Type be long long

typedef long double Type;

const int DIR_LEFT = -1,
          DIR_STRAIGHT = 0,
          DIR_RIGHT = 1,
          LINES_INTERSECT = -1,
          LINES_PARALLEL = 0,
          LINES_COINCIDE = 1;

struct Point {
  Type x, y;

  Point() {}

  Point(Type _x, Type _y) {
    x = _x;
    y = _y;
  }
};

struct Line {
  Point A, B;

  Line() {}

  Line(Point _A, Point _B) {
    A = _A;
    B = _B;
  }
};

Point operator + (Point A, Point B) {
  return Point(A.x + B.x, A.y + B.y);
}

Point operator - (Point A, Point B) {
  return Point(A.x - B.x, A.y - B.y);
}

Point operator * (Type k, Point A) {
  return Point(k * A.x, k * A.y);
}

Type operator * (Point A, Point B) {
  return A.x * B.y - A.y * B.x;
}

int get_dir(Point A, Point B, Point C) {
  Type dir = (B - A) * (C - B);

  if (abs(dir + 0.0) <= 1e-9)
    return DIR_STRAIGHT;

  if (dir > 0)
    return DIR_LEFT;

  return DIR_RIGHT;
}

Type get_dist_sq(Point A, Point B) {
  return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

Type get_dist(Point A, Point B) {
  return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

void get_line_equation(Line l, Type &a, Type &b, Type &c) {
  Point A = l.A,
        B = l.B;

  a = B.y - A.y;
  b = A.x - B.x;
  c = -A.x * (B.y - A.y) + A.y * (B.x - A.x);
}

int get_intersection(Line l1, Line l2, Point &res) {
  Type a1, b1, c1, a2, b2, c2, D, Dx, Dy;

  get_line_equation(l1, a1, b1, c1);
  get_line_equation(l2, a2, b2, c2);

  D = a1 * b2 - a2 * b1;
  Dx = b1 * c2 - b2 * c1;
  Dy = c1 * a2 - c2 * a1;

  if (D != 0) {
    res.x = Dx / D;
    res.y = Dy / D;

    return LINES_INTERSECT;
  }

  if (c1 == c2)
    return LINES_COINCIDE;

  return LINES_PARALLEL;
}

Type get_dist(Line l, Point A) {
  Type a, b, c;
  get_line_equation(l, a, b, c);

  return abs(a * A.x + b * A.y + c) / sqrt(a * a + b * b);
}

Type get_area_2(Point A, Point B, Point C) {
  return abs((B - A) * (C - A));
}

Type get_area(Point A, Point B, Point C) {
  return abs((B - A) * (C - A)) / 2;
}

bool is_in_line(Line l, Point A) {
  if (get_dir(l.A, l.B, A) != DIR_STRAIGHT)
    return false;

  if (A.x < min(l.A.x, l.B.x) || max(l.A.x, l.B.x) < A.x)
    return false;

  if (A.y < min(l.A.y, l.B.y) || max(l.A.y, l.B.y) < A.y)
    return false;

  return true;
}

void convex_hull() {
  sort(a + 1, a + n + 1, [] (TPoint a, TPoint b) {
    if (a.y != b.y)
      return (a.y < b.y);

    return (a.x < b.x);
  });

  int n_up = 1,
      n_down = 1;

  up[1] = down[1] = a[1];

  for (int i = 2; i <= n; i++) {
    while (n_up >= 2) {
      if (dir(up[n_up - 1], up[n_up], a[i]) != LEFT)
        break;

      n_up--;
    }

    while (n_down >= 2) {
      if (dir(down[n_down - 1], down[n_down], a[i]) != RIGHT)
        break;

      n_down--;
    }

    up[++n_up] = down[++n_down] = a[i];
  }
}
