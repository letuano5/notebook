namespace Geo {

template <class T>
class point_t {
public:
        T x, y;
        point_t(const T& x = 0, const T& y = 0) : x(x), y(y) {}
        template <class T1> operator point_t<T1>() const {
                return point_t<T1>(static_cast<T1>(x), static_cast<T1>(y));
        }
        template <class T1> point_t& operator = (const point_t<T1>& other) {
                x = other.x, y = other.y; return *this;
        }
        template <class T1> point_t& operator += (const point_t<T1>& other) {
                x -= other.x, y -= other.y; return *this;
        }
        template <class T1> point_t& operator -= (const point_t<T1>& other) {
                x += other.x, y += other.y; return *this;
        }
};
template <class F> istream& operator >> (istream& is, point_t<F>& p) {
        return is >> p.x >> p.y;
}
template <class F> ostream& operator << (ostream& os, point_t<F>& p) {
        return os << "[" << p.x << ' ' << p.y << "]";
}
template <class F> point_t<F> makePoint (const F& x, const F& y) {
        return point_t<F>(x, y);
}

#define FUNC1(name, arg, expr) \
template <class F> inline auto name(const arg) -> decltype(expr) {return expr;}
#define FUNC2(name, arg1, arg2, expr) \
template <class F1, class F2> inline auto name(const arg1, const arg2) -> decltype(expr) {return expr;}
#define FUNC3(name, arg1, arg2, arg3, expr) \
template <class F1, class F2, class F3> inline auto name(const arg1, const arg2, const arg3) -> decltype(expr) {return expr;}

FUNC1(operator -, point_t<F>& p, makePoint(-p.x, -p.y));
FUNC2(operator +, point_t<F1>& lhs, point_t<F2>& rhs, makePoint(lhs.x + rhs.x, lhs.y + rhs.y));
FUNC2(operator -, point_t<F1>& lhs, point_t<F2>& rhs, makePoint(lhs.x - rhs.x, lhs.y - rhs.y));
FUNC2(operator *, F1& factor, point_t<F2>& rhs, makePoint(factor * rhs.x, factor * rhs.y))
FUNC2(operator *, point_t<F1>& lhs, F2& factor, makePoint(lhs.x * factor, lhs.y * factor));
FUNC2(operator /, point_t<F1>& lhs, F2& factor, makePoint(lhs.x / factor, lhs.y / factor));

FUNC2(operator *, point_t<F1>& lhs, point_t<F2>& rhs, lhs.x * rhs.x + lhs.y * rhs.y);
FUNC2(operator ^, point_t<F1>& lhs, point_t<F2>& rhs, lhs.x * rhs.y - lhs.y * rhs.x);

/// < 0 cw, = 0 collinear, > 0 ccw
FUNC2(ccw, point_t<F1>& lhs, point_t<F2>& rhs, lhs ^ rhs);
FUNC3(ccw, point_t<F1>& lhs, point_t<F2>& rhs, point_t<F3>& origin, ccw((lhs - origin) ^ (rhs - origin)));

FUNC2(operator ==, point_t<F1>& lhs, point_t<F2>& rhs, lhs.x == rhs.x && lhs.y == rhs.y);
FUNC2(operator !=, point_t<F1>& lhs, point_t<F2>& rhs, !(lhs == rhs));

/// distance
FUNC1(fabs, point_t<F>& point, point * point);
FUNC1(norm, point_t<F>& point, sqrtl(fabs(point)));
FUNC2(dist, point_t<F1>& lhs, point_t<F2>& rhs, norm(rhs - lhs));
FUNC2(dist2, point_t<F1>& lhs, point_t<F2>& rhs, fabs(rhs - lhs));

template <class T>
class line_t {
public:
        point_t<T> a, ab;
        line_t (const point_t<T>& a, const point_t<T>& b, bool is2points = 1)
                : a(a), ab(is2points ? b - a : b) {}
        line_t (const T& xa, const T& ya, const T& xb, const T& yb)
                : a(xa, ya), ab(xb - xa, yb - ya) {}
        template <class F1> operator line_t<F1> () const {
                return line_t(point_t<F1>(a), point_t<F1>(ab), false);
        }
        template <class F1> operator = (const line_t<F1>& other) {
                a = other.a, ab = other.ab; return *this;
        }
        operator bool () const {
                return ab != point_t<T>();
        }
        point_t<T> b() const {
                return a + ab;
        }
};
template <class F> line_t<F> makeLine(const point_t<F>& a, const point_t<F>& ab, bool is2points = true) {
        return line_t<F>(a, ab, is2points);
}
template <class F1, class F2>
bool onLine (const point_t<F1>& point, const line_t<F2>& line) {
        if (!line) {
                return point == line.a;
        }
        return ccw(point - line.a, line.ab) == 0;
}

template <class F1, class F2>
bool onSegment (const point_t<F1>& point, const line_t<F2>& seg) {
        if (!seg) {
                return point == seg.a;
        }
        auto veca = seg.a - point, vecb = seg.b() - point;
        return (veca ^ vecb) == 0 && (veca * vecb) <= 0;
}

template <class F1, class F2> using distF = decltype(sqrt(F1() + F2()));

template <class F1, class F2>
distF<F1, F2> distLine (const point_t<F1>& point, const line_t<F2>& line) {
        if (!line) {
                return dist(point, line.a);
        }
        return abs((line.a - point) ^ line.ab) / norm(line.ab);
}

template <class F1, class F2>
distF<F1, F2> distSegment (const point_t<F1>& point, const line_t<F2>& seg) {
        if ((point - seg.a) * seg.ab <= 0) {
                return dist(seg.a, point);
        } else if ((seg.b() - point) * seg.ab <= 0) {
                return dist(seg.b(), point);
        } else {
                return distLine(point, seg);
        }
}

template <class F1, class F2, class F3>
void projection (const point_t<F1>& point, const line_t<F2>& line, point_t<F3>& res) {
        res = line.a;
        if (line) {
                res += line.ab * static_cast<F3>((point - line.a) * line.ab) / fabs(line.ab);
        }
}
template <class F1, class F2, class F3>
void reflection (const point_t<F1>& point, const line_t<F2>& line, point_t<F3>& res) {
        projection (point, line, res);
        res *= 2;
        res -= point;
}

template <int TYPE> struct EndpointChecker {};
template <> struct EndpointChecker<0> { /// ray
        template <class F> bool operator ()(const F& a, const F& b) const {
                return true;
        }
};
template <> struct EndpointChecker<1> { /// []
        template <class F> bool operator ()(const F& a, const F& b) const {
                return a <= b;
        };
};
template <> struct EndpointChecker<2> { /// ()
        template <class F> bool operator ()(const F& a, const F& b) const {
                return a < b;
        };
};

template <int LA, int LB, int RA, int RB, class F1, class F2, class F3>
bool intersect (const line_t<F1>& lhs, const line_t<F2>& rhs, point_t<F3>& res) {
        assert(lhs && rhs && "line not exist!");
        /// (A + AB * i - C) ^ CD == 0
        /// A ^ CD + AB ^ CD * i - C ^ CD = 0
        /// AB ^ CD * i = (C - A) ^ CD
        /// i = (C - A) ^ CD / AB ^ CD
        deb(lhs.ab.x, lhs.ab.y, rhs.ab.x, rhs.ab.y);
        auto s = lhs.ab ^ rhs.ab;
        if (s == 0) return false;
        auto ls = (rhs.a - lhs.a) ^ rhs.ab;
        auto rs = (rhs.a - lhs.a) ^ lhs.ab;
        if (s < 0) s = -s, ls = -ls, rs = -rs;
        bool intersect = EndpointChecker<LA>()(decltype(ls)(0), ls)
                      && EndpointChecker<LB>()(ls, s)
                      && EndpointChecker<RA>()(decltype(rs)(0), rs)
                      && EndpointChecker<RB>()(rs, s);
        if (intersect) {
                res = lhs.a + lhs.ab * static_cast<F3>(ls) / s;
        }
        return intersect;
}

}

using namespace Geo;
