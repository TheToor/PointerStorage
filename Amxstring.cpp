#include "Amxstring.hpp"

Amxstring::Amxstring(AMX* amx, cell prm) {
	m_size = 0;
	cell* addr = NULL;
	amx_GetAddr(amx, prm, &addr);
	amx_StrLen(addr, &m_size);
	m_size++;
	m_string = new char[m_size];
	amx_GetString(m_string, addr, 0, m_size);

	m_stdString = m_string;
}

Amxstring::~Amxstring() {
	if (m_string)
		delete[] m_string;
}

const char Amxstring::operator[](int index) const {
	if (index < m_size)
		return m_string[index];

	return 0;
}

const char* Amxstring::string() const {
	return m_string;
}

const int Amxstring::size() const {
	return m_size;
}

std::string Amxstring::substr(size_t start, size_t end) {
	std::string result;

	for (size_t i = start; i < end; i++)
		result += m_string[i];

	return result;
}

std::string Amxstring::toStdString() const {
	return std::string(m_string);
}


/*std::string Amxstring::toStdString() {
	return m_stdString;
}*/
