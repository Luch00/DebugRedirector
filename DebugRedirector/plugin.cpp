
#ifdef _WIN32
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */
#include <Windows.h>
#endif

#include <QCoreApplication>
#include <QTimer>
#include "plugin.h"
#include "messagehandler.h"
#include "StdOutRedirector.h"

#define PLUGIN_API_VERSION 22

static char* pluginID = nullptr;

StdOutRedirector *redirector;
QTimer *timer;

const char* ts3plugin_name() {
	return "DebugRedirector";
}

const char* ts3plugin_version() {
    return "1.0";
}

int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
    return "Luch";
}

const char* ts3plugin_description() {
    return "Redirect qDebug and stdout to current tab";
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
    ts3Functions = funcs;
}

static void timerTick()
{
	QString out = redirector->readOuts();
	ts3Functions.printMessageToCurrentTab(out.toLatin1().data());
}

static void hideConsole()
{
	HWND handle = 0;
	do
	{
		handle = FindWindowExA(0, handle, "ConsoleWindowClass", 0);
		char *buffer = new char[10];
		GetWindowTextA(handle, buffer, 10);
		printf(buffer);
		if (strcmp(buffer, "ts3client") == 0)
		{
			ShowWindow(handle, SW_HIDE);
			return;
		}
	} while (handle != nullptr);
}

int ts3plugin_init() {
	if (QCoreApplication::arguments().contains("-console"))
	{
		hideConsole();
		qInstallMessageHandler(messageHandler::handler);
		redirector = new StdOutRedirector();
		timer = new QTimer();
		timer->setInterval(1000);
		QObject::connect(timer, &QTimer::timeout, timerTick);
		timer->start();
	}
    return 0;
}

void ts3plugin_shutdown() {
	if (timer != NULL)
	{
		timer->stop();
		delete timer;
		delete redirector;
	}

	if(pluginID) {
		free(pluginID);
		pluginID = NULL;
	}
}

void ts3plugin_registerPluginID(const char* id) {
	const size_t sz = strlen(id) + 1;
	pluginID = (char*)malloc(sz * sizeof(char));
	strcpy_s(pluginID, sz, id);
}

void ts3plugin_freeMemory(void* data) {
	free(data);
}

int ts3plugin_requestAutoload() {
	return 0;
}
