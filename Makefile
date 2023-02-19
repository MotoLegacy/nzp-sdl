# Makefile.in generated by automake 1.16.5 from Makefile.am.
# Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994-2021 Free Software Foundation, Inc.

# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.




am__is_gnu_make = { \
  if test -z '$(MAKELEVEL)'; then \
    false; \
  elif test -n '$(MAKE_HOST)'; then \
    true; \
  elif test -n '$(MAKE_VERSION)' && test -n '$(CURDIR)'; then \
    true; \
  else \
    false; \
  fi; \
}
am__make_running_with_option = \
  case $${target_option-} in \
      ?) ;; \
      *) echo "am__make_running_with_option: internal error: invalid" \
              "target option '$${target_option-}' specified" >&2; \
         exit 1;; \
  esac; \
  has_opt=no; \
  sane_makeflags=$$MAKEFLAGS; \
  if $(am__is_gnu_make); then \
    sane_makeflags=$$MFLAGS; \
  else \
    case $$MAKEFLAGS in \
      *\\[\ \	]*) \
        bs=\\; \
        sane_makeflags=`printf '%s\n' "$$MAKEFLAGS" \
          | sed "s/$$bs$$bs[$$bs $$bs	]*//g"`;; \
    esac; \
  fi; \
  skip_next=no; \
  strip_trailopt () \
  { \
    flg=`printf '%s\n' "$$flg" | sed "s/$$1.*$$//"`; \
  }; \
  for flg in $$sane_makeflags; do \
    test $$skip_next = yes && { skip_next=no; continue; }; \
    case $$flg in \
      *=*|--*) continue;; \
        -*I) strip_trailopt 'I'; skip_next=yes;; \
      -*I?*) strip_trailopt 'I';; \
        -*O) strip_trailopt 'O'; skip_next=yes;; \
      -*O?*) strip_trailopt 'O';; \
        -*l) strip_trailopt 'l'; skip_next=yes;; \
      -*l?*) strip_trailopt 'l';; \
      -[dEDm]) skip_next=yes;; \
      -[JT]) skip_next=yes;; \
    esac; \
    case $$flg in \
      *$$target_option*) has_opt=yes; break;; \
    esac; \
  done; \
  test $$has_opt = yes
am__make_dryrun = (target_option=n; $(am__make_running_with_option))
am__make_keepgoing = (target_option=k; $(am__make_running_with_option))
pkgdatadir = $(datadir)/good-looking-quake
pkgincludedir = $(includedir)/good-looking-quake
pkglibdir = $(libdir)/good-looking-quake
pkglibexecdir = $(libexecdir)/good-looking-quake
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-unknown-linux-gnu
host_triplet = x86_64-unknown-linux-gnu
bin_PROGRAMS = goodlookingquake$(EXEEXT)
subdir = .
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
DIST_COMMON = $(srcdir)/Makefile.am $(top_srcdir)/configure \
	$(am__configure_deps) $(am__DIST_COMMON)
am__CONFIG_DISTCLEAN_FILES = config.status config.cache config.log \
 configure.lineno config.status.lineno
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__installdirs = "$(DESTDIR)$(bindir)"
PROGRAMS = $(bin_PROGRAMS)
am__objects_1 = d_vars.$(OBJEXT) nonintel.$(OBJEXT)
am_goodlookingquake_OBJECTS = cd_sdl.$(OBJEXT) chase.$(OBJEXT) \
	cl_demo.$(OBJEXT) cl_input.$(OBJEXT) cl_main.$(OBJEXT) \
	cl_parse.$(OBJEXT) cl_tent.$(OBJEXT) cmd.$(OBJEXT) \
	common.$(OBJEXT) console.$(OBJEXT) crc.$(OBJEXT) \
	cvar.$(OBJEXT) d_edge.$(OBJEXT) d_fill.$(OBJEXT) \
	d_init.$(OBJEXT) d_modech.$(OBJEXT) d_part.$(OBJEXT) \
	d_polyse.$(OBJEXT) d_scan.$(OBJEXT) d_sky.$(OBJEXT) \
	d_sprite.$(OBJEXT) d_surf.$(OBJEXT) d_zpoint.$(OBJEXT) \
	draw.$(OBJEXT) host.$(OBJEXT) host_cmd.$(OBJEXT) \
	keys.$(OBJEXT) mathlib.$(OBJEXT) menu.$(OBJEXT) \
	model.$(OBJEXT) net_bsd.$(OBJEXT) net_dgrm.$(OBJEXT) \
	net_loop.$(OBJEXT) net_main.$(OBJEXT) net_udp.$(OBJEXT) \
	net_vcr.$(OBJEXT) net_wso.$(OBJEXT) pr_cmds.$(OBJEXT) \
	pr_edict.$(OBJEXT) pr_exec.$(OBJEXT) r_aclip.$(OBJEXT) \
	r_alias.$(OBJEXT) r_bsp.$(OBJEXT) r_draw.$(OBJEXT) \
	r_edge.$(OBJEXT) r_efrag.$(OBJEXT) r_light.$(OBJEXT) \
	r_main.$(OBJEXT) r_misc.$(OBJEXT) r_part.$(OBJEXT) \
	r_sky.$(OBJEXT) r_sprite.$(OBJEXT) r_surf.$(OBJEXT) \
	r_vars.$(OBJEXT) cl_hud.$(OBJEXT) screen.$(OBJEXT) \
	snd_dma.$(OBJEXT) snd_mem.$(OBJEXT) snd_mix.$(OBJEXT) \
	snd_sdl.$(OBJEXT) sv_main.$(OBJEXT) sv_move.$(OBJEXT) \
	sv_phys.$(OBJEXT) sv_user.$(OBJEXT) sys_sdl.$(OBJEXT) \
	vid_sdl.$(OBJEXT) view.$(OBJEXT) wad.$(OBJEXT) world.$(OBJEXT) \
	zone.$(OBJEXT) $(am__objects_1)
