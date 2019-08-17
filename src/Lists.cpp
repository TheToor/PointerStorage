#include "Lists.hpp"

#include <algorithm>

std::vector<Structure*>* lscrp::Lists::structureList() {
	return &m_structureList;
}

std::map<int, Entity*>* lscrp::Lists::entityList() {
	return &m_entities;
}

std::vector<lscrp::Array*>* lscrp::Lists::arrayList() {
	return &m_arrays;
}

void lscrp::Lists::addStructure(Structure* structure) {
	m_structureList.push_back(structure);
}

void lscrp::Lists::addEntity(Entity* entity) {
	int intPtr = reinterpret_cast<int>(entity);
	m_entities.insert(std::pair<int, Entity*>(intPtr, entity));
}

void lscrp::Lists::addArray(lscrp::Array* arr) {
	m_arrays.push_back(arr);
}

void lscrp::Lists::removeEntity(Entity* entity) {
	int intPtr = reinterpret_cast<int>(entity);
	m_entities.erase(intPtr);
	delete entity;
}

void lscrp::Lists::removeArray(lscrp::Array* arr) {
	m_arrays.erase(std::remove(m_arrays.begin(), m_arrays.end(), arr), m_arrays.end());
	delete arr;
}

bool lscrp::Lists::entityExists(int addr, Amxstring* string) {
	try {
		auto result = m_entities.at(addr);
		if (result != nullptr) {
			if (result->structure()->className()->string() == string->string()) {
				return true;
			}
		}
	}
	catch (const std::exception& e) {
		return false;
	}
}

bool lscrp::Lists::entityExists(int addr) {
	try {
		auto result = m_entities.at(addr);
		if (result != nullptr) {
			return true;
		}
	}
	catch (const std::exception& e) {
		return false;
	}
}

lscrp::Array* lscrp::Lists::getEntities(int classPtr) {
	auto result = new lscrp::Array(EntityDataType::Int);

	for (auto& element : m_entities) {
		if (classPtr == reinterpret_cast<int>(element.second->structure())) {
			result->add(new ArrayItem(new int(element.first)));
		}
	}

	return result;
}

lscrp::Lists::~Lists() {
	deleteStructures();
	deleteEntities();
	deleteArrays();
}

void lscrp::Lists::deleteStructures() {
	for (auto& element : m_structureList)
		delete element;
}

void lscrp::Lists::deleteEntities() {
	m_entities.clear();
}

void lscrp::Lists::deleteArrays() {
	for (auto& element : m_arrays) {
		element->clear();
		delete element;
	}
}
