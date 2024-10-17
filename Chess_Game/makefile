all: clean compile run

compile: chessboard.cpp chesspiece.cpp main.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o main chessboard.cpp chesspiece.cpp main.cpp -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./main
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f main
