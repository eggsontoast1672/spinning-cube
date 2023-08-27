#pragma once

#include <string>

#include "spinning-cube/types.hpp"

class Shader {
public:
  Shader(const char *vertex_path, const char *fragment_path);

  void bind() const;
  void set_uniform(const char *name, float value) const;

private:
  uint m_id;

  static constexpr std::size_t log_size = 512;

  static uint create_shader(uint type, const char *source);
  static uint create_program(uint vertex_shader, uint fragment_shader);
  static std::string load_shader_source(const char *path);
};
