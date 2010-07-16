# -*- coding: utf-8 -*-

# TODO:
#  * more than one system include dir (for arg parsing etc)
#  * set a default location for the compiler dir (but where could this be?)
#
# Done:
#  * print help even if the site dir for the compiler stuff is missing.
#  * generate relocated sources from list of real locations
#  * set compiler flags from build properties
#  * show command line summary (e.g. "Cc blah.o") for the actions, but show complete line if the command failed.
#  * accept 'clean' target like make
#  * auto dependency for LDFILE
#

import scons_common
import build_properties

build_properties.Read()

#----------------------------------------------------------------------------
#
# set help text
#
Help("""
	Set the compiler dir with all the gcc_*.py files with --site-dir=path .
	Example: The compiler dir is usually in the folder '.ant' in the users home directory.
	This expands for the user 'brunhild' to '/home/brunhild/.ant'.

	Type: 'scons --site-dir=compiler_dir' to build the production program,
	      'scons --site-dir=compiler_dir clean' to clean everything.
""")

build_properties.GenerateHelp()


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


default_ccflags = """
	-ffreestanding
	-mlong-calls
	-Wall
	-Wextra
	-Wconversion
	-Wshadow
	-Wcast-qual
	-Wwrite-strings
	-Wcast-align
	-Wpointer-arith
	-Wmissing-prototypes
	-Wstrict-prototypes
	-mapcs
	-g3
	-gdwarf-2
	-std=c99
"""

#----------------------------------------------------------------------------
# Only execute this part if the help text is not requested.
# This keeps the help message functional even if no include path for the
# compiler definitions was specified.
if not GetOption('help'):
	# Show summary of the build properties.
	build_properties.PrintSummary()
	
	
	#----------------------------------------------------------------------------
	#
	# import the compiler definitions
	#
	# NOTE: it would be possible to use execfile instead of import here. This
	gcc_arm_elf_4_3_3_3 = scons_common.get_compiler('gcc_arm_elf_4_3_3_3')
	
	
	#----------------------------------------------------------------------------
	#
	# create the default environment
	#
	env_default = Environment()
	gcc_arm_elf_4_3_3_3.ApplyToEnv(env_default)
	env_default.Decider('MD5')
	env_default.Append(CPPPATH = ['src'])
	env_default.Replace(CCFLAGS = Split(default_ccflags))
	env_default.Replace(LIBS = ['m', 'c', 'gcc'])
	env_default.Replace(LINKFLAGS = ['-nostdlib', '-static', '-Map=${TARGET}.map'])
	build_properties.ApplyToEnv(env_default)
	
	
	# create environments for all builds
	env_netx500 = env_default.Clone()
	env_netx500.Append(CCFLAGS = ['-mcpu=arm926ej-s'])
	env_netx500.Replace(LDFILE = 'src/netx500/netx500.ld')
	env_netx500.Replace(LIBPATH = ['${GCC_DIR}/arm-elf/lib/arm926ej-s', '${GCC_DIR}/lib/gcc/arm-elf/${GCC_VERSION}/arm926ej-s'])
	env_netx500.Append(CPPDEFINES = [['ASIC_TYP', '500']])
	env_netx500.Append(CPPPATH = ['src/netx500'])
	env_netx500.VariantDir('targets/netx500', 'src', duplicate=0)
	
	env_netx10 = env_default.Clone()
	env_netx10.Append(CCFLAGS = ['-mcpu=arm966e-s'])
	env_netx10.Replace(LIBPATH = ['${GCC_DIR}/arm-elf/lib/arm966e-s', '${GCC_DIR}/lib/gcc/arm-elf/${GCC_VERSION}/arm966e-s'])
	env_netx10.Append(CPPDEFINES = [['ASIC_TYP', '10']])
	env_netx10.Append(CPPPATH = ['src/netx10'])
	
	env_netx10_intram = env_netx10.Clone()
	env_netx10_intram.Replace(LDFILE = 'src/netx10/netx10_intram.ld')
	
	env_netx10_sqixip = env_netx10.Clone()
	env_netx10_sqixip.Replace(LDFILE = 'src/netx10/netx10_sqixip.ld')
	
	
	#----------------------------------------------------------------------------
	#
	# build the files
	#
#	sources_netx500 = [src.replace('src', 'targets/netx500') for src in Split(sources_common+sources_custom_netx500)]
#	blinki_netx500_elf = env_netx500.Elf('targets/bob_netx500', sources_netx500)
#	env_netx500.ObjCopy('targets/bob_netx500', blinki_netx500_elf)
	
	env_netx10_intram.VariantDir('targets/netx10_intram', 'src', duplicate=0)
	sources_netx10_intram = [src.replace('src', 'targets/netx10_intram') for src in Split(sources_common+sources_custom_netx10)]
	blinki_netx10_intram_elf = env_netx10_intram.Elf('targets/blinki_netx10_intram', sources_netx10_intram)
	blinki_netx10_intram_bin = env_netx10_intram.ObjCopy('targets/blinki_netx10_intram', blinki_netx10_intram_elf)
	
	env_netx10_sqixip.VariantDir('targets/netx10_sqixip', 'src', duplicate=0)
	sources_netx10_sqixip = [src.replace('src', 'targets/netx10_sqixip') for src in Split(sources_common+sources_custom_netx10)]
	blinki_netx10_sqixip_elf = env_netx10_sqixip.Elf('targets/blinki_netx10_sqixip', sources_netx10_sqixip)
	blinki_netx10_sqixip_bin = env_netx10_sqixip.ObjCopy('targets/blinki_netx10_sqixip', blinki_netx10_sqixip_elf)
	
