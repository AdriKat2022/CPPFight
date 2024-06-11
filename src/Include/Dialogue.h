#pragma once

#include <string>
#include <vector>

class Dialogue {

public:
	const std::string& GetNext();

	std::vector<std::string>& GetLinesReference();


private:
	size_t m_current = 0;
	std::vector<std::string> m_lines;

};