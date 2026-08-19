#include "Message.h"

Message::Message(QWidget *parent, MsgData msgdata)
	: QWidget(parent), downloader(this)
{
	ui.setupUi(this);
	QObject::connect(&downloader, &ImageDownloader::imageDownloaded, this, &Message::download_done);
	w_img = 100;
	h_img = 100;
	if (msgdata.image_path.startsWith("http")) {
		downloader.fetchImage(msgdata.image_path);
	}
	else {
		QPixmap pixmap = QPixmap(msgdata.image_path).scaled(w_img, h_img, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		ui.label_img->setPixmap(pixmap);
	}
	ui.label_img->setAlignment(Qt::AlignCenter);

	ui.label_username->setText(msgdata.author);
	ui.label_msg->setText(msgdata.msg);
	ui.label_timestamp->setText(msgdata.timestamp);
	this->adjustSize();
}

Message::~Message()
{}

void Message::download_done(const QPixmap& downloaded_pixmap) {
	ui.label_img->setPixmap(downloaded_pixmap.scaled(w_img, h_img, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

