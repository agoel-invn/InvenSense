#!/usr/bin/env bash

info() { echo "[INFO] ${*}"; }
warn() { echo "[WARNING] ${0}: ${*}"; }
error() { echo "[ERROR] ${0}: ${*}"; }

yell() { error "${*}" >&2; }
die() { yell "${*}"; exit 1; }
try() { "${@}" || die "cannot ${*}"; }

necho() { echo; info "${*}"; }
nechon() { necho "${*}"; echo; }

check_root() { (( EUID != 0 )) && die "Please run script as root"; }
