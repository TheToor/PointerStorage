#include "Tokenizer.hpp"

bool tkz::parse(Amxstring& string, std::vector<Token*>& result, int prmcount) {
	size_t count = 0;
	PropertyType type = PropertyType::PROPERTY_NAME;
	std::string propname;
	std::string proptype;

	result.resize(prmcount);

	for (size_t i = 0; i < string.size(); i++) {
		if (type == PropertyType::PROPERTY_NAME) {
			if (string[i] != ':') {
				count++;
				propname = string.substr(i, count);
				type = PropertyType::PROPERTY_TYPE;
			}
		}

		else if (type == PropertyType::PROPERTY_TYPE) {
			if (string[i] == '%') {
				size_t idx = i;
				idx++;
				while (idx < string.size()) {
					if (string[idx] != ' ') {
						proptype += string[idx];
						type = PropertyType::PROPERTY_REPEAT;
					}
					idx++;
				}
			}
		}

		else if (type == PropertyType::PROPERTY_REPEAT) {
			TokenType tkntype = getTokenType(proptype);
			if (tkntype == TokenType::NONE)
				// unknwon type
				return false;

			result.push_back(new Token(propname, tkntype));

			count = 0;
			propname.clear();
			proptype.clear();
			type = PropertyType::PROPERTY_NAME;
		}
	}


	return true;
}

tkz::TokenType tkz::getTokenType(const std::string& type) {
	if (type == "d")
		return tkz::TokenType::INT;
	else if (type == "f")
		return tkz::TokenType::FLOAT;
	else if (type == "s")
		return tkz::TokenType::STRING;
	else if (type == "ad")
		return tkz::TokenType::ARRAY_OF_INT;
	else if (type == "af")
		return tkz::TokenType::ARRAY_OF_FLOAT;
	else
		return tkz::TokenType::NONE;
}




tkz::Token::Token(std::string string, TokenType type) {
	m_PropName = string;
	m_type = type;
}

tkz::Token::~Token() {
	//delete m_PropName;
}

std::string tkz::Token::propName() {
	return m_PropName;
}

tkz::TokenType tkz::Token::tokenType() {
	return m_type;
}
