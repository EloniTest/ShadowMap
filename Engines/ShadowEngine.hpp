#pragma once

#include <vector>
#include <cmath>
#include "AstronomyEngine.hpp"


// координаты x и y (в метрах)
struct Point2D {
    double x;
    double y;
};


// тип контура и высоты здания
struct Building {
    std::vector<Point2D> Perimetr;
    double height;
};


// тип точки полигона тени
struct shadowPolygon {
    std::vector<Point2D> points;
};

class ShadowEngine {
    private:
        const double PI = 3.14159265358979323846;
        const double DEG2RAD = PI / 180.0;
    public:
        // метод строить полигон тени в зависимости от заданных параметров, building - периметр здания и его высота, sun вектор положения солнца(амплитуда и азимут)
        shadowPolygon calculateBuildingShadow( const Building& building, const solarVector&sun);
};