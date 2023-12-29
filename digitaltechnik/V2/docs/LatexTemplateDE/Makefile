.PHONY: all
all:
	cd "Ausführliche_Dokumentation" && \
		$(MAKE) oesch default
	cd "doc" && \
		$(MAKE) oesch default
	cd "Vorlage" && \
		$(MAKE) oesch default

.PHONY: clean
clean:
	cd Vorlage && \
		$(MAKE) clean
	cd doc && \
		$(MAKE) clean
	cd Ausführliche_Dokumentation && \
		$(MAKE) clean
