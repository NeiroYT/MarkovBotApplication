#pragma once
#include <QJsonObject>
#include <QString>

struct BotCommand {
public:
	QString command;
	QJsonObject args;
};
