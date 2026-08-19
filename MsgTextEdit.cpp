#include "MsgTextEdit.h"

MsgTextEdit::MsgTextEdit(QWidget *parent)
	: QTextEdit(parent)
{}

MsgTextEdit::~MsgTextEdit()
{}

void MsgTextEdit::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Return: {

    }
    case Qt::Key_Enter: {
        // do send
        MsgData new_msg(":/img/img/bot.png", "Neir0bot", this->toPlainText(), QTime::currentTime().toString("hh:mm"));
        emit send_message(new_msg);
        this->clear();
        return;
    }
    }
    QTextEdit::keyPressEvent(event);
}

