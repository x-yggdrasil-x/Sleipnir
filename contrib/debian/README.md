
Debian
====================
This directory contains files used to package odind/odin-qt
for Debian-based Linux systems. If you compile odind/odin-qt yourself, there are some useful files here.

## odin: URI support ##


odin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install odin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your odinqt binary to `/usr/bin`
and the `../../share/pixmaps/odin128.png` to `/usr/share/pixmaps`

odin-qt.protocol (KDE)

