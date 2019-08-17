
#ifndef UTILS_H
#define UTILS_H

#include <string>

#include "amx/amx.h"
#include "Array.hpp"
#include "Entity.hpp"
#include "Structure.hpp"
#include "Lists.hpp"

namespace lscrp
{
	namespace utils
	{
		float getFloat(cell prm);

		bool storeIntToEntity(const std::string&, int*, Entity*);
		bool storeFloatToEntity(const std::string&, float*, Entity*);
		bool storeStringToEntity(const std::string&, std::string*, Entity*);
		bool storeBoolToEntity(const std::string&, bool*, Entity*);
		bool storeIntArrayToEntity(const std::string&, Array*, Entity*);
		bool storeFloatArrayToEntity(const std::string&, lscrp::Array*, Entity*);
		//bool storeFloatArrayToEntity(const std::string&, Array<float>*, Entity*);
		//bool storeStringArrayToEntity(const std::string&, Array<std::string>*, Entity*);

		int* varToInt(const std::string&, Entity*);
		float* varToFloat(const std::string&, Entity*);
		std::string* varToString(const std::string&, Entity*);
		bool* varToBool(const std::string&, Entity*);
		Array* varToIntArray(const std::string&, Entity*);
		//Array<float>* varToFloatArray(const std::string&, Entity*);
		//Array<std::string>* varToStringArray(const std::string&, Entity*);

		Array* pwnArrayToIntArray(AMX*, cell*);
		lscrp::Array * pwnArrayToFloatArray(AMX*, cell*);
		//Array<float>* pwnArrayToFloatArray(AMX*, cell*);
		//Array<std::string>* pwnArrayToStringArray(AMX*, cell*);

		bool entityExistsInList(lscrp::Array*, int);
		lscrp::Array* checkEntityPosition(lscrp::Lists*, Structure*, const std::string&, float, float, float, float);
	}
}

#endif
