#include "NeirobotChatApplication.h"

NeirobotChatApplication::NeirobotChatApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    lock_chat();
    manager = new MessageManager(this);
    model = new MessengerModel(this);
    current_channel_name = "";
    current_server_name = "";
    thread_channels_filling = false;
    thread_chat_filling = false;
    QObject::connect(ui.textEdit, &MsgTextEdit::send_message, this, &NeirobotChatApplication::add_message_UI);
    QObject::connect(manager, &MessageManager::got_message, model, &MessengerModel::got_ext_message);
    QObject::connect(model, &MessengerModel::onModelChanged, this, &NeirobotChatApplication::onModelChanged);
    server_image_width = ui.serversListWidget->maximumWidth();
    server_image_height = 80;
}

void NeirobotChatApplication::add_message_UI_routine(MsgData msgdata) {
    QListWidgetItem* item = new QListWidgetItem();
    Message* myitemWidget = new Message(this, msgdata);
    item->setSizeHint(QSize(0, myitemWidget->height()));
    ui.chatListWidget->addItem(item);
    ui.chatListWidget->setItemWidget(item, myitemWidget);
    ui.chatListWidget->scrollToBottom();
}

void NeirobotChatApplication::add_message_UI(MsgData msgdata) {
    add_message_UI_routine(msgdata);
    ExternalMsg ext;
    ext.author_name = msgdata.author;
    ext.channel_name = current_channel_name;
    ext.server_name = current_server_name;
    ext.image_path = msgdata.image_path;
    ext.msg = msgdata.msg;
    ext.timestamp = msgdata.timestamp;
    manager->send_to_cout(msgdata, current_channel_name, current_server_name);
    model->got_ext_message(ext);
}

void NeirobotChatApplication::add_server_UI(MyServerItem* item) {
    int h = 80;
    QListWidgetItem* listitem = new QListWidgetItem();
    listitem->setSizeHint(QSize(0, h));
    ui.serversListWidget->addItem(listitem);
    ui.serversListWidget->setItemWidget(listitem, item);
}

NeirobotChatApplication::~NeirobotChatApplication()
{}

void NeirobotChatApplication::on_serversListWidget_itemClicked(QListWidgetItem* item) {
    QString servname = static_cast<MyServerItem*>(ui.serversListWidget->itemWidget(item))->get_server_name();
    //QMessageBox::information(this, "Info", "Server " + servname + " was chosen!");
    ui.channelsListWidget->clear();
    ui.chatListWidget->clear();
    lock_chat();
    current_server_name = servname;
    if (!model->has_server(current_server_name)) {
        QMessageBox::warning(this, "Warning", "Failed to load channels from " + current_server_name);
        return;
    }
    loadChannelsFromModel();
}

void NeirobotChatApplication::on_channelsListWidget_itemClicked(QListWidgetItem* item) {
    QString channame = item->text();
    //QMessageBox::information(this, "Info", "Channel " + channame + " was chosen!");
    ui.chatListWidget->clear();
    lock_chat();
    current_channel_name = channame;
    if (current_server_name == "") {
        return;
    }
    if (!model->find_server(current_server_name).has_channel(current_channel_name)) {
        QMessageBox::warning(this, "Warning", "Failed to load chat from " + current_server_name + ". Channel " + current_channel_name);
        return;
    }
    loadChatFromModel();
    unlock_chat();
}

void NeirobotChatApplication::loadChatFromModel() {
    if (thread_chat_filling) {
        return;
    }
    thread_chat_filling = true;
    //qDebug() << "Chat is being filled";
    Channel chan = model->find_server(current_server_name).find_channel(current_channel_name);
    for (int i = 0; i < chan.get_message_count(); i++) {
        add_message_UI_routine(chan.get_message(i));
    }
    thread_chat_filling = false;
    //qDebug() << "Chat is done";
}

void NeirobotChatApplication::loadChannelsFromModel() {
    if (thread_channels_filling) {
        return;
    }
    thread_channels_filling = true;
    //qDebug() << "Channels are being filled";
    Server serv = model->find_server(current_server_name);
    for (int i = 0; i < serv.get_channel_count(); i++) {
        ui.channelsListWidget->addItem(serv.get_channel(i).get_channel_name());
    }
    thread_channels_filling = false;
    //qDebug() << "Channels are done";
}

void NeirobotChatApplication::lock_chat() {
    ui.textEdit->setReadOnly(true);
    ui.checkthis_button->setEnabled(false);
    ui.say_button->setEnabled(false);
}

void NeirobotChatApplication::unlock_chat() {
    ui.textEdit->setReadOnly(false);
    ui.checkthis_button->setEnabled(true);
    ui.say_button->setEnabled(true);
}

void NeirobotChatApplication::onModelChanged() {
    int size_serv = ui.serversListWidget->count();
    while (size_serv < model->get_servers_count()) {
        MyServerItem* item = new MyServerItem(this, model->get_server(size_serv).get_server_name(),
            model->get_server(size_serv).get_avatar_path(), server_image_width, server_image_height);
        add_server_UI(item);
        size_serv++;
    }
    if (current_server_name == "") {
        current_server_name = model->get_server(0).get_server_name();
    }
    while (thread_channels_filling) {
        ;
    }
    thread_channels_filling = true;
    //qDebug() << "Channels are being filled";
    int size_chan = ui.channelsListWidget->count();
    Server& cur_server = model->find_server(current_server_name);
    while (size_chan < cur_server.get_channel_count()) {
        QString item = cur_server.get_channel(size_chan).get_channel_name();
        ui.channelsListWidget->addItem(item);
        size_chan++;
    }
    thread_channels_filling = false;
    //qDebug() << "Channels are done";
    if (current_channel_name == "") {
        current_channel_name = model->get_server(0).get_channel(0).get_channel_name();
        unlock_chat();
    }
    while (thread_chat_filling) {
        ;
    }
    thread_chat_filling = true;
    //qDebug() << "Chat is being filled";
    int size_messages = ui.chatListWidget->count();
    Channel& cur_channel = cur_server.find_channel(current_channel_name);
    while (size_messages < cur_channel.get_message_count()) {
        const MsgData& msg = cur_channel.get_message(size_messages);
        add_message_UI_routine(msg);
        size_messages++;
    }
    thread_chat_filling = false;
    //qDebug() << "Chat is done";
}

void NeirobotChatApplication::on_checkthis_button_clicked() {
    BotCommand command;
    command.command = "checkthis";
    bool num_ok;
    command.args["checkNum"] = ui.checkthis_input->text().toInt(&num_ok);
    if (!num_ok) {
        QMessageBox::critical(this, "Error", "Incorrent number given to checkthis command.");
        return;
    }
    manager->send_to_cout(command, current_channel_name, current_server_name);
}

void NeirobotChatApplication::on_forcesave_button_clicked() {
    BotCommand command;
    command.command = "forcesave";
    manager->send_to_cout(command, current_channel_name, current_server_name);
}

void NeirobotChatApplication::on_pause_button_clicked() {
    BotCommand command;
    command.command = "pause";
    manager->send_to_cout(command, current_channel_name, current_server_name);
}

void NeirobotChatApplication::on_say_button_clicked() {
    BotCommand command;
    command.command = "say";
    command.args["base"] = ui.say_baseinput->text();
    bool length_num_ok;
    command.args["length"] = ui.say_lengthinput->text().toInt(&length_num_ok);
    if (!length_num_ok) {
        QMessageBox::critical(this, "Error", "Incorrent length given to say command.");
        return;
    }
    command.args["startWord"] = ui.say_startwordinput->text();
    manager->send_to_cout(command, current_channel_name, current_server_name);
}
