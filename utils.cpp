#include "utils.h"
#include <cmath>
#include <iostream>
#include <set>

float lscrp::utils::getFloat(cell prm) {
	return amx_ctof(prm);
}

bool lscrp::utils::storeIntToEntity(const std::string& attributeName, int* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	if (entityInfo->value() != nullptr)
		delete entityInfo->value();

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}

bool lscrp::utils::storeFloatToEntity(const std::string& attributeName, float* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	if (entityInfo->value() != nullptr)
		delete entityInfo->value();

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}

bool lscrp::utils::storeStringToEntity(const std::string& attributeName, std::string* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	if (entityInfo->value() != nullptr)
		delete entityInfo->value();

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}

bool lscrp::utils::storeBoolToEntity(const std::string& attributeName, bool* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	if (entityInfo->value() != nullptr)
		delete entityInfo->value();

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}

bool lscrp::utils::storeIntArrayToEntity(const std::string& attributeName, lscrp::Array* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}

bool lscrp::utils::storeFloatArrayToEntity(const std::string& attributeName, lscrp::Array* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}

/*bool lscrp::utils::storeFloatArrayToEntity(const std::string& attributeName, lscrp::Array<float>* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}

bool lscrp::utils::storeStringArrayToEntity(const std::string& attributeName, lscrp::Array<std::string>* value, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return false;

	entityInfo->setValue(static_cast<void*>(value));
	return true;
}*/






int* lscrp::utils::varToInt(const std::string& attributeName, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return nullptr;

	return static_cast<int*>(entityInfo->value());
}

float* lscrp::utils::varToFloat(const std::string& attributeName, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return nullptr;

	return static_cast<float*>(entityInfo->value());
}

std::string* lscrp::utils::varToString(const std::string& attributeName, Entity* entity) {
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return nullptr;

	return static_cast<std::string*>(entityInfo->value());
}

bool* lscrp::utils::varToBool(const std::string& attributeName, Entity* entity)
{
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return nullptr;

	return static_cast<bool*>(entityInfo->value());
}

lscrp::Array* lscrp::utils::varToIntArray(const std::string& attributeName, Entity* entity)
{
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return nullptr;

	return static_cast<lscrp::Array*>(entityInfo->value());
}

/*lscrp::Array<float>* lscrp::utils::varToFloatArray(const std::string& attributeName, Entity* entity)
{
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return nullptr;

	return static_cast<lscrp::Array<float>*>(entityInfo->value());
}

lscrp::Array<std::string>* lscrp::utils::varToStringArray(const std::string& attributeName, Entity* entity)
{
	auto entityInfo = entity->findEntityInfo(attributeName);
	if (!entityInfo)
		return nullptr;

	return static_cast<lscrp::Array<std::string>*>(entityInfo->value());
}*/

lscrp::Array* lscrp::utils::pwnArrayToIntArray(AMX* amx, cell* params) {
	cell* addr[2] = { NULL, NULL };
	auto result = new lscrp::Array(EntityDataType::Int);

	amx_GetAddr(amx, params[3], &addr[0]);
	amx_GetAddr(amx, params[4], &addr[1]);

	for (int i = 0; i < *addr[1]; i++)
		result->add(new ArrayItem(new int(addr[0][i])));

	return result;
}

lscrp::Array* lscrp::utils::pwnArrayToFloatArray(AMX* amx, cell* params) {
	cell* addr[2] = { NULL, NULL };
	auto result = new lscrp::Array(EntityDataType::Float);

	amx_GetAddr(amx, params[3], &addr[0]);
	amx_GetAddr(amx, params[4], &addr[1]);

	for (int i = 0; i < *addr[1]; i++)
		result->add(new ArrayItem(new float(addr[0][i])));

	return result;
}

bool lscrp::utils::entityExistsInList(lscrp::Array* arr, int entityPtr) {
	auto vec = arr->list();

	for (auto& element : *vec) {
		if (*(static_cast<int*>(element->value())) == entityPtr)
			return true;
	}

	return false;
}

lscrp::Array* lscrp::utils::checkEntityPosition(lscrp::Lists* lists, Structure* structure, const std::string& attributeName, float x, float y, float z, float range) {
	cell posX, posY, posZ;
	lscrp::Array* result = new lscrp::Array(EntityDataType::Int);

	std::set<std::pair<float, int>> list;
	for (auto entity : *lists->entityList()) {
		if (entity.first <= 0)
			continue;

		if (entity.second == nullptr)
			continue;

		if (structure != entity.second->structure())
			continue;

		auto entityInfo = entity.second->findEntityInfo(attributeName);
		if (entityInfo == nullptr)
			continue;

		if (entityInfo->entityDataType() != EntityDataType::FloatArray)
			continue;

		auto arr = static_cast<lscrp::Array*>(entityInfo->value());

		if (arr->count() < 3)
			continue;

		posX = *(static_cast<float*>(arr->get(0)->value()));
		posY = *(static_cast<float*>(arr->get(1)->value()));
		posZ = *(static_cast<float*>(arr->get(2)->value()));

		float distance = sqrt(pow(amx_ctof(posX) - x, 2) + pow(amx_ctof(posY) - y, 2) + pow(amx_ctof(posZ) - z, 2));
		if (distance > range)
			continue;

		list.insert(std::pair<float, int>(distance, entity.first));
	}

	for (auto& item : list) {
		result->add(new ArrayItem(new int(item.second)));
	}

	lists->addArray(result);
	return result;
}

/*lscrp::Array<float>* lscrp::utils::pwnArrayToFloatArray(AMX* amx, cell* params) {
	cell* addr[2] = { NULL, NULL };
	auto result = new lscrp::Array<float>();

	amx_GetAddr(amx, params[3], &addr[0]);
	amx_GetAddr(amx, params[4], &addr[1]);

	for (size_t i = 0; i < *addr[1]; i++)
		result->add(getFloat(addr[0][i]));

	return result;
}

lscrp::Array<std::string>* lscrp::utils::pwnArrayToStringArray(AMX* amx, cell* params) {
	cell* addr[2] = { NULL, NULL };
	auto result = new lscrp::Array <std::string> ();

	amx_GetAddr(amx, params[3], &addr[0]);
	amx_GetAddr(amx, params[4], &addr[1]);

	for (size_t i = 0; i < *addr[1]; i++)
		result->add(Amxstring(amx, addr[0][i]).toStdString());

	return result;
}*/

