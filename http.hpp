#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <map>

namespace HTTP {
    typedef std::map<std::string, std::string> Param;
};

class Http {
 private:
    std::string method;
    std::string cookie;
    HTTP::Param param;

    void parse_parameter(const std::istream &input) {
        std::string tmp;
        while (getline(input, tmp, '&')) {
            int pos = tmp.find("=");
            param[tmp.substr(0, pos)] = tmp.substr(pos+1);
        }
    }

 public:
    Http() {
        const char* tmp = getenv("REQUEST_METHOD");
        if (tmp == nullptr) {
            std::cerr << "Failed to identify request method" << std::endl;
            exit(1);
        }
        method = tmp;

       if (method == "GET") {
            char* tmp = getenv("QUERY_STRING");
            if (tmp != nullptr) {
                std::istringstream ss = std::istringstream(tmp);
                parse_parameter(ss);
            }
        } else if (method == "POST") {
            parse_parameter(std::cin);
        }

       tmp = getenv("HTTP_COOKIE");
       if (tmp != nullptr) {
           cookie = std::string(tmp);
       }
    }

    void print() {
        for (auto x: param) {
            std::cout << x.first << " " << x.second << std::endl;
        }
    }

    std::string get_method() {
        return method;
    }

    std::string operator[](std::string index) {
        return param[index];
    }
};

