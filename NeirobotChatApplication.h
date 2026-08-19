#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTime>
#include <QMutex>
#include <iostream>
#include <string>
#include <sstream>
#include "MyServerItem.h"
#include "Message.h"
#include "ui_NeirobotChatApplication.h"
#include "MsgTextEdit.h"
#include "MessageManager.h"
#include "MessengerModel.h"

class NeirobotChatApplication : public QMainWindow
{
    Q_OBJECT

public:
    NeirobotChatApplication(QWidget *parent = nullptr);
    ~NeirobotChatApplication();

private:
    Ui::NeirobotChatApplicationClass ui;
    MessageManager* manager;
    MessengerModel* model;
    QString current_server_name;
    QString current_channel_name;
    int server_image_width;
    int server_image_height;
    bool thread_chat_filling;
    bool thread_channels_filling;
    void loadChatFromModel();
    void loadChannelsFromModel();
    void add_message_UI_routine(MsgData msgdata);
private slots:
    void on_serversListWidget_itemClicked(QListWidgetItem* item);
    void on_channelsListWidget_itemClicked(QListWidgetItem* item);
    void add_message_UI(MsgData msgdata);
    void add_server_UI(MyServerItem* item);
    void lock_chat();
    void unlock_chat();
    void onModelChanged();

    // buttons
    void on_checkthis_button_clicked();
    void on_forcesave_button_clicked();
    void on_pause_button_clicked();
    void on_say_button_clicked();
};

