#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return version;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::ifstream memfile(kProcDirectory + kMeminfoFilename);
  if (memfile) {
    string line, key;
    long value;
    getline(memfile, line);
    std::istringstream mem_string(line);
    mem_string >> key >> value;
    long MemTotal = value;
    getline(memfile, line);
    std::istringstream free_str(line);
    free_str >> key >> value;
    long MemFree = value;
    return (float)(MemTotal - MemFree) / MemTotal;
  }
  return 0;
}

// done: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream upfile(kProcDirectory + kUptimeFilename);
  std::string line;
  long uptime;
  if (getline(upfile, line)) {
    std::istringstream upstring(line);
    upstring >> uptime;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  std::ifstream my_file(kProcDirectory + kStatFilename);
  if (my_file) {
    string line;
    getline(my_file, line);
    std::istringstream ajif_string(line);
    string key;
    int temp;
    int kUser_, kNice_, kSystem_, kIRQ_, kSoftIRQ_, kSteal_;
    ajif_string >> key;
    if (key == "cpu") {
      ajif_string >> kUser_ >> kNice_ >> kSystem_;
      ajif_string >> temp >> temp;
      ajif_string >> kIRQ_ >> kSoftIRQ_ >> kSteal_;
    }
    return kUser_ + kNice_ + kSystem_ + kIRQ_ + kSoftIRQ_ + kSteal_;
  }
  return 0;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  std::ifstream my_file(kProcDirectory + kStatFilename);
  if (my_file) {
    string line;
    getline(my_file, line);
    std::istringstream ajif_string(line);
    string key;
    int temp;
    int kIdle_, kIOwait_;
    ajif_string >> key;
    if (key == "cpu") {
      ajif_string >> temp >> temp >> temp;
      ajif_string >> kIdle_ >> kIOwait_;
    }
    return kIdle_ + kIOwait_;
  }
  return 0;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::TotalProcesses() {
  std::ifstream my_file(kProcDirectory + kStatFilename);
  if (my_file) {
    std::string line, key;
    int value;
    while (getline(my_file, line)) {
      std::istringstream my_line(line);
      my_line >> key >> value;
      if (key == "processes") {
        return value;
      }
    }
  }
  return 0;
}

int LinuxParser::RunningProcesses() {
  std::ifstream my_file(kProcDirectory + kStatFilename);
  if (my_file) {
    string line, key;
    int value;
    while (getline(my_file, line)) {
      std::istringstream my_line(line);
      my_line >> key >> value;
      if (key == "procs_running") {
        return value;
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }