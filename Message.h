#pragma once

#include <QWidget>
#include <ui_Message.h>
#include "MsgData.h"
#include "ImageDownloader.h"

class Message  : public QWidget
{
	Q_OBJECT

public:
	Message(QWidget* parent, MsgData msgdata);
	~Message();
private:
	Ui::Form ui;
	ImageDownloader downloader;
	int w_img;
	int h_img;
private slots:
	void download_done(const QPixmap& downloaded_pixmap);
};

