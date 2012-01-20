# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------#
#   Copyright (C) 2011 by Christoph Thelen                                #
#   doc_bacardi@users.sourceforge.net                                     #
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program; if not, write to the                         #
#   Free Software Foundation, Inc.,                                       #
#   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
#-------------------------------------------------------------------------#


#----------------------------------------------------------------------------
#
# Set up the Muhkuh Build System.
#

SConscript('mbs/SConscript')
Import('env_default')

#----------------------------------------------------------------------------
# This is the list of sources. The elements must be separated with whitespace
# (i.e. spaces, tabs, newlines). The amount of whitespace does not matter.
sources_common = """
	src/i2c_hifsta.c
	src/init_netx_test.S
	src/main.c
	src/systime.c
	src/uart.c
	src/uprintf.c
"""


sources_custom_netx500 = """
	src/netx500/netx500_io_areas.c
"""


sources_custom_netx50 = """
	src/netx50/netx50_io_areas.c
"""


sources_custom_netx10 = """
	src/netx10/netx10_io_areas.c
"""


src_netx500 = Split(sources_common+sources_custom_netx500)
src_netx50  = Split(sources_common+sources_custom_netx50)
src_netx10  = Split(sources_common+sources_custom_netx10)

#----------------------------------------------------------------------------
#
# Create the compiler environments.
#

env_default.Append(CPPPATH = ['src'])

env_netx500_default = env_default.CreateCompilerEnv('500', ['cpu=arm926ej-s'])
env_netx500_default.Append(CPPPATH = ['src/netx500'])

env_netx50_default = env_default.CreateCompilerEnv('50', ['cpu=arm966e-s'])
env_netx50_default.Append(CPPPATH = ['src/netx50'])

env_netx10_default = env_default.CreateCompilerEnv('10', ['cpu=arm966e-s'])
env_netx10_default.Append(CPPPATH = ['src/netx10'])


#----------------------------------------------------------------------------
#
# Build all files.
#
env_netx500_intram = env_netx500_default.Clone()
env_netx500_intram.Replace(LDFILE = 'src/netx500/netx500_intram.ld')
src_netx500_intram = env_netx500_intram.SetBuildPath('targets/netx500_intram', 'src', src_netx500)
elf_netx500_intram = env_netx500_intram.Elf('targets/netx500_intram', src_netx500_intram)
bb0_netx500_intram = env_netx500_intram.BootBlock('targets/mmc/netx500/netx.rom', elf_netx500_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')

env_netx50_intram = env_netx50_default.Clone()
env_netx50_intram.Replace(LDFILE = 'src/netx50/netx50_intram.ld')
src_netx50_intram = env_netx50_intram.SetBuildPath('targets/netx50_intram', 'src', src_netx50)
elf_netx50_intram = env_netx50_intram.Elf('targets/netx50_intram', src_netx50_intram)
bb0_netx50_intram = env_netx50_intram.BootBlock('targets/mmc/netx50/netx.rom', elf_netx50_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')

env_netx10_intram = env_netx10_default.Clone()
env_netx10_intram.Replace(LDFILE = 'src/netx10/netx10_intram.ld')
src_netx10_intram = env_netx10_intram.SetBuildPath('targets/netx10_intram', 'src', src_netx10)
elf_netx10_intram = env_netx10_intram.Elf('targets/netx10_intram', src_netx10_intram)
bin_netx10_intram = env_netx10_intram.ObjCopy('targets/netx10_intram', elf_netx10_intram)
uue_netx10_intram = env_netx10_intram.UUEncode('targets/netx10_intram_uue.txt', bin_netx10_intram, UUE_PRE="L ${LOAD_HEX}\n", UUE_POST='g ${EXEC_HEX} 0', UUE_ELF=elf_netx10_intram)
bb0_netx10_intram = env_netx10_intram.BootBlock('targets/mmc/netx10/netx.rom', elf_netx10_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')

env_netx10_sqixip = env_netx10_default.Clone()
env_netx10_sqixip.Replace(LDFILE = 'src/netx10/netx10_sqixip.ld')
src_netx10_sqixip = env_netx10_sqixip.SetBuildPath('targets/netx10_sqixip', 'src', src_netx10)
elf_netx10_sqixip = env_netx10_sqixip.Elf('targets/netx10_sqixip', src_netx10_sqixip)
bin_netx10_sqixip = env_netx10_sqixip.ObjCopy('targets/netx10_sqixip', elf_netx10_sqixip)
