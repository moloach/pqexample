INCL=-I /usr/include/postgresql
#CPPFLAGS += -I/usr/include/postgresql
# .SUFFIXES: .cpp .c
# .cpp.o:
# 	g++ ${INCL} -c $<

# .c.o:
# 	gcc ${INCL} -c $<

main:
	g++ ${INCL} pgconnection.cpp pgbackend.cpp main.cpp  -o pool -lpthread -lpq 

pqxx:
	clang++ -std=c++20 pqxx.cpp -lpq -lpqxx -o pqxx
#all: main