#include "MessengerModel.h"

MessengerModel::MessengerModel(QObject *parent)
	: QObject(parent)
{}

MessengerModel::~MessengerModel()
{}

void MessengerModel::got_ext_message(ExternalMsg ext) {
	if (!has_server(ext.server_name)) {
		Server temp_serv = Server(ext.server_image, ext.server_name);
		this->add_server(temp_serv);
	}
	Server& serv = find_server(ext.server_name);
	if (!serv.has_channel(ext.channel_name)) {
		Channel temp_chan = Channel(ext.channel_name);
		serv.add_channel(temp_chan);
	}
	Channel& chan = serv.find_channel(ext.channel_name);
	MsgData msg(ext);
	chan.add_message(msg);
	emit onModelChanged();
}

