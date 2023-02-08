# RootDO Minimal

This project aims to be a very slim alternative to sudo, doas and the original RootDO.

Unlike the original project, this has way fewer lines of code.
Any configuration is made by editing the source code.
The configuration file is rdo.h, but any desired features can be patched into rdo.c.
After editing rdo.h the program must be recompiled.
Doing things this way keeps rdo fast, secure and simple.
rdo.h is well commented and the code base is very small, so the source code is the documentation.

If you want to allow multiple users or groups to use the app either add the feature yourself or use the original rootdo or doas. If those don't suit you either, use sudo(don't know why you're here in that case). If you do add some features, make a pull request. I might merge it.

This app is very minimal. The base app is under 100 lines of code. The noconfig option reduces that to under 30 lines of code.

Keep in mind that the performance gain in real world applications is close to nothing.

### Installation

You can clone and build rootdo with the following set of commands (as root if necessary):

```sh
git clone https://github.com/stefan11111/rootdo.git
cd rootdo
make
make install
```
If you just want a word to type before commands that require root priviledges(allow all users to use rdo with no password) you can do the following (as root if necessary) :
 
```sh
git clone https://github.com/stefan11111/rootdo.git
cd rootdo
make noconfig
make install
```
Then you're good to go!

To uninstall (run as root if necessary):
```sh
make uninstall
```

For convenience, you can alias rdo to doas or sudo in your .bashrc or just rename the binary.
By default it is installed in /usr/local/bin.

### Usage

```sh
rdo [command]
```
