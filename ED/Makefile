.DELETE_ON_ERROR:

all: .pdf 

.pdf:
	pdflatex -shell-escape apuntesed.tex
	pdflatex -shell-escape apuntesed.tex

clean:
	rm *.log *aux *.out *.toc *.pdf
	rm -rf _minted*