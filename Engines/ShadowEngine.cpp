#include "ShadowEngine.hpp"

#include <algorithm>
#include <iostream>


// крестное произведение для определения поворота
static double crossProduct(const Point2D& O, const Point2D& A, const Point2D& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// алгоритм построения внешнего контура (Monotone Chain)
static std::vector<Point2D> buildConvexHull(std::vector<Point2D>& pts) {
    size_t n = pts.size(), k = 0;
    if (n <= 3) return pts;

    std::vector<Point2D> h(2 * n);

    // cортировка точек по X, а при равенстве — по Y
    std::sort(pts.begin(), pts.end(), [](const Point2D& a, const Point2D& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    // нижняя
    for (size_t i = 0; i < n; ++i) {
        while (k >= 2 && crossProduct(h[k-2], h[k-1], pts[i]) <= 0) k--;
        h[k++] = pts[i];
    }

    // верхняя
    for (size_t i = n - 1, t = k + 1; i > 0; --i) {
        while (k >= t && crossProduct(h[k-2], h[k-1], pts[i-1]) <= 0) k--;
        h[k++] = pts[i-1];
    }

    h.resize(k - 1);
    return h;
}


shadowPolygon ShadowEngine::calculateBuildingShadow(const Building& building, const solarVector&sun) {
    if (sun.altitude <= 0.0) {
        std::cout << "sun is down from horizon\n";
        return shadowPolygon{};
    }

    // L = height / tan(altitude) рассчет длины тени от вершинной точки
    double altRad = sun.altitude * DEG2RAD;
    double shadowLength = building.height / std::tan(altRad);

    // направление тени (fmod нужен для вычисления остатка от деления чисел с запятой, нужен для double, long, float аналог %)
    double shadowAzimuthDeg = std::fmod(sun.azimuth + 180.0, 360.0);
    double shadowAzimuthRad = shadowAzimuthDeg * DEG2RAD;

    // вектор смещения тени
    double dx = shadowLength * std::sin(shadowAzimuthRad);
    double dy = shadowLength * std::cos(shadowAzimuthRad);

    std::vector<Point2D> shadowPoints;
    
    // генерация точек
    for(const auto& point : building.Perimetr) {
        // точки основания
        shadowPoints.push_back(point);
        // точки крыши
        shadowPoints.push_back(Point2D {.x = point.x + dx, .y = point.y + dy});
    }

    std::vector<Point2D> cleanHull = buildConvexHull(shadowPoints);

    return shadowPolygon{.points = cleanHull};
}