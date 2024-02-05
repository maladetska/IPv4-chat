#include "chat_printer.hpp"

namespace chat {
    void ChatPrinter::Greeting() {
        std::cout << "Welcome to chat!" << std::endl;
    }

    void ChatPrinter::EnteringNickname(std::string& nickname) {
        std::cout << "Enter your nickname:" << std::endl;
        std::getline(std::cin, nickname);
    }

    void ChatPrinter::InitMessageInput() {
        std::cout << "Enter your messages." << std::endl
                  << "(When you want to disconnect, write 'STOP')" << std::endl;
    }

    void ChatPrinter::PrintMessage(const std::string& host, const std::string& text) {
        std::cout << "<" << host << "> "
                  << text.c_str() << std::endl;
    }

    std::string ChatPrinter::GetPrintedMessage() {
        std::string message_text;
        std::getline(std::cin, message_text);

        return message_text;
    }

    void ChatPrinter::Farewell() {
        std::cout << "Goodbye, come back soon!" << std::endl;
    }
} // namespace chat
