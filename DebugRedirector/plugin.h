
#ifndef PLUGIN_H
#define PLUGIN_H

#include "globals.h"
#include <qcompilerdetection.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Required functions */
Q_DECL_EXPORT const char* ts3plugin_name();
Q_DECL_EXPORT const char* ts3plugin_version();
Q_DECL_EXPORT int ts3plugin_apiVersion();
Q_DECL_EXPORT const char* ts3plugin_author();
Q_DECL_EXPORT const char* ts3plugin_description();
Q_DECL_EXPORT void ts3plugin_setFunctionPointers(const struct TS3Functions funcs);
Q_DECL_EXPORT int ts3plugin_init();
Q_DECL_EXPORT void ts3plugin_shutdown();

/* Optional functions */
Q_DECL_EXPORT void ts3plugin_registerPluginID(const char* id);
Q_DECL_EXPORT void ts3plugin_freeMemory(void* data);
Q_DECL_EXPORT int ts3plugin_requestAutoload();

#ifdef __cplusplus
}
#endif

#endif
