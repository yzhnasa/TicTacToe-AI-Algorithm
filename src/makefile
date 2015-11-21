OBJS = tic_tac_toe.o state_expansion.o rule.o greate.o state.o
CC = g++
CFLAGS = -Wall -g

TicTacToe: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o TicTacToe
tic_tac_toe.o: tic_tac_toe.cpp tic_tac_toe.h 
	${CC} ${CFLAGS} -c tic_tac_toe.cpp
state_expansion.o: state_expansion.cpp state_expansion.h state.h greate.h rule.h
	${CC} ${CFLAGS} -c state_expansion.cpp
rule.o: rule.cpp rule.h state.h
	${CC} ${CFLAGS} -c rule.cpp
greate.o: greate.cpp greate.h state.h
	${CC} ${CFLAGS} -c greate.cpp
state.o: state.cpp state.h
	${CC} ${CFLAGS} -c state.cpp

clean:
	/bin/rm ${OBJS}
