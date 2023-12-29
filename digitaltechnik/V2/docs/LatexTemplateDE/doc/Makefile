.PHONY: default
default:
	pdflatex --interaction=nonstopmode muster-buch.tex > tex.log ; \
	pdflatex --interaction=nonstopmode muster-mitschrift.tex >> tex.log ; \
	pdflatex --interaction=nonstopmode muster-praesentation.tex >> tex.log ; \
	pdflatex --interaction=nonstopmode muster-skript.tex >> tex.log ; \
	pdflatex --interaction=nonstopmode muster-thesis.tex >> tex.log ; \
	pdflatex --interaction=nonstopmode docu_v6.tex >> tex.log

.PHONY: clean
clean:
	rm -rf \
		*.cb \
		*.cb2 \
		*.idx \
		*.mw \
		*.out \
		*.snm \
		*.toc \
		*.log \
		*.nav 

.PHONY: oesch
oesch:
	wget http://mirrors.ctan.org/fonts/oesch/oe.def
	wget http://mirrors.ctan.org/fonts/oesch/oesch.mf
	wget http://mirrors.ctan.org/fonts/oesch/oesch.sty
	wget http://mirrors.ctan.org/fonts/oesch/oesch_lig.mf
	wget http://mirrors.ctan.org/fonts/oesch/oesch_m.mf
	wget http://mirrors.ctan.org/fonts/oesch/oeschb.mf