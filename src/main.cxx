#include "entry.hxx"
#include <mutex>

int main()
{
  ServerEntry entry;

  entry.set_interval(20);
  entry.set_consumer([](ServerEntry& self) -> void {
    self.packet_queue.semaphore_wait();
   
    //lock the packet queue's mutex to retrieve packet
    auto lock = std::unique_lock(self.packet_queue.mutex);
    auto packet = self.packet_queue.front();
    self.packet_queue.pop();
    lock.unlock();

    //lock udp and send back data
  });

  entry.set_producer([](ServerEntry& self) -> void {
    auto lock = std::unique_lock(self.socket.mutex);
    
    auto packet = self.receive_packet();
    //if (!packet->valid()) {
    //  logger::error("client tried to send an invalid packet");
    //  return;
    //}
    
    lock.unlock();
    lock = std::unique_lock(self.packet_queue.mutex);
    //TODO:: process this packet and then push it do visitor pattern on packet header 
    //and then promote it to another packet class instance
    self.packet_queue.push(packet);
    lock.unlock();
    self.packet_queue.semaphore_inc();
  });
  
  return 0;
}
