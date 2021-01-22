# MultiThreaded-Operating-System
This is a primitive, educational, small kernel for multithreaded operating systems with time-sharing wrote in C++.
This is actually subsystem because it runs on already existing operating system of your computer.
To test this system there is a files with test code like:
  *keyevent.cpp 1*
  *intLock.cpp 2*
  *bounded.cpp 3*
  *USER.cpp 4*
  This test represents a few producers and one consumer communicating through bounded buffer. Producers and consumers are realized as threads and thay are synchronized with semaphores whitch I also implemented in this system.
  This system supports:
  *semaphores 1*
  *threads 2*
  *events 3*
  *interrupt routines 4*
