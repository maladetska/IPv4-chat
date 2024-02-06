#include "chat.hpp"

#include <algorithm>

#include "chat_printer.hpp"

namespace chat {
    Chat::Chat(in_addr_t host, in_port_t port) : SocketWorker(host, port) {
        text_buffer_in_.SetMaxSize(kMaxNicknameSize + kMaxTextSize + kAdditionalChars.length());
        ChatPrinter::Greeting();
    }

    Chat::~Chat() {
        ChatPrinter::Farewell();
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
        text_buffer_out_.SetMaxSize(nickname_.length() + kAdditionalChars.length() + kMaxTextSize);
        ChatPrinter::InitMessageInput();
    }

    void Chat::WriteMessages() {
        while (!must_stop_) {
            text_buffer_out_.Refresh();
            std::string message;
            do {
                message = ChatPrinter::GetPrintedMessage();
            } while (!isValidMessageText(message));
            IsStopWordPrinted(message);
            SendMessage(nickname_ + kAdditionalChars + GetValidSizeMessageText(message));
        }
    }

    void Chat::ListenMessages() {
        do {
            text_buffer_in_.Refresh();
            ReceiveMessage();
            ChatPrinter::PrintMessage(GetReceivedHost(), text_buffer_in_.GetText());
        } while (!must_stop_);
        CloseSocket();
    }

    void Chat::ReceiveMessage() {
        Recvfrom();
    }

    void Chat::SendMessage(const std::string &full_text) {
        text_buffer_out_.SetText(full_text);
        Sendto();
    }

    bool Chat::isValidNickname() const {
        return nickname_.length() < kMaxNicknameSize &&
               std::none_of(nickname_.begin(), nickname_.end(), isspace);
    }

    bool Chat::isValidMessageText(const std::string &text) {
        return !std::all_of(text.begin(), text.end(), [](char c) { return std::isspace(c); });
    }

    std::string Chat::GetValidSizeMessageText(const std::string &message) {
        return message.size() > kMaxTextSize
                       ? message.substr(0, kMaxTextSize)
                       : message;
    }

    bool Chat::IsStopWordPrinted(const std::string &text) {
        if (text == kStopSign) {
            must_stop_ = true;
        }

        return must_stop_;
    }
} // namespace chat
