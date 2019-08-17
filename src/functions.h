#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <exception>
#include <set>

#include "lscrp.h"

typedef void(*logprintf_t)(char* format, ...);


logprintf_t logprintf;
extern void *pAMXFunctions;

namespace lscrp {
	Lists* lists;
}

Structure* intPtrToStructure(int addr) {
	return reinterpret_cast<Structure*>(addr);
}


void writeToLog(const char* input) {
	std::ofstream file;
	file.open("lscrplog.txt", std::ios::app);
	file << input << "\n";
	file.close();
}


cell AMX_NATIVE_CALL createClass(AMX* amx, cell* params) {
	try {
		Amxstring* string = new Amxstring(amx, params[1]);
		Structure* structure = new Structure(string);
		lscrp::lists->addStructure(structure);

		int addr = reinterpret_cast<int>(structure);
		return addr;
	}
	catch (std::exception &e) {
		writeToLog(e.what());
	}
}

cell AMX_NATIVE_CALL addAttribute(AMX* amx, cell* params) {
	int addr = params[1];
	int dataType = params[2];
	Amxstring string(amx, params[3]);

	Structure* structure = reinterpret_cast<Structure*>(addr);
	if (structure == nullptr)
		return 0;

	structure->addAttribute(string.string(), static_cast<EntityDataType>(dataType));
	return 1;
}

