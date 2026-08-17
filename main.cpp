#include "Engines/AstronomyEngine.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>



int main() {
    std::cout << "Shadow Map Navigator" << std::endl;

    // корды волгограда
    const double volgogradLat = 48.7071;
    const double volgogradLon = 44.5169;


    std::tm timeStruct = {};
    timeStruct.tm_year = 2026 - 1900; // 2026 год
    timeStruct.tm_mon = 6;            // Июль (месяцы от 0 до 11)
    timeStruct.tm_mday = 15;
    timeStruct.tm_hour = 12;          // 12:00 UTC (полдень по Гринвичу)
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;

    #if defined(_WIN32) || defined(_WIN64)
        std::time_t timeT = _mkgmtime(&timeStruct);
    #else
        std::time_t timeT = timegm(&timeStruct);
    #endif

    auto testTime = std::chrono::system_clock::from_time_t(timeT);
    
    
    // вызов движка рассчета
    AstronomyEngine Engine;

    solarVector sun = Engine.calculateSolarPosition(volgogradLat, volgogradLon, testTime);

    std::cout << "Test AstronomyEngine (Volgograd)\n";
    std::cout << "Широта / долгота " << volgogradLat << " / " << volgogradLon << std::endl;
    std::cout << "Дата и время UTC : 2026-07-15 12:00:00 UTC" << std::endl;
    std::cout << "Высота Солнца " << sun.altitude << "° " << std::endl;

    std::cout << "Азимут Солнца " << sun.azimuth << "° " << std::endl;
    std::cout << "Направление вектора тени" << (sun.azimuth + 180.0) / 360.0 << "° " << std::endl;


    return 0;
}