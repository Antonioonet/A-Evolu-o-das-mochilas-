# A Evolução das Mochilas

Este trabalho se baseia em uma aplicação de um algoritmo evolutivo para solucionar o clássico problema da mochila. 

## Instalação 
É necessário possuir o compilador GCC na sua máquina para rodar o código do trabalho.
```
git clone https://github.com/Antonioonet/A-Evolucao-das-mochilas.git
g++ -o s main.cpp
./s < arquivo_teste
```
Para diferentes casos de teste, é necessário mudar manualmente as variáveis N e K dentro do código. 
## Problema da Mochila

O Problema da Mochila é um clássico da computação e consiste em escolher os melhores itens para colocar em uma mochila, respeitando um limite de peso e maximizando o valor total. Imagine que você é um aventureiro com uma mochila que suporta um peso máximo e precisa decidir quais objetos levar entre vários disponíveis, cada um com um peso e um valor. Não dá para levar tudo, então é necessário otimizar a escolha.

## Experimento

Chamemos o peso máximo da mochila de **K** e a quantidade de itens de **N**.

### Métodos

- **Gene:**  
  Vetor de **N** bits representando quais itens serão escolhidos por esse indivíduo. Se o bit **i** estiver em 1, o item **i** será escolhido por essa resposta.

- **Fitness:**  
  A pontuação é baseada em quanto valor está sendo carregado na "mochila" do indivíduo. É aplicada uma penalidade quando o peso da mochila ultrapassa o valor **K**.

- **Reprodução:**  
  A nova geração é feita com elitismo, realizando o crossover entre dois indivíduos aleatórios dentro dos **X%** melhores indivíduos da geração anterior, repetindo esse procedimento **N** vezes, sendo **N** o tamanho da população do experimento.

- **Crossover:**  
  Cada bit **i** do novo indivíduo é determinado escolhendo aleatoriamente entre o bit **i** do pai 1 e do pai 2.

Há um fator de aleatoriedade tanto na reprodução (com mutação e seleção aleatória dos pais), quanto na população inicial. Assim, a mesma execução com os mesmos parâmetros pode culminar em resultados diferentes.

Foi estudado o desempenho do algoritmo nos casos de teste 10 e 11 do problema **Book Shop** do banco de problemas **CSES Files**. Foram desenvolvidas variações otimizadas do algoritmo para cada teste, buscando se adaptar aos desafios de cada um. Também foi comparado o desempenho do algoritmo em relação à solução ótima, encontrada usando programação dinâmica, e à solução gulosa.

### Resultados

- **Caso de teste 10:**  
\n  N = 1000 K = 100000
  O algoritmo não conseguiu atingir o resultado ótimo em nenhuma variação dos parâmetros testados. A melhor versão encontrada apresentou uma diferença média de apenas 0,2% em relação à resposta ótima, usando uma população maior (1000) com uma quantidade de gerações média (500) e um elitismo mais seletivo (10%), quando comparada a outras versões do experimento.

- **Caso de teste 11:**
 \n  N = 1000 K = 99999
  Esse foi um caso de teste em que diversas versões encontraram a resposta ótima, principalmente quando a população era maior (1000). Em versões com população menor (100), algumas execuções conseguiam chegar à resposta ótima em poucas gerações, enquanto outras não conseguiam atingir a resposta ótima mesmo após 1000 gerações, diferindo em apenas 1 ponto no resultado.  
  Para resolver esse problema, foi aplicada a política do genocídio: eliminar completamente a população atual e introduzir uma nova população aleatória caso não houvesse uma melhora significativa na resposta em 50 gerações. Com o genocídio, a grande maioria das execuções conseguiu chegar à resposta ótima.  
  Em uma leve variação, o melhor indivíduo da geração anterior fazia o crossover com alguns indivíduos da nova geração. Nessa variação, a resposta ótima era encontrada com uma quantidade ligeiramente menor de genocídios, em média.

### Discussão

Nota-se que, apesar de não ser sempre perfeito, o algoritmo evolutivo foi capaz de encontrar algumas respostas ótimas. Nesse sentido, uma população grande, mesmo que com menos rodadas de treino, demonstrou ser um fator fundamental para encontrar boas respostas. As adaptações do genocídio no caso de teste 11 também se mostraram uma solução interessante para resolver o problema em que a população parecia ficar "presa" em uma resposta.


## Links

Explicação problema da mochila: https://noic.com.br/materiais-informatica/curso/dp-02/

Problema de onde foram retirados os casos de teste do experimento 
