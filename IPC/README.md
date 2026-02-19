# QNX 8.0 Inter Process Communication Foundations

An exploration of Inter-Process Communication (IPC) primitives within the QNX 8.0 (SDP 8.0) microkernel architecture. This project demonstrates the evolution from basic manual connection management to a robust, name-based client-server model capable of handling concurrent asynchronous pulses and synchronous messages.

## Overview
The goal of this project was to master the "QNX Way" of communication. In a microkernel OS, services are decoupled; therefore, efficient and reliable IPC is the backbone of the system. This repository covers the implementation of the **Send/Receive/Reply** protocol and **Asynchronous Pulses**, using the QNX Native Networking (QNET) style discovery via the Name Service.

## Capabilities
- **Synchronous Messaging:** Client blocks until the server processes the data and sends a reply, ensuring data integrity.
- **Asynchronous Heartbeats:** Non-blocking pulses used for health monitoring without stalling the sender.
- **Dynamic Discovery:** Uses `name_attach` and `name_open` to abstract away Process IDs (PIDs), allowing for a self-healing architecture.
- **Unified Server Logic:** A single server loop capable of discriminating between pulse signals and structured data messages using `rcvid` evaluation.

## Project Structure
```text
IPC/
├── server/                 # The Server Provider
│   ├── src/
│   │   ├── server.cpp      # Main server loop (MsgReceive logic)
│   │   └── shared_header.hpp # Shared protocol definition
├── client_pulse/           # Asynchronous "Heartbeat" Client
│   ├── src/
│   │   └── client_pulse.cpp
├── client_msg/            # Synchronous "Command" Client
│   ├── src/
│   │   ├── client_msg.cpp
│   │   └── shared_header.hpp # Shared protocol definition
├── Stage 1.png 
├── Stage 2.png
├── Stage 3, Client.png
├── Stage 3, Concurrency.png
└── Stage 3, Server.png
```

## Development Stages
# Stage 1: Manual Connection (PID/CHID)
The initial phase focused on the "manual" way of establishing a connection in QNX.
* Server: Created a communication channel using ChannelCreate(). It outputted its PID and CHID to the console and entered a blocking MsgReceive() loop.
* Client Pulse: Required the manual input of the Server's PID and CHID to establish a connection via ConnectAttach(). Once connected, it sent a pulse every 2 seconds.

# Stage 2: Service Discovery (Name Attach)
To make the system more robust, the connection logic was refactored to use the GNS (Global Name Service) approach.
* Server: Updated to use name_attach(). This registered the service under a human-readable string (my_qnx_server) in the QNX pathname space.
* Client Pulse: Updated to use name_open(). The client now "finds" the server by its name, removing the need for hardcoded PIDs or manual command-line arguments.

# Stage 3: Message Protocol & Concurrency
The final stage introduced complexity by handling different types of data (Messages vs. Pulses) simultaneously.
* Shared Header: Implemented shared_header.hpp to define a unified union-based message structure. This ensures the Server correctly interprets the incoming bytes based on the rcvid.
* Server: Enhanced to differentiate between rcvid == 0 (Pulses) and rcvid > 0 (Messages). For messages, the server now processes data and sends a synchronous MsgReply().
* Client Message: A new client was created to send complex data structures (strings and integers). It demonstrates the blocking nature of MsgSend(), where the client waits for the Server's acknowledgement before continuing.
* Concurrency: Demonstrated the microkernel's ability to handle multiple clients (Pulse and Msg) talking to a single server instance simultaneously.
