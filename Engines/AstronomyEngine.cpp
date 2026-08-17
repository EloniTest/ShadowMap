#include "AstronomyEngine.hpp"
#include <cmath>
#include <algorithm>
#include <ctime>

solarVector AstronomyEngine::calculateSolarPosition(double latDeg, double lonDeg, std::chrono::system_clock::time_point timePoint) {
    // Получение дня года и время в UTC часах
    // хз что это но надо для рассчета дня и часов
    std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint);
    std::tm utcTm{};
    #if defined(_WIN32) || defined(_WIN64)
        gmtime_s(&utcTm, &timeT);
    #else
        gmtime_r(&timeT, &utcTm);
    #endif



    int dayOfYear = utcTm.tm_yday + 1; // tm_yday начинается с 0, поэтому + 1
    double utcHours = utcTm.tm_hour + (utcTm.tm_min / 60.0) + (utcTm.tm_sec / 3600.0);

    // склонение солнца в градусах меняется от -23.45 зимой и +23.45 летом (была ошибка в формуле, рассчет был неверен)
    double declinationDeg = 23.45 * std::sin((360.0 / 365.0) * (dayOfYear + 284) * DEG2RAD);
    double declination = declinationDeg * DEG2RAD;

    // часовой угол смещение солнца от местного полудня(1 ч = 15 град)
    double localSolarTime = utcHours + (lonDeg / 15.0); // Местное время по долготе
    double hourAngle = (localSolarTime - 12.0) * 15.0 * DEG2RAD;

    

    // рассчет алтитуды
    double latRad = latDeg * DEG2RAD;
    double sinAlt = std::sin(latRad) * std::sin(declination) + std::cos(latRad) * std::cos(declination) * std::cos(hourAngle);

    // ограничение значения синуса между -1 и 1
    sinAlt = std::clamp(sinAlt, -1.0, 1.0);
    // вычисляет арк синус в радианах
    double altitudeRad = std::asin(sinAlt);



    // рассчет азимута
    double cosAz = (std::sin(declination) - std::sin(latRad) * std::sin(altitudeRad)) / (std::cos(latRad) * std::cos(altitudeRad));
    cosAz = std::clamp(cosAz, -1.0, 1.0);
    // азимут в градусы
    double azimuthDeg = std::acos(cosAz) * RAD2DEG;

    // коррекция направления азимута 
    if (std::sin(hourAngle) > 0) {
        azimuthDeg = 360.0 - azimuthDeg;
    }

    return solarVector{.altitude = altitudeRad * RAD2DEG, .azimuth = azimuthDeg};

};

