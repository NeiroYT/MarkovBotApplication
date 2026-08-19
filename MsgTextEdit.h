#pragma once

#include <QTextEdit>
#include <QTime>
#include <QKeyEvent>
#include "MsgData.h"

class MsgTextEdit  : public QTextEdit
{
	Q_OBJECT

public:
	MsgTextEdit(QWidget *parent);
	~MsgTextEdit();
protected:
	void keyPressEvent(QKeyEvent* event) override;
signals:
	void send_message(MsgData msgdata);
};

