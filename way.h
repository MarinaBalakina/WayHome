#include <iostream>
#include <nlohmann/json.hpp>
#include <chrono>
#include <sstream>
#include<fstream>
#include <string>
#include<ctime>
#include<filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

std::string print(const nlohmann::json& json); 
void print_routes(json& routes, std::ofstream& file_with_routes);
std::string time_difference(const std::string& departure, const std::string& arrival);
void check_and_compare_dates(const std::string& date1, const std::string& date2);
void print_file_content(const std::string& file_name);
bool is_date_past (const std::string& date_str); 
void del_old_file (const std::string& path_to_folder);