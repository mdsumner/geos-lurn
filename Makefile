all : geos1 geos2

geos1 : geos1.c
        cc geos1.c -o geos1 -l geos_c

geos2 : geos2.c
        cc geos2.c -o geos2 -l geos_c


