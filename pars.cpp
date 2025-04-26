#include"way.h"

std::string print(const json& json) {
    if (!json.is_null() && !json.get<std::string>().empty()) {
        return json.get<std::string>();
    }
    return ""; 
}

std::string train_name(const json& json) {
    if (!json.is_null() && !json.get<std::string>().empty()) {
        return "\"" + json.get<std::string>() + "\"";
    }
    return "";
}



void print_routes(json& routes, std::ofstream& file_with_routes) {
    int num_routs = 1;
    for (auto& str : routes["segments"] ) {

        file_with_routes << "Маршрут " << num_routs++ << "\n";
        file_with_routes << print(routes["search"]["from"]["title"]) << " -> " << print(routes["search"]["to"]["title"]) << " - ";

        file_with_routes << time_difference(
            str["departure"].get<std::string>().substr(0, str["departure"].get<std::string>().find('+')),
            str["arrival"].get<std::string>().substr(0, str["arrival"].get<std::string>().find('+'))
        ) << "\n\n";

        if (str["has_transfers"] == false) {
            file_with_routes << "отправка: " << print(str["from"]["title"]) << "\n";
            file_with_routes << "прибытие: " << print(str["to"]["title"]) << "\n\n";
            
            std::string data_time_a = str["departure"]; 
            file_with_routes << "Дата отбытия: " << data_time_a.substr(0, data_time_a.find("T")) << ",  время отбытия: " << data_time_a.substr(data_time_a.find("T") + 1, data_time_a.find('+') - data_time_a.find("T") - 1) 
            << ",  часовой пояс: " << data_time_a.substr(data_time_a.find('+'), data_time_a.size() - data_time_a.find('+')) << "\n";


            std::string data_time_d = str["arrival"];
            file_with_routes << "Дата прибытия: " << data_time_d.substr(0, data_time_d.find("T")) << ",  время прибытия: " << data_time_d.substr(data_time_d.find("T") + 1, data_time_d.find('+') - data_time_d.find("T") - 1) 
            << ",  часовой пояс: " << data_time_d.substr(data_time_d.find('+'), data_time_d.size() - data_time_d.find('+')) << "\n";
            
            
            file_with_routes << "Вид транспорта: " << print(str["from"]["transport_type"]) << "  " << train_name(str["thread"]["title"]) << " " << print(str["thread"]["number"]) << "\n";
                        
            file_with_routes << "\n\n\n";
        } else if (str["has_transfers"] == true && str["transport_types"].size() == 2) {

            auto first_r = str["details"][0];
            auto second_r = str["details"][1];
            auto third_r = str["details"][2];

            file_with_routes << print(str["departure_from"]["station_type_name"]) << ", " << print(str["departure_from"]["title"]) << " -> " <<  print(second_r["transfer_from"]["station_type_name"]) << ", " << print(second_r["transfer_from"]["title"]) << "\n";
            
            file_with_routes << "Вид транспорта: " << print(first_r["thread"]["transport_type"]) << " " << train_name(first_r["thread"]["vehicle"]) << "\n";

            std::string data_a = first_r["departure"];
            file_with_routes << "Дата отбытия: " << data_a.substr(0, data_a.find("T")) << ",  время отбытия: " << data_a.substr(data_a.find("T") + 1, data_a.find('+') - data_a.find("T") - 1) 
            << ",  часовой пояс: " << data_a.substr(data_a.find('+'), data_a.size() - data_a.find('+')) << "\n";

            std::string data_b = first_r["arrival"];
            file_with_routes << "Дата прибытия: " << data_b.substr(0, data_b.find("T")) << ",  время прибытия: " << data_b.substr(data_b.find("T") + 1, data_b.find('+') - data_b.find("T") - 1) 
            << ",  часовой пояс: " << data_b.substr(data_b.find('+'), data_b.size() - data_b.find('+')) << "\n\nПересадка: \n";

            file_with_routes << print(second_r["transfer_to"]["station_type_name"]) << ", " << print(second_r["transfer_to"]["title"]) << " -> " << print(str["arrival_to"]["station_type_name"]) << ", " << print(str["arrival_to"]["title"]) << "\n";
            file_with_routes << "Вид транспорта: " << print(third_r["thread"]["transport_type"]) << " " << train_name(third_r["thread"]["short_title"]) << " " << print(third_r["thread"]["number"]) << "\n\n";
            
            std::string data_c = third_r["departure"];
            file_with_routes << "Дата отбытия: " << data_c.substr(0, data_c.find("T")) << ",  время отбытия: " << data_c.substr(data_c.find("T") + 1, data_c.find('+') - data_c.find("T") - 1) 
            << ",  часовой пояс: " << data_c.substr(data_c.find('+'), data_c.size() - data_c.find('+')) << "\n";

            std::string data_d = third_r["arrival"];
            file_with_routes << "Дата прибытия: " << data_d.substr(0, data_d.find("T")) << ",  время прибытия: " << data_d.substr(data_d.find("T") + 1, data_d.find('+') - data_d.find("T") - 1) 
            << ",  часовой пояс: " << data_d.substr(data_a.find('+'), data_d.size() - data_d.find('+')) << "\n";
            
            file_with_routes << "\n\n\n";
        }
    }
}


void print_file_content(const std::string& file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << file_name << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }

    file.close();
}
