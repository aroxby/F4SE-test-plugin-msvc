#define DLLFUNC extern "C" __declspec(dllexport)

#include "f4se/PluginAPI.h"
#include "f4se/PapyrusNativeFunctions.h"

FILE *LOG = NULL;

void dragon(StaticFunctionTag *tag)
{
	fprintf(LOG, "Called (%p)!\n", tag);
	Console_Print("Called!!");
}

bool registerFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0<StaticFunctionTag, void>("Terabyte", "Game", dragon, vm));

	return true;
}

DLLFUNC bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Terabyte Test Plugin Bravo";
	info->version = 1;
	return true;
}

DLLFUNC bool F4SEPlugin_Load(const F4SEInterface * f4se)
{
	fopen_s(&LOG, "C:\\Users\\Andy\\Source Code\\Visual Studio Projects\\Visual Studio 2017\\F4SE-test-plugin-msvc\\pap.log", "w");
	setvbuf(LOG, NULL, _IONBF, 0);

	F4SEPapyrusInterface * g_papyrus;
	g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
	if (g_papyrus) {
		g_papyrus->Register(registerFuncs);
		fprintf(LOG, "Installed!\n");
	}
	else {
		fprintf(LOG, "FAIL!\n");
	}

	return true;
}