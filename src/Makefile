CC = g++
CFLAGS = -std=c++17
SRC = gap_instance.cpp gap_solution.cpp gap_solver.cpp h_mincost.cpp h_bestfit.cpp h_mt.cpp ls_swap_neighbour.cpp ls_swap.cpp ls_relocate_neighbour.cpp ls_relocate.cpp vnd.cpp main.cpp 
OBJ = $(SRC:.cpp=.o)
EXEC = gap_simulator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
