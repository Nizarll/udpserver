#pragma once

#include <cstddef>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>

enum class PacketType : uint32_t
{
  INVALID,
  DEMAND_CON,
  ACK,
  PLAYER_CON,
  PLAYER_DISCON,
  PLAYER_MOV,
};

class Packet {
  uint32_t m_type;
  std::vector<uint8_t> m_bytes;
public:
  void serialize_header(PacketType type);
  virtual void serialize() = 0;
  virtual Packet deserialize() = 0;
  virtual std::string to_string() const = 0;
  friend std::ostream& operator << (std::ostream& os, const Packet& packet)
  {
    std::cout << "Packet: " << packet.to_string();
    return os;
  }

  template <typename T>
  friend Packet& operator << (Packet& packet, const T& data)
  {
    static_assert(std::is_standard_layout<T>::value, "Can only serialize basic data types");
    
    size_t size = packet.m_bytes.size();
    packet.m_bytes.resize(packet.m_bytes.size() + sizeof(data));
    std::memcpy(packet.m_bytes.data() + size, &data, sizeof(T));
    return packet;
  }
}

