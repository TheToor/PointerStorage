
#include "src/functions.h"

//#include <iostream>

cell AMX_NATIVE_CALL test(AMX* amx, cell* params) {
	//cell* addr = NULL;
	//amx_GetAddr(amx, params[1], &addr);
	//logprintf("Test: %d", *addr);

	/*cell* addr[2] = { NULL, NULL};

	int size = 0;
	amx_GetAddr(amx, params[1], &addr[0]);
	amx_GetAddr(amx, params[2], &addr[1]);
	size = *addr[1];

	for (size_t i = 0; i < size; i++) {
		
		logprintf("Value: %d", addr[0][i]);
	}*/


	int count = params[0] / sizeof(cell);
	logprintf("Count: %d", count);
	if (!(count & 1))
		logprintf("gerade");
	else
		logprintf("Ungerade");

	return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("* LSCRP.DE plugin was loaded.");

	lscrp::lists = new lscrp::Lists();

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("* LSCRP.DE plugin was unloaded.");
	delete lscrp::lists;
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "test", test },
	{ "createClass", createClass },
	{ "addAttribute", addAttribute },
	{ "attributeExists", attributeExists },
	{ "createEntity", createEntity },
	{ "setEntityValue", setEntityValue },
	{ "getEntityValue", getEntityValue },
	{ "cloneEntity", cloneEntity },
	{ "deleteEntity", deleteEntity },
	{ "findEntities", findEntities },
	{ "findEntitiesOr", findEntitiesOr },
	{ "findEntitiesPos", findEntitiesPos },
	{ "createList", createList },
	{ "addListItem", addListItem },
	{ "listCount", listCount },
	{ "listValueByIndex", listValueByIndex },
	{ "setListValueByIndex", setListValueByIndex },
	{ "clearList", clearList },
	{ "removeListItem", removeListItem },
	{ "combineLists", combineLists },
	{ "existsEntity", existsEntity },
	{ "existsEntityByClass", existsEntityByClass },
    { "getEntityList", getEntityList },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}