#include "MessageManager.h"

MessageManager::MessageManager(QObject *parent)
	: QObject(parent)
{
	quit = false;
	std::ios_base::sync_with_stdio(false);
	std::thread thread([&]()->void { routine(); });
	thread.detach();
}

void MessageManager::send_to_cout(MsgData msg, QString channel, QString server) {
	QJsonObject obj;
	obj["server"] = server;
	obj["channel"] = channel;
	obj["command"] = "send";
	obj["msg"] = msg.msg;
	QJsonDocument doc(obj);
	std::string res = doc.toJson(QJsonDocument::Compact).toStdString();
	std::cout << res << std::endl;
	//qDebug() << doc.toJson(QJsonDocument::Compact) << Qt::endl;
}

void MessageManager::send_to_cout(BotCommand command, QString channel, QString server) {
	QJsonObject obj;
	obj["server"] = server;
	obj["channel"] = channel;
	obj["command"] = command.command;
	for (auto arg : command.args.keys()) {
		obj[arg] = command.args[arg];
	}
	QJsonDocument doc(obj);
	std::string res = doc.toJson(QJsonDocument::Compact).toStdString();
	std::cout << res << std::endl;
	//qDebug() << doc.toJson(QJsonDocument::Compact) << Qt::endl;
}

void MessageManager::routine() {
	qDebug() << "Enter the thread";
	std::string input_str;
	QJsonDocument doc;
	while (!quit) {
		std::getline(std::cin, input_str);
		if (input_str == "exit") {
			break;
		}
		try {
			//QByteArray bytearr(input_str.c_str());
			QJsonParseError err;
			doc = QJsonDocument::fromJson(QString::fromStdString(input_str).toUtf8(), &err);
		}
		catch (QException& e) {
			qDebug() << e.what();
			continue;
		}
		catch (std::exception& e) {
			qDebug() << e.what();
			continue;
		}
		if (doc.isEmpty()) {
			continue;
		}
		qDebug() << "Got message: " << doc["msg"] << Qt::endl;
		ExternalMsg ext;
		ext.server_name = doc["server"].toString();
		ext.author_name = doc["author"].toString();
		ext.channel_name = doc["channel"].toString();
		ext.msg = doc["msg"].toString();
		ext.image_path = doc["image_path"].toString();
		ext.timestamp = QTime::currentTime().toString("hh:mm");
		ext.server_image = doc["server_image"].toString();
		emit got_message(ext);
	}
	qDebug() << "Quit the thread";
}

MessageManager::~MessageManager()
{}
