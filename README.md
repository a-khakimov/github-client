# github-client

Простая консольная утилита для отображения информации о репозитории и списка коммитов.

## Зависимости

* [libcurl](https://github.com/curl/curl)
* [nlohmann-json](https://github.com/nlohmann/json)

## Сборка

### Linux (Ubuntu)

#### Установка зависимостей

```bash
$ apt install -y nlohmann-json-dev
$ apt install libcurl4-openssl-dev
```

#### Сборка

```bash
$ make
```

### Windows (msys)

#### Установка зависимостей

```
# pacman -S libcurl-devel
# pacman -S mingw-w64-x86_64-nlohmann-json
```

#### Сборка

`INC=-I/mingw64/include` - путь к `nlohmann/json.hpp`.

```
# INC=-I/mingw64/include make
```

## Запуск

Usage-сообщение:

```bash
$ ./github-client -h
Usage:
	./github-client
Arguments:
	 -h  Help
	 -r  <repo>
	 -o  <owner>
	 -c  Print commits for last [day]|[week]|[month]
	 -i  Print repo information
```

Информация о репозитори:

```bash
$ ./github-client -o curl -r curl -i
Full name: curl/curl
Homepage: https://curl.haxx.se/
Url: git://github.com/curl/curl.git
Languages: C
Created: 2010-03-18T22:32:22Z
Updated: 2020-09-07T16:03:23Z
Description: A command line tool and library for transferring data with URL syntax, 
supporting HTTP, HTTPS, FTP, FTPS, GOPHER, TFTP, SCP, SFTP, SMB, TELNET, DICT, LDAP, 
LDAPS, MQTT, FILE, IMAP, SMTP, POP3, RTSP and RTMP. libcurl offers a myriad of powerful features
```

Список коммитов за неделю:

```bash
$ ./github-client -o curl -r curl -c week
--------------- Commits -------------------
                Date                Author   Message
2020-09-07T14:20:16Z       Daniel Stenberg [ openssl: consider ALERT_CERTIFICATE_EXPI ... ]
2020-09-07T15:08:07Z       Daniel Stenberg [ FAQ: refreshed some very old language ... ]
2020-09-07T09:08:35Z       Daniel Stenberg [ cmake: make HTTP_ONLY also disable MQTT ... ]
2020-09-07T08:46:55Z       Daniel Stenberg [ libtest: remove lib1541 leftoversCausese ... ]
2020-09-07T08:29:40Z       Daniel Stenberg [ tests/libtests: remove test 1900 and 203 ... ]
2020-09-06T19:27:41Z         Marc Hoersken [ CI/azure: add test number to title for d ... ]
....
--------------- Commits -------------------
```