goodlookingquake_OBJECTS = $(am_goodlookingquake_OBJECTS)
goodlookingquake_DEPENDENCIES =
AM_V_P = $(am__v_P_$(V))
am__v_P_ = $(am__v_P_$(AM_DEFAULT_VERBOSITY))
am__v_P_0 = false
am__v_P_1 = :
AM_V_GEN = $(am__v_GEN_$(V))
am__v_GEN_ = $(am__v_GEN_$(AM_DEFAULT_VERBOSITY))
am__v_GEN_0 = @echo "  GEN     " $@;
am__v_GEN_1 = 
AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_VERBOSITY))
am__v_at_0 = @
am__v_at_1 = 
DEFAULT_INCLUDES = -I.
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__maybe_remake_depfiles = depfiles
am__depfiles_remade = ./$(DEPDIR)/cd_sdl.Po ./$(DEPDIR)/chase.Po \
	./$(DEPDIR)/cl_demo.Po ./$(DEPDIR)/cl_hud.Po \
	./$(DEPDIR)/cl_input.Po ./$(DEPDIR)/cl_main.Po \
	./$(DEPDIR)/cl_parse.Po ./$(DEPDIR)/cl_tent.Po \
	./$(DEPDIR)/cmd.Po ./$(DEPDIR)/common.Po \
	./$(DEPDIR)/console.Po ./$(DEPDIR)/crc.Po ./$(DEPDIR)/cvar.Po \
	./$(DEPDIR)/d_edge.Po ./$(DEPDIR)/d_fill.Po \
	./$(DEPDIR)/d_init.Po ./$(DEPDIR)/d_modech.Po \
	./$(DEPDIR)/d_part.Po ./$(DEPDIR)/d_polyse.Po \
	./$(DEPDIR)/d_scan.Po ./$(DEPDIR)/d_sky.Po \
	./$(DEPDIR)/d_sprite.Po ./$(DEPDIR)/d_surf.Po \
	./$(DEPDIR)/d_vars.Po ./$(DEPDIR)/d_zpoint.Po \
	./$(DEPDIR)/draw.Po ./$(DEPDIR)/host.Po \
	./$(DEPDIR)/host_cmd.Po ./$(DEPDIR)/keys.Po \
	./$(DEPDIR)/mathlib.Po ./$(DEPDIR)/menu.Po \
	./$(DEPDIR)/model.Po ./$(DEPDIR)/net_bsd.Po \
	./$(DEPDIR)/net_dgrm.Po ./$(DEPDIR)/net_loop.Po \
	./$(DEPDIR)/net_main.Po ./$(DEPDIR)/net_udp.Po \
	./$(DEPDIR)/net_vcr.Po ./$(DEPDIR)/net_wso.Po \
	./$(DEPDIR)/nonintel.Po ./$(DEPDIR)/pr_cmds.Po \
	./$(DEPDIR)/pr_edict.Po ./$(DEPDIR)/pr_exec.Po \
	./$(DEPDIR)/r_aclip.Po ./$(DEPDIR)/r_alias.Po \
	./$(DEPDIR)/r_bsp.Po ./$(DEPDIR)/r_draw.Po \
	./$(DEPDIR)/r_edge.Po ./$(DEPDIR)/r_efrag.Po \
	./$(DEPDIR)/r_light.Po ./$(DEPDIR)/r_main.Po \
	./$(DEPDIR)/r_misc.Po ./$(DEPDIR)/r_part.Po \
	./$(DEPDIR)/r_sky.Po ./$(DEPDIR)/r_sprite.Po \
	./$(DEPDIR)/r_surf.Po ./$(DEPDIR)/r_vars.Po \
	./$(DEPDIR)/screen.Po ./$(DEPDIR)/snd_dma.Po \
	./$(DEPDIR)/snd_mem.Po ./$(DEPDIR)/snd_mix.Po \
	./$(DEPDIR)/snd_sdl.Po ./$(DEPDIR)/sv_main.Po \
	./$(DEPDIR)/sv_move.Po ./$(DEPDIR)/sv_phys.Po \
	./$(DEPDIR)/sv_user.Po ./$(DEPDIR)/sys_sdl.Po \
	./$(DEPDIR)/vid_sdl.Po ./$(DEPDIR)/view.Po ./$(DEPDIR)/wad.Po \
	./$(DEPDIR)/world.Po ./$(DEPDIR)/zone.Po
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
AM_V_CC = $(am__v_CC_$(V))
am__v_CC_ = $(am__v_CC_$(AM_DEFAULT_VERBOSITY))
am__v_CC_0 = @echo "  CC      " $@;
am__v_CC_1 = 
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CCLD = $(am__v_CCLD_$(V))
am__v_CCLD_ = $(am__v_CCLD_$(AM_DEFAULT_VERBOSITY))
am__v_CCLD_0 = @echo "  CCLD    " $@;
am__v_CCLD_1 = 
SOURCES = $(goodlookingquake_SOURCES)
DIST_SOURCES = $(goodlookingquake_SOURCES)
am__can_run_installinfo = \
  case $$AM_UPDATE_INFO_DIR in \
    n|no|NO) false;; \
    *) (install-info --version) >/dev/null 2>&1;; \
  esac
am__tagged_files = $(HEADERS) $(SOURCES) $(TAGS_FILES) $(LISP) \
	config.h.in
# Read a list of newline-separated strings from the standard input,
# and print each of them once, without duplicates.  Input order is
# *not* preserved.
am__uniquify_input = $(AWK) '\
  BEGIN { nonempty = 0; } \
  { items[$$0] = 1; nonempty = 1; } \
  END { if (nonempty) { for (i in items) print i; }; } \
'
# Make sure the list of sources is unique.  This is necessary because,
# e.g., the same source file might be shared among _SOURCES variables
# for different programs/libraries.
am__define_uniq_tagged_files = \
  list='$(am__tagged_files)'; \
  unique=`for i in $$list; do \
    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
  done | $(am__uniquify_input)`
