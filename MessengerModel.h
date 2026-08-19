#pragma once

#include <QObject>
#include <stdexcept>
#include <vector>
#include "Server.h"
#include "MyServerItem.h"
#include "ExternalMsg.h"

class MessengerModel  : public QObject
{
	Q_OBJECT

public:
	MessengerModel(QObject *parent);
	~MessengerModel();
	void add_server(const Server& server) {
		_servers.push_back(server);
	}
	const Server& get_server(int id) const {
		if (id < 0 || id >= _servers.size()) {
			throw std::runtime_error("Invalid id for get_server()");
		}
		return _servers[id];
	}
	Server& get_server(int id) {
		if (id < 0 || id >= _servers.size()) {
			throw std::runtime_error("Invalid id for get_server()");
		}
		return _servers[id];
	}
	const Server& find_server(QString name) const {
		return *std::find_if(_servers.begin(), _servers.end(), [&](const Server& s)->bool { return s.get_server_name() == name; });
	}
	Server& find_server(QString name) {
		return *std::find_if(_servers.begin(), _servers.end(), [&](const Server& s)->bool { return s.get_server_name() == name; });
	}
	bool has_server(QString name) {
		for (int i = 0; i < _servers.size(); i++) {
			if (_servers[i].get_server_name() == name) {
				return true;
			}
		}
		return false;
	}
	size_t get_servers_count() const {
		return _servers.size();
	}
signals:
	void onModelChanged();
public slots:
	void got_ext_message(ExternalMsg ext);
private:
	std::vector<Server> _servers;
};

