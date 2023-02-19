
bin_PROGRAMS = nzpsdl

nzpsdl_LDADD = @MATHLIB@ @INETLIB@

nzpsdl_SOURCES =		\
	../source/adivtab.h		\
	../source/anorm_dots.h		\
	../source/anorms.h		\
	../source/block16.h		\
	../source/block8.h		\
	../source/bspfile.h		\
	../source/cd_sdl.c		\
	../source/cdaudio.h		\
	../source/chase.c			\
	../source/cl_demo.c		\
	../source/cl_input.c		\
	../source/cl_main.c		\
	../source/cl_parse.c		\
	../source/cl_tent.c		\
	../source/client.h		\
	../source/cmd.c			\
	../source/cmd.h			\
	../source/common.c		\
	../source/common.h		\
	../source/conproc.h		\
	../source/console.c		\
	../source/console.h		\
	../source/crc.c			\
	../source/crc.h			\
	../source/cvar.c			\
	../source/cvar.h			\
	../source/d_edge.c		\
	../source/d_fill.c		\
	../source/d_iface.h		\
	../source/d_ifacea.h		\
	../source/d_init.c		\
	../source/d_local.h		\
	../source/d_modech.c		\
	../source/d_part.c		\
	../source/d_polyse.c		\
	../source/d_scan.c		\
	../source/d_sky.c			\
	../source/d_sprite.c		\
	../source/d_surf.c		\
	../source/d_zpoint.c		\
	../source/draw.c			\
	../source/draw.h			\
	../source/host.c			\
	../source/host_cmd.c		\
	../source/input.h			\
	../source/keys.c			\
	../source/keys.h			\
	../source/mathlib.c		\
	../source/mathlib.h		\
	../source/menu.c			\
	../source/menu.h			\
	../source/model.c			\
	../source/model.h			\
	../source/modelgen.h		\
	../source/mpdosock.h		\
	../source/net.h			\
	../source/net_bsd.c		\
	../source/net_bw.h		\
	../source/net_dgrm.c		\
	../source/net_dgrm.h		\
	../source/net_loop.c		\
	../source/net_loop.h		\
	../source/net_main.c		\
	../source/net_udp.c		\
	../source/net_udp.h		\
	../source/net_vcr.c		\
	../source/net_vcr.h		\
	../source/net_wso.c		\
	../source/pr_cmds.c		\
	../source/pr_comp.h		\
	../source/pr_edict.c		\
	../source/pr_exec.c		\
	../source/progdefs.h		\
	../source/progs.h			\
	../source/protocol.h		\
	../source/quakeasm.h		\
	../source/quakedef.h		\
	../source/r_aclip.c		\
	../source/r_alias.c		\
	../source/r_bsp.c			\
	../source/r_draw.c		\
	../source/r_edge.c		\
	../source/r_efrag.c		\
	../source/r_light.c		\
	../source/r_local.h		\
	../source/r_main.c		\
	../source/r_misc.c		\
	../source/r_part.c		\
	../source/r_shared.h		\
	../source/r_sky.c			\
	../source/r_sprite.c		\
	../source/r_surf.c		\
	../source/r_vars.c		\
	../source/render.h		\
	../source/resource.h		\
	../source/cl_hud.c		\
	../source/cl_hud.h		\
	../source/screen.c		\
	../source/screen.h		\
	../source/server.h		\
	../source/snd_dma.c		\
	../source/snd_mem.c		\
	../source/snd_mix.c		\
	../source/snd_sdl.c		\
	../source/sound.h			\
	../source/spritegn.h		\
	../source/sv_main.c		\
	../source/sv_move.c		\
	../source/sv_phys.c		\
	../source/sv_user.c		\
	../source/sys.h			\
	../source/sys_sdl.c		\
	../source/vgamodes.h		\
	../source/vid.h			\
	../source/vid_sdl.c		\
	../source/view.c			\
	../source/view.h			\
	../source/wad.c			\
	../source/wad.h			\
	../source/winquake.h		\
	../source/world.c			\
	../source/world.h			\
	../source/zone.c			\
	../source/zone.h			\
	$(MAYBE_X86_SRCS) $(NONX86_SRCS)

NONX86_SRCS =			\
	../source/d_vars.c		\
	../source/nonintel.c


NULL_SRCS =			\
	../source/cd_null.c		\
	../source/in_null.c		\
	../source/net_none.c		\
	../source/snd_null.c		\
	../source/sys_null.c		\
	../source/vid_null.c

DOS_SRCS =			\
	../source/cd_audio.c		\
	../source/dosasm.S		\
	../source/dosisms.h		\
	../source/dos_v2.c		\
	../source/in_dos.c		\
	../source/mplib.c			\
	../source/mplpc.c			\
	../source/net_bw.c		\
	../source/net_comx.c		\
	../source/net_dos.c		\
	../source/net_ipx.c		\
	../source/net_ipx.h		\
	../source/net_ser.c		\
	../source/net_ser.h		\
	../source/snd_dos.c		\
	../source/snd_gus.c		\
	../source/sys_dos.c		\
	../source/vid_dos.c		\
	../source/vid_dos.h		\
	../source/vid_ext.c		\
	../source/vid_vga.c		\
	../source/vregset.c		\
	../source/vregset.h

WIN_SRCS =			\
	../source/cd_win.c		\
	../source/conproc.c		\
	../source/in_win.c		\
	../source/net_mp.c		\
	../source/net_mp.h		\
	../source/net_win.c		\
	../source/net_wins.c		\
	../source/net_wins.h		\
	../source/net_wipx.c		\
	../source/net_wipx.h		\
	../source/snd_win.c		\
	../source/sys_win.c		\
	../source/sys_wina.S		\
	../source/sys_wind.c		\
	../source/vid_win.c

LNX_SRCS =			\
	../source/cd_linux.c		\
	../source/snd_linux.c		\
	../source/sys_linux.c		\
	../source/vid_svgalib.c		\
	../source/vid_x.c

EXTRA_DIST =			\
	README.md		\
	README.SDL		\
	../source/progdefs.q1		\
	../source/progdefs.q2		\
	$(NULL_SRCS)		\
	$(WIN_SRCS)		\
	$(LNX_SRCS)		\
	data			\
	docs			\
	kit			