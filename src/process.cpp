#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// done: Return this process's ID
int Process::Pid() { return pid; }
// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  long total_time = LinuxParser::ActiveJiffies(pid);
  long seconds = this->Process::UpTime();
  long total_time_seconds = total_time / sysconf(_SC_CLK_TCK);
  CPUUtil_ = (float)total_time_seconds / seconds;
  return CPUUtil_;
}
// done: Return the command that generated this process
string Process::Command() {
  Command_ = LinuxParser::Command(pid);
  return Command_;
}
// done: Return this process's memory utilization
string Process::Ram() {
  long temp = std::stol(LinuxParser::Ram(pid));
  temp /= 1024;
  RAMUtil_ = to_string(temp);
  return RAMUtil_;
}
// done: Return the user (name) that generated this process
string Process::User() {
  User_ = LinuxParser::User(pid);
  return User_;
}
// done: Return the age of this process (in seconds)
long int Process::UpTime() {
  Uptime_ =
      LinuxParser::UpTime() - (LinuxParser::UpTime(pid) / sysconf(_SC_CLK_TCK));
  return Uptime_;
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return CPUUtil_ > a.CPUUtil_;
}