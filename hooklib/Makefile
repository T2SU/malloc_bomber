CC = clang
CFLAGS = -Wall -Wextra -Werror
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

SRCS = main
LIB_SRCS = rd_route/rd_route.c
INC = -I./ -I./rd_route/

FINAL_SRCS = $(addsuffix .cpp, $(SRCS))
FINAL_OBJS = $(FINAL_SRCS:.cpp=.o) $(LIB_SRCS:.c=.o)

NAME = testmalloc.dylib

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(FINAL_OBJS)
	$(CXX) $(CXXFLAGS) -dynamiclib -o $@ $^

clean:
	rm -f $(FINAL_OBJS)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re