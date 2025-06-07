/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h> /*Ou windows.h para Windows, uso da função Sleep*/

/*Constantes*/
#define TOTPROFS 30
#define MAX_ITENS 5
#define NUM_PRATELEIRAS 10
#define TAM_CARRINHO 50


/*Tipos pré-definidos pelo programador*/
typedef struct
{
	char nome [100];
	char pront [10];
} reg;

typedef struct   
{             
	char nome[50];
    char descricao[100];
    float peso;
    float preco;
} 
Produto; 

typedef struct {
    Produto itens[MAX_ITENS];
    int topo; // Índice do último item
} PilhaEstatica;

// Estrutura do carrinho
typedef struct {
    Produto compras[TAM_CARRINHO];
    int topo;
} Carrinho;

// Estrutura da Fila
typedef struct {
    Produto itens[TAM_CARRINHO]; // Array para armazenar os produtos
    int inicio;              // Índice do primeiro elemento
    int fim;                 // Índice do próximo elemento vazio
    int tamanho;             // Quantidade atual de itens na fila
} Fila;

/*Variáveis Global*/

PilhaEstatica prateleiras[10]; 
Carrinho carrinho;
Fila esteira;

/*Protótipos de Funções*/
void cadastroDefault (reg * vet);
void bubbleSort(reg arr[], int n);
int buscaBinariaArquivo(char *arquivo, char *nome,  char *prontuario);
char    menu ();
void gerenciar (char E);
void exibirUsuarios(char *arquivo);
void removerUsuario(char *arquivo);
void novoUsuario(char *arquivo);
int compararRegistros(const reg *a, const reg *b);
void inicializar (void);
int validarSenhaMaster(void);
void inicializarPilha(PilhaEstatica prateleiras[], int numPrateleiras);
void status(PilhaEstatica prateleiras[], int numPrateleiras);
Produto lerProduto(void);
void adicionarItem(PilhaEstatica *p, Produto produto);
int escolherPrateleira();
void exibirGondula(PilhaEstatica* p, int gandula);
void adicionarItensAleatorios(PilhaEstatica prateleiras[], int numPrateleiras);
void exibirPrateleiras(PilhaEstatica prateleiras[], int numPrateleiras);
void inicializar_carrinho(Carrinho* carrinho);
int escolher_produto(PilhaEstatica* prateleira);
void adicionarCarrinho(Carrinho* c, Produto item);
Produto retirarProduto(PilhaEstatica* p, int prateleiraEscolhida, int posicao);
void exibirCarrinho(Carrinho* c);
void inicializarFila(Fila* fila);
void exibirFila(Fila* fila);
void moverEsteira(Carrinho* carrinho, Fila* esteira);
/*------------------------------------------------------------Corpo do programa------------------------------------------------------------------------------------------------------*/
int main (){
	char op;
	int i =0;

	setlocale(LC_ALL, "Portuguese"); /*Definir padrão da língua e não precisar usar tabela ASCII*/
	
/*1º Inicializar o programa e confirmar se os usuários padrão estão no arquivo .dat*/	
/*Se não existir o .dat ele vai avisar que USUARIOS.DAT é inexistente e em seguida criará um*/
	inicializar(); 

/*2º Capturar o login do usuário*/
	int tent = 3;
	char nome[100], prontuario[10];

	while (tent != 0)
	{
		system ("cls");
		printf ("Você tem %d tentativa(s) de login\n", tent);
		printf("\nNome do usuário: "); fgets(nome, 100, stdin);
		printf("Prontuário do usuário: "); fgets(prontuario, 10, stdin);
		/*Remover o caractere '\n' se ele estiver presente após fgets (quando aperta enter ele adiciona o \n que afeta na comparação*/
	    nome[strcspn(nome, "\n")] = '\0';
	    prontuario[strcspn(prontuario, "\n")] = '\0';
		
		/*Validar login*/
	    int pos = buscaBinariaArquivo("USUARIOS.DAT", nome, prontuario);
	    if (pos == -1) {
	        printf("\nUsuário ou prontuário inválido!\n");
	        tent = tent - 1;
	        getchar();
	        if (tent == 0) return -1;
	    } else {
	        printf("\nLogin bem-sucedido!\n"); break;
		}
	}	    

/* 3º Exibir Menu do sistema e inicializar as prateleiras*/
	sleep(1);  /*Para sistemas UNIX-like*/
    /*Sleep(2000); /*Para sistemas Windows*/
    
	inicializarPilha(prateleiras, NUM_PRATELEIRAS);
	inicializar_carrinho (&carrinho);
	inicializarFila (&esteira);
	adicionarItensAleatorios (prateleiras, NUM_PRATELEIRAS); /*Colocar itens para testar programa*/
	
	do
	{
		op = menu();
		gerenciar(op);
	}
	 while ( op!='0' );
	
	return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Funções*/
char op;
char    menu ()
{
	do
	{
   	 system ("cls");
   	 printf ("\n====== MENU PRINCIPAL ======");
   	 printf ("\n1. Abastecer Gôndolas  ");
   	 printf ("\n2. Caixa/PDV   	");
   	 printf ("\n3. Gerenciar Usuários 	");
   	 printf ("\n0. Sair             	");
   	 printf ("\n============================");
   	 printf ("\n   Escolha opção: ");
   	 fflush (stdin);
   	 op = getche();
    }
    while ( op < '0' || op > '3' );
    return (op);
}

void gerenciar (char E)
{
   switch (E)
   	{
  		 	case '1': { int opgerenciar;
						do
						{
						system ("cls");
						printf("\n========== ADMINISTRAR GÔNDOLA ==========");
						printf("\n1 - Acessar (APENAS USUÁRIO MASTER)\n");
						printf("2 - Voltar ao menu principal");
						printf("\n=========================================\n");
						printf("Escolha uma opção: ");
						opgerenciar = getche();
														
						switch (opgerenciar){
												case '1': 	if (validarSenhaMaster() == 1) {
																					
															do{	
																system ("cls");																				
																printf("\n============ MENU REPOSITOR ============");
																printf("\n1 - Abastecer prateleiras\n");
																printf("2 - Exibir gôndula");
																printf("\n========================================\n");
																status(prateleiras, NUM_PRATELEIRAS);
																printf ("\nPressione '0' para voltar\n\n");
																
																printf("Escolha uma opção: ");
																opgerenciar = getche();
																						
																switch (opgerenciar){
																					case '1': 	{																														
																								int p = escolherPrateleira();
																								Produto x = lerProduto();
																								adicionarItem(&prateleiras[p], x);																								
																								} break;
																					case '2': 	{
																								int c = escolherPrateleira();
																								exibirGondula(&prateleiras[c], c); break;
																								}																																																						
																					case '0': break;
																					default: printf("\nOpção inválida.\n"); getche(); break;																							
																											}
																} while (opgerenciar != '0'); break;
																							} else exit (0); break;  																								
												case '2': return; break; 
												default: printf("\nOpção inválida.\n"); getche(); break;
						   												}  
						} while (op != '2'); break;												
					}					
  		 case '2': 	{
  		 			int opgerenciar;
					do
					{
						system ("cls");
						printf("\n============ MENU COMPRAS ==============");
						printf("\n1 - Colocar produtos no carrinho\n");
						printf("2 - Visualizar carrinho\n");
						printf("3 - Exibir prateleiras\n");
						printf("4 - Gerar cupom fiscal");
						printf("\n========================================\n");
						status(prateleiras, NUM_PRATELEIRAS);
						printf ("\nPressione '0' para voltar\n\n");
						
						printf("Escolha uma opção: ");
						opgerenciar = getche();
						
						switch (opgerenciar){
											case '1': 	{char opcao;
													do 	{
														system ("cls");
														int Pescolhida = escolherPrateleira();
														exibirGondula(&prateleiras[Pescolhida], Pescolhida);
														printf("\nSe o produto desejado não está nessa prateleira selecione '0' para retornar, caso contrário\nPressione qualquer tecla para continuar... ");
														fflush (stdin); scanf ("%c", &opcao);
														if (opcao == '0') break;
														int produtoEscolhido = escolher_produto(&prateleiras[Pescolhida]);
        												Produto produto = retirarProduto(prateleiras, Pescolhida, produtoEscolhido);
        												adicionarCarrinho (&carrinho, produto);														
														printf("\nDeseja transferir mais produtos? (s/n): ");
        												opcao = getche ();
														} while (opcao == 's' || opcao == 'S'); break;
														}break;
											case'2': exibirCarrinho(&carrinho); getchar (); break;
											case'3': exibirPrateleiras(prateleiras, NUM_PRATELEIRAS); break;
											case'4': moverEsteira (&carrinho, &esteira);
													 getch(); system ("cls");
													 exibirFila (&esteira);
													 getchar (); exit (0); break;
											case '0': return; break;
											default: printf("\nOpção inválida.\n"); getche(); break;
											}
						
  		 			} while (op != '0'); break;
		
		   			}
		   
		   
		   
		   printf ("\n\nEm desenvolvimento..."); getch(); break;
  		 case '3': 	{char voltar;
  		 
  		 			do
					   {
	  		 			system ("cls");
	  					printf("\n====== GERENCIAR USUÁRIOS ======");
	  		 	  		printf("\n1 - Cadastrar Usuário\n");
			            printf("2 - Remover Usuário\n");
			            printf("3 - Exibir Usuários\n");
			            printf("4 - Restaurar padrão\n");
			            printf("5 - Voltar ao menu principal");
			            printf("\n================================\n");
			            printf("Escolha uma opção: ");
			            op = getche();
			            
						switch (op) {
					                case '1': novoUsuario("USUARIOS.DAT"); getch(); break;
					                case '2': removerUsuario("USUARIOS.DAT"); getch(); break;
					                case '3': exibirUsuarios("USUARIOS.DAT"); getch(); break;
					                case '4':{ 	reg padrao [TOTPROFS];
												cadastroDefault(padrao); 
												printf("\nPadrão de usuários restaurado"); getch(); 
											} break;
					                case '5': break;    
					                default: printf("\nOpção inválida.\n"); getche(); break;
		   							}  
						} while (op != '5'); break;	
           			}
   	 	 
		case '0':  exit(0); break;    
	}
}

void cadastroDefault (reg * vet)
{
	FILE * Arq;
	int i = 0;
    
    memset(vet, '\0', sizeof(vet)); /*Limpar o vetor, adicionar \0 no buffer de memória do vetor*/
    
	strcpy (vet[0].nome,"Domingos Lucas Latorre de Oliveira"); strcpy (vet[0].pront,"CJ146456"); /*strcpy = string copy, copiar o nome e colocar no vetor na posição inicial*/ 
	strcpy (vet[1].nome,"Leandro Pinto Santana"); strcpy (vet[1].pront,"CP220383");
	strcpy (vet[2].nome,"Rodrigo Ribeiro de Oliveira"); strcpy (vet[2].pront,"RG134168");
	strcpy (vet[3].nome,"Andre Luiz da Silva"); strcpy (vet[3].pront,"SP030028");
	strcpy (vet[4].nome,"Claudia Miyuki Werhmuller"); strcpy (vet[4].pront,"SP030041");
	strcpy (vet[5].nome,"Claudete de Oliveira Alves"); strcpy (vet[5].pront,"SP03020X");
	strcpy (vet[6].nome,"Francisco Verissimo Luciano"); strcpy (vet[6].pront,"SP030247");
	strcpy (vet[7].nome,"Luk Cho Man"); strcpy (vet[7].pront,"SP060380");
	strcpy (vet[8].nome,"Ivan Francolin Martinez"); strcpy (vet[8].pront,"SP060835");
	strcpy (vet[9].nome,"Joao Vianei Tamanini"); strcpy (vet[9].pront,"SP060914");
	strcpy (vet[10].nome,"Jose Oscar Machado Alexandre"); strcpy (vet[10].pront,"SP070038");
	strcpy (vet[11].nome,"Jose Braz de Araujo"); strcpy (vet[11].pront,"SP070385");
	strcpy (vet[12].nome,"Paulo Roberto de Abreu"); strcpy (vet[12].pront,"SP070816");
	strcpy (vet[13].nome,"Eurides Balbino da Silva"); strcpy (vet[13].pront,"SP07102X");
	strcpy (vet[14].nome,"Domingos Bernardo Gomes Santos"); strcpy (vet[14].pront,"SP090888");
	strcpy (vet[15].nome,"Andre Evandro Lourenco"); strcpy (vet[15].pront,"SP100092");
	strcpy (vet[16].nome,"Miguel Angelo Tancredi Molina"); strcpy (vet[16].pront,"SP102763");
	strcpy (vet[17].nome,"Antonio Airton Palladino"); strcpy (vet[17].pront,"SP112197");
	strcpy (vet[18].nome,"Luis Fernando Aires Branco Menegueti"); strcpy (vet[18].pront,"SP145385");
	strcpy (vet[19].nome,"Antonio Ferreira Viana"); strcpy (vet[19].pront,"SP200827");
	strcpy (vet[20].nome,"Leonardo Bertholdo"); strcpy (vet[20].pront,"SP204973");
	strcpy (vet[21].nome,"Marcelo Tavares de Santana"); strcpy (vet[21].pront,"SP20500X");
	strcpy (vet[22].nome,"Wagner de Paula Gomes"); strcpy (vet[22].pront,"SP215016");
	strcpy (vet[23].nome,"Daniel Marques Gomes de Morais"); strcpy (vet[23].pront,"SP220097");
	strcpy (vet[24].nome,"Alexandre Beletti Ferreira"); strcpy (vet[24].pront,"SP226117");
	strcpy (vet[25].nome,"Vladimir Camelo Pinto"); strcpy (vet[25].pront,"SP240291");
	strcpy (vet[26].nome,"Leonardo Andrade Motta de Lima"); strcpy (vet[26].pront,"SP24031X");
	strcpy (vet[27].nome,"Aldo Marcelo Paim"); strcpy (vet[27].pront,"SP240497");
	strcpy (vet[28].nome,"Cesar Lopes Fernandes"); strcpy (vet[28].pront,"SP890534");
	strcpy (vet[29].nome,"Josceli Maria Tenorio"); strcpy (vet[29].pront,"SZ124382");
    
	bubbleSort(vet, TOTPROFS);

	Arq = fopen ("USUARIOS.DAT", "wb"); /*dat para usar o fread e ler tudo de uma vez*/
    
	if (Arq == NULL)
  	  {
  		  printf ("\nERRO AO ABRIR ARQUIVO");
  		  getch();
  		  exit (0);
  	  }
  	  
	for (i = 0; i < 30; i++) {
		if (vet[i].nome[0] != '\0') { // Nome não vazio indica registro válido
	    fwrite(&vet[i], sizeof(reg), 1, Arq);
		}
	}
	fclose(Arq);
}

void bubbleSort(reg arr[], int n) { /*n = tamanho do vetor*/
    int i, j;        // Declaração de variáveis antes do for
    reg temp;      // Reg temporário para troca structs

    // Loop externo para cada string do array
    for (i = 0; i < n - 1; i++) {
        // Loop interno para comparar strings adjacentes
        for (j = 0; j < n - i - 1; j++) {
            // Se a string atual for "maior" que a próxima, trocamos
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int buscaBinariaArquivo(char *arquivo, char *nome,  char *prontuario) {
    FILE *Arq;
    reg *vet;
    int tamanho, i, esq, dir, meio;
    reg registroAtual;

    // Abrir o arquivo em modo leitura binária
    Arq = fopen(arquivo, "rb");
    if (Arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return -1;
    }

    // Determinar o tamanho do arquivo para saber quantos registros existem
    fseek(Arq, 0, SEEK_END);
    tamanho = ftell(Arq) / sizeof(reg); // Quantidade de registros
    rewind(Arq);

    // Alocar memória para armazenar todos os registros
    vet = (reg *)malloc(tamanho * sizeof(reg));
    if (vet == NULL) {
        printf("malloc devolveu NULL\n");
        fclose(Arq);
        return -1;
    }

    // Ler todos os registros do arquivo para o vetor
    fread(vet, sizeof(reg), tamanho, Arq);
    fclose(Arq);

    // Implementar a busca binária
    esq = 0;
    dir = tamanho - 1;
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        if (strcmp(vet[meio].nome, nome) == 0 && strcmp(vet[meio].pront, prontuario) == 0) {
            free(vet); // Liberar memória antes de retornar
            return meio; // Usuário encontrado
        } else if (strcmp(vet[meio].nome, nome) < 0) {
            esq = meio + 1; // Procura à direita
        } else {
            dir = meio - 1; // Procura à esquerda
        }
    }

    free(vet); // Liberar memória antes de retornar
    return -1; // Usuário não encontrado
}

void exibirUsuarios(char *arquivo) {
    FILE *Arq;
    reg usuario;
    
    Arq = fopen(arquivo, "rb");
    if (Arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\n\n======================= LISTA DE USUÁRIOS =======================\n\n");
    while (fread(&usuario, sizeof(reg), 1, Arq)) {
        printf("Nome: %s | Prontuário: %s\n", usuario.nome, usuario.pront);
    }
    printf("=================================================================\n");
    fclose(Arq);
}

void removerUsuario(char *arquivo) {
    FILE *Arq;
    reg *vet;
    char nome[100];
    int tamanho, i, j = 0, encontrado = -1;

    exibirUsuarios(arquivo);
    printf("\nDigite o nome do usuário a ser removido: ");
    fflush(stdin); fgets(nome, 100, stdin); nome[strcspn(nome, "\n")] = '\0';

    // Abrir arquivo e carregar usuários
    Arq = fopen(arquivo, "rb");
    if (Arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fseek(Arq, 0, SEEK_END);
    tamanho = ftell(Arq) / sizeof(reg);
    rewind(Arq);

    vet = (reg *)malloc(tamanho * sizeof(reg));
    fread(vet, sizeof(reg), tamanho, Arq);
    fclose(Arq);

    // Procurar o usuário
    for (i = 0; i < tamanho; i++) {
        if (strcmp(nome, vet[i].nome) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Usuário não encontrado.\n");
        free(vet);
        return;
    }

    // Ajustar vetor excluindo o encontrado
    for (i = 0; i < tamanho; i++) {
        if (i != encontrado) {
            vet[j] = vet[i];
            j++;
        }
    }

    // Regravar o arquivo
    Arq = fopen(arquivo, "wb");
    if (Arq == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        free(vet);
        return;
    }
    fwrite(vet, sizeof(reg), j, Arq);
    fclose(Arq);

    free(vet);
    printf("Usuário removido com sucesso!\n");
}

void novoUsuario(char *arquivo) {
    FILE *Arq;
    reg novo;
    reg *vet;
    int tamanho, i;

    // Abrir o arquivo em modo leitura/escrita binária
    Arq = fopen(arquivo, "rb+");
    if (Arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return;
    }

    // Determinar o tamanho atual do arquivo
    fseek(Arq, 0, SEEK_END);
    tamanho = ftell(Arq) / sizeof(reg); // Quantidade de registros
    rewind(Arq);

    // Alocar memória para armazenar todos os registros
    vet = (reg *)malloc((tamanho + 1) * sizeof(reg)); // +1 para o novo registro
    if (vet == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(Arq);
        return;
    }

    // Ler os registros existentes para o vetor
    fread(vet, sizeof(reg), tamanho, Arq);

    // Solicitar os dados do novo usuário
    printf("\n\nDigite o nome do novo usuário: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remover o \n do final
    printf("Digite o prontuário do novo usuário: ");
    fgets(novo.pront, sizeof(novo.pront), stdin);
    novo.pront[strcspn(novo.pront, "\n")] = '\0'; // Remover o \n do final

    // Adicionar o novo registro ao vetor
    vet[tamanho] = novo;
    tamanho++; // Atualizar o tamanho do vetor

    // Ordenar os registros usando Bubble Sort
    bubbleSort(vet, tamanho);

    // Reescrever o arquivo com os registros ordenados
    rewind(Arq);
    fwrite(vet, sizeof(reg), tamanho, Arq);

    // Fechar o arquivo e liberar memória
    fclose(Arq);
    free(vet);

    printf("\nNovo usuário cadastrado com sucesso e arquivo atualizado!\n");
}

void inicializar (void){
	FILE * Arq;
	int tamanho, i, j;
	reg * vet;
	
	Arq = fopen("USUARIOS.DAT", "rb"); /*Leitura binária*/
    if (Arq == NULL) {
        printf("ARQUIVO USUARIOS.DAT INEXISTENTE\n");
        printf("\nCriando novo arquivo padrão...\n");
        getche();
        reg vet [TOTPROFS];
        cadastroDefault(vet);
        return;
    } else{
    
    	// Determinar o tamanho do arquivo para saber quantos registros existem
    fseek(Arq, 0, SEEK_END);
    tamanho = ftell(Arq) / sizeof(reg); // Quantidade de registros
    rewind(Arq);

    // Alocar memória para armazenar todos os registros
    vet = (reg *)malloc(tamanho * sizeof(reg));
    if (vet == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(Arq);
    }

    // Ler todos os registros do arquivo para o vetor
    fread(vet, sizeof(reg), tamanho, Arq);
    fclose(Arq);

    
    reg *inicio = malloc(TOTPROFS * sizeof(reg));
	    if (inicio == NULL) {
		printf("Erro: Malloc devolveu NULL.\n");
		free(vet);
		}
    
	strcpy (inicio[0].nome,"Domingos Lucas Latorre de Oliveira"); strcpy (inicio[0].pront,"CJ146456"); /*strcpy = string copy, copiar o nome e colocar no vetor na posição inicial*/ 
	strcpy (inicio[1].nome,"Leandro Pinto Santana"); strcpy (inicio[1].pront,"CP220383");
	strcpy (inicio[2].nome,"Rodrigo Ribeiro de Oliveira"); strcpy (inicio[2].pront,"RG134168");
	strcpy (inicio[3].nome,"Andre Luiz da Silva"); strcpy (inicio[3].pront,"SP030028");
	strcpy (inicio[4].nome,"Claudia Miyuki Werhmuller"); strcpy (inicio[4].pront,"SP030041");
	strcpy (inicio[5].nome,"Claudete de Oliveira Alves"); strcpy (inicio[5].pront,"SP03020X");
	strcpy (inicio[6].nome,"Francisco Verissimo Luciano"); strcpy (inicio[6].pront,"SP030247");
	strcpy (inicio[7].nome,"Luk Cho Man"); strcpy (inicio[7].pront,"SP060380");
	strcpy (inicio[8].nome,"Ivan Francolin Martinez"); strcpy (inicio[8].pront,"SP060835");
	strcpy (inicio[9].nome,"Joao Vianei Tamanini"); strcpy (inicio[9].pront,"SP060914");
	strcpy (inicio[10].nome,"Jose Oscar Machado Alexandre"); strcpy (inicio[10].pront,"SP070038");
	strcpy (inicio[11].nome,"Jose Braz de Araujo"); strcpy (inicio[11].pront,"SP070385");
	strcpy (inicio[12].nome,"Paulo Roberto de Abreu"); strcpy (inicio[12].pront,"SP070816");
	strcpy (inicio[13].nome,"Eurides Balbino da Silva"); strcpy (inicio[13].pront,"SP07102X");
	strcpy (inicio[14].nome,"Domingos Bernardo Gomes Santos"); strcpy (inicio[14].pront,"SP090888");
	strcpy (inicio[15].nome,"Andre Evandro Lourenco"); strcpy (inicio[15].pront,"SP100092");
	strcpy (inicio[16].nome,"Miguel Angelo Tancredi Molina"); strcpy (inicio[16].pront,"SP102763");
	strcpy (inicio[17].nome,"Antonio Airton Palladino"); strcpy (inicio[17].pront,"SP112197");
	strcpy (inicio[18].nome,"Luis Fernando Aires Branco Menegueti"); strcpy (inicio[18].pront,"SP145385");
	strcpy (inicio[19].nome,"Antonio Ferreira Viana"); strcpy (inicio[19].pront,"SP200827");
	strcpy (inicio[20].nome,"Leonardo Bertholdo"); strcpy (inicio[20].pront,"SP204973");
	strcpy (inicio[21].nome,"Marcelo Tavares de Santana"); strcpy (inicio[21].pront,"SP20500X");
	strcpy (inicio[22].nome,"Wagner de Paula Gomes"); strcpy (inicio[22].pront,"SP215016");
	strcpy (inicio[23].nome,"Daniel Marques Gomes de Morais"); strcpy (inicio[23].pront,"SP220097");
	strcpy (inicio[24].nome,"Alexandre Beletti Ferreira"); strcpy (inicio[24].pront,"SP226117");
	strcpy (inicio[25].nome,"Vladimir Camelo Pinto"); strcpy (inicio[25].pront,"SP240291");
	strcpy (inicio[26].nome,"Leonardo Andrade Motta de Lima"); strcpy (inicio[26].pront,"SP24031X");
	strcpy (inicio[27].nome,"Aldo Marcelo Paim"); strcpy (inicio[27].pront,"SP240497");
	strcpy (inicio[28].nome,"Cesar Lopes Fernandes"); strcpy (inicio[28].pront,"SP890534");
	strcpy (inicio[29].nome,"Josceli Maria Tenorio"); strcpy (inicio[29].pront,"SZ124382");
    	
	// Comparar e adicionar os itens faltantes de "inicio" em "vet"
    
    for (i = 0; i < TOTPROFS; i++) {
        int encontrado = 0;
        for (j = 0; j < tamanho; j++) {
            if (compararRegistros(&inicio[i], &vet[j])) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) { /*se encontrado for 0*/
            vet = realloc(vet, (tamanho + 1) * sizeof(reg));
            if (vet == NULL) {
                printf("Erro ao alocar memória\n");
                exit(1);
            }
            vet[tamanho] = inicio[i];
            (tamanho)++;
        }
    }
    
    bubbleSort (vet, tamanho);

    // Salvar os registros atualizados de "vet" de volta ao arquivo
    Arq = fopen("USUARIOS.DAT", "wb");
    if (Arq == NULL) {
        printf("Erro ao abrir arquivo para escrita\n");
    } else {
        fwrite(vet, sizeof(reg), tamanho, Arq);
        fclose(Arq);
    }
     free(inicio);
	}
    // Liberar memória alocada
    free(vet);   
}

int compararRegistros(const reg *a, const reg *b) {
    return (strcmp(a->nome, b->nome) == 0 && strcmp(a->pront, b->pront) == 0);
}        

/* Função para validar a senha do usuário master */
int validarSenhaMaster(void) {
    char s1, s2, s3, s4;
    int tentativas = 3;

    while (tentativas > 0) {
    	system ("cls");
        printf("\nDigite a senha do usuário master (4 Caracteres): ");
        fflush (stdin); s1 = getch(); printf ("*");
        fflush (stdin); s2 = getch(); printf ("*");
        fflush (stdin); s3 = getch(); printf ("*");
        fflush (stdin); s4 = getch(); printf ("*");
		
		if (s1 == '1' && s2 == '2' && s3 == '3' && s4 == '4')
			return 1;
        else {
            tentativas--;
            printf("\nSenha incorreta! Tentativas restantes: %d\n", tentativas);
            getch();
        }
    }

    return 0; // Falha na autenticação
}
														
void status(PilhaEstatica prateleiras[], int numPrateleiras) {
	int i;
    printf("\n======== STATUS DAS PRATELEIRAS ========\n");
    for (i = 0; i < numPrateleiras; i++) {
        int quantidadeItens = prateleiras[i].topo + 1; // topo + 1 indica quantidade de itens
        printf("Prateleira %d: ", i);
        if (prateleiras[i].topo == -1) {
            printf("Vazia (0/%d preenchidos)\n", MAX_ITENS);
        } else if (prateleiras[i].topo == MAX_ITENS - 1) {
            printf("Cheia (%d/%d preenchidos)\n", MAX_ITENS, MAX_ITENS);
        } else {
            printf("Parcial (%d/%d preenchidos)\n", quantidadeItens, MAX_ITENS);
        }
    }
    printf("========================================\n");
}	

void inicializarPilha(PilhaEstatica prateleiras[], int numPrateleiras) {
    // Inicializa todas as prateleiras
    int j, i;
    
    for (i = 0; i < numPrateleiras; i++) {
        prateleiras[i].topo = -1; // Define o topo como -1 para indicar pilha vazia
        
        // Zera os campos dos itens das prateleiras
        for (j = 0; j < MAX_ITENS; j++) {
            prateleiras[i].itens[j].nome[0] = '\0'; // Zera o nome
            prateleiras[i].itens[j].descricao[0] = '\0'; // Zera a descrição
            prateleiras[i].itens[j].peso = 0.0f; // Zera o peso
            prateleiras[i].itens[j].preco = 0.0f; // Zera o preço
        }
    }
}

Produto lerProduto(void) {
	Produto p;
    do {
        printf("\nDigite o nome do produto: ");
        fgets(p.nome, sizeof(p.nome), stdin); // Lê até o limite do buffer
        p.nome[strcspn(p.nome, "\n")] = '\0'; // Remove a nova linha
        if (strlen(p.nome) == 0) {
            printf("Nome não pode ser vazio. Tente novamente.\n");
        }
    } while (strlen(p.nome) == 0);

    // Ler a descrição do produto e garantir que não seja deixado em branco
        printf("Digite a descrição do produto: ");
        fgets(p.descricao, sizeof(p.descricao), stdin); // Lê até o limite do buffer
        p.descricao[strcspn(p.descricao, "\n")] = '\0'; // Remove a nova linha
        
// Ler o peso do produto e garantir que seja um número válido e maior que zero
    do {
        printf("Digite o peso do produto (em kg): ");        
        // Verificar se a entrada é um número válido
        if (scanf("%f", &p.peso) != 1) {
            printf("Peso inválido. Tente novamente.\n");
            while(getchar() != '\n'); // Limpar o buffer de entrada
        } else if (&p.peso <= 0) {
            printf("Peso deve ser maior que zero. Tente novamente.\n");
        }
    } while (&p.peso <= 0); // Continua pedindo até que o peso seja válido

    // Ler o preço do produto e garantir que seja um número válido
    do {
        printf("Digite o preço do produto (em R$): ");
        if (scanf("%f", &p.preco) != 1) {
            printf("Preço inválido. Tente novamente.\n");
            while(getchar() != '\n'); // Limpar o buffer de entrada
        }
    } while (p.preco <= 0);

    // Limpar o buffer de entrada de qualquer caractere residual
    while(getchar() != '\n');

    return p;
}

void adicionarItem(PilhaEstatica *p, Produto produto) {
    if (p->topo < MAX_ITENS - 1) {
        p->topo++;
        p->itens[p->topo] = produto; // Adiciona o produto no topo
        printf("\nProduto '%s' adicionado.\n", produto.nome);
    } else {
        printf("\nA prateleira está cheia! Não é possível adicionar o produto.\n");
    }
}

// Função para escolher a prateleira
int escolherPrateleira() {
    int prateleiraEscolhida;
    char buffer[100];

    while (1) {
    	system ("cls");
        printf("\nEscolha a prateleira (0 a 9): ");
        fflush(stdin); // Limpa o buffer de entrada
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Verificar se o input contém apenas um número válido
            if (sscanf(buffer, "%d", &prateleiraEscolhida) == 1) {
                // Verificar se a escolha está dentro do intervalo válido
                if (prateleiraEscolhida >= 0 && prateleiraEscolhida < NUM_PRATELEIRAS) {
                    return prateleiraEscolhida;
                } else {
                    printf("\nOpção inválida! A prateleira deve ser entre 0 e 9.\n");
                    getch();
                }
            } else {
                printf("\nEntrada inválida! Por favor, digite um número.\n");
                getch();
            }
        }
    }
}

// Função para exibir a gondula (as prateleiras e seus itens)
void exibirGondula(PilhaEstatica* p, int gondula) {
	if (p->topo == -1) 
		{
	        printf("A prateleira esta vazia!\n");
	        getch();
	        return;
	    }
	    printf("\nItens na prateleira %d:\n", gondula);
	    printf("Topo = %d:\n", p->topo);
	    
	    int i;
	    for ( i = 0; i < MAX_ITENS; i++) 
		{
	        printf("\n------------- Posicao %d -------------\n", i); 
	        printf("Nome: %s      \n", p->itens[i].nome);
	        printf("Descricao: %s \n", p->itens[i].descricao);
	        printf("Preco: %.2f   \n", p->itens[i].preco);
	        printf("Peso: %.2f    \n", p->itens[i].peso);
	        printf("-------------------------------------\n");
	    }
		getch();
	    
}

void adicionarItensAleatorios(PilhaEstatica prateleiras[], int numPrateleiras) {
    // Lista de itens para adicionar
    int i;
	
	Produto itens[25] = {
        {"Arroz", "Pacote de 5kg", 5.0, 20.0},
        {"Feijão", "Pacote de 1kg", 1.0, 7.5},
        {"Macarrão", "Pacote de 500g", 0.5, 4.0},
        {"Açúcar", "Pacote de 2kg", 2.0, 5.0},
        {"Sal", "Pacote de 1kg", 1.0, 2.0},
        {"Café", "Pacote de 250g", 0.25, 10.0},
        {"Farinha", "Pacote de 1kg", 1.0, 6.0},
        {"Óleo", "Garrafa de 900ml", 0.9, 8.0},
        {"Leite", "Caixa de 1L", 1.0, 4.5},
        {"Biscoito", "Pacote de 400g", 0.4, 3.0},
        {"Chocolate", "Barra de 200g", 0.2, 12.0},
        {"Sabão", "Pacote com 5 unidades", 1.5, 15.0},
        {"Detergente", "Frasco de 500ml", 0.5, 3.5},
        {"Shampoo", "Frasco de 1L", 1.0, 20.0},
        {"Condicionador", "Frasco de 1L", 1.0, 18.0},
        {"Amaciante", "Frasco de 2L", 2.0, 10.0},
        {"Papel Higiênico", "Pacote com 12 rolos", 1.2, 15.0},
        {"Água", "Garrafa de 1.5L", 1.5, 2.0},
        {"Refrigerante", "Garrafa de 2L", 2.0, 6.0},
        {"Suco", "Caixa de 1L", 1.0, 5.0},
        {"Pão", "Pacote de 500g", 0.5, 4.0},
        {"Queijo", "Pacote de 300g", 0.3, 15.0},
        {"Presunto", "Pacote de 300g", 0.3, 12.0},
        {"Manteiga", "Pote de 200g", 0.2, 8.0},
        {"Iogurte", "Pote de 170g", 0.17, 3.0}
    };

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Adicionar itens aleatórios nas prateleiras
    for (i = 0; i < 25; i++) {
        int indicePrateleira = rand() % numPrateleiras; // Escolhe uma prateleira aleatoriamente
        if (prateleiras[indicePrateleira].topo < MAX_ITENS - 1) {
            adicionarItem(&prateleiras[indicePrateleira], itens[i]);
        } 
    }
}

void exibirPrateleiras(PilhaEstatica prateleiras[], int numPrateleiras) {
	int i, j;
    system("cls"); // Limpa a tela
    printf("\n========== CONTEÚDO DAS PRATELEIRAS ==========\n");

    for (i = 0; i < numPrateleiras; i++) {
        printf("\nPrateleira %d:\n", i);

        if (prateleiras[i].topo == -1) {
            printf("  [Vazia]\n");
        } else {
            for (j = 0; j < prateleiras[i].topo + 1; j++) {
            	
                Produto p = prateleiras[i].itens[j];
                printf("  - Nome: %s\n", p.nome);
                printf("    Descrição: %s\n", p.descricao);
                printf("    Peso: %.2f kg\n", p.peso);
                printf("    Preço: R$ %.2f\n\n", p.preco);
            }
        }
    }

    printf("\n=============================================\n");
    printf("Pressione qualquer tecla para voltar...\n");
    getch();
}

void inicializar_carrinho(Carrinho* carrinho) {
    carrinho->topo = -1;
}

// Função para o usuário escolher o produto
int escolher_produto(PilhaEstatica* prateleira) {
    int produtoEscolhido;
    char buffer[100];

    while (1) { /*Loop infinito*/
        printf("\nEscolha o produto pela posição do item listado acima: ");
        fflush(stdin); // Limpa o buffer de entrada
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &produtoEscolhido) == 1) {
                if (produtoEscolhido >= 0 && produtoEscolhido <= prateleira->topo) {
                    return produtoEscolhido;
                } else {
                    printf("\nOpção inválida! Escolha um número válido.\n");
                }
            } else {
                printf("\nEntrada inválida! Por favor, digite um número.\n");
            }
        }
    }
}

Produto retirarProduto(PilhaEstatica* p, int prateleiraEscolhida, int posicao) {
    PilhaEstatica* prateleira = &p[prateleiraEscolhida]; // Referência à prateleira escolhida
    int i;

    if (prateleira->topo == -1) {
        printf("\nErro: A prateleira está vazia!\n");
        Produto produtoVazio = {"", "", 0.0, 0.0}; // Produto vazio como retorno padrão
        return produtoVazio;
    }

    if (posicao < 0 || posicao > prateleira->topo) {
        printf("\nErro: Posição inválida!\n");
        Produto produtoVazio = {"", "", 0.0, 0.0}; // Produto vazio como retorno padrão
        return produtoVazio;
    }

    // Pegar o produto na posição especificada
    Produto produtoRemovido = prateleira->itens[posicao];

    // Reorganizar os produtos acima da posição removida
    for (i = posicao; i < prateleira->topo; i++) {
        prateleira->itens[i] = prateleira->itens[i + 1];
    }
	
    // Ajustar o topo da pilha
    Produto vazio = {"", "", 0.0, 0.0};
    prateleiras[prateleiraEscolhida].itens[prateleira->topo] = vazio;
    prateleira->topo--;

    printf("\nProduto \"%s\" retirado com sucesso da prateleira %d, posição %d!\n",
           produtoRemovido.nome, prateleiraEscolhida, posicao);

    return produtoRemovido;
}


void adicionarCarrinho(Carrinho* c, Produto item) {
    // Verifica se a pilha está cheia
    if (c->topo >= MAX_ITENS - 1) {
        printf("\nErro: O carrinho está cheio! Não é possível adicionar mais itens.\n");
        return;
    }

    // Incrementa o topo e adiciona o item
    c->topo++;
    c->compras[c->topo] = item;

    printf("\nProduto \"%s\" adicionado ao carrinho com sucesso!\n", item.nome);
}

void exibirCarrinho(Carrinho* c) {
	int i;
    // Verifica se o carrinho está vazio
    system ("cls");
	if (c->topo == -1) {
        printf("\nO carrinho está vazio.\n");
        return;
    }
	printf ("\nTopo igual a %d\n", c->topo);
    printf("\nItens no carrinho:\n");
    printf("------------------------\n");

    // Itera sobre os itens no carrinho e exibe os detalhes
    for (i = 0; i <= c->topo; i++) {
        printf("Item %d:\n", i);
        printf("Nome: %s\n", c->compras[i].nome);
        printf("Descrição: %s\n", c->compras[i].descricao);
        printf("Peso: %.2f kg\n", c->compras[i].peso);
        printf("Preço: R$ %.2f\n", c->compras[i].preco);
        printf("------------------------\n");
    }
}

void inicializarFila(Fila* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
}

void moverEsteira(Carrinho* carrinho, Fila* esteira) {
    // Verificar se o carrinho está vazio
    if (carrinho->topo == -1) {
        printf("\nErro: O carrinho está vazio! Não há produtos para mover.\n");
        return;
    }

    // Mover todos os produtos do carrinho para a esteira
    while (carrinho->topo >= 0) {
        // Verificar se a esteira está cheia
        if (esteira->tamanho >= TAM_CARRINHO) {
            printf("\nErro: A esteira está cheia! Não é possível adicionar mais produtos.\n");
            break;
        }
		
        // Retirar o produto do topo do carrinho
        Produto produtoMovido = carrinho->compras[carrinho->topo];
		Produto vazio = {"", "", 0.0, 0.0};
    	carrinho->compras[carrinho->topo] = vazio;
        carrinho->topo--;

        // Adicionar o produto na fila (esteira)
        esteira->itens[esteira->fim] = produtoMovido;
        esteira->fim = (esteira->fim + 1) % TAM_CARRINHO; // Incremento circular
        esteira->tamanho++;

        printf("\nProduto \"%s\" movido do carrinho para a esteira com sucesso!\n", produtoMovido.nome);
    }

    // Informar que todos os produtos foram movidos, se aplicável
    if (carrinho->topo == -1) {
        printf("\nTodos os produtos foram movidos para a esteira.\n");
    }
}

void exibirFila(Fila* fila) {
    // Verificar se a fila está vazia
    if (fila->tamanho == 0) {
        printf("\nA esteira está vazia! Nenhum produto para exibir.\n");
        return;
    }

    printf("\nCupom Fiscal (ordem de processamento):\n");
    printf("--------------------------------------------------\n");
    
    float valorTotal = 0.0; // Variável para armazenar o valor total dos produtos
    int i, posicaoAtual = fila->inicio;

    for (i = 0; i < fila->tamanho; i++) {
        Produto produto = fila->itens[posicaoAtual];
        printf("Produto %d:\n", i + 1);
        printf("Nome: %s\n", produto.nome);
        printf("Descrição: %s\n", produto.descricao);
        printf("Peso: %.2f kg\n", produto.peso);
        printf("Preço: R$ %.2f\n", produto.preco);
        printf("--------------------------------------------------\n");

        // Adicionar o preço do produto ao valor total
        valorTotal += produto.preco;

        // Incremento circular para avançar na fila
        posicaoAtual = (posicaoAtual + 1) % TAM_CARRINHO;
    }

    // Exibir o valor total ao final
    printf("Valor Total a Pagar: R$ %.2f\n", valorTotal);
    printf("--------------------------------------------------\n");
}