AM_RECURSIVE_TARGETS = cscope
am__DIST_COMMON = $(srcdir)/Makefile.in $(srcdir)/config.h.in AUTHORS \
	COPYING ChangeLog INSTALL NEWS README compile config.guess \
	config.sub depcomp install-sh missing mkinstalldirs
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
distdir = $(PACKAGE)-$(VERSION)
top_distdir = $(distdir)
am__remove_distdir = \
  if test -d "$(distdir)"; then \
    find "$(distdir)" -type d ! -perm -200 -exec chmod u+w {} ';' \
      && rm -rf "$(distdir)" \
      || { sleep 5 && rm -rf "$(distdir)"; }; \
  else :; fi
am__post_remove_distdir = $(am__remove_distdir)
DIST_ARCHIVES = $(distdir).tar.gz
GZIP_ENV = --best
DIST_TARGETS = dist-gzip
# Exists only to be overridden by the user if desired.
AM_DISTCHECK_DVI_TARGET = dvi
distuninstallcheck_listfiles = find . -type f -print
am__distuninstallcheck_listfiles = $(distuninstallcheck_listfiles) \
  | sed 's|^\./|$(prefix)/|' | grep -v '$(infodir)/dir$$'
distcleancheck_listfiles = find . -type f -print
ACLOCAL = ${SHELL} '/home/deck/git/glq/missing' aclocal-1.16
ALLOCA = 
AMTAR = $${TAR-tar}
AM_DEFAULT_VERBOSITY = 1
AUTOCONF = ${SHELL} '/home/deck/git/glq/missing' autoconf
AUTOHEADER = ${SHELL} '/home/deck/git/glq/missing' autoheader
AUTOMAKE = ${SHELL} '/home/deck/git/glq/missing' automake-1.16
AWK = gawk
CC = gcc
CCAS = gcc
CCASDEPMODE = depmode=gcc3
CCASFLAGS = -g -O0
CCDEPMODE = depmode=gcc3
CFLAGS = -g -O0 -ffast-math -funroll-loops -fomit-frame-pointer -fexpensive-optimizations -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT 
CPP = gcc -E
CPPFLAGS =  -DSDL
CSCOPE = cscope
CTAGS = ctags
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
ECHO_C = 
ECHO_N = -n
ECHO_T = 
ETAGS = etags
EXEEXT = 
ICONOBJ = 
INETLIB = 
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LDFLAGS = 
LIBOBJS = 
LIBS =  -lSDL 
LTLIBOBJS = 
MAKEINFO = ${SHELL} '/home/deck/git/glq/missing' makeinfo
MATHLIB = -lm
MKDIR_P = /usr/bin/mkdir -p
OBJEXT = o
PACKAGE = good-looking-quake
PACKAGE_BUGREPORT = 
PACKAGE_NAME = Good Looking Quake
PACKAGE_STRING = Good Looking Quake 1.0.9
PACKAGE_TARNAME = good-looking-quake
PACKAGE_URL = 
PACKAGE_VERSION = 1.0.9
PATH_SEPARATOR = :
PKG_CONFIG = /usr/bin/pkg-config
PKG_CONFIG_LIBDIR = 
PKG_CONFIG_PATH = 
SDL_CFLAGS = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT 
SDL_LIBS = -lSDL 
SET_MAKE = 
SHELL = /bin/sh
STRIP = 
VERSION = 1.0.9
XMKMF = 
abs_builddir = /home/deck/git/glq
abs_srcdir = /home/deck/git/glq
abs_top_builddir = /home/deck/git/glq
abs_top_srcdir = /home/deck/git/glq
ac_ct_CC = gcc
am__include = include
am__leading_dot = .
am__quote = 
am__tar = tar --format=posix -chf - "$$tardir"
am__untar = tar -xf -
bindir = ${exec_prefix}/bin
build = x86_64-unknown-linux-gnu
build_alias = 
build_cpu = x86_64
build_os = linux-gnu
build_vendor = unknown
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = x86_64-unknown-linux-gnu
host_alias = 
host_cpu = x86_64
host_os = linux-gnu
host_vendor = unknown
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /home/deck/git/glq/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(MKDIR_P)
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr/local
program_transform_name = s,x,x,
psdir = ${docdir}
runstatedir = ${localstatedir}/run
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = 
top_builddir = .
top_srcdir = .
goodlookingquake_LDADD = -lm 
goodlookingquake_SOURCES = \
	adivtab.h		\
	anorm_dots.h		\
	anorms.h		\
	block16.h		\
	block8.h		\
	bspfile.h		\
	cd_sdl.c		\
	cdaudio.h		\
	chase.c			\
	cl_demo.c		\
	cl_input.c		\
	cl_main.c		\
	cl_parse.c		\
	cl_tent.c		\
	clean.bat		\
	client.h		\
	cmd.c			\
	cmd.h			\
	common.c		\
	common.h		\
	conproc.h		\
	console.c		\
	console.h		\
	crc.c			\
	crc.h			\
	cvar.c			\
	cvar.h			\
	d_edge.c		\
	d_fill.c		\
	d_iface.h		\
	d_ifacea.h		\
	d_init.c		\
	d_local.h		\
	d_modech.c		\
	d_part.c		\
	d_polyse.c		\
	d_scan.c		\
	d_sky.c			\
	d_sprite.c		\
	d_surf.c		\
	d_zpoint.c		\
	draw.c			\
	draw.h			\
	host.c			\
	host_cmd.c		\
	input.h			\
	keys.c			\
	keys.h			\
	mathlib.c		\
	mathlib.h		\
	menu.c			\
	menu.h			\
	model.c			\
	model.h			\
	modelgen.h		\
	mpdosock.h		\
	net.h			\
	net_bsd.c		\
	net_bw.h		\
	net_dgrm.c		\
	net_dgrm.h		\
	net_loop.c		\
	net_loop.h		\
	net_main.c		\
	net_udp.c		\
	net_udp.h		\
	net_vcr.c		\
	net_vcr.h		\
	net_wso.c		\
	pr_cmds.c		\
	pr_comp.h		\
	pr_edict.c		\
	pr_exec.c		\
	progdefs.h		\
	progs.h			\
	protocol.h		\
	quakeasm.h		\
	quakedef.h		\
	r_aclip.c		\
	r_alias.c		\
	r_bsp.c			\
	r_draw.c		\
	r_edge.c		\
	r_efrag.c		\
	r_light.c		\
	r_local.h		\
	r_main.c		\
	r_misc.c		\
	r_part.c		\
	r_shared.h		\
	r_sky.c			\
	r_sprite.c		\
	r_surf.c		\
	r_vars.c		\
	render.h		\
	resource.h		\
	cl_hud.c		\
	cl_hud.h		\
	screen.c		\
	screen.h		\
	server.h		\
	snd_dma.c		\
	snd_mem.c		\
	snd_mix.c		\
	snd_sdl.c		\
	sound.h			\
	spritegn.h		\
	sv_main.c		\
	sv_move.c		\
	sv_phys.c		\
	sv_user.c		\
	sys.h			\
	sys_sdl.c		\
	vgamodes.h		\
	vid.h			\
	vid_sdl.c		\
	view.c			\
	view.h			\
	wad.c			\
	wad.h			\
	winquake.h		\
	world.c			\
	world.h			\
	zone.c			\
	zone.h			\
	$(MAYBE_X86_SRCS) $(NONX86_SRCS)

