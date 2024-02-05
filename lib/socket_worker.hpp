#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace chat {
    class SocketWorker {
    public:
        SocketWorker() = default;
        explicit SocketWorker([[maybe_unused]] in_addr_t, in_port_t);

        [[nodiscard]] static int Socket();
        void Setsockopt();
        void Bind();

        void Sendto();
        void Recvfrom();

        [[nodiscard]] std::string GetReceivedHost() const;

        void CloseSocket() const;

    protected:
        std::string text_buffer_in_{};
        std::string text_buffer_out_{};

        static const size_t c_MaxBufferSize = 1007;

    private:
        using Descriptor = int;

        static int CheckError(const std::string &, Descriptor);
        static void FillAddressInfo(sockaddr_in &, in_addr_t, in_port_t);

        int sockfd_{};

        sockaddr_in addr_in_{};
        sockaddr_in addr_out_{};
        sockaddr_in broadcast_addr_{};

        const int c_Broadcast = 1;
    };
} // namespace chat
