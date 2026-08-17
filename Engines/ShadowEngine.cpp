#include "ShadowEngine.hpp"

#include <algorithm>
#include <iostream>


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

    shadowPolygon result;

    // генерация точек
    for(auto& point : building.Perimetr) {
        // точки основания
        result.points.push_back(point);
        // точки крыши
        result.points.push_back(Point2D {.x = point.x + dx, .y = point.y + dy});
    }
    return result;
}