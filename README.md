# Algorithms-and-Data-Structure_I

### Ex1) Simple hello world

Hello World para testar debugger.


### Ex2) Names in a single dynamic string

- Faça um programa que armazena nomes.
- O programa deve armazenar todos os nomes na mesma tring.
- O tamanho da string deve crescer e diminuir conforme nomes forem colocados ou removidos. Não pode ter desperdício de memória.
- Faça o seguinte menu:
1) Adicionar nome
2) Remover nome
3) Listar
4) Sair


### Ex3) Different data on a single dynamic void buffer

- Faça uma agenda capaz de incluir, apagar, buscar e listar quantas pessoas o usuário desejar, porém, toda a informação incluída na agenda deve ficar num único lugar chamado: “void *pBuffer”.
- Não pergunte para o usuário quantas pessoas ele vai incluir.
- Nãoo pode alocar espaço para mais pessoas do que o necessário.
- Cada pessoa tem nome[10], idade e telefone.


### Ex5) Dynamic struct

- Faça um programa que armazene a informação de várias pessoas.
- O programa só deve sair quando o usuário disser que não deseja mais entrar com os dados de outra pessoa.
- Antes de sair o programa deve apresentar, de forma organizada, os dados de todas as pessoas.


### Ex7) Basically the inverse of exercise 3

- O programa deve armazenar no máximo 10 pessoas.
- Todas as variáveis que forem usadas no programa deve ser ponteiros. A única exceção é o item 1 que deve ser uma variável global Pessoa pessoas[10].
- Os ponteiros devem apontar para um buffer chamado pBuffer onde os dados devem ser armazenados. 
- Por exemplo, um contador para um for deve ser um ponteiro para int e o int vai ficar armazenado dentro de pBuffer.
- Não pode usar struct dentro do pBuffer.


### Agenda) Basically an overpowered version of exercise 3

- Continuar a sua implementação da agenda, mas incluir o seguinte.
- Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
- Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
- Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
- Não pode usar struct em todo o programa.
- Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
- Implementar a base de dados da agenda usando lista duplamente ligada
- Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.


### AVL Tree) AVL Tree implementation with random numbers

- O programa só pergunta 1 número para o usuário quantos nós (n)
- O programa automaticamente gera n nós em sequência com valor aleatório e vai adicionando na árvore
- Use srand(time(0));
- Ao final, use um código de verificação para validar a árvore e dar ok
