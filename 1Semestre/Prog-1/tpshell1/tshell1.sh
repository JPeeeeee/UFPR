#!/bin/bash

# removeTemp é a função que vai remover os arquivos de controle criados durante a execução do script.
removeTemp(){
  local lixo="bairros.txt index.html ocorrencias_2022.csv"
  rm $lixo
}

# move_156 é a função que move arquivos para o diretório disque156
move_156(){
  mv $1 disque156
}

# Baixa o index.html da base de dados
wget -q http://dadosabertos.c3sl.ufpr.br/curitiba/156/


# Criação do diretorio disque156
mkdir disque156

# Variável contendo todos os arquivos .csv de 2022
CSVS=$(cat "index.html" | cut -d '"' -f8 | sed 1,18d | head -n -3 | grep 2022 | grep -v Historico)

# Laço que faz o download de cada arquivo .csv que foi separado na variável, converte o arquivo para UTF-8 retira as duas primeiras linhas indesejadas do .csv e os coloca juntos em um unico arquivo chamado ocorrencias_2022.csv

# Para cada laço conlcuído com sucesso, o terminal avisa ao usuário que o arquivo em questão foi baixado.
for elemento in $CSVS
do
  wget -q http://dadosabertos.c3sl.ufpr.br/curitiba/156/$elemento
  iconv $elemento -f ISO-8859-1 -t UTF8 > $elemento.convertido
  mv $elemento.convertido $elemento
  sed -i '1,2d' $elemento
  cat $elemento >> ocorrencias_2022.csv
done

# Separação dos assuntos contidos em ocorrencias_2022.csv. O resultado é colocado no arquivo assuntos_geral.txt, que será movido para a pasta "disque156" em breve.
cut ocorrencias_2022.csv -d ';' -f6 | sort | uniq -c | sort -r -g > assuntos_geral.txt


# O arquivo "bairros.txt" contém todos os bairros existentes nos arquivos .csv de 2022 baixados anteriormente.
cut ocorrencias_2022.csv -d ';' -f10 | sort | uniq > bairros.txt
sed -i '1d' bairros.txt

# Usando como parâmetro os elementos do arquivo "bairros.txt", este laço transforma os espaços existentes em nomes de bairros com nome composto em underlines e separa, por frequencia, as 5 ocorrencias que mais aparecem
while read bairro
do
  grep -s -a ${bairro} ocorrencias_2022.csv | cut -d ';' -f6 | sort | uniq -c | sort -r -g | head -5 > "assuntos_"${bairro// /_}"_top5.txt"
done < bairros.txt

# Assim como no laço anterior, este usa como parâmetro os arquivos .csv que colocamos na variável CSVS no início do script e cria um arquivo com as 5 ocorrências mais frequentes de cada mês.
for arquivo in $CSVS
do
   cut $arquivo -d ';' -f6 | sort | uniq -c | sort -r -g | head -5 > "assuntos_"$(basename $arquivo | cut -d '_' -f1)"_top5.txt"
done

# Chama a função removeTemp que foi explicada no início do código.
removeTemp

# Chama a função move_156 que foi explicada no início do código e move o diretório disque156 para /nobackup/bcc/jpvs21 
move_156 "assuntos_* 2022-0*"
mv disque156/ /nobackup/bcc/jpvs21/
