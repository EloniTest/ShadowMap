#include "Engines/AstronomyEngine.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>



int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Shadow Map Navigator" << std::endl;

    // корды волгограда
    const double volgogradLat = 48.7071;
    const double volgogradLon = 44.5169;
    const double PI = 3.14159265358979323846;


    std::tm timeStruct = {};
    timeStruct.tm_year = 2026 - 1900; // 2026 год
    timeStruct.tm_mon = 7;            // Август (месяцы от 0 до 11)
    timeStruct.tm_mday = 17;
    timeStruct.tm_hour = 12;          // 12 UTC == 15:00 мск
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
    std::cout << "Latitude / Longitude " << volgogradLat << " / " << volgogradLon << std::endl;
    std::cout << "Date and Time UTC : 2026-08-17 15:00:00 UTC" << std::endl;
    std::cout << "Sun altitude " << sun.altitude << "° " << std::endl;

    std::cout << "Sun Azimuth " << sun.azimuth << "° " << std::endl;
    std::cout << "Shadow Vector Direction " << ((sun.azimuth + 180.0) / 360.0) * (180.0 / PI) << "° " << std::endl;


    return 0;
}