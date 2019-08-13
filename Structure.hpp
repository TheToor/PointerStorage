
#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include "Amxstring.hpp"
#include "Enums.h"
#include <string>
#include <map>


class Structure {
private:
	Amxstring* m_className;
	std::map<std::string, EntityDataType> m_attributeList;

	Structure();
public:

	Structure(Amxstring*);
	~Structure();

	Amxstring* className() const;
	std::map<std::string, EntityDataType>* attributeList();

	void addAttribute(std::string, EntityDataType);
	bool attributeExists(std::string);

};


#endif // STRUCTURE_HPP

