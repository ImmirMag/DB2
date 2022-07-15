all:
	g++ -std=c++11 -O0 -g -pthread -o a.out \
	config/config.cpp config/iniparser.cpp config/dictionary.cpp \
	iface/iface.cpp			\
	handler/handler.cpp 	\
	commands/command.cpp 	\
	commands/resulter.cpp 	\
	commands/structures.cpp 	\
	operations/operations.cpp 	\
	data_format/data_format.cpp 	\
	main.cpp 