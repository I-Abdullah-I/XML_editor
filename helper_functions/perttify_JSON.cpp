#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

void prettify_json(std::string line);
void indentaion(int indentation_index, std::string &line);

int main()
{
	std::string file_path, line;
	file_path = "line.json";
	std::ifstream file(file_path);
	std::getline(file, line);
	// std::cout << line << std::endl;
	prettify_json(line);
	system("pause");
    return 0;
}

void prettify_json(std::string line) {
	std::string prettified_line, line0, line1;
	int indentation_index = 0;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '{' || line[i] == '[') {
			line0 = line.substr(0, i + 1);
			line = line.substr(i + 1);
			line0 = line0 + "\n";
			indentaion(indentation_index, line0);
			prettified_line = prettified_line + line0;
			indentation_index++;
			i = -1;
		}
		else if (line[i] == ',') {
			line0 = line.substr(0, i + 1);
			line = line.substr(i + 1);
			line0 = line0 + "\n";
			indentaion(indentation_index, line0);
			prettified_line = prettified_line + line0;
			i = -1;
		}
		else if (line[i] == '}' && line[i + 1] == ',') {
			// before },
			line0 = line.substr(0, i);
			line = line.substr(i);
			line1 = line.substr(0, 2);
			line = line.substr(2);
			line0 = line0 + "\n";
			line1 = line1 + "\n";
			indentaion(indentation_index, line0);
			prettified_line = prettified_line + line0;
			indentation_index--;
			indentaion(indentation_index, line1);
			prettified_line = prettified_line + line1;
			i = -1;
		}
		else if (line[i] == '}' || line[i] == ']') {
			line0 = line.substr(0, i + 1);
			if (line0.size() == 1) {
				indentation_index--;
				line = line.substr(i + 1);
				line0 = line0 + "\n";
				indentaion(indentation_index, line0);
				prettified_line = prettified_line + line0;
				i = -1;
			}
			else {
				line0 = line.substr(0, i);
				line = line.substr(i);
				line1 = line.substr(0, 1);
				line = line.substr(1);
				line0 = line0 + "\n";
				line1 = line1 + "\n";
				indentaion(indentation_index, line0);
				prettified_line = prettified_line + line0;
				indentation_index--;
				indentaion(indentation_index, line1);
				prettified_line = prettified_line + line1;
				i = -1;
			}
		}
	}
	std::cout << prettified_line << std::endl;
}

void indentaion(int indentation_index, std::string &line) {
	int i = 0;
	while (i < indentation_index) {
		line = "    " + line;
		i++;
	}
}

s