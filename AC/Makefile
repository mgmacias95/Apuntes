.DELETE_ON_ERROR:

all: .pdf 

.pdf:
	pdflatex -shell-escape apuntesac.tex
	pdflatex -shell-escape apuntesac.tex

clean:
	rm *.log *aux *.out *.toc *.pdf
	rm -rf _minted*