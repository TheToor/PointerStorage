#include "Array.hpp"

lscrp::Array::Array(EntityDataType dataType) {
	m_entityDataType = dataType;
}

lscrp::Array::~Array() {
	for (auto& element : m_list) {
		switch (m_entityDataType) {
		case EntityDataType::Int: {
			int* value = static_cast<int*>(element->value());
			delete value;
			break;
		}
		case EntityDataType::Float: {
			float* value = static_cast<float*>(element->value());
			delete value;
			break;
		}
		case EntityDataType::String: {
			std::string* value = static_cast<std::string*>(element->value());
			delete value;
			break;
		}
		}

		delete element;
	}
}

EntityDataType lscrp::Array::entityDataType() {
	return m_entityDataType;
}
/*
lscrp::Array& lscrp::Array::operator+=(lscrp::Array& arr) {
	if (arr.entityDataType() == m_entityDataType) {
		for (int i = 0; i < arr.count(); i++) {
			ArrayItem* item = arr.get(i);
			if (item != nullptr) {
				m_list.push_back(item);
			}
		}
	}
	return *this;
}*/

lscrp::Array* lscrp::Array::combine(lscrp::Array* arr) {
	if (arr->entityDataType() == m_entityDataType) {
		for (int i = 0; i < arr->count(); i++) {
			auto val = static_cast<int*>(arr->get(i)->value());
			ArrayItem* item = new ArrayItem(new int(*val));
			if (item != nullptr) {
				m_list.push_back(item);
			}
		}
	}
	return this;
}

int lscrp::Array::count() const {
	return m_list.size();
}

void lscrp::Array::add(ArrayItem* value) {
	m_list.push_back(value);
}

int lscrp::Array::index(ArrayItem* value) {
	auto it = std::find(m_list.begin(), m_list.end(), value);
	if (it == m_list.end())
		return -1;

	return distance(m_list.begin(), it);
}

bool lscrp::Array::remove(int index) {
	if (index < count()) {
		m_list.erase(m_list.begin() + index);
		return true;
	}

	return false;
}

bool lscrp::Array::set(ArrayItem value, int index) {
	if (index >= count())
		return false;

	switch (m_entityDataType) {
	case EntityDataType::Int: {
		int* val = static_cast<int*>(m_list.at(index)->value());
		delete val;
		val = nullptr;
		break;
	}
	case EntityDataType::Float: {
		float* val = static_cast<float*>(m_list.at(index)->value());
		delete val;
		val = nullptr;
		break;
	}
	case EntityDataType::String: {
		std::string* val = static_cast<std::string*>(m_list.at(index)->value());
		delete val;
		val = nullptr;
		break;
	}
	default:
		return false;
	}

	m_list.at(index)->setValue(value.value());
	return true;
}

ArrayItem* lscrp::Array::get(int index) {
	if (index >= count())
		return nullptr;

	return m_list.at(index);
}

void lscrp::Array::clear() {
	for (auto& element : m_list)
		delete element;

	m_list.clear();
}

auto lscrp::Array::data() {
	return m_list.data();
}

std::vector<ArrayItem*>* lscrp::Array::list() {
	return &m_list;
}

bool lscrp::Array::itemExists(int pwnPtr) {
	for (auto& item : m_list) {
		if (*(reinterpret_cast<int*>(item->value())) == pwnPtr)
			return true;
	}

	return false;
}
