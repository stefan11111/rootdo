# RootDO Minimal

This project aims to be a very slim alternative to sudo, doas and the original RootDO.

Unlike the original project, this has way fewer lines of code.
Any configuration is made by editing the sourcecode.
The configuration file is rdo.h, but any desired features can be patched into rdo.c.
After editing rdo.h the program must be recompiled.
Doing things this way is more efficient than having a separate config file.
rdo.h is well commented and the code base is very small, so the source code if the documentation.

You can remove rdo.c and replace it with rdo.noconfig.c.
Doing this is not recommended as it removes all security.
This removes the need for config files as this allows all users on the system to use RootDO without password.
If you do this, you can also remove rdo.h, as it is only a config file, which this doesn't need.

This app is very minimal. If you want to allow multiple users or groups to use the app either add the feature yourself or use the original rootdo or doas. If those don't suit you either, use sudo(don't know why you're here in that case). If you do add some features, make a pull request. I might merge it.

Keep in mind thet the performance gain in real world applications is close to nothing.

### Installation

You can clone and build rdo with the following set of commands:

```sh
git clone https://codeberg.org/sw1tchbl4d3/rdo
cd rdo
make
sudo make install
```

Then you're good to go!

To uninstall:
```sh
sudo make uninstall
```

### Usage

```sh
rdo [command]
```
