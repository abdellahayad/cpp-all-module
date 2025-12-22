NAME = Span

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror 

SRC = main.cpp Span.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = Span.hpp

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
