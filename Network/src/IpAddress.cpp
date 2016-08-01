#include "../include/IpAddress.hpp"
#include "SocketBE.hpp"
#include <cstring>
#include <utility>

namespace wv {
    const IpAddress	IpAddress::None;
    const IpAddress	IpAddress::Any(0, 0, 0, 0);
    const IpAddress	IpAddress::LocalHost(127, 0, 0, 1);
    const IpAddress	IpAddress::Broadcast(255, 255, 255, 255);

    IpAddress::IpAddress() :
        m_address(0),
        m_valid(false)
    {}

    IpAddress::IpAddress(const std::string& l_ip) :
        m_address(0),
        m_valid(false)
    {
        Resolve(l_ip);
    }

    IpAddress::IpAddress(const char* l_ip) :
        m_address(0),
        m_valid(false)
    {
        Resolve(l_ip);
    }

    IpAddress::IpAddress(intU8 l_a, intU8 l_b, intU8 l_c, intU8 l_d) :
        m_address(htonl(l_a << 24 | l_b << 16 | l_c << 8 | l_d)),
        m_valid(true)
    {}

    IpAddress::IpAddress(intU32 l_ip) :
        m_address(htonl(l_ip)),
        m_valid(true)
    {}

    std::string IpAddress::toString() const {
        in_addr		address;
        address.s_addr = m_address;
        return inet_ntoa(address);
    }
    intU32 IpAddress::toInteger() const {
        return ntohl(m_address);
    }

    IpAddress IpAddress::GetLocalAddress() {
        IpAddress localAddress;
        SocketHandle sock = socket(PF_INET, SOCK_DGRAM, 0); //
        if (sock == be::SocketBE::invalidSocket()) {
            return localAddress;
        }
        sockaddr_in address = be::SocketBE::createAddress(ntohl(INADDR_LOOPBACK), 9);
        if (connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1) {
            be::SocketBE::close(sock);
            return localAddress;
        }

        be::SocketBE::AddrLength size = sizeof(address);
        if (getsockname(sock, reinterpret_cast<sockaddr*>(&address), &size) == -1)
        {
            be::SocketBE::close(sock);
            return localAddress;
        }
        be::SocketBE::close(sock);
        localAddress = IpAddress(ntohl(address.sin_addr.s_addr));
        return localAddress;
    }

    //empty
    IpAddress IpAddress::GetPublicAddress() { return IpAddress::None; }

    void IpAddress::Resolve(const std::string& l_address) {
        m_address = 0;
        m_valid = false;

        if (l_address == "255.255.255.255")
        {
            m_address = INADDR_BROADCAST;
            m_valid = true;
        }
        else if (l_address == "0.0.0.0")
        {
            m_address = INADDR_ANY;
            m_valid = true;
        }
        else
        {
            intU32 ip = inet_addr(l_address.c_str());
            if (ip != INADDR_NONE)
            {
                m_address = ip;
                m_valid = true;
            }
            else
            {
                addrinfo hints;
                std::memset(&hints, 0, sizeof(hints));
                hints.ai_family = AF_INET;
                addrinfo* result = NULL;
                if (getaddrinfo(l_address.c_str(), NULL, &hints, &result) == 0)
                {
                    if (result)
                    {
                        ip = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr.s_addr;
                        freeaddrinfo(result);
                        m_address = ip;
                        m_valid = true;
                    }
                }
            }
        }
    }


    bool operator == (const IpAddress& l_left, const IpAddress& l_right) {
        return !(l_left < l_right) && !(l_right < l_left);
    }
    bool operator != (const IpAddress& l_left, const IpAddress& l_right) {
        return !(l_left == l_right);
    }
    bool operator < (const IpAddress& l_left, const IpAddress& l_right) {
        return
            std::make_pair(l_left.m_valid, l_left.m_address) <
            std::make_pair(l_right.m_valid, l_right.m_address);
    }
    bool operator > (const IpAddress& l_left, const IpAddress& l_right) {
        return l_right < l_left;
    }
    bool operator <= (const IpAddress& l_left, const IpAddress& l_right) {
        return !(l_right < l_left);
    }
    bool operator >= (const IpAddress& l_left, const IpAddress& l_right) {
        return !(l_left < l_right);
    }

    std::istream& operator >> (std::istream& cin, IpAddress& l_address) {
        std::string str;
        cin >> str;
        l_address = IpAddress(str);
        return cin;
    }
    std::ostream& operator << (std::ostream& cout, const IpAddress& l_address) {
        return cout << l_address.toString();
    }
}
