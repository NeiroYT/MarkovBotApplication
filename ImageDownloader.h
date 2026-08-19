#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QUrl>

class ImageDownloader  : public QObject
{
	Q_OBJECT

public:
	ImageDownloader(QObject *parent);
	~ImageDownloader();
	void fetchImage(const QString& url);
signals:
	void imageDownloaded(const QPixmap& pixmap);
	void errorOccurred(const QString& err);
private slots:
	void onDownloadFinished(QNetworkReply* reply);
private:
	QNetworkAccessManager manager;
};

