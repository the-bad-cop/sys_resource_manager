#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  Process(int p) : pid(p) {}
  // TODO: Declare any necessary private members
 private:
  int pid;
  std::string User_;
  std::string Command_;
  float CPUUtil_;
  std::string RAMUtil_;
  long Uptime_;
  // long prev_total_time_seconds = 0;
  // long prev_seconds;

  long prevTotJiffies = 0;
  long prevProcJiffies = 0;
  long TotJiffies;
  long ProcJiffies;
};

#endif