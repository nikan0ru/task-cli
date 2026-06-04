#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

std::string writeTask(int id, std::string desc, std::string status = "Todo")
{
	std::string TaskId;
	std::string Task;
	std::stringstream ss;
	ss << id;
	TaskId = ss.str();
	if(id != 0)
	{
		Task.append(",");
	}
	Task += "\n\t{\n\t\t\"taskId\":\"" + TaskId + "\",\n\t\t\"description\":\"" + desc + "\",\n\t\t\"status\":\"" + status + "\"\n\t}\n";
	return Task;
}

std::string * parseCommand(int argc, const char *argv[], std::string fileName)
{
	if (argc < 3)
	{
		std::cout << "task-cli \nUsage: \n";
		std::cout << "\tadd <description > <status>\n";
		std::cout << "\tupdate <id> <description>\n";
		std::cout << "\tmark-in-progress <id> \n";
		std::cout << "\tmark-done <id> \n";
		std::cout << "\tdelete <id>\n";
		std::cout << "\tlist <status> (done, todo, in-progress)\n";
		return NULL;
	}
	std::fstream file(fileName.c_str(), std::ios::in);
	if (!file.is_open())
	{
		std::cout << "Cannot open " + fileName + "!" << std::endl;
		std::cout << "Creating " + fileName << std::endl;
		std::ofstream newfile(fileName.c_str());
		newfile << "[]";
		newfile.close();
		return NULL;
	}
	file.close();
	std::string *command = new std::string[argc-1];
	for (size_t i = 1; i < argc; i++)
	{
		command[i-1] = argv[i];
	}
	return command;
}

int getLastId(std::string fileName, std::stringstream& ss)
{
	int id;

	id = 0;
	std::string line;
	while (std::getline(ss, line))
	{
		if(!line.compare(0, 11, "\t\t\"taskId\":"))
			id++;
	}

	return id;
}
void AddTask(std::string fileName,std::string *command)
{
	std::stringstream ss;
	std::fstream file;
	std::string Task;
	int id;
	file.open(fileName.c_str(), std::ios::in | std::ios::out);
	ss << file.rdbuf();
	file.close();
	std::string content = ss.str();
	id = getLastId(fileName, ss);
	int pos;
	pos = content.find_last_of("]");
	Task = writeTask(id, command[1]);
	content.insert(pos, Task);
	file.open(fileName.c_str(), std::ios::out);
	file << content;
	file.close();
}

int main(int argc, char const *argv[])
{
	std::string fileName("tasks.json");
	std::string *command = parseCommand(argc, argv, fileName);
	if(!command)
		return 1;
	if (command[0].compare("add") == 0)
	{
		AddTask(fileName, command);
	}

	return 0;
}
