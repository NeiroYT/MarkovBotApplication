#pragma once

#include <QWidget>
#include <QLabel>
#include <QListWidgetItem>
#include "ImageDownloader.h"

class MyServerItem  : public QWidget
{
	Q_OBJECT
public:
	MyServerItem(QWidget *parent, QString servername, QString filename, int w, int h);
	~MyServerItem();
	QString get_server_name() const noexcept {
		return server_name;
	}
	QString get_file_name() const noexcept {
		return file_name;
	}
private:
	ImageDownloader downloader;
	int w_img;
	int h_img;
	QString server_name;
	QString file_name;
	QLabel* label_img;
private slots:
	void download_done(const QPixmap& downloaded_pixmap);
};

