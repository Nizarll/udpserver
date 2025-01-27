#include "udp.hxx"

void UdpSocket::open_serv()
{
  m_sock = socket(AF_INET, SOCK_DGRAM, 0);
  sockaddr_in m_addr;
  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons(m_port);
}

void UdpSocket::close_serv()
{
  close(m_sock);
}

int UdpSocket::receive_data()
{
  int len = sizeof(m_addr);
  return recvfrom(m_sock, m_buffer.data(), m_buffer.size(), 0, (sockaddr *) &m_addr, (socklen_t *) &len);
}
int UdpSocket::send_data(const std::vector<char>& bytes)
{
  int len = sizeof(client);
  return sendto(m_sock, m_buffer.data(), m_buffer.size(), 0, (sockaddr *) &client, len);
}