NONX86_SRCS = \
	d_vars.c		\
	nonintel.c

NULL_SRCS = \
	cd_null.c		\
	in_null.c		\
	net_none.c		\
	snd_null.c		\
	sys_null.c		\
	vid_null.c

DOS_SRCS = \
	cd_audio.c		\
	dosasm.S		\
	dosisms.h		\
	dos_v2.c		\
	in_dos.c		\
	mplib.c			\
	mplpc.c			\
	net_bw.c		\
	net_comx.c		\
	net_dos.c		\
	net_ipx.c		\
	net_ipx.h		\
	net_ser.c		\
	net_ser.h		\
	snd_dos.c		\
	snd_gus.c		\
	sys_dos.c		\
	vid_dos.c		\
	vid_dos.h		\
	vid_ext.c		\
	vid_vga.c		\
	vregset.c		\
	vregset.h

WIN_SRCS = \
	cd_win.c		\
	conproc.c		\
	in_win.c		\
	net_mp.c		\
	net_mp.h		\
	net_win.c		\
	net_wins.c		\
	net_wins.h		\
	net_wipx.c		\
	net_wipx.h		\
	snd_win.c		\
	sys_win.c		\
	sys_wina.S		\
	sys_wind.c		\
	vid_win.c

LNX_SRCS = \
	cd_linux.c		\
	snd_linux.c		\
	sys_linux.c		\
	vid_svgalib.c		\
	vid_x.c

EXTRA_DIST = \
	README.md		\
	README.SDL		\
	progdefs.q1		\
	progdefs.q2		\
	q.bat			\
	qa.bat			\
	qb.bat			\
	qe3.ico			\
	qt.bat			\
	quake-data.spec.sh	\
	quake-hipnotic.spec.sh	\
	quake-rogue.spec.sh	\
	quake-shareware.spec.sh	\
	quake.gif		\
	quake.ico		\
	quake.spec.sh		\
	winquake.aps		\
	winquake.rc		\
	wq.bat			\
	wqreadme.txt		\
	$(NULL_SRCS)		\
	$(WIN_SRCS)		\
	$(LNX_SRCS)		\
	data			\
	docs			\
	kit			

all: config.h
	$(MAKE) $(AM_MAKEFLAGS) all-am

.SUFFIXES:
.SUFFIXES: .c .o .obj
am--refresh: Makefile
	@:
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      echo ' cd $(srcdir) && $(AUTOMAKE) --gnu'; \
	      $(am__cd) $(srcdir) && $(AUTOMAKE) --gnu \
		&& exit 0; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --gnu Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    echo ' $(SHELL) ./config.status'; \
	    $(SHELL) ./config.status;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__maybe_remake_depfiles)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__maybe_remake_depfiles);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck

$(top_srcdir)/configure:  $(am__configure_deps)
	$(am__cd) $(srcdir) && $(AUTOCONF)
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	$(am__cd) $(srcdir) && $(ACLOCAL) $(ACLOCAL_AMFLAGS)
$(am__aclocal_m4_deps):

config.h: stamp-h1
	@test -f $@ || rm -f stamp-h1
	@test -f $@ || $(MAKE) $(AM_MAKEFLAGS) stamp-h1

stamp-h1: $(srcdir)/config.h.in $(top_builddir)/config.status
	@rm -f stamp-h1
	cd $(top_builddir) && $(SHELL) ./config.status config.h
$(srcdir)/config.h.in:  $(am__configure_deps) 
	($(am__cd) $(top_srcdir) && $(AUTOHEADER))
	rm -f stamp-h1
	touch $@

