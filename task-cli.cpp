#include <iostream>
#include <fstream>
#include "json.hpp"

int main(int argc, char const *argv[])
{
	using json = nlohmann::json;
	std::string fileName{"tasks.json"};
	std::fstream file(fileName, std::ios::in);
	if(!file.is_open())
	{
		std::cout << "Cannot open " + fileName + "!"<< std::endl;
		std::cout << "Creating "+ fileName << std::endl;
		std::ofstream newfile(fileName);
		newfile << "[]";
		newfile.close();
		return 0;
	}
	if(!json::accept(file))
	{
		std::cout << "File Contains invalid JSON !" << std::endl;
		return 1;
	}
	file.close();
	if(argc < 2)
	{
		std::cout << "task-cli :)" << std::endl;
		return 0;
	}
	std::string command{argv[1]};
	if(command.compare("add") == 0)
	{
		file.clear();
        file.seekg(0);
		file.open(fileName, std::ios::out);
		try
		{
			json j = json::parse(file);
			j["data"] = "mimi";
		}catch (const json::parse_error& e) {
        	std::cerr << "JSON Parse Error: " << e.what() << std::endl;
		}
		file.close();
	}

	return 0;
}

