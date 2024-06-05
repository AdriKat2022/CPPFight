#pragma once

#include <string>
#include <vector>

class Dialogue {

public:
	Dialogue();

	const std::string_view& GetNext();


private:
	size_t m_current = 0;
	std::vector<std::string_view> m_lines;

};