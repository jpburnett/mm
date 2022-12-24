
# TODO much of the build targets in the project are placed into a static
# "build/" location will this break later scripts? Particularly the python ones?
# In z64compress here it wants the o/($TARGET) directory. How necessary is
# this?

# TODO add this NATIVE_OPT as an option
# Whether to use native optimizations, specify with NATIVE_OPT=0/1 on the command line, default is 0.
# This is not supported by all compilers which is particularly an issue on Mac, and may inhibit tests.
# NATIVE_OPT ?= 0
# ifeq ($(NATIVE_OPT),1)
# 	TARGET_CFLAGS += -march=native -mtune=native
# endif


threads_dep = dependency('threads')
#TODO -lm already a dependency in a lower down meson.build but is needed here,
# should pull all dependencies into top-level meson.build

z64_c_args = ['-DNDEBUG', '-s', '-Os', '-flto']
z64compress_srcs = ['src/main.c',
  'src/n64crc.c',
  'src/rom.c',
  'src/sha1.c',
  'src/wow.c']

enc_c_args = ['-DNDEBUG', '-s', '-Ofast', '-flto']
enc_src = [
  'src/enc/aplib.c',
  'src/enc/lzo.c',
  'src/enc/ucl.c',
  'src/enc/yar.c',
  'src/enc/yaz.c',
  'src/enc/zx7.c',
  'src/enc/ucl/n2b_d.c',
  'src/enc/ucl/comp/n2b_99.c',
  'src/enc/apultra/apultra.c',
  'src/enc/apultra/divsufsort.c',
  'src/enc/apultra/expand.c',
  'src/enc/apultra/matchfinder.c',
  'src/enc/apultra/shrink.c',
  'src/enc/apultra/shrink_context.c',
  'src/enc/apultra/sssort.c',
  'src/enc/apultra/trsort.c',
  'src/enc/lzo/lzo1x_1.c',
  'src/enc/lzo/lzo1x_9x.c',
  'src/enc/lzo/lzo1x_d1.c',
  'src/enc/lzo/lzo1x_d2.c',
  'src/enc/lzo/lzo1x_d3.c',
  'src/enc/lzo/lzo_ptr.c']

# The original make file had this recipe
#    $(OBJ_DIR)/src/enc/%.o: CFLAGS := -DNDEBUG -s -Ofast -flto -Wall
# which should just change the CFLAGS for sources at and after enc/* in the
# generated list. To do that here, a static library is made with those arguments
z64compress_enc_lib = static_library('z64compress_enc', enc_src,
c_args:enc_c_args)

executable('z64compress', z64compress_srcs,
  c_args: z64_c_args,
  link_with: z64compress_enc_lib,
  dependencies: [m_dep, threads_dep])
