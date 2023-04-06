----------------------------MODEL-SQL-SERVER-BY-DANIEL-ELISHAKOV--------------------------
|				                                                         |
|                                    version 1.0 beta                                    |
|                                                                                        |
-----------------------------------all rights reserved------------------------------------
	
______________________________WELCOME TO README OF MY PROGRAM_____________________________

This ReadMe refers to the first stage of Model SQL web-server MSU task. This part requires database management system header and one more to work with sockets. My code is based on examples from http://cmcmsu.info/2course/

This part contains: dbms.hpp, sockets.hpp, server.cpp, client.cpp, dbms_test.cpp 

First header-file dbms.hpp deals with tables of database. Table itself is a binary file with special identifier FILE_SIGNATURE and certain data spread into columns and rows.
Example:

    /* |----------------|-------------------|----------|.....|---------|   */
    /*   FILE_SIGNATURE    struct TableInfo    Field1          FiedldN     */  

FILE_SIGNATURE is used to distinguish tables from other binary files, so if you try to open binary file with no signature, the program throws exception. There are also few more possible exceptions. All of them are described in exception class.

There are some structures defining properties of the table and its records. Those are TableStruct, FieldStruct etc. It may be uncomfortable to work with them and the methods they are used for, but it is necessary for the next part of the task and for comfortable operations with the table. dbms.h header is some kind of modification of the example from the website above.

I attach dbms_test.cpp file, in which I test some methods of the header and also makefile for building the program. Type "make dbms_test" and then "./dbms_test" to test it.

The next header sockets.hpp refers to socket implementation. The model of the task is so-called server-client and they somehow need to communicate. Here comes the socket-mechanism for this occasion. I decided to create main class base_socket with some in/output methods and 2 derived classes for server sockets and client sockets. There is one more derived class for server sockets in server.cpp. This model is suggested in task methodology and seems to be correct. There is also an exception class for some errors connected with creation, bindind etc. of socket. 

I attach server.cpp and client.cpp files, in which I test socket header and also makefile for building the program. Type "make sockets" and then "./server" and "./client" in OTHER CONSOLE WINDOW!!! The latter is important, because client and server should be on different consoles or computers to be tested.

The next 2.0 part will include lexical part of the task, which requires analyzers based on Model SQL language grammar and some other mechanisms for correct application of the program. 

Thank you for using my program and reading this.

P.S. Will be glad to answer your questions or getting the feedback on mail: s02190256.gse.cs.msu.ru

----------------------------MODEL-SQL-SERVER-BY-DANIEL-ELISHAKOV--------------------------
|				                                                         |
|                                    version 1.0 beta                                    |
|                                                                                        |
-----------------------------------all rights reserved------------------------------------