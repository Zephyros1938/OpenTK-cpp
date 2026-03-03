#pragma once

#include <string>

namespace OpenTK::Windowing::Common {
struct FileDropEventsArgs {
  FileDropEventsArgs(std::string paths[]) : Filenames(paths) {}
  std::string *Filenames;
};
} // namespace OpenTK::windowing::common
