#pragma once

#include <iostream>

namespace chat {
    class ChatPrinter {
    public:
        static void Greeting();
        static void EnteringNickname(std::string &);
        static void InitMessageInput();
        static void PrintReceivedMessage(const std::string &);
        [[nodiscard]] static std::string GetPrintedMessage();
        static void Farewell();
    };
} // namespace chat
