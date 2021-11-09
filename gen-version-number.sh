#!/bin/env bash
#
# Copyright (C) 2021, 7ym0n
#
# Author: 7ym0n <bb.qnyd@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

set -euo pipefail

next-version() {

  prev_version="$1"; release_type="$2"

  if [[ "$prev_version" == "" ]]; then
    echo "could not read previous version"; exit 1
  fi

  possible_release_types="major feature bug alpha beta rc"

  if [[ ! ${possible_release_types[*]} =~ ${release_type} ]]; then
    echo "valid argument: [ ${possible_release_types[*]} ]"; exit 1
  fi

  major=0; minor=0; patch=0; pre=""; preversion=0

  # break down the version number into it's components
  regex="^([0-9]+).([0-9]+).([0-9]+)((-[a-z]+)([0-9]+))?$"
  if [[ $prev_version =~ $regex ]]; then
    major="${BASH_REMATCH[1]}"
    minor="${BASH_REMATCH[2]}"
    patch="${BASH_REMATCH[3]}"
    pre="${BASH_REMATCH[5]}"
    preversion="${BASH_REMATCH[6]}"
  else
    echo "previous version '$prev_version' is not a semantic version"
    exit 1
  fi

  # increment version number based on given release type
  case "$release_type" in
    "major")
      ((++major)); minor=0; patch=0; pre="";;
    "feature")
      ((++minor)); patch=0; pre="";;
    "bug")
      ((++patch)); pre="";;
    "alpha")
      if [[ -z "$preversion" ]];
      then
        preversion=0
      else
        if [[ "$pre" != "-alpha" ]];
        then
          preversion=1
        else ((++preversion))
        fi
      fi
      pre="-alpha$preversion";;
    "beta")
      if [[ -z "$preversion" ]];
      then
        preversion=0
      else
        if [[ "$pre" != "-beta" ]];
        then
          preversion=1
        else ((++preversion))
        fi
      fi
      pre="-beta$preversion";;
    "rc")
      if [[ -z "$preversion" ]];
      then
        preversion=0
      else
        if [[ "$pre" != "-rc" ]];
        then
          preversion=1
        else ((++preversion))
        fi
      fi
      pre="-rc$preversion";;
  esac

  next_version="${major}.${minor}.${patch}${pre}"

  echo "$next_version"
}
