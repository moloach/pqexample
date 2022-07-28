INCL=-I /usr/include/postgresql
#CPPFLAGS += -I/usr/include/postgresql
# .SUFFIXES: .cpp .c
# .cpp.o:
# 	g++ ${INCL} -c $<

# .c.o:
# 	gcc ${INCL} -c $<

main:
	g++ ${INCL} pgconnection.cpp pgbackend.cpp main.cpp  -o pool -lpthread -lpq 


#all: main