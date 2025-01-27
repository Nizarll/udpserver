#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class UdpSocket {
  int m_sock;
  int m_port;
  sockaddr_in m_addr;
  std::vector<char> m_buffer;
public:
  sockaddr_in client;
  UdpSocket(int port, int buff_size = 1024) : m_port(port) { m_buffer.reserve(buff_size); }
  ~UdpSocket() { close_serv(); }
  void open_serv();
  void close_serv();
  int receive_data();
  int send_data(const std::vector<char>& bytes);
};

