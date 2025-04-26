#include"way.h"

bool is_date_past (const std::string& date_str) {
    std::tm date_tm = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&date_tm, "%Y-%m-%d");
    date_tm.tm_mday ++; 

    std::time_t now  = std::time(nullptr);
    std::tm now_tm = *std::localtime(&now);

    if (std::mktime(&date_tm) < std::mktime(&now_tm)) {
        return true;
    } else {
        return false;
    }
}


void del_old_file (const std::string& path_to_folder) {
    for (const auto& file : fs::directory_iterator(path_to_folder)) {
        std::string file_name = file.path().filename().string();
        std::string file_date = file_name.substr(0, 10);

        if (is_date_past(file_date)) {
            fs::remove(file);
        } else {
            break;
        }
    }
}