#pragma once

#include <string>
namespace windowing {
namespace common {
struct FileDropEventsArgs {
  FileDropEventsArgs(std::string paths[]) : Filenames(paths) {}
  std::string *Filenames;
};
} // namespace common
} // namespace windowing
