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
}

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

