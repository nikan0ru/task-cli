#include "task-cli.h"

void AddTask(std::string &fileName,std::string *command, std::stringstream& ss)
{
	std::fstream file;
	std::string Task;
	int lastId;
	int startPosition;

	std::string content = ss.str();
	lastId = getLastId(ss);

	startPosition = content.find_last_of("]");
	Task = writeTask(++lastId, command[1]);
	content.insert(startPosition, Task);
	file.open(fileName.c_str(), std::ios::out);
	file << content;
	std::cout << "Task Added Successfully (ID : "<< lastId << ")\n" ;
	file.close();
}


void deleteTask(std::string id, std::stringstream & ss)
{
	std::fstream file;
	std::string line;
	std::string Taskid = "\t{\n\t\t\"taskId\":" + id +",";
	
	if(id.empty())
	{
		std::cout << "Error No Id provided\n";
		return;
	}

	std::string content = ss.str();
	size_t start = content.find(Taskid);
	if(start == std::string::npos)
	{
		std::cout << "NO task with ID : " + id;
		return;
	}
	size_t end = content.find("}\n", start);
	if(end == std::string::npos)
	{
		std::cout << "Error: Missing } symbol in file!";
		return;
	}
	content.erase(start, end - start +4);
	file.open("tasks.json", std::ios::out);
	if(!file.is_open())
	{
		std::cout << "Error: Couldn't open tasks.json!";
		return;
	}
	file << content;
	file.close();
	std::cout << "Task " + id + " Deleted Successfully\n";

}

