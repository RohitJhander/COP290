/**
 * \class Thread
 */
#ifndef THR_H_INCLUDED
#define THR_H_INCLUDED

#include <pthread.h>

///Class to be inherited by MyThread
class Thread
{
  public:
    ///Constructor
    Thread();
    ///Destructor
    ~Thread();

    ///creates a thread and calls run() method
    int start();
    ///joins the thread
    int join();
    ///detaches the thread
    int detach();
    ///return thread Id
    pthread_t self();
    
    //must be overridden by child classed
    virtual void* run() = 0;
    
  private:
    pthread_t  m_tid;           ///<thread
    int        m_running;       ///<running status of thread
    int        m_detached;      ///<detach status of thread
};

#endif
