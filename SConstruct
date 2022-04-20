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
Import('atEnv')

# Create a build environment for the ARM9 based netX chips.
env_arm9 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.7', 'asciidoc'])
env_arm9.CreateCompilerEnv('NETX500', ['arch=armv5te'])
env_arm9.CreateCompilerEnv('NETX56', ['arch=armv5te'])
env_arm9.CreateCompilerEnv('NETX50', ['arch=armv5te'])
env_arm9.CreateCompilerEnv('NETX10', ['arch=armv5te'])

# Create a build environment for the Cortex-R7 and Cortex-A9 based netX chips.
env_cortexR7 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.9', 'asciidoc'])
env_cortexR7.CreateCompilerEnv('NETX4000_RELAXED', ['arch=armv7', 'thumb'], ['arch=armv7-r', 'thumb'])

# Create a build environment for the Cortex-M4 based netX chips.
env_cortexM4 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.9', 'asciidoc'])
env_cortexM4.CreateCompilerEnv('NETX90_MPW', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])
env_cortexM4.CreateCompilerEnv('NETX90_MPW_APP', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])
env_cortexM4.CreateCompilerEnv('NETX90', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])

# Build the platform libraries.
SConscript('platform/SConscript')


#----------------------------------------------------------------------------
#
# Get the source code version from the VCS.
#
atEnv.DEFAULT.Version('#targets/version/version.h', 'templates/version.h')


#----------------------------------------------------------------------------
# This is the list of sources. The elements must be separated with whitespace
# (i.e. spaces, tabs, newlines). The amount of whitespace does not matter.
sources = """
	src/hboot_dpm.c
	src/header.c
	src/init.S
	src/main.c
"""

sources_netx90_app = """
	src/hboot_dpm.c
	src/header.c
	src/init.S
	src/main.c
	src/netx90/app_hboot_header_iflash.c
	src/netx90/cm4_app_vector_table_iflash.c
"""

sources_netx90_com_led = """
	src/hboot_dpm.c
	src/header.c
	src/init.S
	src/main_com_led.c
	src/netx90/comled.c
"""

sources_netx4000_ca9 = """
	src/netx4000/portcontrol.c
"""

# special files for netX 4000 bootup
sources_cr7_openfirewalls = """
	src/netx4000/cr7_open_netx4000_firewalls.S
"""

#----------------------------------------------------------------------------
#
# Build all files.
#

# The list of include folders. Here it is used for all files.
astrIncludePaths = ['src', '#platform/src', '#platform/src/lib', '#targets/version']


# Blinki for the netX90 communication CPU.
env_netx90_com_intram = atEnv.NETX90.Clone()
env_netx90_com_intram.Append(CPPPATH = astrIncludePaths)
env_netx90_com_intram.Replace(LDFILE = 'src/netx90/netx90_com_intram.ld')
src_netx90_com_intram = env_netx90_com_intram.SetBuildPath('targets/netx90_return_com_intram', 'src', sources)
elf_netx90_com_intram = env_netx90_com_intram.Elf('targets/netx90_return_com_intram/blinki_return_netx90_com_intram.elf', src_netx90_com_intram + env_netx90_com_intram['PLATFORM_LIBRARY'])
bin_netx90_com_intram = env_netx90_com_intram.ObjCopy('targets/netx90_return_com_intram/blinki_return_netx90_com_intram.bin', elf_netx90_com_intram)
txt_netx90_com_intram = env_netx90_com_intram.ObjDump('targets/netx90_return_com_intram/blinki_return_netx90_com_intram.txt', elf_netx90_com_intram, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
bb0_netx90_com_intram = env_netx90_com_intram.HBootImage('targets/blinki_return_netx90_com_intram.bin', 'src/netx90/COM_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_com_intram}))

