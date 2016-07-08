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

# Create a build environment for the ARM9 based netX chips.
env_arm9 = env_default.CreateEnvironment(['gcc-arm-none-eabi-4.7', 'asciidoc'])

# Create a build environment for the Cortex-R based netX chips.
env_cortex7 = env_default.CreateEnvironment(['gcc-arm-none-eabi-4.9', 'asciidoc'])


#----------------------------------------------------------------------------
#
# Create the compiler environments.
#
astrIncludePaths = ['src', '#platform/src', '#platform/src/lib', '#targets/version']


env_netx4000_default = env_cortex7.CreateCompilerEnv('4000', ['arch=armv7', 'thumb'], ['arch=armv7-r', 'thumb'])
env_netx4000_default.Append(CPPPATH = astrIncludePaths)
env_netx4000_default.Replace(BOOTBLOCK_CHIPTYPE = 4000)

env_netx500_default = env_arm9.CreateCompilerEnv('500', ['arch=armv5te'])
env_netx500_default.Append(CPPPATH = astrIncludePaths)
env_netx500_default.Replace(BOOTBLOCK_CHIPTYPE = 500)

env_netx56_default = env_arm9.CreateCompilerEnv('56', ['arch=armv5te'])
env_netx56_default.Append(CPPPATH = astrIncludePaths)
env_netx56_default.Replace(BOOTBLOCK_CHIPTYPE = 56)

env_netx50_default = env_arm9.CreateCompilerEnv('50', ['arch=armv5te'])
env_netx50_default.Append(CPPPATH = astrIncludePaths)
env_netx50_default.Replace(BOOTBLOCK_CHIPTYPE = 50)

env_netx10_default = env_arm9.CreateCompilerEnv('10', ['arch=armv5te'])
env_netx10_default.Append(CPPPATH = astrIncludePaths)
env_netx10_default.Replace(BOOTBLOCK_CHIPTYPE = 10)

Export('env_netx4000_default', 'env_netx500_default', 'env_netx56_default', 'env_netx50_default', 'env_netx10_default')


#----------------------------------------------------------------------------
#
# Get the source code version from the VCS.
#
env_default.Version('#targets/version/version.h', 'templates/version.h')


#----------------------------------------------------------------------------
#
# Build the platform libraries.
#
PLATFORM_LIB_CFG_BUILDS = [4000]
SConscript('platform/SConscript', exports='PLATFORM_LIB_CFG_BUILDS')
Import('platform_lib_netx4000')


#----------------------------------------------------------------------------
# This is the list of sources. The elements must be separated with whitespace
# (i.e. spaces, tabs, newlines). The amount of whitespace does not matter.
sources = """
	src/header.c
	src/init_netx_test.S
	src/main.c
"""

# special files for netX 4000 bootup
sources_cr7_openfirewalls = """
	src/netX4000/cr7_open_netx4000_firewalls.S
"""

sources_cr7_EndlessLoop = """
	src/netX4000/cr7_EndlessLoop.S
"""

