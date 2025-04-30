project(
  'starter',
  'cpp',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
    'warning_level=3',
    'buildtype=release',
    'strip=true',
  ],
)

#── Subprojects ───────────────────────────────────────────────────────────────#
fmt = subproject('fmt')
fmt_dep = fmt.get_variable('fmt_dep')

toml = subproject('tomlplusplus')
toml_dep = toml.get_variable('tomlplusplus_dep')

subdir('hipo4')

#── ROOT via root-config ─────────────────────────────────────────────────────#
root_incdir   = run_command('root-config', '--incdir', check: true).stdout().strip()
root_libs     = run_command('root-config', '--libs',   check: true).stdout().strip().split()

root_dep = declare_dependency(
  include_directories: include_directories(root_incdir),
  link_args:           root_libs,
)

#── Project sources & include dirs ────────────────────────────────────────────#

inc = include_directories('include')

sources = files(
  'src/Core/Particle.cpp',
  'src/main.cpp',
  'src/study1/Drawing.cpp',
  'src/study1/Reader.cpp',
)

executable(
  meson.project_name(),
  sources,
  include_directories: [inc],
  dependencies: [hipo_dep, fmt_dep, toml_dep, root_dep],
)