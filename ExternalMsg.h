#pragma once

#include <QString>
#include <QMetaType>

struct ExternalMsg {
	QString server_name;
	QString channel_name;
	QString author_name;
	QString msg;
	QString image_path;
	QString timestamp;
	QString server_image;
};
Q_DECLARE_METATYPE(ExternalMsg);
