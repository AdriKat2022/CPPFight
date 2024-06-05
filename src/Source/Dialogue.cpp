#include "Dialogue.h"


Dialogue::Dialogue()
{
	// Load the dialogue
}


const std::string_view& Dialogue::GetNext()
{
	const auto& line = m_lines[m_current];
	m_current = (m_current + 1) % m_lines.size();

	return line;
}