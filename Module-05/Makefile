NAME		= trains

SRC_DIR		= src
INC_DIR		= include
SRCS		= $(wildcard $(SRC_DIR)/*.cpp)
OBJS		= $(SRCS:.cpp=.o)
CXX			= c++
CXXFLAGS	= -std=c++17 -Wall -Wextra -Werror -I$(INC_DIR)
RM			= rm -rf

OUTPUT_EXT	= .result

all: $(NAME)

.cpp.o:
	@$(CXX) $(CXXFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) *$(OUTPUT_EXT)

re: fclean all

.PHONY: clean fclean re all
