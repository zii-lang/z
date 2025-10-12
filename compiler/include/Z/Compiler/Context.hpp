#ifndef Z_COMPILER_CONTEXT_HPP
#define Z_COMPILER_CONTEXT_HPP

#include <Z/ZConfig.hpp>

#include <string>
#include <unordered_map>

namespace Z::Compiler {
struct CompilerContext {
  std::string host;
  std::string target;
  std::string version;
  mutable std::unordered_map<std::string, std::string> defines = {};

  bool isDefined(const std::string &name) const noexcept {
#if Z_CPP_STANDARD >= 20
    if (defines.contains(name))
      return true;
#else
    if (defines.find(name) != defines.end())
      return true;
#endif
    if (std::getenv(name.c_str()))
      return true;

    return false;
  }

  std::string getDefine(const std::string &name) const noexcept {
    auto it = defines.find(name);
    if (it != defines.end())
      return it->second;

    if (const char *env = std::getenv(name.c_str()))
      return std::string(env);

    return nullptr;
  }

  void setDefine(const std::string &name,
                 const std::string &value = "1") const noexcept {
    defines[name] = value;
  }

  CompilerContext() {}
};

}; // namespace Z::Compiler

#endif
