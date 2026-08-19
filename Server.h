#pragma once

#include <stdexcept>
#include <QString>
#include <vector>
#include "Channel.h"
#include "MyServerItem.h"

class Server {
public:
	Server(QString image_path, QString server_name) : _avatar_path(image_path), _server_name(server_name) {}
	Server(MyServerItem* item) : _avatar_path(item->get_file_name()), _server_name(item->get_server_name()) {}
	void add_channel(const Channel& channel) {
		_channels.push_back(channel);
	}
	const Channel& get_channel(int id) const {
		if (id < 0 || id >= _channels.size()) {
			throw std::runtime_error("Invalid id for get_channel()");
		}
		return _channels[id];
	}
	Channel& get_channel(int id) {
		if (id < 0 || id >= _channels.size()) {
			throw std::runtime_error("Invalid id for get_channel()");
		}
		return _channels[id];
	}
	size_t get_channel_count() const {
		return _channels.size();
	}
	const Channel& find_channel(QString name) const {
		return *std::find_if(_channels.begin(), _channels.end(), [&](const Channel& c)->bool { return c.get_channel_name() == name; });
	}
	Channel& find_channel(QString name) {
		return *std::find_if(_channels.begin(), _channels.end(), [&](const Channel& c)->bool { return c.get_channel_name() == name; });
	}
	bool has_channel(QString name) {
		for (int i = 0; i < _channels.size(); i++) {
			if (_channels[i].get_channel_name() == name) {
				return true;
			}
		}
		return false;
	}
	void set_avatar_path(QString path) {
		_avatar_path = path;
	}
	QString get_avatar_path() const {
		return _avatar_path;
	}
	QString get_server_name() const {
		return _server_name;
	}
private:
	std::vector<Channel> _channels;
	QString _avatar_path;
	QString _server_name;
};