#----------------------------------------------------------------------------
#
# Build all files.
#
# open firewalls from RAP into netX area at netX 4000
env_netx4000_cr7_openfirewalls = env_netx4000_default.Clone()
env_netx4000_cr7_openfirewalls.Replace(LDFILE = 'src/netx4000/netx4000_cr7_intram.ld')
src_netx4000_cr7_openfirewalls = env_netx4000_cr7_openfirewalls.SetBuildPath('targets/netx4000_intram', 'src', sources_cr7_openfirewalls)
elf_netx4000_cr7_openfirewalls = env_netx4000_cr7_openfirewalls.Elf('targets/netx4000_intram/netx4000_cr7_openfirewalls.elf', src_netx4000_cr7_openfirewalls + platform_lib_netx4000)
txt_netx4000_cr7_openfirewalls = env_netx4000_cr7_openfirewalls.ObjDump('targets/netx4000_intram/netx4000_cr7_openfirewalls.txt', elf_netx4000_cr7_openfirewalls, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

# Endless loop required for CR7, if only CA9 needs to be started.
env_netx4000_cr7_EndlessLoop = env_netx4000_default.Clone()
env_netx4000_cr7_EndlessLoop.Replace(LDFILE = 'src/netx4000/netx4000_cr7_intram.ld')
src_netx4000_cr7_EndlessLoop = env_netx4000_cr7_EndlessLoop.SetBuildPath('targets/netx4000_intram', 'src', sources_cr7_EndlessLoop)
elf_netx4000_cr7_EndlessLoop = env_netx4000_cr7_EndlessLoop.Elf('targets/netx4000_intram/netx4000_cr7_EndlessLoop.elf', src_netx4000_cr7_EndlessLoop + platform_lib_netx4000)
txt_netx4000_cr7_EndlessLoop = env_netx4000_cr7_EndlessLoop.ObjDump('targets/netx4000_intram/netx4000_cr7_EndlessLoop.txt', elf_netx4000_cr7_EndlessLoop, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

# Blinki programm for cortex CPUs
env_netx4000_blinki_intram = env_netx4000_default.Clone()
env_netx4000_blinki_intram.Replace(LDFILE = 'src/netx4000/netx4000_ca9_intram.ld')
src_netx4000_blinki_intram = env_netx4000_blinki_intram.SetBuildPath('targets/netx4000_intram', 'src', sources)
elf_netx4000_blinki_intram = env_netx4000_blinki_intram.Elf('targets/netx4000_intram/netx4000_blinki_intram.elf', src_netx4000_blinki_intram + platform_lib_netx4000)
txt_netx4000_blinki_intram = env_netx4000_blinki_intram.ObjDump('targets/netx4000_intram/netx4000_blinki_intram.txt', elf_netx4000_blinki_intram, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

# Build 3 hboot images to be loaded into netX 4000
# hboot image: RUN blinki at CR7
bb0_netx4000_intram = env_netx4000_blinki_intram.HBootImage('targets/blinki_netx4000_cr7_spi_intram.bin', 'src/netx4000/CR7_to_INTRAM.xml', KNOWN_FILES=dict({'tElfCR7': elf_netx4000_blinki_intram[0]}))

# hboot image: open firewalls from RAP into netX area; RUN blinki at CR9 core 0; keep CR7 inside endless loop
bb1_netx4000_intram = env_netx4000_blinki_intram.HBootImage('targets/blinki_netx4000_ca9core0_spi_intram.bin', 'src/netx4000/CA9core0_to_INTRAM.xml', KNOWN_FILES=dict({'tElfCR7OpenFirewalls': elf_netx4000_cr7_openfirewalls[0], 'tElfCA9core0': elf_netx4000_blinki_intram[0], 'tElfCR7': elf_netx4000_cr7_EndlessLoop[0]}))

# hboot image: open firewalls from RAP into netX area; RUN blinki at CR9 core 1; keep CR7 inside endless loop
bb2_netx4000_intram = env_netx4000_blinki_intram.HBootImage('targets/blinki_netx4000_ca9core1_spi_intram.bin', 'src/netx4000/CA9core1_to_INTRAM.xml', KNOWN_FILES=dict({'tElfCR7OpenFirewalls': elf_netx4000_cr7_openfirewalls[0], 'tElfCA9core1': elf_netx4000_blinki_intram[0], 'tElfCR7': elf_netx4000_cr7_EndlessLoop[0]}))


#bb5_netx4000_intram = env_netx4000_ca9_intram.HBootImage('targets/mmc/netx4000/netx.rom', 'src/netx4000/DEFAULT_to_INTRAM.xml', KNOWN_FILES=dict({'tElfCR7': elf_netx4000_cr7_intram[0], 'tElfCA9': elf_netx4000_ca9_intram[0]}))
#bb1_netx4000_intram = env_netx4000_intram.HBootImage('targets/blinki_netx4000_spi_intram.bin', 'src/netx4000/DEFAULT_to_INTRAM.xml', KNOWN_FILES=dict({'tElf': elf_netx4000_intram[0]}))

