#include "chat.hpp"

#include <algorithm>

#include "chat_printer.hpp"

namespace chat {
    Chat::Chat(in_addr_t host, in_port_t port) : SocketWorker(host, port) {
        ChatPrinter::Greeting();
    }

    void *Chat::StartWritingMessages(void *chat_ptr) {
        Chat *chat = static_cast<Chat *>(chat_ptr);
        chat->WriteMessages();

        return nullptr;
    }

    void *Chat::StartListeningMessages(void *chat_ptr) {
        Chat *chat = static_cast<Chat *>(chat_ptr);
        chat->ListenMessages();

        return nullptr;
    }

    void Chat::SetNickname() {
        do {
            ChatPrinter::EnteringNickname(nickname_);
        } while (!isValidNickname());

        ChatPrinter::InitMessageInput();
    }

    void Chat::WriteMessages() {
        while (!must_stop_) {
            RefreshTextBuffer(text_buffer_out_);
            std::string message;
            do {
                message = ChatPrinter::GetPrintedMessage();
            } while (!isValidMessageText(message));
            IsStopWordPrinted(message);
            SendMessage(nickname_ + ": " + GetValidSizeMessageText(message));
        }
    }

    void Chat::ListenMessages() {
        do {
            RefreshTextBuffer(text_buffer_in_);
            ReceiveMessage();
            ChatPrinter::PrintMessage(GetReceivedHost(), text_buffer_in_);
        } while (!must_stop_);
        CloseSocket();
    }

    Chat::~Chat() {
        ChatPrinter::Farewell();
    }

    void Chat::ReceiveMessage() {
        Recvfrom();
    }

    void Chat::SendMessage(const std::string &full_text) {
        text_buffer_out_.clear();
        text_buffer_out_ = full_text;
        Sendto();
    }

    void Chat::RefreshTextBuffer(std::string &text_buffer) {
        text_buffer.clear();
        text_buffer.resize(c_MaxBufferSize);
    }

    bool Chat::isValidNickname() {
        return std::none_of(nickname_.begin(), nickname_.end(), isspace);
    }

    bool Chat::isValidMessageText(const std::string &text) {
        return !std::all_of(text.begin(),
                            text.end(),
                            [](char c) { return std::isspace(c); });
    }

    std::string Chat::GetValidSizeMessageText(const std::string &message) {
        return message.size() > c_MaxBufferSize
                       ? message
                       : message.substr(0, c_MaxBufferSize);
    }

    bool Chat::IsStopWordPrinted(const std::string &text) {
        if (text == c_StopSign) {
            must_stop_ = true;
        }

        return must_stop_;
    }
} // namespace chat
