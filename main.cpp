#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "pgbackend.h"

std::default_random_engine e;
std::uniform_int_distribution<unsigned> u(0, 9);

void testConnection(std::shared_ptr<PGBackend> pgbackend)
{

  unsigned num = u(e);
  unsigned counter = 0;
  auto conn = pgbackend->connection();

  while (true)
  {
    if(counter > num){
      break;
    }
    //std::string demo = "select max(userid) from user_info;";
    std::string demo = "select random();";
    PQsendQuery(conn->connection().get(), demo.c_str());

    while (auto res_ = PQgetResult(conn->connection().get()))
    {
      if (PQresultStatus(res_) == PGRES_TUPLES_OK && PQntuples(res_))
      {
        auto ID = PQgetvalue(res_, 0, 0);
        std::cout  << counter << "/" << num << ": " << std::this_thread::get_id() << " : " << ID <<  std::endl;
      }

      if (PQresultStatus(res_) == PGRES_FATAL_ERROR)
      {
        std::cout << PQresultErrorMessage(res_) << std::endl;
      }

      PQclear(res_);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    counter += 1;
  }

  pgbackend->freeConnection(conn);
}

int main(int argc, const char *argv[])
{
  auto pgbackend = std::make_shared<PGBackend>();

  std::vector<std::shared_ptr<std::thread>> threads;
  for (size_t i = 0; i < 50; i++)
  {
    threads.push_back(std::make_shared<std::thread>(std::thread(testConnection, pgbackend)));
  }

  for (auto &i : threads)
  {
    i.get()->join();
  }
}
