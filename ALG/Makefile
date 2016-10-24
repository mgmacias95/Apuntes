.DELETE_ON_ERROR:

all: .pdf 

.pdf:
	pdflatex -shell-escape apuntesag.tex
	pdflatex -shell-escape apuntesag.tex

clean:
	rm *.log *aux *.out *.toc *.pdf
	rm -rf _minted*