#include "Structure.hpp"

Structure::Structure(Amxstring* string) {
	m_className = string;
}

Structure::~Structure() {
	delete m_className;
}

Amxstring* Structure::className() const {
	return m_className;
}

std::map<std::string, EntityDataType>* Structure::attributeList() {
	return &m_attributeList;
}

void Structure::addAttribute(std::string attributeName, EntityDataType dataType) {
	m_attributeList.insert(std::pair<std::string, EntityDataType>(attributeName, dataType));
}

bool Structure::attributeExists(std::string string) {
	return m_attributeList.find(string) != m_attributeList.end();
}
