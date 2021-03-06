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

# open firewalls from RAP into netX area at netX 4000
env_netx4000_cr7_openfirewalls = atEnv.NETX4000_RELAXED.Clone()
env_netx4000_cr7_openfirewalls.Append(CPPPATH = astrIncludePaths)
env_netx4000_cr7_openfirewalls.Replace(LDFILE = 'src/netx4000/netx4000_cr7_intram.ld')
src_netx4000_cr7_openfirewalls = env_netx4000_cr7_openfirewalls.SetBuildPath('targets/netx4000_openfirewalls', 'src', sources_cr7_openfirewalls)
elf_netx4000_cr7_openfirewalls = env_netx4000_cr7_openfirewalls.Elf('targets/netx4000_openfirewalls/netx4000_cr7_openfirewalls.elf', src_netx4000_cr7_openfirewalls + env_netx4000_cr7_openfirewalls['PLATFORM_LIBRARY'])
txt_netx4000_cr7_openfirewalls = env_netx4000_cr7_openfirewalls.ObjDump('targets/netx4000_openfirewalls/netx4000_cr7_openfirewalls.txt', elf_netx4000_cr7_openfirewalls, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

# Blinki for the CR7.
env_netx4000_blinki_cr7 = atEnv.NETX4000_RELAXED.Clone()
env_netx4000_blinki_cr7.Append(CPPPATH = astrIncludePaths)
env_netx4000_blinki_cr7.Replace(LDFILE = 'src/netx4000/netx4000_cr7_intram.ld')
src_netx4000_blinki_cr7 = env_netx4000_blinki_cr7.SetBuildPath('targets/netx4000_cr7', 'src', sources)
elf_netx4000_blinki_cr7 = env_netx4000_blinki_cr7.Elf('targets/netx4000_cr7/netx4000_blinki_cr7.elf', src_netx4000_blinki_cr7 + env_netx4000_blinki_cr7['PLATFORM_LIBRARY'])
txt_netx4000_blinki_cr7 = env_netx4000_blinki_cr7.ObjDump('targets/netx4000_cr7/netx4000_blinki_cr7.txt', elf_netx4000_blinki_cr7, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

# Blinki for the CR7/XIP
env_netx4000_blinki_cr7_sqirom = atEnv.NETX4000_RELAXED.Clone()
env_netx4000_blinki_cr7_sqirom.Append(CPPPATH = astrIncludePaths)
env_netx4000_blinki_cr7_sqirom.Replace(LDFILE = 'src/netx4000/netx4000_cr7_sqirom.ld')
src_netx4000_blinki_cr7_sqirom = env_netx4000_blinki_cr7_sqirom.SetBuildPath('targets/netx4000_cr7_sqirom', 'src', sources)
elf_netx4000_blinki_cr7_sqirom = env_netx4000_blinki_cr7_sqirom.Elf('targets/netx4000_cr7_sqirom/netx4000_blinki_cr7_sqirom.elf', src_netx4000_blinki_cr7_sqirom + env_netx4000_blinki_cr7_sqirom['PLATFORM_LIBRARY'])
txt_netx4000_blinki_cr7_sqirom = env_netx4000_blinki_cr7_sqirom.ObjDump('targets/netx4000_cr7_sqirom/netx4000_blinki_cr7_sqirom.txt', elf_netx4000_blinki_cr7_sqirom, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])


# Blinki for one of the CA9 cores.
env_netx4000_blinki_ca9 = atEnv.NETX4000_RELAXED.Clone()
env_netx4000_blinki_ca9.Append(CPPPATH = astrIncludePaths)
env_netx4000_blinki_ca9.Replace(LDFILE = 'src/netx4000/netx4000_ca9_intram.ld')
env_netx4000_blinki_ca9.Append(CPPPATH = ['src/netx4000'])
env_netx4000_blinki_ca9.Append(CPPDEFINES = [['CFG_USE_RAP_UART', '1']])
src_netx4000_blinki_ca9 = env_netx4000_blinki_ca9.SetBuildPath('targets/netx4000_ca9', 'src', sources + sources_netx4000_ca9)
elf_netx4000_blinki_ca9 = env_netx4000_blinki_ca9.Elf('targets/netx4000_ca9/netx4000_blinki_ca9.elf', src_netx4000_blinki_ca9 + env_netx4000_blinki_ca9['PLATFORM_LIBRARY'])
txt_netx4000_blinki_ca9 = env_netx4000_blinki_ca9.ObjDump('targets/netx4000_ca9/netx4000_blinki_ca9.txt', elf_netx4000_blinki_ca9, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

# Build 3 hboot images to be loaded into netX 4000
# hboot image: RUN blinki at CR7
bb0_netx4000_intram = env_netx4000_blinki_cr7.HBootImage('targets/blinki_netx4000_cr7_spi_intram.bin', 'src/netx4000/CR7_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCR7': elf_netx4000_blinki_cr7}))
bb1_netx4000_intram = env_netx4000_blinki_cr7.HBootImage('targets/mmc/netx4000/cr7/netx.rom', 'src/netx4000/CR7_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCR7': elf_netx4000_blinki_cr7}))

