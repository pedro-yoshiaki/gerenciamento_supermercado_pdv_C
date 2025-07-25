# 🛒 Sistema de Gerenciamento de Supermercado (PDV)
Este projeto é uma aplicação de console desenvolvida em linguagem C que simula as operações de um sistema de Ponto de Venda (PDV) e gerenciamento de um supermercado. O sistema abrange desde o controle de acesso de usuários até o abastecimento de produtos nas gôndolas e a finalização de uma compra no caixa.

## ✨ Funcionalidades Principais
O sistema é dividido em três etapas principais, cada uma utilizando estruturas de dados específicas para resolver problemas do mundo real.

### 1. Login e Gerenciamento de Usuários
- **Controle de Acesso**: O sistema inicia com uma tela de login que exige nome e prontuário do usuário. A validação é feita através de busca binária em um arquivo de usuários (`USUARIOS.DAT`).

- **Armazenamento e Ordenação**: Os dados dos usuários são mantidos em ordem alfabética crescente no arquivo `USUARIOS.DAT`. O sistema utiliza o algoritmo Bubble Sort para garantir essa ordenação sempre que um novo usuário é adicionado.

- **Cadastro Padrão e Adicional**: O sistema garante um cadastro padrão de usuários  e permite a adição e remoção de novos usuários, mantendo o arquivo sempre ordenado.

### 2. Abastecimento das Gôndolas
- **Estrutura de Pilha (LIFO)**: As gôndolas do supermercado são simuladas como 10 prateleiras, onde cada prateleira é uma Pilha com capacidade para 5 produtos. O princípio "Last In, First Out" (o último a entrar é o primeiro a sair) rege o abastecimento e a retirada de itens.

- **Acesso Restrito**: Apenas um usuário master (repositor) pode abastecer as prateleiras.
- **Carrinho de Compras**: O cliente utiliza um carrinho de compras, que também é implementado como uma Pilha, para guardar os produtos retirados das gôndolas.
- **Controle de Estoque**: O sistema alerta quando uma prateleira está cheia ou vazia  e permite a visualização do conteúdo das gôndolas.

### 3. Caixa / Ponto de Venda (PDV)
- **Estrutura de Fila (FIFO)**: A esteira do caixa é implementada como uma Fila, onde o primeiro produto a chegar é o primeiro a ser processado ("First In, First Out").
- **Processo de Checkout**: Os produtos são movidos do carrinho (Pilha) para a esteira (Fila) para serem processados.
- **Geração de Cupom Fiscal**: Ao final, o sistema processa todos os itens da Fila, calcula o valor total e exibe um cupom fiscal detalhado na tela.

## 🛠️ Tecnologias e Conceitos Aplicados
- Linguagem: C
- Estruturas de Dados:
     - `Struct` para modelagem de Usuários e Produtos.
     - Pilha Estática (implementada com Vetor) para as prateleiras e carrinho de compras.
     - Fila Estática (implementada com Vetor) para a esteira do caixa.
- Algoritmos:
     - `Bubble Sort` para ordenação de usuários.
     - `Busca Binária` para validação de login.
- Conceitos de Arquivos: Manipulação de arquivos binários (`.DAT`) para persistência de dados.
- Memória: Alocação dinâmica (`malloc`) para a leitura de dados do arquivo durante a busca.

## 🚀 Como Executar
- Compilar o Código: Utilize um compilador C (como o `GCC`) para compilar o arquivo fonte.
```C
gcc "main.c" -o supermercado.exe
```
Executar o Programa:
```C
./supermercado.exe
```
- Primeira Execução: Ao rodar pela primeira vez, o programa criará o arquivo `USUARIOS.DAT` com uma lista de usuários padrão, caso ele não exista.
- Login: Utilize um dos usuários padrão para acessar o sistema. Por exemplo:
```
Nome: Eurides Balbino da Silva
Prontuário: SP07102X
```
- Navegação: Após o login, um menu principal será exibido, permitindo acesso a todas as funcionalidades do sistema. 
- Para abastecer as gôndolas, a senha master padrão é `1234`.

## 🧠 Conclusão e Aprendizados
Este projeto foi fundamental para solidificar o conhecimento teórico em Estrutura de Dados, demonstrando como conceitos abstratos são aplicados para criar soluções funcionais e organizadas para problemas do cotidiano.

- **Aplicação Prática de Estruturas de Dados**: Ficou claro como a escolha da estrutura correta é crucial para a lógica do negócio. A Pilha (LIFO) se mostrou perfeita para simular o empilhamento de produtos em uma prateleira, enquanto a Fila (FIFO) foi a escolha natural para representar a ordem de atendimento em um caixa. 

- **Importância dos Algoritmos**: A exigência de manter os usuários ordenados para realizar uma busca binária no login não foi apenas um exercício acadêmico, mas uma demonstração prática de como a performance de um sistema pode ser otimizada com a combinação de ordenação e algoritmos de busca eficientes. 

- **Gerenciamento de Dados com Arquivos**: A manipulação de arquivos binários para persistir os dados dos usuários ensinou sobre a importância da gestão de dados fora da memória, garantindo que as informações não sejam perdidas ao final da execução do programa.

- **Desenvolvimento de um Sistema Modular**: A divisão do projeto em funções específicas para cada tarefa (login, gerenciar menus, manipular pilhas/filas) foi essencial para manter o código organizado, legível e de fácil manutenção, refletindo as boas práticas de engenharia de software.
