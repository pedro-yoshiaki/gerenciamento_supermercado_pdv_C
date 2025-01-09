/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h> /*Ou windows.h para Windows, uso da função Sleep*/

/*Constantes*/
#define TOTPROFS 30
/*Variáveis Global*/
char op;

/*Tipos pré-definidos pelo programador*/
typedef struct
{
	char nome [100];
	char pront [10];
} reg;


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

/*------------------------------------------------------------Corpo do programa------------------------------------------------------------------------------------------------------*/
int main (){
	
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

/* 3º Exibir Menu do sistema*/
	sleep(1);  /*Para sistemas UNIX-like*/
    /*Sleep(2000); /*Para sistemas Windows*/
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

char    menu ()
{
	do
	{
   	 system ("cls");
   	 printf ("\n========== MENU ==========");
   	 printf ("\n1. Abastecer Gôndolas  ");
   	 printf ("\n2. Caixa/PDV   	");
   	 printf ("\n3. Gerenciar Usuários 	");
   	 printf ("\n0. Sair             	");
   	 printf ("\n==========================");
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
  		 case '1': printf ("\n\nEm desenvolvimento..."); getch(); break;
  		 case '2': printf ("\n\nEm desenvolvimento..."); getch(); break;
  		 case '3': 	{char voltar;
  		 
  		 			do
					   {
	  		 			system ("cls");
	  					printf("Gerenciar Usuários\n");
	  		 	  		printf("\n1 - Cadastrar Usuário\n");
			            printf("2 - Remover Usuário\n");
			            printf("3 - Exibir Usuários\n");
			            printf("4 - Restaurar padrão\n");
			            printf("5 - Voltar ao menu\n");
			            printf("Escolha uma opção: ");
			            op = getche();
			            
						switch (op) {
					                case '1': novoUsuario("USUARIOS.DAT"); getch(); break;
					                case '2': removerUsuario("USUARIOS.DAT"); getch(); break;
					                case '3': exibirUsuarios("USUARIOS.DAT"); getch(); break;
					                case '4':{ 	reg *padrao = malloc(TOTPROFS * sizeof(reg)); // Alocação dinâmica do vetor
											    if (padrao == NULL) {
											        printf("Erro: Malloc devolveu NULL.\n");
											        exit(1); // Finaliza o programa
											    }
									cadastroDefault(padrao); 
									printf("\nPadrão de usuários restaurado"); getch(); 
									} break;
					                case '5': break;    
					                default: printf("\nOpção inválida.\n"); getche(); break;
		   							}  
						} while (op != '5'); break;	
           			}
   	 	 
		case '0':  exit(0);     	 break;
   }    
}

void exibirUsuarios(char *arquivo) {
    FILE *Arq;
    reg usuario;
    
    Arq = fopen(arquivo, "rb");
    if (Arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nLista de Usuários:\n\n");
    while (fread(&usuario, sizeof(reg), 1, Arq)) {
        printf("Nome: %s | Prontuário: %s\n", usuario.nome, usuario.pront);
    }
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

    printf("Novo usuário cadastrado com sucesso e arquivo atualizado!\n");
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
