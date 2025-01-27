#pragma once

#include <cstdint>
#include <functional>
#include <mutex>
#include <queue>
#include <semaphore>
#include <thread>
#include <vector>
#include <string>

#include "logger.hxx"
#include "packet.hxx"
#include "udp.hxx"

using
std::vector,
std::thread,
std::mutex,
std::queue,
std::counting_semaphore,
std::function;

class PacketQueue {
  counting_semaphore m_sema;
  queue<Packet*> m_queue;
public:
  mutex mutex;
  void pop() { m_queue.pop(); }
  void push(Packet* p) { m_queue.push(p); }
  size_t size() { return m_queue.size(); }
  void semaphore_inc() { m_sema.release(); }
  void semaphore_wait() { m_sema.acquire(); }
};

class ServerEntry {
  UdpSocket m_udp;
  int m_nb_threads;
  vector<thread> m_workers;
  function<void(Packet)> m_producer;
  function<void(Packet)> m_consumer;
public:
  PacketQueue packet_queue;
  Packet* receive_packet();
  void set_interval(int ms);
  void set_producer(function<void(ServerEntry&)> producer);
  void set_consumer(function<void(ServerEntry&)> consumer);
  ServerEntry(int nb_threads, int port, int buff_size = 1024) : m_udp(UdpSocket(buff_size)), m_nb_threads(nb_threads) {}
  void start();
};
