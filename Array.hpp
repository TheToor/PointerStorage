#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "ArrayItem.hpp"
#include "Enums.h"

namespace lscrp
{
// int, float, string
class Array
{
private:
	std::vector<ArrayItem*> m_list;
	EntityDataType m_entityDataType;
	Array();
public:
	Array(EntityDataType);
	~Array();

	EntityDataType entityDataType();

	//Array& operator+=(Array&);

	lscrp::Array* combine(lscrp::Array*);

	int count() const;

	void add(ArrayItem*);

	/*void insertArray(T* value, int size) {
		for (size_t i = 0; i < size; i++)
			m_list.push_back(value[i]);
	}*/

	/*int index(ArrayItem*) {
		auto i = std::find(m_list.begin(), m_list.end(), value);
		if (i != m_list.end()) {
		m_list.erase(i);
		return true;
		}

		return false;
	}*/

	//bool remove(ArrayItem*);

	int lscrp::Array::index(ArrayItem*);
	bool remove(int index);

	bool set(ArrayItem, int);

	/*bool set(T value, T oldValue) {
		auto it = std::find(m_list.begin(), m_list.end(), oldValue);
		if (it == m_list.end())
			return false;

		it* = value;
		return true;
	}*/

	ArrayItem* get(int);

	void clear();

	auto data();
	std::vector<ArrayItem*>* list();
	bool itemExists(int pwnPtr);

};

}

#endif // !ARRAY_HPP