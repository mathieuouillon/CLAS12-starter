# dependencies
lz4_minver = '1.9'
lz4_dep = dependency(
  'liblz4',
  method: 'pkg-config',
  version: f'>=@lz4_minver@',
  fallback: ['lz4', 'liblz4_dep'],
)

lz4_preproc_def = '-D__LZ4__'
add_project_arguments(lz4_preproc_def, language: ['cpp'])



hipo_sources = files(
  'bank.cpp',
  'datastream.cpp',
  'dictionary.cpp',
  'event.cpp',
  'fusion.cpp',
  'node.cpp',
  'parser.cpp',
  'reaction.cpp',
  'reader.cpp',
  'record.cpp',
  'recordbuilder.cpp',
  'tuple.cpp',
  'utils.cpp',
  'wrapper.cpp',
  'writer.cpp',
)
hipo_headers = files(
  'bank.h',
  'datastream.h',
  'dictionary.h',
  'event.h',
  'fizika.h',
  'fusion.h',
  'hipoexceptions.h',
  'json.h',
  'jsonutil.h',
  'node.h',
  'parser.h',
  'reaction.h',
  'reader.h',
  'record.h',
  'recordbuilder.h',
  'tuple.h',
  'twig.h',
  'utils.h',
  'writer.h',
)

hipo_lib = library(
  meson.project_name(),
  hipo_sources,
  dependencies: [ lz4_dep ],
  cpp_args: [ # FIXME: fix the warnings; they are suppressed by these args
    '-Wno-sign-compare',
    '-Wno-unused-variable',
    '-Wno-unused-but-set-variable',
    '-Wno-misleading-indentation',
    '-Wno-format',
    '-Wno-stringop-overflow',
    ],
)

hipo_dep = declare_dependency(include_directories : include_directories('.'), link_with : hipo_lib)