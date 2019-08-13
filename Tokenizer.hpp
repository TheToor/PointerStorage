#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "Amxstring.hpp"

#include <string>
#include <vector>

namespace tkz {

	enum class PropertyType {
		NONE			= 0x0,
		PROPERTY_NAME	= 0x1,
		PROPERTY_TYPE	= 0x2,
		PROPERTY_REPEAT = 0x3
	};

	enum class TokenType {
		NONE			= 0x0,
		INT				= 0x1,
		FLOAT			= 0x2,
		STRING			= 0x3,
		ARRAY_OF_INT	= 0x4,
		ARRAY_OF_FLOAT	= 0x5
	};

	class Token {
	private:
		std::string m_PropName;
		TokenType m_type;
		// default constructor
		Token();
	public:
		Token(std::string, TokenType);
		~Token();

		std::string propName();

		TokenType tokenType();
	};

	bool parse(Amxstring& string, std::vector<Token*>& result, int prmcount);
	TokenType getTokenType(const std::string& type);

}

#endif
