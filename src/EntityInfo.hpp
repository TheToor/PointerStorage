#ifndef ENTITYINFO_HPP
#define ENTITYINFO_HPP

#include <string>

#include "Enums.h"

class EntityInfo
{
private:
	std::string m_attributeName;
	EntityDataType m_dataType;
	void* m_value;

	EntityInfo();
public:
	EntityInfo(EntityDataType, void*);

	//std::string attributeName() const;
	EntityDataType entityDataType() const;
	void* value() const;
	void setValue(void*);
};

#endif // ENTITYINFO_HPP
