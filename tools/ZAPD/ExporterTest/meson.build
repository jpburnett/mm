
exporter_srcs = ['CollisionExporter.cpp', 'RoomExporter.cpp', 'TextureExporter.cpp', 'Main.cpp']

libExporterTest = static_library('ExporterTest',
  sources: exporter_srcs,
  # note: can ZAPD and tinyxml2 includes be convereted to objects? This will
  # depend on the `subdir()` run structure and resolving "who runs first"
  include_directories: [zapd_utils_inc, '../ZAPD', '../lib/tinyxml2'],
  cpp_args:['-Wextra', '-std=c++17'])
