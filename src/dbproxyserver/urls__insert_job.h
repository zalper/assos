/*
 * urls__insert_job.h
 *
 * Author: alper
 */

#ifndef DBPROXYSERVER_URLS__INSERT_JOB_H_
#define DBPROXYSERVER_URLS__INSERT_JOB_H_

#include <cassert>
#include <mutex>
#include <map>
#include "Ijob_queue.h"

extern std::mutex urls__insert__accessor_mutex;

template <typename T>
class urls__insert_job : Ijob_queue<std::extract_link_type>
{
public:
  urls__insert_job<T>(){}
  virtual ~urls__insert_job<T> (){}

/**
 * Pull job from job list and remove it from list
 * @param data	:	copy of value
 * @return key	: 	-1: No job available, other: job key
 */
  int pull_job(std::vector<std::extract_link_type> &data)
  {
    std::lock_guard<std::mutex> guard(urls__insert__accessor_mutex);

    if(jobs.size() == 0)
      {
	return -1;
      }

    data.clear();

    std::map<int, std::vector<std::extract_link_type>>::iterator it = jobs.begin();
    int key = it->first;
    data = it->second;

    jobs.erase(it);

    return key;
}

/**
 * Add job into job list
 * TODO: Return different error states, data null, empty, already has, etc
 * @param key
 * @param data
 * @return true: Success, false: Already has this job
 */
  bool add_job(int key, std::vector<std::extract_link_type> data)
  {
    assert( !data.empty() );

    std::lock_guard<std::mutex> guard(urls__insert__accessor_mutex);

    std::pair<std::map<int, std::vector<std::extract_link_type>>::iterator,bool> return_val = jobs.insert(std::make_pair(key, data));

    return return_val.second;
  }

  unsigned int get_job_count()
  {
    std::lock_guard<std::mutex> guard(urls__insert__accessor_mutex);

    return jobs.size();
  }

  bool is_key_exist(int key)
  {
    std::lock_guard<std::mutex> guard(urls__insert__accessor_mutex);

    return (jobs.find(key) != jobs.end());
  }

private:
  // Concurrent operations are protected by global mutex
  // int key, vector<T> job data
  std::map <int, std::vector<std::extract_link_type>> jobs;
};

#endif /* DBPROXYSERVER_URLS__INSERT_JOB_H_ */
