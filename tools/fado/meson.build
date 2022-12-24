# TODO add these flags
#ifneq ($(ASAN),0)
#  CFLAGS    += -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined
#endif

# TODO add this define 
#ifneq ($(EXPERIMENTAL),0)
#  CFLAGS    += -DEXPERIMENTAL
#endif

# TODO add this check 
## GCC is too stupid to be trusted with these warnings
#ifeq ($(CC),gcc)
#  WARNINGS += -Wno-implicit-fallthrough -Wno-maybe-uninitialized
#endif

fado_c_args = ['-std=c11', '-Wpedantic', '-Wshadow', '-Werror=implicit-function-declaration', '-Wvla', '-Wno-unused-function']

if get_option('buildtype') == 'debug'
  fado_c_args += '-DDEGBU_ON'
endif

fado_src_inc_dir = include_directories('./include')
fado_fairy_inc_dir = include_directories('./lib')

fado_srcs = ['./src/fado.c', './src/help.c', './src/main.c', './src/mido.c']#, 'version.inc']
fairy_srcs = ['./lib/fairy/fairy.c', './lib/fairy/fairy_print.c']
vc_vec_srcs = ['./lib/vc_vector/vc_vector.c']

executable('fado.elf', [fado_srcs, fairy_srcs, vc_vec_srcs],
  include_directories: [fado_src_inc_dir, fado_fairy_inc_dir],
  c_args: fado_c_args )