cell AMX_NATIVE_CALL attributeExists(AMX* amx, cell* params) {
	int addr = params[1];
	Amxstring attributeName(amx, params[2]);
	std::string string = attributeName.string();

	Structure* structure = reinterpret_cast<Structure*>(addr);
	if (structure == nullptr)
		return -1;

	if (structure->attributeExists(string)) {
		logprintf("Attribut existstiert");
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL createEntity(AMX* amx, cell* params) {
	int addr = params[1];
	auto structure = intPtrToStructure(addr);
	if (structure == nullptr)
		return 0;

	Entity* entity = new Entity(structure);
	lscrp::lists->addEntity(entity);
	return reinterpret_cast<int>(entity);
}


cell AMX_NATIVE_CALL setEntityValue(AMX* amx, cell* params) {
	try {
		cell entityPtr = params[1];
		Amxstring attributeName(amx, params[2]);

		Entity* entity = reinterpret_cast<Entity*>(entityPtr);
		if (entity != nullptr) {
			auto entityInfo = entity->findEntityInfo(attributeName.string());
			if (entityInfo == nullptr)
				return -1;

			cell* addr = NULL;
			amx_GetAddr(amx, params[3], &addr);


			switch (entityInfo->entityDataType()) {
			case EntityDataType::Int: {
				lscrp::utils::storeIntToEntity(attributeName.string(), new int(*addr), entity);
				break;
			}

			case EntityDataType::Float: {
				lscrp::utils::storeFloatToEntity(attributeName.string(), new float(lscrp::utils::getFloat(*addr)), entity);
				break;
			}

			case EntityDataType::String: {
				lscrp::utils::storeStringToEntity(attributeName.string(), new std::string(Amxstring(amx, params[3]).string()), entity);
				break;
			}

			case EntityDataType::Bool: {
				lscrp::utils::storeBoolToEntity(attributeName.string(), new bool(static_cast<bool>(*addr)), entity);
				break;
			}

			case EntityDataType::Array: {
				lscrp::Array* arr = lscrp::utils::pwnArrayToIntArray(amx, params);
				lscrp::utils::storeIntArrayToEntity(attributeName.string(), arr, entity);
				lscrp::lists->addArray(arr);
				break;
			}

			case EntityDataType::FloatArray: {
				lscrp::Array* arr = lscrp::utils::pwnArrayToFloatArray(amx, params);
				lscrp::utils::storeFloatArrayToEntity(attributeName.toStdString(), arr, entity);
				lscrp::lists->addArray(arr);
				break;
			}

			/*case EntityDataType::FloatArray:
				lscrp::utils::storeFloatArrayToEntity(attributeName.toStdString(), lscrp::utils::pwnArrayToFloatArray(amx, params), entity);
				break;

			case EntityDataType::StringArray:
				lscrp::utils::storeStringArrayToEntity(attributeName.toStdString(), lscrp::utils::pwnArrayToStringArray(amx, params), entity);
				break;*/

			default:
				return 0;
			}
		}


		return 1;

	}
	catch (std::exception &e) {
		writeToLog(e.what());
	}
}

cell AMX_NATIVE_CALL getEntityValue(AMX* amx, cell* params) {
	int entityPtr = params[1];
	Amxstring attributeName(amx, params[2]);

	Entity* entity = reinterpret_cast<Entity*>(entityPtr);
	if (entity != nullptr) {
		auto entityInfo = entity->findEntityInfo(attributeName.string());
		if (entityInfo == nullptr)
			return -1;

		cell* addr = NULL;
		amx_GetAddr(amx, params[3], &addr);

		switch (entityInfo->entityDataType()) {
		case EntityDataType::Int: {
			int* value = static_cast<int*>(entityInfo->value());
			if (value == nullptr)
				return -2;
			*addr = *value;
			break;
		}

		case EntityDataType::Float: {
			float* value = static_cast<float*>(entityInfo->value());
			if (value == nullptr)
				return -2;
			*addr = amx_ftoc(*value);
			break;
		}

		case EntityDataType::String: {
			std::string* value = static_cast<std::string*>(entityInfo->value());
			if (value == nullptr)
				return -2;
			amx_SetString(addr, value->c_str(), 0, 0, value->length() + 1);
			break;
		}

		case EntityDataType::Bool: {
			bool* value = static_cast<bool*>(entityInfo->value());
			if (value == nullptr)
				return -2;
			*addr = *value;
			break;
		}

		case EntityDataType::Array: {
			auto value = static_cast<lscrp::Array*>(entityInfo->value());

			if (value == nullptr)
				return -2;

			cell* arrSize[2] = { NULL, NULL };

			amx_GetAddr(amx, params[4], &arrSize[0]);
			int maxSize = *arrSize[0];

			amx_GetAddr(amx, params[5], &arrSize[1]);
			int size = value->count();
			*arrSize[1] = size > maxSize ? maxSize : static_cast<cell>(size);

			for (int i = 0; i < value->count(); i++) {
				if (i >= maxSize)
					break;
				addr[i] = *(static_cast<int*>(value->get(i)->value()));
			}

			break;
		}

		case EntityDataType::FloatArray: {
			auto value = static_cast<lscrp::Array*>(entityInfo->value());
			if (value == nullptr)
				return -2;

			cell* arrSize[2] = { NULL, NULL };

			amx_GetAddr(amx, params[4], &arrSize[0]);
			int maxSize = *arrSize[0];

			amx_GetAddr(amx, params[5], &arrSize[1]);
			int size = value->count();
			*arrSize[1] = size > maxSize ? maxSize : static_cast<cell>(size);

			for (size_t i = 0; i < value->count(); i++) {
				if (i >= maxSize)
					break;
				addr[i] = *(static_cast<float*>(value->get(i)->value()));
			}

			break;
		}

		/*case EntityDataType::FloatArray: {
			//auto value = static_cast<lscrp::Array<float*>*>(entityInfo->value());
			cell* arrSize = NULL;
			amx_GetAddr(amx, params[4], &arrSize);
			int size = *arrSize;

			float arr[10] = { 10.0f, 9.0f, 8.0, 7.4, 6.5, 5.6, 4.1, 3.0, 2.1, 1.9 };
			float* ptr = arr;

			for (size_t i = 0; i < size; i++) {
				 addr[i] = amx_ftoc(ptr[i]);
			}
			break;
		}

		case EntityDataType::StringArray: {
			auto value = static_cast<lscrp::Array<std::string*>*>(entityInfo->value());
			cell* arrSize = NULL;
			amx_GetAddr(amx, params[4], &arrSize);
			int size = *arrSize;
			const char* text;

			for (size_t i = 0; i < size; i++) {
				//amx_SetString(&addr[i], value->get(i)->c_str(), 0, 0, value->get(i)->length() + 1);
				amx_SetString(&addr[i], "asd", 0, 0, 4);
				text = value->get(i)->c_str();
				logprintf("String: %s", text);
			}
			break;
		}*/

		default:
			return 0;
		}
	}

	return 1;
}

cell AMX_NATIVE_CALL cloneEntity(AMX* amx, cell* params) {
	int addr = params[1];
	Entity* entity = reinterpret_cast<Entity*>(addr);
	if (entity != nullptr) {
		Entity* clone = entity->clone();
		lscrp::lists->addEntity(clone);
		return reinterpret_cast<int>(clone);
	}

	return 0;
}

cell AMX_NATIVE_CALL deleteEntity(AMX* amx, cell* params) {
	int addr = params[1];
	Entity* entity = reinterpret_cast<Entity*>(addr);
	if (entity != nullptr) {
		lscrp::lists->removeEntity(entity);
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL findEntities(AMX* amx, cell* params) {
	int prmCount = params[0] / sizeof(cell);
	if (!(prmCount & 1))
		return 0;

	int addr = params[1];
	Structure* structure = reinterpret_cast<Structure*>(addr);
	if (structure == nullptr)
		return -1;

	cell* amx_addr = NULL;

	std::vector<std::string> attributes;
	std::vector<cell*> values;

	for (int i = 0; i < ((prmCount - 1) / 2); i++) {
		cell* amx_addr = NULL;
		attributes.push_back(Amxstring(amx, params[(i * 2) + 2]).string());
		amx_GetAddr(amx, params[(i * 2) + 3], &amx_addr);
		values.push_back(amx_addr);
	}

	lscrp::Array* result = new lscrp::Array(EntityDataType::Int);

	int resultPtr = 0;
	const int count = (prmCount - 1) / 2;
	int counter = 0;

	try {
		for (auto element : *lscrp::lists->entityList()) {
			counter = 0;
			resultPtr = reinterpret_cast<int>(element.second);
			for (int i = 0; i < ((prmCount - 1) / 2); i++) {
				EntityDataType dataType = structure->attributeList()->at(attributes.at(i));

				if (resultPtr == 0 || element.second == nullptr)
					continue;

				if (addr != reinterpret_cast<int>(element.second->structure()))
					continue;

				switch (dataType) {
				case EntityDataType::Int: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						int* value = static_cast<int*>(entityInfo->value());
						int val = *values.at(i);
						if (*value == val) {
							counter++;
						}
					}
					break;
				}
				case EntityDataType::Float: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						float* value = static_cast<float*>(entityInfo->value());
						float val = amx_ftoc(*values.at(i));
						if (*value == val) {
							counter++;
						}
					}
					break;
				}
				case EntityDataType::String: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						std::string* value = static_cast<std::string*>(entityInfo->value());
						if (*value == Amxstring(amx, params[(i * 2) + 3]).string()) {
							counter++;
						}
					}
					break;
				}
				case EntityDataType::Bool: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						bool* value = static_cast<bool*>(entityInfo->value());
						bool val = *values.at(i);
						if (*value == val) {
							counter++;
						}
					}
					break;
				}
				default:
					continue;
				}

				if (count == counter)
					result->add(new ArrayItem(new int(resultPtr)));
			}
		}
	}
	catch (std::exception& e) {
		logprintf("[error] findEtities: %s", e.what());
	}

	lscrp::lists->addArray(result);
	return reinterpret_cast<int>(result);
}

