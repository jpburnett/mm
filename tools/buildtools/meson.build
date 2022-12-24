c_args = ['-pedantic', '-std=c99']

elf2rom_srcs      = ['elf2rom.c', 'elf32.c', 'n64chksum.c', 'util.c']
makeromfs_srcs    = ['makeromfs.c', 'n64chksum.c', 'util.c']
mkldscript_srcs   = ['mkldscript.c', 'spec.c', 'util.c']
reloc_prereq_srcs = ['reloc_prereq.c', 'spec.c', 'util.c']
yaz0_srcs         = ['yaz0tool.c', 'yaz0.c', 'util.c']

executable('elf2rom', elf2rom_srcs,
  c_args: c_args)
executable('makeromfs', makeromfs_srcs,
  c_args: c_args)
executable('mkldscript', mkldscript_srcs,
  c_args: c_args)
executable('reloc_prereg', reloc_prereq_srcs,
  c_args: c_args)
executable('yaz0', yaz0_srcs,
  c_args: c_args)
