#include "Entity.hpp"
#include <iostream>

Entity::Entity(Structure* structure) {
	auto map = structure->attributeList();
	m_className = structure->className()->string();
	m_structure = structure;

	for (auto it = map->begin(); it != map->end(); it++) {
		switch (it->second) {
			case EntityDataType::Int: {
				m_attributes.insert(std::pair<std::string, EntityInfo*>(it->first, new EntityInfo(it->second, new int(0))));
				break;
			}
			case EntityDataType::Float: {
				m_attributes.insert(std::pair<std::string, EntityInfo*>(it->first, new EntityInfo(it->second, new float(0.0f))));
				break;
			}
			case EntityDataType::String: {
				m_attributes.insert(std::pair<std::string, EntityInfo*>(it->first, new EntityInfo(it->second, new std::string(" "))));
				break;
			}
			case EntityDataType::Bool: {
				m_attributes.insert(std::pair<std::string, EntityInfo*>(it->first, new EntityInfo(it->second, new bool(false))));
				break;
			}
			default: 
				m_attributes.insert(std::pair<std::string, EntityInfo*>(it->first, new EntityInfo(it->second, nullptr)));
				break;
		}	
	}
}

Entity::~Entity() {
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++) {
		auto& entityInfo = it->second;

		switch (entityInfo->entityDataType()) {
			case EntityDataType::Int: {
				int* value = static_cast<int*>(entityInfo->value());
				delete value;
				break;
			}

			case EntityDataType::Float: {
				float* value = static_cast<float*>(entityInfo->value());
				delete value;
				break;
			}

			case EntityDataType::String: {
				std::string* value = static_cast<std::string*>(entityInfo->value());
				delete value;
				break;
			}

			case EntityDataType::Bool: {
				bool* value = static_cast<bool*>(entityInfo->value());
				delete value;
				break;
			}
		}
	}
}

bool Entity::setValue(const std::string& attributeName, void* value) {
	auto& it = m_attributes.find(attributeName);
	if (it != m_attributes.end()) {
		it->second->setValue(value);
		return true;
	}

	return false;
}

void* Entity::value(const std::string& attributeName) {
	auto& it = m_attributes.find(attributeName);
	if (it != m_attributes.end()) {
		return it->second->value();
	}

	return nullptr;
}


EntityInfo* Entity::findEntityInfo(const std::string& attributeName) const {
	auto& it = m_attributes.find(attributeName);
	if (it == m_attributes.end())
		return nullptr;

	return it->second;
}

Entity * Entity::clone() {
	Entity* entity = new Entity(m_structure);

	auto map = m_structure->attributeList();

	for (auto it = map->begin(); it != map->end(); it++) {
		switch (it->second) {
			case EntityDataType::Int: {
				auto val = static_cast<int*>(value(it->first));
				if (val != nullptr)
					entity->setValue(it->first, new int(*val));
				break;
			}
			case EntityDataType::Float: {
				auto val = static_cast<float*>(value(it->first));
				if (val != nullptr)
					entity->setValue(it->first, new float(*val));
				break;
			}
			case EntityDataType::String: {
				auto val = static_cast<std::string*>(value(it->first));
				if (val != nullptr)
					entity->setValue(it->first, new std::string(*val));
				break;
			}
			case EntityDataType::Bool: {
				auto val = static_cast<bool*>(value(it->first));
				if (val != nullptr)
					entity->setValue(it->first, new bool(*val));
				break;
			}
			default:
			
				break;
		}
	}

	return entity;
}

Structure* Entity::structure() const {
	return m_structure;
}
