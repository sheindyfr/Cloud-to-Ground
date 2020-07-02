# Cloud To Ground
#### Server side for the IoT sensors data 

As part of a group project, 
this project implements the server side of a system 
that processes the data of IoT sensors of a filed.

**Participants**: [Racheli](https://github.com/Rachelch2000) [Sheindy](https://github.com/sheindyfr) [Ayala](https://github.com/ayalabe)  [Ruth](https://github.com/ruthst822) 

**Goal**: The main project simulates a smart filed. 
The sensors transmit a lot of data to a client side (the 'GETWAY'),
the client needs to decide if some operation (like: water the filed etc.)
is needed. The client use a *Data compression* Algorithm and send it to a server side.
The server gets the data from the client, figure out the data and restore it in a DataBase.

**Implementation**: We used Socket Programming on Windows ([winsock2 library](https://gist.github.com/piscisaureus/906386)).
