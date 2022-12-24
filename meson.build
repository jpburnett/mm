project('mm', 'c', 'cpp')

#CC       := tools/ido_recomp/$(DETECTED_OS)/7.1/cc
#CC_OLD   := tools/ido_recomp/$(DETECTED_OS)/5.3/cc

if host_machine.system() == 'linux'
  sys = 'linux'
elif host_machine.system() == 'darwin'
  sys = 'macos'
elif host_machine.system() == 'windows'
  sys = 'windows'
endif

ido_comp_path = './tools/ido_recomp/@0@/7.1/cc'.format(sys)
ido_comp_old_path = './tools/ido_recomp/@0@/5.3/cc'.format(sys)

message(ido_comp_path)

ido_comp = find_program(ido_comp_path)
ido_comp_old = find_program(ido_comp_old_path)

ELF2ROM    = find_program('./tools/buildtools/elf2rom')
MKLDSCRIPT = find_program('./tools/buildtools/mkldscript')
YAZ0       = find_program('./tools/buildtools/yaz0')
ZAPD       = find_program('./tools/ZAPD/ZAPD.out')
FADO       = find_program('./tools/fado/fado.elf')


#setup
subdir('tools')
#fixbaserom = find_program('./tools/

