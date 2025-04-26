#include"way.h"

std::string time_difference(const std::string& departure, const std::string& arrival) {
    std::chrono::system_clock::time_point departure_time;
    std::chrono::system_clock::time_point arrival_time;

    std::tm tm_departure = {}, tm_arrival = {};

    std::istringstream departure_ss(departure);
    departure_ss >> std::get_time(&tm_departure, "%Y-%m-%dT%H:%M:%S");
    departure_time = std::chrono::system_clock::from_time_t(std::mktime(&tm_departure));

    std::istringstream arrival_ss(arrival);
    arrival_ss >> std::get_time(&tm_arrival, "%Y-%m-%dT%H:%M:%S");
    arrival_time = std::chrono::system_clock::from_time_t(std::mktime(&tm_arrival));

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(arrival_time - departure_time);

    int days = duration.count() / (60 * 60 * 24);
    int hours = (duration.count() % (60 * 60 * 24)) / (60 * 60);
    int minutes = (duration.count() % (60 * 60)) / 60;

    return std::to_string(days) + " дней " + std::to_string(hours) + " часов " + std::to_string(minutes) + " минут";
}

void check_and_compare_dates(const std::string& date1, const std::string& date2) {
    std::tm tm1 = {}, tm2 = {};
    std::istringstream ss1(date1);
    std::istringstream ss2(date2);
    
    ss1 >> std::get_time(&tm1, "%Y-%m-%d");
    ss2 >> std::get_time(&tm2, "%Y-%m-%d");

    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    if (time1 >= time2) {
        std::cerr << "Ошибка: вторая дата должна быть позднее первой.\n";
        std::exit(EXIT_FAILURE);
    } 
}