cell AMX_NATIVE_CALL findEntitiesOr(AMX* amx, cell* params) {
	int prmCount = params[0] / sizeof(cell);
	if (!(prmCount & 1))
		return 0;

	int addr = params[1];
	Structure* structure = reinterpret_cast<Structure*>(addr);
	if (structure == nullptr)
		return -1;

	cell* amx_addr = NULL;

	std::vector<std::string> attributes;
	std::vector<cell*> values;

	for (int i = 0; i < ((prmCount - 1) / 2); i++) {
		cell* amx_addr = NULL;
		attributes.push_back(Amxstring(amx, params[(i * 2) + 2]).string());
		amx_GetAddr(amx, params[(i * 2) + 3], &amx_addr);
		values.push_back(amx_addr);
	}

	lscrp::Array* result = new lscrp::Array(EntityDataType::Int);

	int resultPtr = 0;
	//const int count = (prmCount - 1) / 2;
	int counter = 0;

	try {
		for (auto element : *lscrp::lists->entityList()) {
			resultPtr = reinterpret_cast<int>(element.second);
			for (int i = 0; i < ((prmCount - 1) / 2); i++) {
				counter = 0;

				EntityDataType dataType = structure->attributeList()->at(attributes.at(i));

				if (resultPtr == 0 || element.second == nullptr)
					continue;

				if (addr != reinterpret_cast<int>(element.second->structure()))
					continue;

				switch (dataType) {
				case EntityDataType::Int: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						int* value = static_cast<int*>(entityInfo->value());
						int val = *values.at(i);
						if (*value == val) {
							counter++;
						}
					}
					break;
				}
				case EntityDataType::Float: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						float* value = static_cast<float*>(entityInfo->value());
						float val = amx_ftoc(*values.at(i));
						if (*value == val) {
							counter++;
						}
					}
					break;
				}
				case EntityDataType::String: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						std::string* value = static_cast<std::string*>(entityInfo->value());
						if (*value == Amxstring(amx, params[(i * 2) + 3]).string()) {
							counter++;
						}
					}
					break;
				}
				case EntityDataType::Bool: {
					EntityInfo* entityInfo = element.second->findEntityInfo(attributes.at(i));
					if (entityInfo != nullptr) {
						bool* value = static_cast<bool*>(entityInfo->value());
						bool val = *values.at(i);
						if (*value == val) {
							counter++;
						}
					}
					break;
				}
				default:
					continue;
				}

				if (counter > 0) {
					result->add(new ArrayItem(new int(resultPtr)));
					break;
				}
			}
		}
	}
	catch (std::exception& e) {
		logprintf("[error] findEtities: %s", e.what());
	}

	lscrp::lists->addArray(result);
	return reinterpret_cast<int>(result);
}


