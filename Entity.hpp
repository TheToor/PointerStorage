#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <map>

#include "EntityInfo.hpp"
#include "Structure.hpp"

class Entity {
private:
	Entity();

	std::map<std::string, EntityInfo*> m_attributes;
	std::string m_className;
	Structure* m_structure;
public:

	Entity(Structure*);
	~Entity();

	bool setValue(const std::string&, void*);
	void* value(const std::string&);
	EntityInfo* findEntityInfo(const std::string&) const;
	Entity* clone();
	Structure* structure() const;
};

#endif // ENTITY_HPP

