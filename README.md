# IP Over Proto

This project allows you to tunnel IPv4 traffic over 4 different transports (in order of lowest preference to highest).

1. DNS
2. ICMP
3. TCP
4. ICMP

## Building

The first step is to build the binaries. The client and server binaries will live at `./bin/iop-client` and `./bin/iop-server` respectively.

```bash
# Use this to build both client and server
make

# Build only the client
make client

# Build only the server
make server
```

You have the choice of manually installing the binary or automatically installing.

```bash
make install
```

Automatic installation will place the project(s) in the bin folder, with the names `iop-client` and `iop-server` respectively.

## Starting the client

The following options are available when starting the client:

* __--no-daemonize__ - By default, the client daemonizes after initialization. This flag disables that
* __-address__ _[IPv4 address]_ - Specifies the server to connect to
* __--force-dns__ - Forces the client to either tunnel over DNS (port 53) or abort the connection
* __--force-icmp__ - Forces the client to either tunnel over ICMP or abort the connection
* __--force-tcp__ - Forces the client to either tunnel over TCP (port 443) or abort the connection
* __--force-udp__ - Forces the client to either tunnel over UDP (port 9191) or abort the connection

For example, to start a background instance of the client that connects to a server at `1.2.3.4` over DNS, you could use

```bash
iop-client -address "1.2.3.4" --force-dns # DNS implies port 53
```

## Starting the server

The following options are available when starting the server:

* __--no-daemonize__ - By default the server daemonizes after initialization. This flag disables that
* __-bind__ _[address]_ - By default the server binds to 0.0.0.0. This option will override that behavior
* __-transports__ _[protocol list]_ - A comma-delimited list (no spaces) of transports that the server should support. By default, the server supports all of them. This option can be used to reduce that list

For example, to start a server that listens on `1.2.3.4` and only accepts connections over DNS or ICMP, you could use

```bash
iop-server -address "1.2.3.4" -transports "dns,icmp"
```