cell AMX_NATIVE_CALL findEntitiesPos(AMX* amx, cell* params) {
	int addr = params[1];
	Structure* structure = reinterpret_cast<Structure*>(addr);
	if (structure == nullptr)
		return -1;

	Amxstring attributeName(amx, params[2]);
	std::string string = attributeName.string();

	if (!structure->attributeExists(string))
		return -2;

	float x = lscrp::utils::getFloat(params[3]);
	float y = lscrp::utils::getFloat(params[4]);
	float z = lscrp::utils::getFloat(params[5]);
	float r = lscrp::utils::getFloat(params[6]);

	auto list = lscrp::utils::checkEntityPosition(lscrp::lists, structure, string, x, y, z, r);
	return reinterpret_cast<int>(list);
}


cell AMX_NATIVE_CALL createList(AMX* amx, cell* params) {
	EntityDataType entityType = EntityDataType::Int;

	int prmCount = params[0] / sizeof(cell);
	if (prmCount > 0)
		entityType = static_cast<EntityDataType>(params[1]);

	switch (entityType) {
		case EntityDataType::Int: {
			lscrp::Array* list = new lscrp::Array(EntityDataType::Int);
			lscrp::lists->addArray(list);
			return reinterpret_cast<int>(list);
		}
		case EntityDataType::Float: {
			lscrp::Array* list = new lscrp::Array(EntityDataType::Float);
			lscrp::lists->addArray(list);
			return reinterpret_cast<int>(list);
		}
		case EntityDataType::String: {
			lscrp::Array* list = new lscrp::Array(EntityDataType::String);
			lscrp::lists->addArray(list);
			return reinterpret_cast<int>(list);
		}
		default:
		return 0;
	}
}

cell AMX_NATIVE_CALL combineLists(AMX* amx, cell* params) {
	int prmCount = params[0] / sizeof(cell);

	lscrp::Array* list = new lscrp::Array(EntityDataType::Int);
	lscrp::lists->addArray(list);
	
	for (int i = 0; i < prmCount; i++) {
		int addr = params[1 + i];
		if (addr <= 0) {
			delete list;
			return 0;
		}

		lscrp::Array* arr = reinterpret_cast<lscrp::Array*>(addr);
		if (arr != nullptr) {
			//*list += *arr;
			list->combine(arr);
		} else {
			delete list;
			return 0;
		}
	}
	return reinterpret_cast<int>(list);
}

cell AMX_NATIVE_CALL addListItem(AMX* amx, cell* params) {
	int prmCount = (params[0] / sizeof(cell)) - 1;
	int addr = params[1];
	if (addr <= 0)
		return 0;

	lscrp::Array* arr = reinterpret_cast<lscrp::Array*>(addr);
	if (arr == nullptr)
		return 0;

	cell* amx_addr = NULL;

	switch (arr->entityDataType()) {
	case EntityDataType::Int: {
		for (int i = 0; i < prmCount; i++) {
			amx_GetAddr(amx, params[2 + i], &amx_addr);
			arr->add(new ArrayItem(new int(*amx_addr)));
		}
		return 1;
	}
	case EntityDataType::Float: {
		for (int i = 0; i < prmCount; i++) {
			amx_GetAddr(amx, params[2 + i], &amx_addr);
			arr->add(new ArrayItem(new float(lscrp::utils::getFloat(*amx_addr))));
		}
		return 1;
	}
	case EntityDataType::String: {
		for (int i = 0; i < prmCount; i++) {
			Amxstring string(amx, params[2 + i]);
			arr->add(new ArrayItem(new std::string(string.string())));
		}
		return 1;
	}
	default:
		return -1;
	}
}

