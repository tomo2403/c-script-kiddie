# LatexTemplateDE
Eine LaTeX-Vorlage mit vielen vordefinierten Befehlen. Perfekt für Einsteiger.

Verzeichnisstruktur:

./

    mircol-v6.tex:      Diese Datei enthält alle Befehlsdefinitionen.

doc/

    muster-*.pdf:       Diese PDFs werden in die Dokumentation eingebunden. Die dazugehörigen tex-Dateien können ebenfalls
        eingesehen werden.

    zfg_v6_doc.pdf:     Die Dokumentation zur Vorlage. Enhält Befehlslisten und Beispiele.

Vorlage/:               Diesen Ordner sollte man als Grundlage für eine neues Projekt verwenden.

    index.ist:          Diese Datei dient der Konfiguration von makeindex.

	quellen.bib:		Die BibTex-Datei. Diese darf nicht umbenannt werden.

	titel.jpg:			Exisitert diese Datei, wird wie automatisch als Titelbild in die PDF übernommen. Fehlt sie, bleibt der Platz leer.

	Vorlage.tex:		In dieser Datei wird gearbeitet. Sie kann beliebig umbenannt werden
	    und wie jede tex-Datei bearbeitet werden. Details siehe doc/zfg_v6_doc.pdf.
