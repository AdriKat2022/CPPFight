#include "Dialogue.h"



const std::string& Dialogue::GetNext()
{
	const auto& line = m_lines[m_current];
	m_current = (m_current + 1) % m_lines.size();

	return line;
}

std::vector<std::string>& Dialogue::GetLinesReference()
{
	return m_lines;
}

size_t Dialogue::GetSize() const
{
	return m_lines.size();
}

void Dialogue::Reset()
{
	m_current = 0;
}