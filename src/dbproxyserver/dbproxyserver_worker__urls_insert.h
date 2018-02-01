/*
 *
 * dbproxyserver_worker__urls_insert.h
 *      Author: alper
 */

#ifndef DBPROXYSERVER_DBPROXYSERVER_WORKER__URLS_INSERT_H_
#define DBPROXYSERVER_DBPROXYSERVER_WORKER__URLS_INSERT_H_

#include <iostream>

#include "IworkerTask.h"

void* start_dbproxyserver_worker__urls_insert(void* arg);

namespace std
{

// TODO: Move this struct to common types header file
typedef struct
{
  string raw;
  string url;
  string url_without_protocol;
  string host;
  string hash;
  int protocol;
  bool valid;
} extract_link_type;

template <typename T>
class dbproxyserver_worker__urls_insert : IworkerTask<extract_link_type>
{
public:
  dbproxyserver_worker__urls_insert (){}

  virtual ~dbproxyserver_worker__urls_insert (){}

  void action(int key, vector<extract_link_type> &data)
  {
    // Put here your own implementation, do something with data

    // Demo: Print out contents of data packet
    cout << "Barrel: " << key << " has elements: " << data.size() << endl;

    for(extract_link_type &element : data)
      {
	cout << element.hash << endl;
      }

    cout << "End of record dump" << endl;
  }
};

} // End of namespace

#endif /* DBPROXYSERVER_DBPROXYSERVER_WORKER__URLS_INSERT_H_ */
