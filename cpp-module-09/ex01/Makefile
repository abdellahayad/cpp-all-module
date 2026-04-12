NAME = PPN

CXX = c++
CXXFLAGS =-Wall -Wextra -Werror -std=c++98

SRC = main.cpp RPN.cpp 
OBJ = $(SRC:.cpp=.o)
DEPS = RPN.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
