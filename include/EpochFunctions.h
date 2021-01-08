// EpochFunctions.h
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <iomanip>
#include <regex>
#include <cctype>

std::string strip_string(std::string s){
    std::regex r("\\s+");
    s = std::regex_replace(s, r, "");
    return s;
};

std::vector<std::string> split_string(std::string str, std::string delim){

    std::vector<std::string> v;

    auto start = 0U;
    auto end = str.find(delim);
    while (end != std::string::npos) {
        v.push_back(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    v.push_back(str.substr(start, end));

    return v;
};

int epoch_from_string(std::string time_str)
{
    
    int epoch = 0;
    std::tm t = {};
    std::istringstream ss(time_str);

    if (ss >> std::get_time(&t, "%d/%m/%Y %H:%M")) {
        std::put_time(&t, "%c");
        std::stringstream buffer;
        buffer << std::mktime(&t);
        epoch = stoi( buffer.str() );
    } else {
        std::cout << "Parse failed" << std::endl;
    }
    return epoch;
};

int get_whole_day_start(std::string fullstr){
    std::string day_start_str = fullstr.substr(0, 11) + "00:00";
    return epoch_from_string(day_start_str);
};

void get_epoch_limits(std::vector<std::string> &lines, int num_lines, int &start_day, int &end_day){
    std::string start = split_string(lines[0], ",")[0];
    std::string last  = split_string(lines[num_lines-1], ",")[0];
    start_day = get_whole_day_start(start);
    end_day = get_whole_day_start(last);
};


// 02/06/2020 16:39, 13.3,---,d

void load_csv_file(std::vector<std::string> &lines){

    std::string filepath = "C://2020/recent_bloodsugar.csv";

    std::ifstream file (filepath);
    std::string header_names;
    getline(file, header_names);

    std::string s;
    while (getline(file, s))
        lines.push_back(s);

    file.close();
};

