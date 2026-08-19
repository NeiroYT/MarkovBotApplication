#pragma once

#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QException>
#include <iostream>
#include <string>
#include <thread>
#include "MsgData.h"
#include "ExternalMsg.h"
#include "BotCommand.h"

class MessageManager  : public QObject
{
	Q_OBJECT

public:
	MessageManager(QObject *parent);
	void routine();
	void send_to_cout(MsgData msg, QString channel, QString server);
	void send_to_cout(BotCommand command, QString channel, QString server);
	~MessageManager();
signals:
	void got_message(ExternalMsg msg);
private:
	bool quit;
};

