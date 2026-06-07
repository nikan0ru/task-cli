#include "task-cli.h"

void AddTask(std::string &fileName,std::string *command, std::stringstream& ss)
{
	std::fstream file;
	std::string Task;
	int id;
	int pos;

	std::string content = ss.str();
	id = getLastId(ss);

	pos = content.find_last_of("]");
	Task = writeTask(++id, command[1]);
	content.insert(pos, Task);
	file.open(fileName.c_str(), std::ios::out);
	file << content;
	file.close();
}


void deleteTask(std::string id, std::stringstream & ss)
{
	if(id.empty())
	{
		std::cout << "Error No Id provided\n";
		return;
	}
	std::fstream file("tasks.json", std::ios::in);
	std::string line;
	std::string Taskid = "\t{\n\t\t\"taskId\":\"" + id +"\",";

	std::string content = ss.str();
	size_t start = content.find(Taskid);
	if(start == std::string::npos)
	{
		std::cout << "NO task with ID : " + id;
		return;
	}
	size_t end = content.find("}\n,", start);
	content.erase(start, end - start +3);
	std::cout << content ;
	file.open("tasks.json", std::ios::out);
	file << content;
	file.close();
}

