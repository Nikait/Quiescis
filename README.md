# Quiescis 1.3.2

<b>Quescis</b> is a powerful Remote Access Trojan for windows computer on C++

## Update 1.3.2
     1. Passive keylogger! (command keydump)
     2. Many improvements and optimizations

![alt text](img/header.png)

# Installing
## Server
    - Clone this repository 
    - Get a static ip or purchase VDS
    - Server Questions cross platform
      you can run it on linux distributions
      and windows

### Config settings
|     option     |                     description                         |
| -------------- |:--------------------------------------------------------|
| chrome_stealer | connect sqlite3.h and sqlite3.cpp files to your project |
|       IP       | white ip of server (default 127.0.0.1)                  |
|      PORT      | port of ip (default 4001)                               |


### <b>Linux distributions</b>:<br/>
   - cd server/server
   - set Config.h, change PORT
   - g++ server.cpp -w
   - ./a.out
   
### <b>Windows</b>:<br/>
   - cd server
   - open server.sln in Visual Studio
   - change PORT in Config.h
   - compile Ctrl + F5
   - server.exe in Debug/
   
## Client

### Config settings
|     option     |                     description                         |
| -------------- |:--------------------------------------------------------|
|    autorun     | add rat to startup (1-on, 0-off)                        |
| chrome_stealer | connect sqlite3.h and sqlite3.cpp files to your project |
|       IP       | white ip of server (default 127.0.0.1)                  |
|      PORT      | port of ip (default 4001)                               |
|  autorun_name  | file name at startup (default: "explorer.exe")          |
|      lang      | language the victime machine (optional) (default: "ru") |

    - Open in Visual Studio client/client.sln
    - Set the Config.h
    - Compile Ctrl + F5

# Features
- ⚙️ Autorun
- 📋 Information of system

![alt text](img/info.png)

- 🔭 Browse directories, delete files / folders

![alt text](img/ls.png)

![alt text](img/rm.png)

- ✔️ View all processes

![alt text](img/ps.png)

- Ability to delete a process

![alt text](img/kill.png)

- 🔒 Encrypting files and directories

before:

![alt text](img/cryptfile_before.png)

after:

![alt text](img/cryptfile_after.png)

- 📲 download file

![alt text](img/download.png)

- 📲 chrome stealer
-    get history
-    get information about downloaded files
-    get search requests
![alt text](img/chrome_st.png)

- 🔌 Shutting down the operating system
- 😄 Throw Error MessageBox

![alt text](img/error.png)

# Commands
|   command   |                    description                 |
| ----------- |:-----------------------------------------------|
|     pwd     |  find out current directory                    |
|     ls      |  list files and dirs                           |
|  rm, rmdir  |  delete file; delete directory                 |
|    info     |  system information (cpu, gpu hardware id, os) |
|     ps      |  process info                                  |
|    kill     |  kill process                                  |
|   keydump   |  dump all recorded logs by keylogger           |
|  cryptfile  |  encrypt file        with using XOR            |
|  cryptdir   |  encrypt directory   with using XOR            |
|  download   |  download file                                 |
|  chrome_st  |  chrome history stealer                        |
|  shutdown   |  shutting down                                 |
|   error     |  throw error MessageBox                        |

#  Donate
    monero: 
    48TmwHGVsqSKgD7giTALoK7P2muKLTJn5R8s5XtKZL1jEr4MJFBAwczVtofuFGvzsT1CzTcFXotwZCDno1UsskqFFZe9wVC

***
    bitcoin:
    18LKUKWAUBAFKzLBdFFkt687vh8rMPhL1u
***
    ethereum:
    0x189a9436b2fbBd0b1C3927E8a398379DBb7105AA
