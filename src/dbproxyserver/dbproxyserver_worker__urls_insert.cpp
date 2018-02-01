/*
 * dbproxyserverworker.cpp
 *
 *      Author: alper
 */

#include <condition_variable>
#include "dbproxyserver_worker__urls_insert.h"
#include "urls__insert_job.h"

using namespace std;

extern urls__insert_job<extract_link_type> urls__insert__accessor;

// This condition variable  prevents worker threads from digging for jobs in while loop. (accepts job on-demand)
std::mutex mutex__urls_insert;
std::condition_variable cond_variable__urls_insert;

void* start_dbproxyserver_worker__urls_insert(void* arg)
{
  int key = 0;
  vector<extract_link_type> data;
  dbproxyserver_worker__urls_insert<extract_link_type> dbpWorker__urls_insert;

  while(true)
    {
      {
	std::unique_lock<std::mutex> lock__urls_insert(mutex__urls_insert);
	cond_variable__urls_insert.wait(lock__urls_insert);
      }

      // data.clear(); // data is not cleared due to performance reasons
      key = urls__insert__accessor.pull_job(data);

      if(key == -1)
	{
	  // TODO: Switch to logger
	  cout << "No job exists currently: " << endl;
	}
      else
	{
	  dbpWorker__urls_insert.action(key, data);
	}
    }

  return 0;
}