cell AMX_NATIVE_CALL listCount(AMX* amx, cell* params) {
	int addr = params[1];
	if (addr <= 0)
		return 0;

	lscrp::Array* arr = reinterpret_cast<lscrp::Array*>(addr);
	if (arr == nullptr)
		return -1;

	return arr->count();
}

cell AMX_NATIVE_CALL listValueByIndex(AMX* amx, cell* params) {
	int addr = params[1];
	if (addr <= 0)
		return 0;

	int index = params[2];

	try {

		lscrp::Array* arr = reinterpret_cast<lscrp::Array*>(addr);
		if (arr == nullptr)
			return -1;

		if (index >= arr->count())
			return -2;

		cell* amx_addr = NULL;
		amx_GetAddr(amx, params[3], &amx_addr);

		switch (arr->entityDataType()) {
		case EntityDataType::Int: {
			*amx_addr = *(static_cast<int*>(arr->get(index)->value()));
			return 1;
		}
		case EntityDataType::Float: {
			*amx_addr = amx_ftoc(*(static_cast<float*>(arr->get(index)->value())));
			return 1;
		}
		case EntityDataType::String: {
			std::string* string = static_cast<std::string*>(arr->get(index)->value());
			amx_SetString(amx_addr, string->c_str(), 0, 0, string->length() + 1);
			return 1;
		}
		default:
			return 0;
		}
	}
	catch (const std::exception& e) {
		logprintf("[error] listValueByIndex: %s", e.what());
	}
}

cell AMX_NATIVE_CALL setListValueByIndex(AMX* amx, cell* params) {
	int addr = params[1];
	if (addr <= 0)
		return 0;

	int index = params[2];

	lscrp::Array* arr = reinterpret_cast<lscrp::Array*>(addr);
	if (arr == nullptr)
		return -1;

	if (index >= arr->count())
		return -2;

	cell* amx_addr = NULL;
	amx_GetAddr(amx, params[3], &amx_addr);
	bool result = false;

	switch (arr->entityDataType()) {
	case EntityDataType::Int: {
		//int value = *amx_addr;
		result = arr->set(ArrayItem(new int(*amx_addr)), index);
		return result;
	}
	case EntityDataType::Float: {
		result = arr->set(ArrayItem(new float(lscrp::utils::getFloat(*amx_addr))), index);
		return result;
	}
	case EntityDataType::String: {
		result = arr->set(ArrayItem(new std::string(Amxstring(amx, params[3]).string())), index);
		return result;
	}
	default:
		return 0;
	}
}

cell AMX_NATIVE_CALL clearList(AMX* amx, cell* params) {
	int addr = params[1];
	if (addr <= 0)
		return 0;

	lscrp::Array* arr = reinterpret_cast<lscrp::Array*>(addr);
	if (arr == nullptr)
		return 0;

	arr->clear();
	return 1;
}

cell AMX_NATIVE_CALL removeListItem(AMX* amx, cell* params) {
	int addr = params[1];
	if (addr <= 0)
		return 0;

	int index = params[2];

	lscrp::Array* arr = reinterpret_cast<lscrp::Array*>(addr);
	if (arr == nullptr)
		return -1;

	if (index >= arr->count())
		return 0;

	arr->remove(index);
	return 1;
}

cell AMX_NATIVE_CALL existsEntityByClass(AMX* amx, cell* params) {
	int classPtr = params[1];
	int entityPtr = params[2];

	auto structure = intPtrToStructure(classPtr);
	if (structure != nullptr) {
		bool result = lscrp::lists->entityExists(entityPtr, structure->className());
		return result ? 1 : 0;
	}

	return 0;
}

cell AMX_NATIVE_CALL existsEntity(AMX* amx, cell* params) {
	int entityPtr = params[1];

	bool result = lscrp::lists->entityExists(entityPtr);
	return result ? 1 : 0;
}

cell AMX_NATIVE_CALL getEntityList(AMX* amx, cell* params) {
	int classPtr = params[1];
	auto structure = intPtrToStructure(classPtr);

	if (structure == nullptr)
		return 0;

	auto list = lscrp::lists->getEntities(classPtr);
	return reinterpret_cast<int>(list);
}



#endif // FUNCTIONS_H