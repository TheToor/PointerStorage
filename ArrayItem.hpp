#ifndef ARRAYITEM_HPP
#define ARRAYITEM_HPP

class ArrayItem {
private:
	void* m_value;
public:
	ArrayItem(void*);
	void* value() const;
	void setValue(void*);
};

#endif // !ARRAYITEM_HPP

