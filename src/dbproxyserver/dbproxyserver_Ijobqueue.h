/*
 * dbproxyserver_Ijobqueue.h
 *
 * Author: alper
 */

#ifndef DBPROXYSERVER_IJOB_QUEUE_H_
#define DBPROXYSERVER_IJOB_QUEUE_H_

template <typename T>
class Ijob_queue
{
public:
  Ijob_queue<T> (){}
  virtual ~Ijob_queue<T>(){}
};

#endif /* DBPROXYSERVER_IJOB_QUEUE_H_ */
