#pragma once

#include <QString>
#include "ExternalMsg.h"

struct MsgData {
	QString image_path;
	QString author;
	QString msg;
	QString timestamp;
	MsgData(QString image_path, QString author, QString msg, QString timestamp)
		: image_path(image_path), author(author), msg(msg), timestamp(timestamp) {}
	MsgData(ExternalMsg ext) : image_path(ext.image_path), author(ext.author_name), msg(ext.msg), timestamp(ext.timestamp) {}
};
