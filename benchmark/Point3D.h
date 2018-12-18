//
// Created by jiahua on 2018/12/17.
//

#ifndef JHASHTABLE_POINT3D_H
#define JHASHTABLE_POINT3D_H
#include <cstddef>
#include <functional>

struct Point3D {
    int x;
    int y;
    int z;
};

struct PointHash {
    std::size_t operator()(const Point3D &point) const noexcept
    {
        std::hash<int> h;
        std::size_t h1 = h(point.x);
        std::size_t h2 = h(point.y);
        std::size_t h3 = h(point.z);
        return h1 ^ ((h2 ^ (h3 << 10)) << 10);
    }
};

struct PointEqual {
    bool operator()(const Point3D &lhs, const Point3D &rhs) const noexcept {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
    }
};

#endif //JHASHTABLE_POINT3D_H
