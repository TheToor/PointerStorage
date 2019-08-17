#include "EntityInfo.hpp"

EntityInfo::EntityInfo(EntityDataType dataType, void* value) {
	//m_attributeName = attributeName;
	m_dataType = dataType;
	m_value = value;
}

/*std::string EntityInfo::attributeName() const {
	return m_attributeName;
}*/

EntityDataType EntityInfo::entityDataType() const {
	return m_dataType;
}

void* EntityInfo::value() const {
	return m_value;
}

void EntityInfo::setValue(void* value) {
	m_value = value;
}
