CXX = g++
CXXFLAGS = -std=c++17 -g -O2
TARGET = main
PYTHON = python3

all: $(TARGET)

$(TARGET): main.cpp expression_evaluator.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

report:
	xelatex report.tex

run_cpp: $(TARGET)
	./$(TARGET) > cpp_output.txt

valgrind_cpp: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

run_python:
	$(PYTHON) test.py > python_output.txt

test: run_cpp run_python
	@bash compare_results.sh

clean:
	rm -f $(TARGET)
	rm -f cpp_output.txt python_output.txt
	rm -f report.aux report.log report.out report.pdf report.toc
	rm -f report.synctex.gz report.synctex.gz\(busy\) report.synctex\(busy\)
	rm -f report.synctex report.fdb_latexmk report.fls report.blg
	rm -f report.bbl report.run.xml report.bcf report.lot report.lof report.xdv
