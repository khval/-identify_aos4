
all: identify.ct updated

identify.ct: identify.cd
	CATCOMP identify.cd CTFILE identify.ct

updated: identify.ct
	protect update +s
	update
	date > updated
