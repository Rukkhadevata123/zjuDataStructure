all:
	clang++ main.cpp cuckoo.cpp -o main -std=c++20 -O2
test:
	./main
	python3 test.py
report:
	xelatex report.tex
clean:
	rm -f main
	rm -f report.aux
	rm -f report.log
	rm -f report.out
	rm -f report.pdf
	rm -f report.toc
	rm -f report.synctex.gz
	rm -f report.synctex.gz\(busy\)
	rm -f report.synctex\(busy\)
	rm -f report.synctex
	rm -f report.fdb_latexmk
	rm -f report.fls
	rm -f report.blg
	rm -f report.bbl
	rm -f report.run.xml
	rm -f report.bcf
	rm -f report.lot
	rm -f report.lof
	rm -f report.xdv