distclean-hdr:
	-rm -f config.h stamp-h1
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(bindir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(bindir)" || exit 1; \
	fi; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p \
	  ; then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' \
	    -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	      echo " $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(bindir)$$dir'"; \
	      $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(bindir)$$dir" || exit $$?; \
	    } \
	; done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' \
	`; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(bindir)' && rm -f" $$files ")"; \
	cd "$(DESTDIR)$(bindir)" && rm -f $$files

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

goodlookingquake$(EXEEXT): $(goodlookingquake_OBJECTS) $(goodlookingquake_DEPENDENCIES) $(EXTRA_goodlookingquake_DEPENDENCIES) 
	@rm -f goodlookingquake$(EXEEXT)
	$(AM_V_CCLD)$(LINK) $(goodlookingquake_OBJECTS) $(goodlookingquake_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/cd_sdl.Po # am--include-marker
include ./$(DEPDIR)/chase.Po # am--include-marker
include ./$(DEPDIR)/cl_demo.Po # am--include-marker
include ./$(DEPDIR)/cl_hud.Po # am--include-marker
include ./$(DEPDIR)/cl_input.Po # am--include-marker
include ./$(DEPDIR)/cl_main.Po # am--include-marker
include ./$(DEPDIR)/cl_parse.Po # am--include-marker
include ./$(DEPDIR)/cl_tent.Po # am--include-marker
include ./$(DEPDIR)/cmd.Po # am--include-marker
include ./$(DEPDIR)/common.Po # am--include-marker
include ./$(DEPDIR)/console.Po # am--include-marker
include ./$(DEPDIR)/crc.Po # am--include-marker
include ./$(DEPDIR)/cvar.Po # am--include-marker
include ./$(DEPDIR)/d_edge.Po # am--include-marker
include ./$(DEPDIR)/d_fill.Po # am--include-marker
include ./$(DEPDIR)/d_init.Po # am--include-marker
include ./$(DEPDIR)/d_modech.Po # am--include-marker
include ./$(DEPDIR)/d_part.Po # am--include-marker
include ./$(DEPDIR)/d_polyse.Po # am--include-marker
include ./$(DEPDIR)/d_scan.Po # am--include-marker
include ./$(DEPDIR)/d_sky.Po # am--include-marker
include ./$(DEPDIR)/d_sprite.Po # am--include-marker
include ./$(DEPDIR)/d_surf.Po # am--include-marker
include ./$(DEPDIR)/d_vars.Po # am--include-marker
include ./$(DEPDIR)/d_zpoint.Po # am--include-marker
include ./$(DEPDIR)/draw.Po # am--include-marker
include ./$(DEPDIR)/host.Po # am--include-marker
include ./$(DEPDIR)/host_cmd.Po # am--include-marker
include ./$(DEPDIR)/keys.Po # am--include-marker
include ./$(DEPDIR)/mathlib.Po # am--include-marker
include ./$(DEPDIR)/menu.Po # am--include-marker
include ./$(DEPDIR)/model.Po # am--include-marker
include ./$(DEPDIR)/net_bsd.Po # am--include-marker
include ./$(DEPDIR)/net_dgrm.Po # am--include-marker
include ./$(DEPDIR)/net_loop.Po # am--include-marker
include ./$(DEPDIR)/net_main.Po # am--include-marker
include ./$(DEPDIR)/net_udp.Po # am--include-marker
include ./$(DEPDIR)/net_vcr.Po # am--include-marker
include ./$(DEPDIR)/net_wso.Po # am--include-marker
include ./$(DEPDIR)/nonintel.Po # am--include-marker
include ./$(DEPDIR)/pr_cmds.Po # am--include-marker
include ./$(DEPDIR)/pr_edict.Po # am--include-marker
include ./$(DEPDIR)/pr_exec.Po # am--include-marker
include ./$(DEPDIR)/r_aclip.Po # am--include-marker
include ./$(DEPDIR)/r_alias.Po # am--include-marker
include ./$(DEPDIR)/r_bsp.Po # am--include-marker
include ./$(DEPDIR)/r_draw.Po # am--include-marker
include ./$(DEPDIR)/r_edge.Po # am--include-marker
include ./$(DEPDIR)/r_efrag.Po # am--include-marker
include ./$(DEPDIR)/r_light.Po # am--include-marker
include ./$(DEPDIR)/r_main.Po # am--include-marker
include ./$(DEPDIR)/r_misc.Po # am--include-marker
include ./$(DEPDIR)/r_part.Po # am--include-marker
include ./$(DEPDIR)/r_sky.Po # am--include-marker
include ./$(DEPDIR)/r_sprite.Po # am--include-marker
include ./$(DEPDIR)/r_surf.Po # am--include-marker
include ./$(DEPDIR)/r_vars.Po # am--include-marker
include ./$(DEPDIR)/screen.Po # am--include-marker
include ./$(DEPDIR)/snd_dma.Po # am--include-marker
include ./$(DEPDIR)/snd_mem.Po # am--include-marker
include ./$(DEPDIR)/snd_mix.Po # am--include-marker
include ./$(DEPDIR)/snd_sdl.Po # am--include-marker
include ./$(DEPDIR)/sv_main.Po # am--include-marker
include ./$(DEPDIR)/sv_move.Po # am--include-marker
include ./$(DEPDIR)/sv_phys.Po # am--include-marker
include ./$(DEPDIR)/sv_user.Po # am--include-marker
include ./$(DEPDIR)/sys_sdl.Po # am--include-marker
include ./$(DEPDIR)/vid_sdl.Po # am--include-marker
include ./$(DEPDIR)/view.Po # am--include-marker
include ./$(DEPDIR)/wad.Po # am--include-marker
include ./$(DEPDIR)/world.Po # am--include-marker
include ./$(DEPDIR)/zone.Po # am--include-marker

$(am__depfiles_remade):
	@$(MKDIR_P) $(@D)
	@echo '# dummy' >$@-t && $(am__mv) $@-t $@

am--depfiles: $(am__depfiles_remade)

.c.o:
	$(AM_V_CC)depbase=`echo $@ | sed 's|[^/]*$$|$(DEPDIR)/&|;s|\.o$$||'`;\
	$(COMPILE) -MT $@ -MD -MP -MF $$depbase.Tpo -c -o $@ $< &&\
	$(am__mv) $$depbase.Tpo $$depbase.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ $<

.c.obj:
	$(AM_V_CC)depbase=`echo $@ | sed 's|[^/]*$$|$(DEPDIR)/&|;s|\.obj$$||'`;\
	$(COMPILE) -MT $@ -MD -MP -MF $$depbase.Tpo -c -o $@ `$(CYGPATH_W) '$<'` &&\
	$(am__mv) $$depbase.Tpo $$depbase.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

ID: $(am__tagged_files)
	$(am__define_uniq_tagged_files); mkid -fID $$unique
tags: tags-am
TAGS: tags

tags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	set x; \
	here=`pwd`; \
	$(am__define_uniq_tagged_files); \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: ctags-am

CTAGS: ctags
ctags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	$(am__define_uniq_tagged_files); \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"
cscope: cscope.files
	test ! -s cscope.files \
	  || $(CSCOPE) -b -q $(AM_CSCOPEFLAGS) $(CSCOPEFLAGS) -i cscope.files $(CSCOPE_ARGS)
clean-cscope:
	-rm -f cscope.files
cscope.files: clean-cscope cscopelist
cscopelist: cscopelist-am

cscopelist-am: $(am__tagged_files)
	list='$(am__tagged_files)'; \
	case "$(srcdir)" in \
	  [\\/]* | ?:[\\/]*) sdir="$(srcdir)" ;; \
	  *) sdir=$(subdir)/$(srcdir) ;; \
	esac; \
	for i in $$list; do \
	  if test -f "$$i"; then \
	    echo "$(subdir)/$$i"; \
	  else \
	    echo "$$sdir/$$i"; \
	  fi; \
	done >> $(top_builddir)/cscope.files

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags
	-rm -f cscope.out cscope.in.out cscope.po.out cscope.files
distdir: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) distdir-am

distdir-am: $(DISTFILES)
	$(am__remove_distdir)
	test -d "$(distdir)" || mkdir "$(distdir)"
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
	-test -n "$(am__skip_mode_fix)" \
	|| find "$(distdir)" -type d ! -perm -755 \
		-exec chmod u+rwx,go+rx {} \; -o \
	  ! -type d ! -perm -444 -links 1 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -400 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -444 -exec $(install_sh) -c -m a+r {} {} \; \
	|| chmod -R a+r "$(distdir)"
dist-gzip: distdir
	tardir=$(distdir) && $(am__tar) | eval GZIP= gzip $(GZIP_ENV) -c >$(distdir).tar.gz
	$(am__post_remove_distdir)

dist-bzip2: distdir
	tardir=$(distdir) && $(am__tar) | BZIP2=$${BZIP2--9} bzip2 -c >$(distdir).tar.bz2
	$(am__post_remove_distdir)

dist-lzip: distdir
	tardir=$(distdir) && $(am__tar) | lzip -c $${LZIP_OPT--9} >$(distdir).tar.lz
	$(am__post_remove_distdir)

dist-xz: distdir
	tardir=$(distdir) && $(am__tar) | XZ_OPT=$${XZ_OPT--e} xz -c >$(distdir).tar.xz
	$(am__post_remove_distdir)

dist-zstd: distdir
	tardir=$(distdir) && $(am__tar) | zstd -c $${ZSTD_CLEVEL-$${ZSTD_OPT--19}} >$(distdir).tar.zst
	$(am__post_remove_distdir)

dist-tarZ: distdir
	@echo WARNING: "Support for distribution archives compressed with" \
		       "legacy program 'compress' is deprecated." >&2
	@echo WARNING: "It will be removed altogether in Automake 2.0" >&2
	tardir=$(distdir) && $(am__tar) | compress -c >$(distdir).tar.Z
	$(am__post_remove_distdir)

dist-shar: distdir
	@echo WARNING: "Support for shar distribution archives is" \
	               "deprecated." >&2
	@echo WARNING: "It will be removed altogether in Automake 2.0" >&2
	shar $(distdir) | eval GZIP= gzip $(GZIP_ENV) -c >$(distdir).shar.gz
	$(am__post_remove_distdir)

dist-zip: distdir
	-rm -f $(distdir).zip
	zip -rq $(distdir).zip $(distdir)
	$(am__post_remove_distdir)

dist dist-all:
	$(MAKE) $(AM_MAKEFLAGS) $(DIST_TARGETS) am__post_remove_distdir='@:'
	$(am__post_remove_distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	case '$(DIST_ARCHIVES)' in \
	*.tar.gz*) \
	  eval GZIP= gzip $(GZIP_ENV) -dc $(distdir).tar.gz | $(am__untar) ;;\
	*.tar.bz2*) \
	  bzip2 -dc $(distdir).tar.bz2 | $(am__untar) ;;\
	*.tar.lz*) \
	  lzip -dc $(distdir).tar.lz | $(am__untar) ;;\
	*.tar.xz*) \
	  xz -dc $(distdir).tar.xz | $(am__untar) ;;\
	*.tar.Z*) \
	  uncompress -c $(distdir).tar.Z | $(am__untar) ;;\
	*.shar.gz*) \
	  eval GZIP= gzip $(GZIP_ENV) -dc $(distdir).shar.gz | unshar ;;\
	*.zip*) \
	  unzip $(distdir).zip ;;\
	*.tar.zst*) \
	  zstd -dc $(distdir).tar.zst | $(am__untar) ;;\
	esac
	chmod -R a-w $(distdir)
	chmod u+w $(distdir)
	mkdir $(distdir)/_build $(distdir)/_build/sub $(distdir)/_inst
	chmod a-w $(distdir)
	test -d $(distdir)/_build || exit 0; \
	dc_install_base=`$(am__cd) $(distdir)/_inst && pwd | sed -e 's,^[^:\\/]:[\\/],/,'` \
	  && dc_destdir="$${TMPDIR-/tmp}/am-dc-$$$$/" \
	  && am__cwd=`pwd` \
	  && $(am__cd) $(distdir)/_build/sub \
	  && ../../configure \
	    $(AM_DISTCHECK_CONFIGURE_FLAGS) \
	    $(DISTCHECK_CONFIGURE_FLAGS) \
	    --srcdir=../.. --prefix="$$dc_install_base" \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) $(AM_DISTCHECK_DVI_TARGET) \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) uninstall \
	  && $(MAKE) $(AM_MAKEFLAGS) distuninstallcheck_dir="$$dc_install_base" \
	        distuninstallcheck \
	  && chmod -R a-w "$$dc_install_base" \
	  && ({ \
	       (cd ../.. && umask 077 && mkdir "$$dc_destdir") \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" install \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" uninstall \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" \
	            distuninstallcheck_dir="$$dc_destdir" distuninstallcheck; \
	      } || { rm -rf "$$dc_destdir"; exit 1; }) \
	  && rm -rf "$$dc_destdir" \
	  && $(MAKE) $(AM_MAKEFLAGS) dist \
	  && rm -rf $(DIST_ARCHIVES) \
	  && $(MAKE) $(AM_MAKEFLAGS) distcleancheck \
	  && cd "$$am__cwd" \
	  || exit 1
	$(am__post_remove_distdir)
	@(echo "$(distdir) archives ready for distribution: "; \
	  list='$(DIST_ARCHIVES)'; for i in $$list; do echo $$i; done) | \
	  sed -e 1h -e 1s/./=/g -e 1p -e 1x -e '$$p' -e '$$x'
distuninstallcheck:
	@test -n '$(distuninstallcheck_dir)' || { \
	  echo 'ERROR: trying to run $@ with an empty' \
	       '$$(distuninstallcheck_dir)' >&2; \
	  exit 1; \
	}; \
	$(am__cd) '$(distuninstallcheck_dir)' || { \
	  echo 'ERROR: cannot chdir into $(distuninstallcheck_dir)' >&2; \
	  exit 1; \
	}; \
	test `$(am__distuninstallcheck_listfiles) | wc -l` -eq 0 \
	   || { echo "ERROR: files left after uninstall:" ; \
	        if test -n "$(DESTDIR)"; then \
	          echo "  (check DESTDIR support)"; \
	        fi ; \
	        $(distuninstallcheck_listfiles) ; \
	        exit 1; } >&2
distcleancheck: distclean
	@if test '$(srcdir)' = . ; then \
	  echo "ERROR: distcleancheck can only run from a VPATH build" ; \
	  exit 1 ; \
	fi
	@test `$(distcleancheck_listfiles) | wc -l` -eq 0 \
	  || { echo "ERROR: files left in build directory after distclean:" ; \
	       $(distcleancheck_listfiles) ; \
	       exit 1; } >&2
check-am: all-am
check: check-am
all-am: Makefile $(PROGRAMS) config.h
installdirs:
	for dir in "$(DESTDIR)$(bindir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	if test -z '$(STRIP)'; then \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	      install; \
	else \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	    "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'" install; \
	fi
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-binPROGRAMS clean-generic mostlyclean-am

distclean: distclean-am
	-rm -f $(am__CONFIG_DISTCLEAN_FILES)
		-rm -f ./$(DEPDIR)/cd_sdl.Po
	-rm -f ./$(DEPDIR)/chase.Po
	-rm -f ./$(DEPDIR)/cl_demo.Po
	-rm -f ./$(DEPDIR)/cl_hud.Po
	-rm -f ./$(DEPDIR)/cl_input.Po
	-rm -f ./$(DEPDIR)/cl_main.Po
	-rm -f ./$(DEPDIR)/cl_parse.Po
	-rm -f ./$(DEPDIR)/cl_tent.Po
	-rm -f ./$(DEPDIR)/cmd.Po
	-rm -f ./$(DEPDIR)/common.Po
	-rm -f ./$(DEPDIR)/console.Po
	-rm -f ./$(DEPDIR)/crc.Po
	-rm -f ./$(DEPDIR)/cvar.Po
	-rm -f ./$(DEPDIR)/d_edge.Po
	-rm -f ./$(DEPDIR)/d_fill.Po
	-rm -f ./$(DEPDIR)/d_init.Po
	-rm -f ./$(DEPDIR)/d_modech.Po
	-rm -f ./$(DEPDIR)/d_part.Po
	-rm -f ./$(DEPDIR)/d_polyse.Po
	-rm -f ./$(DEPDIR)/d_scan.Po
	-rm -f ./$(DEPDIR)/d_sky.Po
	-rm -f ./$(DEPDIR)/d_sprite.Po
	-rm -f ./$(DEPDIR)/d_surf.Po
	-rm -f ./$(DEPDIR)/d_vars.Po
	-rm -f ./$(DEPDIR)/d_zpoint.Po
	-rm -f ./$(DEPDIR)/draw.Po
	-rm -f ./$(DEPDIR)/host.Po
	-rm -f ./$(DEPDIR)/host_cmd.Po
	-rm -f ./$(DEPDIR)/keys.Po
	-rm -f ./$(DEPDIR)/mathlib.Po
	-rm -f ./$(DEPDIR)/menu.Po
	-rm -f ./$(DEPDIR)/model.Po
	-rm -f ./$(DEPDIR)/net_bsd.Po
	-rm -f ./$(DEPDIR)/net_dgrm.Po
	-rm -f ./$(DEPDIR)/net_loop.Po
	-rm -f ./$(DEPDIR)/net_main.Po
	-rm -f ./$(DEPDIR)/net_udp.Po
	-rm -f ./$(DEPDIR)/net_vcr.Po
	-rm -f ./$(DEPDIR)/net_wso.Po
	-rm -f ./$(DEPDIR)/nonintel.Po
	-rm -f ./$(DEPDIR)/pr_cmds.Po
	-rm -f ./$(DEPDIR)/pr_edict.Po
	-rm -f ./$(DEPDIR)/pr_exec.Po
	-rm -f ./$(DEPDIR)/r_aclip.Po
	-rm -f ./$(DEPDIR)/r_alias.Po
	-rm -f ./$(DEPDIR)/r_bsp.Po
	-rm -f ./$(DEPDIR)/r_draw.Po
	-rm -f ./$(DEPDIR)/r_edge.Po
	-rm -f ./$(DEPDIR)/r_efrag.Po
	-rm -f ./$(DEPDIR)/r_light.Po
	-rm -f ./$(DEPDIR)/r_main.Po
	-rm -f ./$(DEPDIR)/r_misc.Po
	-rm -f ./$(DEPDIR)/r_part.Po
	-rm -f ./$(DEPDIR)/r_sky.Po
	-rm -f ./$(DEPDIR)/r_sprite.Po
	-rm -f ./$(DEPDIR)/r_surf.Po
	-rm -f ./$(DEPDIR)/r_vars.Po
	-rm -f ./$(DEPDIR)/screen.Po
	-rm -f ./$(DEPDIR)/snd_dma.Po
	-rm -f ./$(DEPDIR)/snd_mem.Po
	-rm -f ./$(DEPDIR)/snd_mix.Po
	-rm -f ./$(DEPDIR)/snd_sdl.Po
	-rm -f ./$(DEPDIR)/sv_main.Po
	-rm -f ./$(DEPDIR)/sv_move.Po
	-rm -f ./$(DEPDIR)/sv_phys.Po
	-rm -f ./$(DEPDIR)/sv_user.Po
	-rm -f ./$(DEPDIR)/sys_sdl.Po
	-rm -f ./$(DEPDIR)/vid_sdl.Po
	-rm -f ./$(DEPDIR)/view.Po
	-rm -f ./$(DEPDIR)/wad.Po
	-rm -f ./$(DEPDIR)/world.Po
	-rm -f ./$(DEPDIR)/zone.Po
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-hdr distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am: install-binPROGRAMS

install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -f $(am__CONFIG_DISTCLEAN_FILES)
	-rm -rf $(top_srcdir)/autom4te.cache
		-rm -f ./$(DEPDIR)/cd_sdl.Po
	-rm -f ./$(DEPDIR)/chase.Po
	-rm -f ./$(DEPDIR)/cl_demo.Po
	-rm -f ./$(DEPDIR)/cl_hud.Po
	-rm -f ./$(DEPDIR)/cl_input.Po
	-rm -f ./$(DEPDIR)/cl_main.Po
	-rm -f ./$(DEPDIR)/cl_parse.Po
	-rm -f ./$(DEPDIR)/cl_tent.Po
	-rm -f ./$(DEPDIR)/cmd.Po
	-rm -f ./$(DEPDIR)/common.Po
	-rm -f ./$(DEPDIR)/console.Po
	-rm -f ./$(DEPDIR)/crc.Po
	-rm -f ./$(DEPDIR)/cvar.Po
	-rm -f ./$(DEPDIR)/d_edge.Po
	-rm -f ./$(DEPDIR)/d_fill.Po
	-rm -f ./$(DEPDIR)/d_init.Po
	-rm -f ./$(DEPDIR)/d_modech.Po
	-rm -f ./$(DEPDIR)/d_part.Po
	-rm -f ./$(DEPDIR)/d_polyse.Po
	-rm -f ./$(DEPDIR)/d_scan.Po
	-rm -f ./$(DEPDIR)/d_sky.Po
	-rm -f ./$(DEPDIR)/d_sprite.Po
	-rm -f ./$(DEPDIR)/d_surf.Po
	-rm -f ./$(DEPDIR)/d_vars.Po
	-rm -f ./$(DEPDIR)/d_zpoint.Po
	-rm -f ./$(DEPDIR)/draw.Po
	-rm -f ./$(DEPDIR)/host.Po
	-rm -f ./$(DEPDIR)/host_cmd.Po
	-rm -f ./$(DEPDIR)/keys.Po
	-rm -f ./$(DEPDIR)/mathlib.Po
	-rm -f ./$(DEPDIR)/menu.Po
	-rm -f ./$(DEPDIR)/model.Po
	-rm -f ./$(DEPDIR)/net_bsd.Po
	-rm -f ./$(DEPDIR)/net_dgrm.Po
	-rm -f ./$(DEPDIR)/net_loop.Po
	-rm -f ./$(DEPDIR)/net_main.Po
	-rm -f ./$(DEPDIR)/net_udp.Po
	-rm -f ./$(DEPDIR)/net_vcr.Po
	-rm -f ./$(DEPDIR)/net_wso.Po
	-rm -f ./$(DEPDIR)/nonintel.Po
	-rm -f ./$(DEPDIR)/pr_cmds.Po
	-rm -f ./$(DEPDIR)/pr_edict.Po
	-rm -f ./$(DEPDIR)/pr_exec.Po
	-rm -f ./$(DEPDIR)/r_aclip.Po
	-rm -f ./$(DEPDIR)/r_alias.Po
	-rm -f ./$(DEPDIR)/r_bsp.Po
	-rm -f ./$(DEPDIR)/r_draw.Po
	-rm -f ./$(DEPDIR)/r_edge.Po
	-rm -f ./$(DEPDIR)/r_efrag.Po
	-rm -f ./$(DEPDIR)/r_light.Po
	-rm -f ./$(DEPDIR)/r_main.Po
	-rm -f ./$(DEPDIR)/r_misc.Po
	-rm -f ./$(DEPDIR)/r_part.Po
	-rm -f ./$(DEPDIR)/r_sky.Po
	-rm -f ./$(DEPDIR)/r_sprite.Po
	-rm -f ./$(DEPDIR)/r_surf.Po
	-rm -f ./$(DEPDIR)/r_vars.Po
	-rm -f ./$(DEPDIR)/screen.Po
	-rm -f ./$(DEPDIR)/snd_dma.Po
	-rm -f ./$(DEPDIR)/snd_mem.Po
	-rm -f ./$(DEPDIR)/snd_mix.Po
	-rm -f ./$(DEPDIR)/snd_sdl.Po
	-rm -f ./$(DEPDIR)/sv_main.Po
	-rm -f ./$(DEPDIR)/sv_move.Po
	-rm -f ./$(DEPDIR)/sv_phys.Po
	-rm -f ./$(DEPDIR)/sv_user.Po
	-rm -f ./$(DEPDIR)/sys_sdl.Po
	-rm -f ./$(DEPDIR)/vid_sdl.Po
	-rm -f ./$(DEPDIR)/view.Po
	-rm -f ./$(DEPDIR)/wad.Po
	-rm -f ./$(DEPDIR)/world.Po
	-rm -f ./$(DEPDIR)/zone.Po
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-binPROGRAMS

.MAKE: all install-am install-strip

.PHONY: CTAGS GTAGS TAGS all all-am am--depfiles am--refresh check \
	check-am clean clean-binPROGRAMS clean-cscope clean-generic \
	cscope cscopelist-am ctags ctags-am dist dist-all dist-bzip2 \
	dist-gzip dist-lzip dist-shar dist-tarZ dist-xz dist-zip \
	dist-zstd distcheck distclean distclean-compile \
	distclean-generic distclean-hdr distclean-tags distcleancheck \
	distdir distuninstallcheck dvi dvi-am html html-am info \
	info-am install install-am install-binPROGRAMS install-data \
	install-data-am install-dvi install-dvi-am install-exec \
	install-exec-am install-html install-html-am install-info \
	install-info-am install-man install-pdf install-pdf-am \
	install-ps install-ps-am install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic pdf pdf-am ps ps-am tags tags-am uninstall \
	uninstall-am uninstall-binPROGRAMS

.PRECIOUS: Makefile


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
