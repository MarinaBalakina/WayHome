#include <iostream>
#include "cpr/cpr.h"
#include "way.h"



int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::string year, month, day;
    std::cout << "Введите год, месяц и день отъезда из Санкт-Петербурга\n";
    std::cin >> year >> month >> day;
    std::string date_spb = year + '-' + month + '-' + day;

    std::cout << "Введите год, месяц, день отъезда из Ростова-на-Дону\n";
    std::cin >> year >> month >> day;
    std::string date_rnd = year + '-' + month + '-' + day;

    check_and_compare_dates(date_spb, date_rnd);

    cpr::Response https_to_rnd = cpr::Get(
        cpr::Url{"https://api.rasp.yandex.net/v3.0/search/"},
        cpr::Parameters{
            {"apikey", "b44f8635-73d6-49e6-b8f3-3c778ac4e359"},
            {"from", "c2"},
            {"to", "c39"},
            {"date", date_spb},
            {"transfers", "true"},
            {"format", "json"}
        }
    );

    cpr::Response https_to_spb = cpr::Get(
        cpr::Url{"https://api.rasp.yandex.net/v3.0/search/"},
        cpr::Parameters{
            {"apikey", "b44f8635-73d6-49e6-b8f3-3c778ac4e359"},
            {"from", "c39"},
            {"to", "c2"},
            {"date", date_rnd},
            {"transfers", "true"},
            {"format", "json"}
        }
    );
    
    if (https_to_rnd.status_code == 200 && https_to_spb.status_code == 200) {
        json json_to_rnd = json::parse(https_to_rnd.text);
        json json_to_spb = json::parse(https_to_spb.text);

        std::ofstream outFile("output.json");  
        outFile << json_to_spb.dump(4);  


        if (!fs::exists("to_rnd/" + date_spb + ".txt")){
            std::ofstream routes_to_rnd("to_rnd/" + date_spb + ".txt");
            print_routes(json_to_rnd, routes_to_rnd);
            routes_to_rnd.close();
        } 

        if (!fs::exists("to_spb/" + date_rnd + ".txt")){
            std::ofstream routes_to_spb("to_spb/" + date_rnd + ".txt");
            print_routes(json_to_spb, routes_to_spb);
            routes_to_spb.close();
        }
        
       
        print_file_content("to_rnd/" + date_spb + ".txt");

        std:: cout << "\n\n";
        print_file_content("to_spb/" + date_rnd + ".txt");

       
    
        
    } else {
        if (https_to_rnd.status_code != 200) {
            std::cout << "Error Message: " << https_to_rnd.status_code << "\n";
        }

        if (https_to_spb.status_code != 200) {
            std::cout << "Error Message: " << https_to_spb.status_code << "\n";
        }
    }

    del_old_file("to_rnd");
    del_old_file("to_spb");
   
}
