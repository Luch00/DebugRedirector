#pragma once
#include "globals.h"
#include <QString>
#include <qlogging.h>

namespace messageHandler
{
	inline void handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
	{
		QByteArray arr = msg.toLatin1();
		const char* c_str = arr.data();
		ts3Functions.printMessageToCurrentTab(c_str);
	}

}
