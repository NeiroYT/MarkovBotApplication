#include "ImageDownloader.h"

ImageDownloader::ImageDownloader(QObject *parent)
	: QObject(parent)
{
	connect(&manager, &QNetworkAccessManager::finished, this, &ImageDownloader::onDownloadFinished);
}

ImageDownloader::~ImageDownloader()
{}

void ImageDownloader::fetchImage(const QString& url) {
	QUrl qurl(url);
	QNetworkRequest request(qurl);
	manager.get(request);
}

void ImageDownloader::onDownloadFinished(QNetworkReply* reply) {
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        return;
    }

    QByteArray data = reply->readAll();
    QPixmap pixmap;

    if (pixmap.loadFromData(data)) {
        emit imageDownloaded(pixmap);
    }
    else {
        emit errorOccurred("Failed to convert byte data into an image.");
    }
}