# hboot image: open firewalls from RAP into netX area; RUN blinki at CR9 core 0; keep CR7 inside endless loop
bb2_netx4000_intram = env_netx4000_blinki_ca9.HBootImage('targets/blinki_netx4000_ca9core0_spi_intram.bin', 'src/netx4000/CA9core0_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCR7OpenFirewalls': elf_netx4000_cr7_openfirewalls[0], 'tElfCA9core0': elf_netx4000_blinki_ca9}))
bb3_netx4000_intram = env_netx4000_blinki_ca9.HBootImage('targets/mmc/netx4000/ca9core0/netx.rom', 'src/netx4000/CA9core0_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCR7OpenFirewalls': elf_netx4000_cr7_openfirewalls[0], 'tElfCA9core0': elf_netx4000_blinki_ca9}))

# hboot image: open firewalls from RAP into netX area; RUN blinki at CR9 core 1; keep CR7 inside endless loop
bb4_netx4000_intram = env_netx4000_blinki_ca9.HBootImage('targets/blinki_netx4000_ca9core1_spi_intram.bin', 'src/netx4000/CA9core1_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCR7OpenFirewalls': elf_netx4000_cr7_openfirewalls[0], 'tElfCA9core1': elf_netx4000_blinki_ca9}))
bb5_netx4000_intram = env_netx4000_blinki_ca9.HBootImage('targets/mmc/netx4000/ca9core1/netx.rom', 'src/netx4000/CA9core1_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCR7OpenFirewalls': elf_netx4000_cr7_openfirewalls[0], 'tElfCA9core1': elf_netx4000_blinki_ca9}))

# hboot image: run on CR7 from SQIROM
# includes snippet to correct the MPU configuration
bb6_netx4000_sqirom_mpu = env_netx4000_blinki_cr7_sqirom.HBootImage(
	'targets/blinki_netx4000_cr7_mpu_sqirom.bin', 
	'src/netx4000/CR7_to_SQIROM_mpu_sqirom.xml', 
	HBOOTIMAGE_KNOWN_FILES=dict({'tElfCR7': elf_netx4000_blinki_cr7_sqirom}), 
	HBOOTIMAGE_SNIPLIB_SEARCHPATHS=['sniplib'])

