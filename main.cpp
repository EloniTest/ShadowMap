#include "Engines/AstronomyEngine.hpp"
#include "Engines/ShadowEngine.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>



int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Shadow Map Navigator" << std::endl;

    // корды волгограда
    const double volgogradLat = 48.7194;
    const double volgogradLon = 44.5018;
    const double PI = 3.14159265358979323846;


    
    // координаты и время
    std::tm timeStruct = {};
    timeStruct.tm_year = 2026 - 1900; // 2026 год
    timeStruct.tm_mon = 7;            // Август (месяцы от 0 до 11)
    timeStruct.tm_mday = 17;
    timeStruct.tm_hour = 9;          // 9 UTC == 12:00 мск
    timeStruct.tm_min = 59;
    timeStruct.tm_sec = 0;
    


    // здание 10 на 10 метров, высотой 30 метров
    Building building{
        .Perimetr = {
            {0.0, 0.0},
            {10.0, 0.0},
            {10.0, 10.0},
            {0.0, 10.0}
        },
        .height = 30.0
    };



    #if defined(_WIN32) || defined(_WIN64)
        std::time_t timeT = _mkgmtime(&timeStruct);
    #else
        std::time_t timeT = timegm(&timeStruct);
    #endif

    auto testTime = std::chrono::system_clock::from_time_t(timeT);
    
    
    // вызов движка рассчета
    AstronomyEngine Engine;

    solarVector sun = Engine.calculateSolarPosition(volgogradLat, volgogradLon, testTime);
    
    // вызов движка тени
    ShadowEngine SEngine;
    auto Shadow = SEngine.calculateBuildingShadow(building, sun);

    // =========================================================
    std::cout << "\n\nTest AstronomyEngine (Volgograd)\n";
    std::cout << "Latitude / Longitude " << volgogradLat << " / " << volgogradLon << std::endl;
    std::cout << "Date and Time UTC : 2026-08-17 15:00:00 UTC" << std::endl;
    std::cout << "Sun altitude " << sun.altitude << " deg" << std::endl;

    std::cout << "Sun Azimuth " << sun.azimuth << " deg" << std::endl;
    std::cout << "Shadow Vector Direction " << ((sun.azimuth + 180.0) / 360.0) * (180.0 / PI) << " deg" << std::endl;
    // =========================================================

    // =========================================================
    std::cout << "\n\nTest ShadowEngine\n";
    std::cout << "Building height: " << building.height << " M" << std::endl;
    std::cout << "Points in shadow polygon: " << Shadow.points.size() << std::endl;
    std::cout << "Cords calculated points of shadow: " << std::endl;
    for(int i = 0; i < Shadow.points.size(); i++) {
        std::cout << "  Pt " << i << ": X = " << Shadow.points[i].x << " M, Y = " << Shadow.points[i].y << " M\n";
    }
    // =========================================================




    return 0;
}