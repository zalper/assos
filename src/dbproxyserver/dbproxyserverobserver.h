/*
 * dbproxyserverobserver.h
 *
 *      Author: alper
 */

#ifndef DBPROXYSERVER_DBPROXYSERVEROBSERVER_H_
#define DBPROXYSERVER_DBPROXYSERVEROBSERVER_H_

#include "dbproxyserverstore.h"
#include "dbproxyserver_worker__urls_insert.h"
#include "urls__insert_job.h"

void* start_dbproxyserver_observer(void* arg);

class config_observer
{
public:
  unsigned int visit_delay; // in milliseconds
  unsigned int wait_timeout;
  unsigned int barrel_count;
  unsigned int barrel_capacity;
  unsigned int barrel_threshold;
  unsigned int concurrent_process;
};

class dbproxyserver_observer
{
public:
  dbproxyserver_observer(config_observer& config);
  virtual ~dbproxyserver_observer ();

  void run();
  void trigger_process(int current_barrel);

private:
  config_observer cfg;
  dbproxyserver_store<extract_link_type> *dbpStore[];
};

#endif /* DBPROXYSERVER_DBPROXYSERVEROBSERVER_H_ */