env_netx500_intram = atEnv.NETX500.Clone()
env_netx500_intram.Append(CPPPATH = astrIncludePaths)
env_netx500_intram.Replace(LDFILE = 'src/netx500/netx500_intram.ld')
src_netx500_intram = env_netx500_intram.SetBuildPath('targets/netx500_intram', 'src', sources)
elf_netx500_intram = env_netx500_intram.Elf('targets/netx500_intram/netx500_intram.elf', src_netx500_intram + env_netx500_intram['PLATFORM_LIBRARY'])
bb0_netx500_intram = env_netx500_intram.BootBlock('targets/mmc/netx500/netx.rom', elf_netx500_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx500_intram = env_netx500_intram.BootBlock('targets/blinki_netx500_spi_intram.bin', elf_netx500_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

# Blinki for the netX90 MPW communication CPU.
env_netx90_mpw_com_intram = atEnv.NETX90_MPW.Clone()
env_netx90_mpw_com_intram.Append(CPPPATH = astrIncludePaths)
env_netx90_mpw_com_intram.Replace(LDFILE = 'src/netx90/netx90_com_intram.ld')
src_netx90_mpw_com_intram = env_netx90_mpw_com_intram.SetBuildPath('targets/netx90_mpw_com_intram', 'src', sources)
elf_netx90_mpw_com_intram = env_netx90_mpw_com_intram.Elf('targets/netx90_mpw_com_intram/blinki_netx90_mpw_com_intram.elf', src_netx90_mpw_com_intram + env_netx90_mpw_com_intram['PLATFORM_LIBRARY'])
bin_netx90_mpw_com_intram = env_netx90_mpw_com_intram.ObjCopy('targets/netx90_mpw_com_intram/blinki_netx90_mpw_com_intram.bin', elf_netx90_mpw_com_intram)
txt_netx90_mpw_com_intram = env_netx90_mpw_com_intram.ObjDump('targets/netx90_mpw_com_intram/blinki_netx90_mpw_com_intram.txt', elf_netx90_mpw_com_intram, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
bb0_netx90_mpw_com_intram = env_netx90_mpw_com_intram.HBootImage('targets/blinki_netx90_mpw_com_intram.bin', 'src/netx90/COM_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com_intram}))

# Blinki for the netX90 communication CPU.
env_netx90_com_intram = atEnv.NETX90.Clone()
env_netx90_com_intram.Append(CPPPATH = astrIncludePaths)
env_netx90_com_intram.Replace(LDFILE = 'src/netx90/netx90_com_intram.ld')
src_netx90_com_intram = env_netx90_com_intram.SetBuildPath('targets/netx90_com_intram', 'src', sources)
elf_netx90_com_intram = env_netx90_com_intram.Elf('targets/netx90_com_intram/blinki_netx90_com_intram.elf', src_netx90_com_intram + env_netx90_com_intram['PLATFORM_LIBRARY'])
bin_netx90_com_intram = env_netx90_com_intram.ObjCopy('targets/netx90_com_intram/blinki_netx90_com_intram.bin', elf_netx90_com_intram)
txt_netx90_com_intram = env_netx90_com_intram.ObjDump('targets/netx90_com_intram/blinki_netx90_com_intram.txt', elf_netx90_com_intram, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
bb0_netx90_com_intram = env_netx90_com_intram.HBootImage('targets/blinki_netx90_com_intram.bin', 'src/netx90/COM_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_com_intram}))

env_netx90_mpw_com_sqirom = atEnv.NETX90_MPW.Clone()
env_netx90_mpw_com_sqirom.Append(CPPPATH = astrIncludePaths)
env_netx90_mpw_com_sqirom.Replace(LDFILE = 'src/netx90/netx90_com_sqirom.ld')
src_netx90_mpw_com_sqirom = env_netx90_mpw_com_sqirom.SetBuildPath('targets/netx90_mpw_com_sqirom', 'src', sources)
elf_netx90_mpw_com_sqirom = env_netx90_mpw_com_sqirom.Elf('targets/netx90_mpw_com_sqirom/blinki_netx90_mpw_com_sqirom.elf', src_netx90_mpw_com_sqirom + env_netx90_mpw_com_sqirom['PLATFORM_LIBRARY'])
txt_netx90_mpw_com_sqirom = env_netx90_mpw_com_sqirom.ObjDump('targets/netx90_mpw_com_sqirom/blinki_netx90_mpw_com_sqirom.txt', elf_netx90_mpw_com_sqirom, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
bb0_netx90_mpw_com_sqirom = env_netx90_mpw_com_sqirom.HBootImage('targets/blinki_netx90_mpw_com_sqirom.bin', 'src/netx90/COM_SQIROM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com_sqirom}))

# Blinki for the COM0 LED on the netX90 communication CPU.
env_netx90_mpw_com_comled_iflash = atEnv.NETX90_MPW.Clone()
env_netx90_mpw_com_comled_iflash.Append(CPPPATH = astrIncludePaths)
env_netx90_mpw_com_comled_iflash.Replace(LDFILE = 'src/netx90/netx90_com_iflash.ld')
src_netx90_mpw_com_comled_iflash = env_netx90_mpw_com_comled_iflash.SetBuildPath('targets/netx90_mpw_com_comled_iflash', 'src', sources_netx90_com_led)
elf_netx90_mpw_com_comled_iflash = env_netx90_mpw_com_comled_iflash.Elf('targets/netx90_mpw_com_comled_iflash/blinki_netx90_mpw_com_comled_iflash.elf', src_netx90_mpw_com_comled_iflash + env_netx90_mpw_com_comled_iflash['PLATFORM_LIBRARY'])
txt_netx90_mpw_com_comled_iflash = env_netx90_mpw_com_comled_iflash.ObjDump('targets/netx90_mpw_com_comled_iflash/blinki_netx90_mpw_com_comled_iflash.txt', elf_netx90_mpw_com_comled_iflash, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
bb0_netx90_mpw_com_comled_iflash = env_netx90_mpw_com_comled_iflash.HBootImage('targets/blinki_netx90_mpw_com_comled_iflash.bin', 'src/netx90/COM_IFLASH_XIP.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com_comled_iflash}))
bb1_netx90_mpw_com_comled_iflash = env_netx90_mpw_com_comled_iflash.HBootImage('targets/blinki_netx90_mpw_com_comled_iflash_app.bin', 'src/netx90/COM_IFLASH_XIP_ACTIVATE_APP.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com_comled_iflash}))

# Blinki for the COM0 LED on the netX90 communication CPU.
env_netx90_mpw_com_comled_intram = atEnv.NETX90_MPW.Clone()
env_netx90_mpw_com_comled_intram.Append(CPPPATH = astrIncludePaths)
env_netx90_mpw_com_comled_intram.Replace(LDFILE = 'src/netx90/netx90_com_intram.ld')
src_netx90_mpw_com_comled_intram = env_netx90_mpw_com_comled_intram.SetBuildPath('targets/netx90_mpw_com_comled_intram', 'src', sources_netx90_com_led)
elf_netx90_mpw_com_comled_intram = env_netx90_mpw_com_comled_intram.Elf('targets/netx90_mpw_com_comled_intram/blinki_netx90_mpw_com_comled_intram.elf', src_netx90_mpw_com_comled_intram + env_netx90_mpw_com_comled_intram['PLATFORM_LIBRARY'])
txt_netx90_mpw_com_comled_intram = env_netx90_mpw_com_comled_intram.ObjDump('targets/netx90_mpw_com_comled_intram/blinki_netx90_mpw_com_comled_intram.txt', elf_netx90_mpw_com_comled_intram, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
bb0_netx90_mpw_com_comled_intram = env_netx90_mpw_com_comled_intram.HBootImage('targets/blinki_netx90_mpw_com_comled_intram.bin', 'src/netx90/COM_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com_comled_intram}))

# A large boot image with a 512 KB SKIP chunk at the beginning that starts the APP CPU and then loads a COM LED blinki for the COM CPU to intram.
bb1_netx90_mpw_com_comled_intram = env_netx90_mpw_com_comled_intram.HBootImage('targets/blinki_netx90_mpw_com_comled_intram_app_512k.bin', 'src/netx90/COM_to_INTRAM_ACTIVATE_APP_512K.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com_comled_intram}))

# A boot image that starts the APP CPU and then loads a COM LED blinki for the COM CPU to intram.
# Includes with two 'breakpoints' before starting the APP CPU and before starting the blinki on the COM CPU.
bb2_netx90_mpw_com_comled_intram = env_netx90_mpw_com_comled_intram.HBootImage('targets/blinki_netx90mpw_com_comled_intram_app_bpdemo.bin', 'src/netx90/netx90mpw_bp_COM_to_INTRAM_ACTIVATE_APP.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com_comled_intram}))


## Blinki for the netX90 application CPU.
#env_netx90_mpw_app = atEnv.NETX90_MPW_APP.Clone()
#env_netx90_mpw_app.Append(CPPPATH = astrIncludePaths)
#env_netx90_mpw_app.Replace(LDFILE = 'src/netx90/netx90_app.ld')
#src_netx90_mpw_app = env_netx90_mpw_app.SetBuildPath('targets/netx90_mpw_app', 'src', sources_netx90_app)
#elf_netx90_mpw_app = env_netx90_mpw_app.Elf('targets/netx90_mpw_app/blinki_netx90_mpw_app.elf', src_netx90_mpw_app + env_netx90_mpw_app['PLATFORM_LIBRARY'])
#txt_netx90_mpw_app = env_netx90_mpw_app.ObjDump('targets/netx90_mpw_app/blinki_netx90_mpw_app.txt', elf_netx90_mpw_app, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
#bin_netx90_mpw_app = env_netx90_mpw_app.ObjCopy('targets/netx90_mpw_app/blinki_netx90_mpw_app.bin', elf_netx90_mpw_app)
#bb0_netx90_mpw_app = env_netx90_mpw_app.IFlashImage('targets/blinki_netx90_mpw_app.bin', bin_netx90_mpw_app)

## Blinki for the netX90 application CPU.
#env_netx90_mpw_app_intram = atEnv.NETX90_MPW_APP.Clone()
#env_netx90_mpw_app_intram.Append(CPPPATH = astrIncludePaths)
#env_netx90_mpw_app_intram.Replace(LDFILE = 'src/netx90/netx90_app_intram.ld')
#src_netx90_mpw_app_intram = env_netx90_mpw_app_intram.SetBuildPath('targets/netx90_mpw_app_intram', 'src', sources_netx90_app)
#elf_netx90_mpw_app_intram = env_netx90_mpw_app_intram.Elf('targets/netx90_mpw_app_intram/blinki_netx90_mpw_app_intram.elf', src_netx90_mpw_app_intram + env_netx90_mpw_app_intram['PLATFORM_LIBRARY'])
#txt_netx90_mpw_app_intram = env_netx90_mpw_app_intram.ObjDump('targets/netx90_mpw_app_intram/blinki_netx90_mpw_app_intram.txt', elf_netx90_mpw_app_intram, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

## Blinki for the netX90 application and communication CPU running in SDRAM.
#env_netx90_mpw_app_sdram = atEnv.NETX90_MPW_APP.Clone()
#env_netx90_mpw_app_sdram.Append(CPPPATH = astrIncludePaths)
#env_netx90_mpw_app_sdram.Replace(LDFILE = 'src/netx90/netx90_sdram.ld')
#src_netx90_mpw_app_sdram = env_netx90_mpw_app_sdram.SetBuildPath('targets/netx90_mpw_app_sdram', 'src', sources)
#elf_netx90_mpw_app_sdram = env_netx90_mpw_app_sdram.Elf('targets/netx90_mpw_app_sdram/blinki_netx90_mpw_app_sdram.elf', src_netx90_mpw_app_sdram + env_netx90_mpw_app_sdram['PLATFORM_LIBRARY'])
#txt_netx90_mpw_app_sdram = env_netx90_mpw_app_sdram.ObjDump('targets/netx90_mpw_app_sdram/blinki_netx90_mpw_app_sdram.txt', elf_netx90_mpw_app_sdram, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
#bb0_netx90_mpw_app_sdram = env_netx90_mpw_app_sdram.HBootImage('targets/blinki_netx90_mpw_app_sdram.bin', 'src/netx90/APP_to_SDRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElf': elf_netx90_mpw_app_sdram}))

#bb0_netx90_mpw_com_pass_to_app_sdram = atEnv.NETX90_MPW.HBootImage('targets/netx90_mpw_com_pass_to_app_with_sdram_IS42S16800F-7BLI.bin', 'src/netx90/COM_pass_to_APP_with_SDRAM_IS42S16800F-7BLI.xml')

env_netx56_intram = atEnv.NETX56.Clone()
env_netx56_intram.Append(CPPPATH = astrIncludePaths)
env_netx56_intram.Replace(LDFILE = 'src/netx56/netx56_intram.ld')
src_netx56_intram = env_netx56_intram.SetBuildPath('targets/netx56_intram', 'src', sources)
elf_netx56_intram = env_netx56_intram.Elf('targets/netx56_intram/netx56_intram.elf', src_netx56_intram + env_netx56_intram['PLATFORM_LIBRARY'])
bb0_netx56_intram = env_netx56_intram.BootBlock('targets/mmc/netx56/netx.rom', elf_netx56_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx56_intram = env_netx56_intram.BootBlock('targets/blinki_netx56_spi_intram.bin', elf_netx56_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

env_netx56_sqixip = atEnv.NETX56.Clone()
env_netx56_sqixip.Append(CPPPATH = astrIncludePaths)
env_netx56_sqixip.Replace(LDFILE = 'src/netx56/netx56_sqixip.ld')
src_netx56_sqixip = env_netx56_sqixip.SetBuildPath('targets/netx56_sqixip', 'src', sources)
elf_netx56_sqixip = env_netx56_sqixip.Elf('targets/netx56_sqixip/netx56_sqixip.elf', src_netx56_sqixip + env_netx56_sqixip['PLATFORM_LIBRARY'])
bb0_netx56_sqixip = env_netx56_sqixip.BootBlock('targets/blinki_netx56_sqixip.bin', elf_netx56_sqixip, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')

env_netx50_intram = atEnv.NETX50.Clone()
env_netx50_intram.Append(CPPPATH = astrIncludePaths)
env_netx50_intram.Replace(LDFILE = 'src/netx50/netx50_intram.ld')
src_netx50_intram = env_netx50_intram.SetBuildPath('targets/netx50_intram', 'src', sources)
elf_netx50_intram = env_netx50_intram.Elf('targets/netx50_intram/netx50_intram.elf', src_netx50_intram + env_netx50_intram['PLATFORM_LIBRARY'])
bb0_netx50_intram = env_netx50_intram.BootBlock('targets/mmc/netx50/netx.rom', elf_netx50_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx50_intram = env_netx50_intram.BootBlock('targets/blinki_netx50_spi_intram.bin', elf_netx50_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')
bb2_netx50_intram = env_netx50_intram.BootBlock('targets/blinki_netx50_pfl16_intram.bin', elf_netx50_intram, BOOTBLOCK_SRC='SRB_PF_GEN_16', BOOTBLOCK_DST='INTRAM')

env_netx10_intram = atEnv.NETX10.Clone()
env_netx10_intram.Append(CPPPATH = astrIncludePaths)
env_netx10_intram.Replace(LDFILE = 'src/netx10/netx10_intram.ld')
src_netx10_intram = env_netx10_intram.SetBuildPath('targets/netx10_intram', 'src', sources)
elf_netx10_intram = env_netx10_intram.Elf('targets/netx10_intram/netx10_intram.elf', src_netx10_intram + env_netx10_intram['PLATFORM_LIBRARY'])
bb0_netx10_intram = env_netx10_intram.BootBlock('targets/mmc/netx10/netx.rom', elf_netx10_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx10_intram = env_netx10_intram.BootBlock('targets/blinki_netx10_spi_intram.bin', elf_netx10_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

env_netx10_sqixip = atEnv.NETX10.Clone()
env_netx10_sqixip.Append(CPPPATH = astrIncludePaths)
env_netx10_sqixip.Replace(LDFILE = 'src/netx10/netx10_sqixip.ld')
src_netx10_sqixip = env_netx10_sqixip.SetBuildPath('targets/netx10_sqixip', 'src', sources)
elf_netx10_sqixip = env_netx10_sqixip.Elf('targets/netx10_sqixip/netx10_sqixip.elf', src_netx10_sqixip + env_netx10_sqixip['PLATFORM_LIBRARY'])
bb0_netx10_sqixip = env_netx10_sqixip.BootBlock('targets/blinki_netx10_sqixip.bin', elf_netx10_sqixip, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
