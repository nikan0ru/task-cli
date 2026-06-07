#ifndef TASK_CLI_H
#define TASK_CLI_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>


std::string writeTask(int id, std::string desc, std::string status = "Todo");
int getLastId(std::stringstream& ss);
void AddTask(std::string& fileName,std::string *command, std::stringstream& ss);
void deleteTask(std::string id, std::stringstream& ss);

#endif
