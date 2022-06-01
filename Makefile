CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++17

SRCS = main
INC = -I./

FINAL_SRCS = $(addsuffix .cpp, $(SRCS))
FINAL_OBJS = $(FINAL_SRCS:.cpp=.o)

NAME = malloct
HOOKLIB = hooklib

all: $(NAME) $(HOOKLIB)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(FINAL_OBJS)
	@make -C ./hooklib
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(FINAL_OBJS)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re