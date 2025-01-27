#include "entry.hxx"

void ServerEntry::start()
{
  const int max_threads = std::thread::hardware_concurrency();
  if (max_threads == 0) logger::fatal("could not detect platform\'s core count !");
  if (m_nb_threads >= max_threads) {
    logger::fatal(
      "cannot set the amount of worker threads"
      "to be greater or equal to the amount of cores"
      "consider leaving one core to the operating system !"
      );
  }

  //start udp socket:
  if (m_udp.open() < 0) logger::fatal("failed to open udp socket! maybe port is in use ?");

  //TODO: have some kind of value that checks weither the program is stopped or not ?
  const auto producer_lambda = [](const ServerEntry& entry) -> void () { for (;;) { m_producer(entry); } }
  const auto consumer_lambda = [](const ServerEntry& entry) -> void () { for (;;) { m_consumer(entry); } }
  
  thread _consumer(consumer_lambda, *this);

  for (int i = 0; i < m_nb_threads - 1; i++) {
    std::thread _producer(producer_lambda, *this);
    m_workers.push_back(_producer);
  }

  for (const auto& worker : m_workers) {
    worker.join();
  }
}

void ServerEntry::set_producer(function<void()> producer) { m_producer = producer; }
void ServerEntry::set_consumer(function<void()> consumer) { m_consumer = consumer; }
