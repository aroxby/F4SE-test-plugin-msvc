#define DLLFUNC extern "C" __declspec(dllexport)

#include "f4se/PluginAPI.h"

DLLFUNC bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Terabyte Test Plugin Bravo";
	info->version = 1;
	return true;
}

DLLFUNC bool F4SEPlugin_Load(const F4SEInterface * f4se)
{
	return true;
}