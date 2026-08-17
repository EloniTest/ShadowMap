#pragma once

#include <chrono>


struct solarVector { 
    double altitude; // показывает угол между горинтом и солнцем, измеряется в градусах
    double azimuth;  // показывает угол между севером и солнцем, измеряется в градусах
};

class AstronomyEngine {
    private:
        const double PI = 3.14159265358979323846;
        const double DEG2RAD = PI / 180.0;
        const double RAD2DEG = 180.0 / PI;
    public:
        solarVector calculateSolarPosition(double latDeg, double lonDeg, std::chrono::system_clock::time_point timePoint);
};