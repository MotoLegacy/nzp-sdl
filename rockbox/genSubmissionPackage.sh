#!/bin/bash

set -o errexit

usage()
{
	echo "Usage: $0 -r <rockbox-path> -s <source-path> [-c]" 1>&2
	echo "     r: /path/to/rockbox source code dir (this needs to run before choosing the device and creating a build)"
	echo "     s: /path/to/nzp-sdl (this repository)"
        echo "     c: copy sources only (do not overwrite rockbox data)"
	exit 1
}

bail_if_missing()
{
	filepath="${1}"
	if [ -f ${filepath} ]
	then
		return 0
	else
		echo "[ERROR] Could not find file ${filepath}, exiting!"
		exit 1
	fi
}


while getopts ":r:s:hc" o; do
    case "${o}" in
        r)
            rockbox_path=${OPTARG}
            ;;
        s)
            source_path=${OPTARG}
            ;;
        c)
            copy_only=1
            ;;
        h|*)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${rockbox_path}" ] || [ -z "${source_path}" ]; then
    usage
fi

#############################

## Config data
#

# Gather file config data (data in our source repo we will copy)
NZP_OVL_LOADER_FILE="${source_path}"/rockbox/apps/plugins/nzp.c
APPS_SOURCES_STUB="${source_path}"/rockbox/apps/plugins/SOURCES.stub
SDL_SOURCES_NZP="${source_path}"/rockbox/apps/plugins/sdl/SOURCES.nzp
SOURCE_SDL_MAKE="${source_path}"/rockbox/apps/plugins/sdl/sdl.make.stub

# Gather target config data (data in rockbox source we will append to)
ROCKBOX_APPS_SOURCES_FILE="${rockbox_path}"/apps/plugins/SOURCES
ROCKBOX_SDL_SOURCES_FILE="${rockbox_path}"/apps/plugins/sdl/sdl.make


##############################

## Validate data
#

# Source repo
bail_if_missing "${NZP_OVL_LOADER_FILE}"
bail_if_missing "${APPS_SOURCES_STUB}"
bail_if_missing "${SDL_SOURCES_NZP}"
bail_if_missing "${SOURCE_SDL_MAKE}"

# rockbox repo
bail_if_missing "${ROCKBOX_APPS_SOURCES_FILE}"
bail_if_missing "${ROCKBOX_SDL_SOURCES_FILE}"

###############################


## Combine our packages into theirs
#

# ovl loader
rsync -avzP "${NZP_OVL_LOADER_FILE}" "${rockbox_path}"/apps/plugins/nzp.c
if [ -z "${copy_only}" ]
then
	cat "${APPS_SOURCES_STUB}" >> "${ROCKBOX_APPS_SOURCES_FILE}"
fi
# Modify sdl sources
rsync -avzP "${SDL_SOURCES_NZP}" "${rockbox_path}"/apps/plugins/sdl/SOURCES.nzp
if [ -z "${copy_only}" ]
then
	cat "${SOURCE_SDL_MAKE}" >> "${ROCKBOX_SDL_SOURCES_FILE}"
fi

# Create and copy NZP sources
ROCKBOX_SDL_PROGS_NZP="${rockbox_path}"/apps/plugins/sdl/progs/nzp
rm -rf "{ROCKBOX_SDL_PROGS_NZP}"
mkdir -p "${ROCKBOX_SDL_PROGS_NZP}"
rsync -avzP --delete "${source_path}"/source/ "${ROCKBOX_SDL_PROGS_NZP}"/


# Should be fine now
echo "SUCCESS!"
exit 0
