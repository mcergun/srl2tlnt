# SRL2TLNT

## Introduction

This program aims to solve a problem I've faced at work. I was far away from the device that is controlled by serial channel and extending it to my place was not possible. Etiher I had to switch places with the coworker that was close to the device, or I had to use an extra layer of protocol to communicate with the device.

That's where I thought of Telnet. Telnet is old but supported on many platforms. There are an absurd number of clients and servers available on nearly all platforms.

_There are a lot of serial to telnet converters also. But using them defeats the whole purpose of this Toy Project._

## Road Plan

> 19.08.2018  
> My current plan is to get a cross platform serial library and employ it directly.  
> For telnet, however, I would like to implement the platform by myself as there is a logic behind the curtains.

> 21.08.2018  
> Captured message interaction from telnetd server and ubuntu telnet client.  
> This will serve as a good benchmark.

> 29.08.2018  
> `ProcessBuffer` function implements following pseudo code:  
> ```c++
> if (buf[0] == IAC)
> {
>         isCommand = true;
> }
> for (i = 1; i < count; ++i)
> {
>         if (buf[i] == IAC)
>         {
>                 if (buf[i + 1] != IAC)
>                 {
>                         HandleCommand(startingIdx, i, isCommand)
>                         startingIdx = i + 1
>                 }
>         }
> }
> HandleCommand(startingIdx, count, isCommand)
> ```

## Telnet

### Protocol Overview

Telnet employs a client/server design. Connection is initiated by the client and each side can dictate what is supported or not over the line. This makes the protocol a little bit complicated.

Some key points about the protocol:

- Telnet commands start with `IAC` byte and are exactly 3 bytes long, except for the negotiation commands `SB` and `SE` commands.
- When an `IAC` byte is needed to be sent inside another context, it has to be preceeded with another `IAC`.
