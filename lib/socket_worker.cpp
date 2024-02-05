#include "socket_worker.hpp"

namespace chat {
    SocketWorker::SocketWorker([[maybe_unused]] in_addr_t host, in_port_t port) : sockfd_(Socket()) {
        Setsockopt();
        FillAddressInfo(broadcast_addr_, INADDR_BROADCAST, port);

        FillAddressInfo(addr_out_, INADDR_ANY, port);
        Bind();
    }

    int SocketWorker::Socket() {
        return CheckError("socket failed",
                          socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
    }

    void SocketWorker::Bind() {
        CheckError("bind failed",
                   bind(sockfd_, reinterpret_cast<const sockaddr *>(&addr_out_), sizeof(addr_out_)));
    }

    void SocketWorker::Setsockopt() {
        CheckError("setsockopt failed",
                   setsockopt(sockfd_, SOL_SOCKET, SO_BROADCAST, &c_Broadcast, sizeof(c_Broadcast)));
    }

    void SocketWorker::Sendto() {
        socklen_t sockaddr_len = sizeof(broadcast_addr_);
        CheckError("sendto failed",
                   static_cast<int>(sendto(
                           sockfd_, text_buffer_out_.c_str(), text_buffer_out_.size(),
                           0, reinterpret_cast<const sockaddr *>(&broadcast_addr_), sockaddr_len)));
    }

    void SocketWorker::Recvfrom() {
        socklen_t sockaddr_len = sizeof(sockaddr);
        CheckError("recvfrom failed",
                   static_cast<int>(recvfrom(
                           sockfd_, text_buffer_in_.data(), c_MaxBufferSize,
                           MSG_WAITALL, reinterpret_cast<sockaddr *>(&addr_in_), &sockaddr_len)));
    }

    std::string SocketWorker::GetReceivedHost() const {
        return inet_ntoa(addr_in_.sin_addr);
    }

    void SocketWorker::CloseSocket() const {
        close(sockfd_);
    }

    int SocketWorker::CheckError(const std::string &str, Descriptor descriptor) {
        if (descriptor == -1) {
            perror(str.c_str());
            exit(EXIT_FAILURE);
        }

        return descriptor;
    }

    void SocketWorker::FillAddressInfo(sockaddr_in &addr, in_addr_t host, in_port_t port) {
        memset((void *) &addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(host);
        addr.sin_port = htons(port);
    }
} // namespace chat
