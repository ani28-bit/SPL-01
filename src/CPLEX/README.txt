CPLEX Integration Notes:

1. Header files (.h) are in include/
2. Library files (.a, .so) are in lib/
3. Compile example:
   g++ main.cpp -I./cplex/include -L./cplex/lib -lcplex -lconcert -o tsp_ga
4. Make sure LD_LIBRARY_PATH includes ./cplex/lib if using .so files:
   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./cplex/lib
