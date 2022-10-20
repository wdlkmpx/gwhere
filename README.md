# GWhere - removable media catalog management
**GWhere** allows you to manage a catalog of your CDs and any other removable media (such as hard disks, floppy disks, Zip disks, CD-ROMs, etc...) indexed in a database. With **GWhere** it is easy to browse your CDs or to make a quick search without needing to insert each CD one after another.

**GWhere** is not finalized, but it will still work and is very usable. **GWhere** is free and distributed under the free GNU GPL license. 
This program is written in C with GTK+

![gwhere](https://user-images.githubusercontent.com/17054153/197054084-511097bb-3bf0-4bfb-855a-2f3c0727c767.png)


## Compile from source in GNU/Linux
### Required packages / tools:
git, gcc, libtool, m4, autoconf, automake, make, pkgconf, gtk2

### Build & install:
```sh
git clone https://github.com/wdlkmpx/gwhere
cd gwhere
./autogen.sh
./configure
make -j
sudo make install
```

### Uninstall:
```sh
cd gwhere
sudo make uninstall
```
