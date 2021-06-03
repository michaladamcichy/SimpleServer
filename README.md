# SimpleServer

g++ -std=c++11 -Wall s.cpp -o s.out -lpthread -lstdc++ -ljsoncpp -lmysqlcppconn

./s.out port_to_run_server database_address database_port db_user db_password
db_password="_" jeżeli brak hasła

Uwagi:

Na późnym etapie pracy zdałem sobie sprawę, że używając synchronicznych send i receive nie jestem w stanie zaimplementować 30-sekundowego timeoutu i tak już zostawiłem.
Powinienem był użyć async_read i async_write.

Zapomniałem też o obsłudze requesta "DEL" - natomiast jest on analogiczny do pozostałych korzystających z bazy danych.

SCHEMAT BAZY DANYCH:
nazwa schematu: server
nazwa tabeli: keyvalues
kolumny: keyvalue_key (varchar(100)) oraz keyvalue_value (varchar(100))

