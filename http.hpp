#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

typedef std::map<std::string, std::string> Param;

class Http {
private:
	std::string method;
	Param param;
public:
	Http() {
		char* tmp = getenv("REQUEST_METHOD");
		if (tmp == NULL) {
			std::cerr << "Failed to identify request method" << std::endl;
			exit(1);
		}
		method = tmp;
		std::string input;

		if (method == "GET") {
			char* tmp = getenv("QUERY_STRING");
			if (tmp != NULL) {
				input = std::string(tmp);
			}
		} else if (method == "POST") {
			getline(std::cin, input);
		}

		int pos = 0; 
		int start = 0;
		while ( pos != std::string::npos) {
			std::string key;
			std::string value;

			pos = input.find("=", start);
			key = input.substr(start, pos - start);
			start = ++pos;
			pos = input.find("&", start);
			value = input.substr(start, pos - start);
			param[key] = value;
			if (pos == std::string::npos) break;
			start = ++pos;
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

