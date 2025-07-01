NAME = webserv
SERV = server
CLI = client
COMPILER = c++
FLAGS = -Wall -Werror -Wextra -g -std=c++98

SERVER =	Server/main.cpp 	\
			Server/Server.cpp

CLIENT =	Client/main.cpp		\
			Client/Client.cpp

OBJS =	$(SERVER:.cpp=.o)
OBJC =	$(CLIENT:.cpp=.o)

%.o : %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

# $(NAME) :

$(SERV) : $(OBJS)
	$(COMPILER) $(FLAGS) $(OBJS) -o $(SERV)

$(CLI) : $(OBJC)
	$(COMPILER) $(FLAGS) $(OBJC) -o $(CLI)

all : $(SERV) $(CLI)

Server : $(SERV)

clean :
	rm -f $(OBJS) $(OBJC)

fclean : clean
	rm -f $(SERV) $(CLI)

re : clean all

.PHONY : all clean fclean re
