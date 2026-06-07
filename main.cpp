#include "task-cli.h"

std::string *parseCommand(int argc, const char *argv[])
{
	if (argc < 2)
	{
		std::cout << "task-cli \nUsage: \n";
		std::cout << "\tadd <description> <status>\n";
		std::cout << "\tupdate <id> <description>\n";
		std::cout << "\tmark-in-progress <id> \n";
		std::cout << "\tmark-done <id> \n";
		std::cout << "\tdelete <id>\n";
		std::cout << "\tlist \n";
		return NULL;
	}
	std::string *command = new std::string[argc - 1];
	int j = 0;
	for (int i = 1; i < argc; i++)
	{
		command[j++] = argv[i];
	}
	return command;
}

void listTasks(std::stringstream &ss)
{
	std::cout << " id | Description       " << "\n";
	std::cout << "------------------------\n";

	// ss.seekg(0);
	std::string line;
	std::string TaskId;
	std::string TaskDescription;
	std::string TaskStatus;
	while (std::getline(ss, line))
	{
		if (line.find("\t\t\"taskId\":") != std::string::npos)
		{
			TaskId = line.substr(11, line.length() -12);
			std::cout << " " + TaskId + "  " << "|";
		}
		if (line.find("\t\t\"description\":\"") != std::string::npos)
		{
			TaskDescription = line.substr(17, line.length() -19);
			std::cout << " " + TaskDescription << "\n";
		}
	}
}

int main(int argc, char const *argv[])
{
	std::stringstream ss;
	std::string fileContent;
	std::string fileName("tasks.json");

	std::string *command = parseCommand(argc, argv);
	if (!command)
		return 1;
	std::fstream file(fileName.c_str(), std::ios::in);
	if (!file.is_open())
	{
		std::cout << "Cannot open " + fileName + "!" << std::endl;
		return 1;
	}
	ss << file.rdbuf();
	file.close();
	if (command[0].compare("add") == 0)
	{
		AddTask(fileName, command, ss);
	}
	else if (command[0].compare("delete") == 0)
	{
		deleteTask(command[1], ss); // not working
	}
	else if (command[0].compare("list") == 0)
	{
		listTasks(ss);
	}
	delete[] command;
	return 0;
}
