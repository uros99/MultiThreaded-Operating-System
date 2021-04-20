# MultiThreaded-Operating-System
This is a primitive, educational, small kernel for multithreaded operating systems with time-sharing wrote in C++. <br>
This is actually subsystem because it runs on already existing operating system of your computer. <br>
To test this system there is a files with test code like: <br>
  *keyevent.cpp* <br>
  *intLock.cpp* <br>
  *bounded.cpp* <br>
  *USER.cpp* <br>
  This test represents a few producers and one consumer communicating through bounded buffer. Producers and consumers are built as threads and thay are synchronized with semaphores whitch I also implemented in this system. <br>
  This system supports:<br>
  **-semaphores** <br>
  **-threads** <br>
  **-events** <br>
  **-interrupt routines** <br>
