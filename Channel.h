#pragma once

#include <QString>
#include <stdexcept>
#include <vector>
#include "MsgData.h"

class Channel {
public:
	Channel(QString channel_name) : _channel_name(channel_name) {}
	QString get_channel_name() const {
		return _channel_name;
	}
	void add_message(const MsgData& msg) {
		_messages.push_back(msg);
	}
	const MsgData& get_message(int id) const {
		if (id < 0 || id >= _messages.size()) {
			throw std::runtime_error("Invalid id for get_message()");
		}
		return _messages[id];
	}
	size_t get_message_count() const {
		return _messages.size();
	}
private:
	std::vector<MsgData> _messages;
	QString _channel_name;
};