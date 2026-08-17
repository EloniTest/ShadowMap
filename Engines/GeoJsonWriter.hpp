
// НЕЙРОНКА!!!!!!!!!!!!!!!!
#pragma once

#include <fstream>
#include <string>
#include <cmath>
#include "ShadowEngine.hpp" // Подключаем ваш файл заголовок

class GeoJsonWriter {
public:
    static bool saveShadowToGeoJson(
        const std::string& filename,
        const shadowPolygon& shadow, // Используем ваше имя структуры
        double baseLat,
        double baseLon
    ) {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        constexpr double METERS_PER_DEG_LAT = 111139.0;
        double metersPerDegLon = 111139.0 * std::cos(baseLat * 3.141592653589793 / 180.0);

        file << "{\n";
        file << "  \"type\": \"FeatureCollection\",\n";
        file << "  \"features\": [\n";
        file << "    {\n";
        file << "      \"type\": \"Feature\",\n";
        file << "      \"properties\": { \"name\": \"Building Shadow\" },\n";
        file << "      \"geometry\": {\n";
        file << "        \"type\": \"Polygon\",\n";
        file << "        \"coordinates\": [[\n";

        for (size_t i = 0; i < shadow.points.size(); ++i) {
            double lon = baseLon + (shadow.points[i].x / metersPerDegLon);
            double lat = baseLat + (shadow.points[i].y / METERS_PER_DEG_LAT);

            file << "          [" << lon << ", " << lat << "]";
            if (i + 1 < shadow.points.size()) file << ",";
            file << "\n";
        }

        // Замыкаем контур
        if (!shadow.points.empty()) {
            double firstLon = baseLon + (shadow.points[0].x / metersPerDegLon);
            double firstLat = baseLat + (shadow.points[0].y / METERS_PER_DEG_LAT);
            file << "         ,[" << firstLon << ", " << firstLat << "]\n";
        }

        file << "        ]]\n";
        file << "      }\n";
        file << "    }\n";
        file << "  ]\n";
        file << "}\n";

        return true;
    }
};