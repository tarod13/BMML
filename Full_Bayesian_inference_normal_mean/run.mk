# run.mk

results : results.csv plotter.py
	python plotter.py

results.csv : header.h
	./header.h

header.h : main.c
	gcc main.c -lm -o header.h
