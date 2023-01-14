# RootDO Minimal

This project aims to be a very slim alternative to sudo, doas and the original rootdo.

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

### Benchmarks

The benchmark: Execute `whoami` (GNU coreutils 9.1) 10000 times.

Keep in mind thet the performance gain in real world applications is close to nothing.

But it's fun!

The benchmark can be executed through a Docker container by running:

```
make bench-build bench-run
```
