# MultiThreaded-Operating-System
This is a primitive, educational, small kernel for multithreaded operating systems with time-sharing wrote in C++.
This is actually subsystem because it runs on already existing operating system of your computer.
To test this system there is a files with test code like:
  *keyevent.cpp*
  *intLock.cpp*
  *bounded.cpp*
  *USER.cpp*
  This test represents a few producers and one consumer communicating through bounded buffer. Producers and consumers are realized as threads and thay are synchronized with semaphores whitch I also implemented in this system.
  This system supports:
  *semaphores*
  *threads*
  *events*
  *interrupt routines*
