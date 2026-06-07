#include "task-cli.h"

std::string writeTask(int id, std::string desc, std::string status)
{
	std::string Task;
	if(id != 0)
	{
		Task.append(",");
	}
	std::stringstream ss;
	ss << id;

	Task += "\n\t{\n\t\t\"taskId\":" + ss.str() + ",\n\t\t\"description\":\"" + desc + "\",\n\t\t\"status\":\"" + status + "\"\n\t}\n";
	return Task;
}

int getLastId(std::stringstream& ss)
{
	std::string lastID;
	int id;
	std::string line;
	while (std::getline(ss, line))
	{
		if(!line.compare(0, 11, "\t\t\"taskId\":"))
		{
			lastID = line.substr(11, line.length() -12);
		}
	}
	if(lastID.empty())
		lastID = "0";
	id = std::atoi(lastID.c_str());
	return id;
}
