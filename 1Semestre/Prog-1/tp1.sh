wget http://dadosabertos.c3sl.ufpr.br/curitiba/BaseAlvaras/2022-02-23_Alvaras-Base_de_Dados.CSV | iconv -f ISO_8859-1 -t UTF8 2022-02-23_Alvaras-Base_de_Dados.CSV | grep -a 'BACACHERI' | grep -a 'FARMACIA' | cut -d ';' -f10 | sort > Farmacias.txt

echo "Rua das Farmacias: "
cat Farmacias.txt

echo "Numero de farmacias: " 
cat Farmacias.txt | wc -l
