#ifndef AMXSTRING_HPP
#define AMXSTRING_HPP

#include "..\SDK\amx\amx.h"
#include <string>

class Amxstring {
private:
	char* m_string;
	int m_size;
	std::string m_stdString;

	//default constructor
	Amxstring();
public:
	Amxstring(AMX * amx, cell prm);	
	~Amxstring();

	Amxstring& operator=(const Amxstring&) = delete;
	//Amxstring(const Amxstring&) = delete;

	const char operator[](int index) const;

	const char* string() const;
	const int size() const;
	std::string substr(size_t start, size_t end);
	std::string toStdString() const;
};

#endif