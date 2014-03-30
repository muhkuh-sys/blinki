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
#
# Create the compiler environments.
#
env_default.Append(CPPPATH = ['src', '#platform/src', '#platform/src/lib'])

env_netx500_default = env_default.CreateCompilerEnv('500', ['arch=armv5te'])
env_netx500_default.Replace(BOOTBLOCK_CHIPTYPE = 500)

env_netx56_default = env_default.CreateCompilerEnv('56', ['arch=armv5te'])
env_netx56_default.Replace(BOOTBLOCK_CHIPTYPE = 56)

env_netx50_default = env_default.CreateCompilerEnv('50', ['arch=armv5te'])
env_netx50_default.Replace(BOOTBLOCK_CHIPTYPE = 50)

env_netx10_default = env_default.CreateCompilerEnv('10', ['arch=armv5te'])
env_netx10_default.Replace(BOOTBLOCK_CHIPTYPE = 10)

Export('env_netx500_default', 'env_netx56_default', 'env_netx50_default', 'env_netx10_default')


#----------------------------------------------------------------------------
#
# Build the platform libraries.
#
PLATFORM_LIB_CFG_BUILDS = [500, 56, 50, 10]
SConscript('platform/SConscript', exports='PLATFORM_LIB_CFG_BUILDS')
Import('platform_lib_netx500', 'platform_lib_netx56', 'platform_lib_netx50', 'platform_lib_netx10')


#----------------------------------------------------------------------------
# This is the list of sources. The elements must be separated with whitespace
# (i.e. spaces, tabs, newlines). The amount of whitespace does not matter.
sources = """
	src/init_netx_test.S
	src/main.c
"""


#----------------------------------------------------------------------------
#
# Build all files.
#
env_netx500_intram = env_netx500_default.Clone()
env_netx500_intram.Replace(LDFILE = 'src/netx500/netx500_intram.ld')
src_netx500_intram = env_netx500_intram.SetBuildPath('targets/netx500_intram', 'src', sources)
elf_netx500_intram = env_netx500_intram.Elf('targets/netx500_intram', src_netx500_intram + platform_lib_netx500)
bb0_netx500_intram = env_netx500_intram.BootBlock('targets/mmc/netx500/netx.rom', elf_netx500_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx500_intram = env_netx500_intram.BootBlock('targets/netx500_spi_intram.img', elf_netx500_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

env_netx56_intram = env_netx56_default.Clone()
env_netx56_intram.Replace(LDFILE = 'src/netx56/netx56_intram.ld')
src_netx56_intram = env_netx56_intram.SetBuildPath('targets/netx56_intram', 'src', sources)
elf_netx56_intram = env_netx56_intram.Elf('targets/netx56_intram', src_netx56_intram + platform_lib_netx56)
bb0_netx56_intram = env_netx56_intram.BootBlock('targets/mmc/netx56/netx.rom', elf_netx56_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx56_intram = env_netx56_intram.BootBlock('targets/netx56_spi_intram.img', elf_netx56_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

env_netx50_intram = env_netx50_default.Clone()
env_netx50_intram.Replace(LDFILE = 'src/netx50/netx50_intram.ld')
src_netx50_intram = env_netx50_intram.SetBuildPath('targets/netx50_intram', 'src', sources)
elf_netx50_intram = env_netx50_intram.Elf('targets/netx50_intram', src_netx50_intram + platform_lib_netx50)
bb0_netx50_intram = env_netx50_intram.BootBlock('targets/mmc/netx50/netx.rom', elf_netx50_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx50_intram = env_netx50_intram.BootBlock('targets/netx50_spi_intram.img', elf_netx50_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

env_netx10_intram = env_netx10_default.Clone()
env_netx10_intram.Replace(LDFILE = 'src/netx10/netx10_intram.ld')
src_netx10_intram = env_netx10_intram.SetBuildPath('targets/netx10_intram', 'src', sources)
elf_netx10_intram = env_netx10_intram.Elf('targets/netx10_intram', src_netx10_intram + platform_lib_netx10)
bb0_netx10_intram = env_netx10_intram.BootBlock('targets/mmc/netx10/netx.rom', elf_netx10_intram, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
bb1_netx10_intram = env_netx10_intram.BootBlock('targets/netx10_spi_intram.img', elf_netx10_intram, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

env_netx10_sqixip = env_netx10_default.Clone()
env_netx10_sqixip.Replace(LDFILE = 'src/netx10/netx10_sqixip.ld')
src_netx10_sqixip = env_netx10_sqixip.SetBuildPath('targets/netx10_sqixip', 'src', sources)
elf_netx10_sqixip = env_netx10_sqixip.Elf('targets/netx10_sqixip', src_netx10_sqixip + platform_lib_netx10)
bb0_netx10_sqixip = env_netx10_sqixip.BootBlock('targets/netx10_sqixip.img', elf_netx10_sqixip, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')

