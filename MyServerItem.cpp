#include "MyServerItem.h"

MyServerItem::MyServerItem(QWidget *parent, QString servername, QString filename, int w, int h)
	: QWidget(parent), server_name(servername), file_name(filename), downloader(this)
{
	QObject::connect(&downloader, &ImageDownloader::imageDownloaded, this, &MyServerItem::download_done);
	w_img = 60;
	h_img = 60;
	label_img = new QLabel(this);
	if (filename.startsWith("http")) {
		downloader.fetchImage(filename);
	}
	else {
		QPixmap pixmap = QPixmap(filename).scaled(w_img, h_img, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		label_img->setPixmap(pixmap);
	}
	label_img->setGeometry(0, 0, w, h);
	label_img->setAlignment(Qt::AlignCenter);
}

MyServerItem::~MyServerItem()
{}

void MyServerItem::download_done(const QPixmap& downloaded_pixmap) {
	label_img->setPixmap(downloaded_pixmap.scaled(w_img, h_img, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
