#include "ArrayItem.hpp"

ArrayItem::ArrayItem(void* value) {
	m_value = value;
}

void * ArrayItem::value() const {
	return m_value;
}

void ArrayItem::setValue(void* value) {
	m_value = value;
}
