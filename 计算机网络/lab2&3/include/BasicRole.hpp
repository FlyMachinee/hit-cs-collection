#ifndef _BASIC_ROLE_HPP_
#define _BASIC_ROLE_HPP_

#include "./Entity.hpp"
#include "./UDPDataframe.h"

namespace my
{
    template <int windowSize, int seqNumBound>
    class BasicRole
    {
    public:
        BasicRole() = default;
        BasicRole(SOCKET host_socket) : m_host(host_socket) {};
        virtual ~BasicRole() = 0;
        BasicRole(const BasicRole &) = delete;
        BasicRole &operator=(const BasicRole &) = delete;

        virtual void setPeer(::std::string_view ip, unsigned short port) final
        {
            m_peer.m_address.sin_family = AF_INET;
            m_peer.m_address.sin_addr.s_addr = inet_addr(ip.data());
            m_peer.m_address.sin_port = htons(port);
        }
        virtual void setPeer(sockaddr_in peer_address) final { m_peer.m_address = peer_address; }
        virtual void setPeer(const Peer &peer) final { m_peer = peer; }

    protected:
        Host m_host;
        Peer m_peer;
        int getActualLine(int base, char ack_num) const noexcept;
    };

    template <int senderWindowSize, int seqNumBound>
    class BasicSender : virtual public BasicRole<senderWindowSize, seqNumBound>
    {
    public:
        BasicSender() = default;
        BasicSender(SOCKET host_socket) : BasicRole<senderWindowSize, seqNumBound>(host_socket) {};
        virtual ~BasicSender() = 0;
        BasicSender(const BasicSender &) = delete;
        BasicSender &operator=(const BasicSender &) = delete;

        virtual void sendtoPeer(::std::string_view filename) = 0;

    protected:
        int recvAckFromPeer();
    };

    template <int receiverWindowSize, int seqNumBound>
    class BasicReceiver : virtual public BasicRole<receiverWindowSize, seqNumBound>
    {
    public:
        BasicReceiver() = default;
        BasicReceiver(SOCKET host_socket) : BasicRole<receiverWindowSize, seqNumBound>(host_socket) {};
        virtual ~BasicReceiver() = 0;
        BasicReceiver(const BasicReceiver &) = delete;
        BasicReceiver &operator=(const BasicReceiver &) = delete;

        virtual void recvfromPeer(::std::string_view file_path) = 0;

    protected:
        void sendAckToPeer(char ack_num);
    };

    template <int windowSize, int seqNumBound>
    BasicRole<windowSize, seqNumBound>::~BasicRole() {}

    template <int windowSize, int seqNumBound>
    int BasicRole<windowSize, seqNumBound>::getActualLine(int base, char ack_num) const noexcept
    {
        int base_mod_M = base % seqNumBound;
        // if (base_mod_M <= ack_num) {
        //     return base + ack_num - base_mod_M;
        // } else {
        //     return base + ack_num + seqNumBound - base_mod_M;
        // }
        return (base + ack_num - base_mod_M) + (base_mod_M <= ack_num ? 0 : seqNumBound);
    }

    template <int senderWindowSize, int seqNumBound>
    BasicSender<senderWindowSize, seqNumBound>::~BasicSender() {}

    template <int senderWindowSize, int seqNumBound>
    int BasicSender<senderWindowSize, seqNumBound>::recvAckFromPeer()
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(this->m_host.getSocket(), &readfds);
        TIMEVAL timeout = {0, 100000};

        int sum = select(0, &readfds, nullptr, nullptr, &timeout);
        if (sum == SOCKET_ERROR) {
            pretty_out << ::std::format("throw from BasicSender::recvAckFromPeer(): select() failed, WSAGetLastError() = {0}", WSAGetLastError());
            throw std::runtime_error("select() failed");
        } else if (sum == 0) {
            return -1;
        }

        Peer peer;
        char ack_num;
        try {
            ack_num = recvAckFrom(this->m_host, peer);
        } catch (const std::runtime_error &e) {
            pretty_out
                << ::std::format("catch by BasicSender::recvAckFromPeer():")
                << e.what();
            return -1;
        }

        return (peer == this->m_peer) ? ack_num : -1;
    }

    template <int receiverWindowSize, int seqNumBound>
    BasicReceiver<receiverWindowSize, seqNumBound>::~BasicReceiver() {}

    template <int receiverWindowSize, int seqNumBound>
    void BasicReceiver<receiverWindowSize, seqNumBound>::sendAckToPeer(char ack_num)
    {
        sendAckTo(ack_num, this->m_host, this->m_peer);
    }
} // namespace my

#endif // _BASIC_ROLE_HPP_