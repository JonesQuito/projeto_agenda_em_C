#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOME 0
#define RESUMIDO 1
#define FULL 2


// DEFININDO ESTRUTURAS
typedef struct{
	char nome[100];
	char email[100];
	char telefone[15];
	char nascimento[11];
	int byteInicial;
}tContato;

//VARI�VEIS GLOBAIS


//PROT�TIPOS DE FUN�OES
int menu();
void testaAberturaDoArquivo(FILE *f, const char *nomeArquivo);
void lerTotalContatos(const char *nomeArquivo, int *totalContatos);
tContato *alocarMemoria(tContato *contato, int tamanhoDoBloco);
tContato *cadastrarContato(tContato *contato, int *totalContatos);
void liberarMemoria(tContato *contato);
void gravarContatoNoArquivo(tContato *contato, int *totalContatos, const char *nomeArquivo);
void atualizarArquivoTotalContatos(const char *nomeArquivo, int *totalContatos);
tContato *lerArquivoDeContatos(tContato *contato, const char *nomeArquivo, int *totalContatos);
void ordenarContatosPeloNomes(tContato *contatos, int *totalContatos);
void ordenarContatosPelaDataDeNascimento(tContato *contatos, int *totalContatos);
int pesquisarContatoPeloNome(tContato *contato, int *totalContatos, const char *nomeContato);
void fazerPesquisaPorNome(tContato *contato, int *totalContatos);
void imprimirContatoNaTela(tContato *contato, int indice, int modoImpressao);
void listarTodosOsContatos(tContato *contato, int *totalContatos, int modoImpressao);
void tituloFormatado(const char *texto);
int listarContatosPorLetra(tContato *contato, int *totalContatos);
int editarContato(tContato *contato, int indice, int *totalContatos);
void *capturarNomeParaPesquisa(char *nome);

void fazerPesquisaAproximadaPorNome(tContato *contato, int *totalContatos);

int pesquisarContatoPeloNomeAproximado(tContato *contato, int *totalContatos);


//*********************************************************
//TESTAR ABERTURA DE UM ARQUIVO
void testaAberturaDoArquivo(FILE *f, const char *nomeArquivo){
	system("cls");
	char resposta;
	if(f == NULL){
		printf("Erro na abertura do arquivo \" %s\"\n\n", nomeArquivo);
		printf("Deseja criar o arquivo.\n\n");
		printf("\tS(sim)	/	N(nao)\n");
		scanf(" %c", &resposta);
		while(toupper(resposta) != 'S' && toupper(resposta) != 'N'){
			system("cls");
			printf("Resposta Invalida\n");
			printf("S(sim)	/	N(nao)\n");
			scanf(" %c", &resposta);
		}
		if(toupper(resposta) == 'S'){
			f = fopen(nomeArquivo, "a");
			testaAberturaDoArquivo(f, nomeArquivo);
		}
		else if(toupper(resposta) == 'N'){
			printf("A aplicacao sera encerrada...\n\n");
			system("pause");
			exit(EXIT_FAILURE);
		}	
		system("pause");	
	}
}
//FUN��O LER TOTALCONTATO
void lerTotalContatos(const char *nomeArquivo, int *totalContatos){
	FILE *f;
	f = fopen(nomeArquivo, "r");
	testaAberturaDoArquivo(f, nomeArquivo);
	fscanf(f, "%d", totalContatos);
	fclose(f);
}
//FUN��O PARA ALOCAR MEM�RIA
tContato *alocarMemoria(tContato *contato, int tamanhoDoBloco){
	contato = (tContato*) realloc(contato, tamanhoDoBloco + 1);
	if(contato == NULL){
		printf("Erro ao realocar memoria\n\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	return contato;
}
//FUN��O PARA LIBERAR MEM�RIA
void liberarMemoria(tContato *contato){
	free(contato);
}
//FUN��O PARA CADASTRO DE UM CONTATO
tContato *cadastrarContato(tContato *contato, int *totalContatos){
	contato = alocarMemoria(contato, sizeof(tContato));
	tituloFormatado("CADASTRO DE CONTATOS");
	
	printf("Digite um nome de Contato: ");
	scanf(" %[^\n]s", contato->nome);
	printf("Digite um e-mail de Contato: ");
	scanf(" %[^\n]s", contato->email);
	printf("Digite o telefone de Contato: ");
	scanf(" %[^\n]s", contato->telefone);
	printf("Digite a data de nascimento do Contato: ");
	scanf(" %[^\n]s", contato->nascimento);	
	lerTotalContatos("Total de Contatos.txt", totalContatos);
	gravarContatoNoArquivo(contato, totalContatos, "Contatos.txt");
	printf("Contato Cadastrado com sucesso\n\n");

	return contato;
}
//GRAVAR CONTATO NO ARQUIVO
void gravarContatoNoArquivo(tContato *contato, int *totalContatos, const char *nomeArquivo){
	FILE *f;
	f = fopen(nomeArquivo, "a");
	testaAberturaDoArquivo(f, nomeArquivo);
	fprintf(f, "%s\n", contato->nome);
	fprintf(f, "%s\n", contato->email);
	fprintf(f, "%s\n", contato->telefone);
	fprintf(f, "%s\n", contato->nascimento);
	fprintf(f, "\n");
	fclose(f);
	*totalContatos += 1;
}
//ATUALIZAR ARQUIVO DO TOTAL DE CONTATOS
void atualizarArquivoTotalContatos(const char *nomeArquivo, int *totalContatos){
	FILE *f;
	f = fopen(nomeArquivo, "w");
	testaAberturaDoArquivo(f, nomeArquivo);
	fprintf(f, "%d", *totalContatos);
	fclose(f);
}
//FUN��O QUE EXIBE UM MENU PARA O USU�RIO DA AGENDA
int menu(){
	int opcao;
	printf("***************************************\n");
	printf("\t AGENDA ELETRONICA 2016\n");
	printf("\t AUTOR:   Jones Quito\n");
	printf("***************************************\n");
	printf("ESCOLHA UMA DAS OP��ES A SEGUIR:\n\n");
	printf(" 1 - CADASTRAR UM NOVO CONTATO\n");
	printf(" 2 - LISTAR TODOS OS CONTATOS\n");
	printf(" 3 - PESQUISA EXATA PELO NOME\n");
	printf(" 4 - PESQUISA APROXIMADA PELO NOME\n");
	printf(" 5 - LISTAR CONTATOS INICIADOS COM DETERMINADA LETRA\n");
	printf(" 6 - EDITAR UM CONTATO\n");
	printf(" 7 - EXCLUIR UM CONTATO\n");
	printf(" 8 - CLASSIFICAR CONTATOS PELO NOME\n");
	printf(" 9 - CLASSIFICAR CONTATOS POR INDADES\n");
	printf(" 0 - ENCERRAR AGENDA\n");
	printf("\nINFORME SUA ESCOLHA: ");
	scanf("%d", &opcao);
	return opcao;
}
// FUN��O QUE LER OS CONTATOS DO ARQUIVO E ARMAZENA A POSI��O ONDE INICIA CADA UM DOS CONTATOS
tContato *lerArquivoDeContatos(tContato *contato, const char *nomeArquivo, int *totalContatos){
	FILE *f;
	int i;
	f = fopen(nomeArquivo, "r");
	testaAberturaDoArquivo(f, nomeArquivo);
	lerTotalContatos("Total de Contatos.txt", totalContatos);
	contato = alocarMemoria(contato, (*totalContatos) * sizeof(tContato));
	for(i = 0; i < *totalContatos; i++){
		contato[i].byteInicial = ftell(f);
		fscanf(f, " %[^\n]s", contato[i].nome);
		fscanf(f, " %[^\n]s", contato[i].email);
		fscanf(f, " %[^\n]s", contato[i].telefone);
		fscanf(f, " %[^\n]s", contato[i].nascimento);
	}
	fclose(f);
	return contato;	
}
//FUN��O QUE ORDENA OS CONTATOS PELO NOME (m�todo do bolha)
void ordenarContatosPeloNomes(tContato *contatos, int *totalContatos){
	tContato auxiliarOrdenacao;
	int i, ordenado = 0;
	while(!ordenado){
		ordenado = 1;
		for(i = 0; i < *totalContatos - 1; i++){
			if(stricmp(contatos[i].nome, contatos[i+1].nome) == 1){
				auxiliarOrdenacao = contatos[i];
				contatos[i] = contatos[i+1];
				contatos[i+1] = auxiliarOrdenacao;
				ordenado = 0;
			}
		}
	}
}
//FUN��O QUE ORDENA CONTATOS PELA DATA DE NASCIMENTO
void ordenarContatosPelaDataDeNascimento(tContato *contatos, int *totalContatos){
	tContato auxiliarOrdenacao;
	int i, ordenado = 0;
	while(!ordenado){
		for(i = 0; i < *totalContatos - 1; i++){
			if(stricmp(contatos[i].nascimento, contatos[i+1].nascimento) == 1){
				auxiliarOrdenacao = contatos[i];
				contatos[i] = contatos[i+1];
				contatos[i+1] = auxiliarOrdenacao;
				ordenado = 0;
			}
		}
	}
}
//FUN��O QUE PESQUISA UM CONTATO PELO NOME
int pesquisarContatoPeloNome(tContato *contato, int *totalContatos, const char *nomeContato){
	tituloFormatado("PESQUISAR CONTATO PELO NOME");
	int i;
	lerTotalContatos("Total de Contatos.txt", totalContatos);
	contato = lerArquivoDeContatos(contato, "Contatos.txt", totalContatos);
	for(i = 0; i < *totalContatos; i++){
		if(stricmp(nomeContato, contato[i].nome) == 0){
//		if(strnicmp(nomeContato, contato[i].nome, strlen(nomeContato)) == 0){//////////////////////////////////////////////////////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			return i;
		}
	}
	return -1;
}
//FUN��O QUE IMPRIMI UM CONTATO NA TELA
void imprimirContatoNaTela(tContato *contato, int indice, int modoImpressao){
	if(modoImpressao == NOME){
		printf("-%s\n", contato[indice].nome);	
	}
	else if(modoImpressao == RESUMIDO){
		printf("Nome: %s\n", contato[indice].nome);
		printf("Email: %s\n", contato[indice].email);
		printf("Telefone: %s\n", contato[indice].telefone);
		printf("Nascimento: %s\n", contato[indice].nascimento);
	}
	else if(modoImpressao == FULL){
		printf("Nome: %s\n", contato[indice].nome);
		printf("Email: %s\n", contato[indice].email);
		printf("Telefone: %s\n", contato[indice].telefone);
		printf("Nascimento: %s\n", contato[indice].nascimento);
	}	
}
//FUN��O QUE LISTA TODOS OS CONTATOS
void listarTodosOsContatos(tContato *contato, int *totalContatos, int modoImpressao){
	int i;
	lerTotalContatos("Total de Contatos.txt", totalContatos);
	if(*totalContatos == 0){
		printf("N�O H� CONTATOS CADASTRADOS\n\n");
		getch();
	}
	else{
		if(modoImpressao == RESUMIDO || modoImpressao == FULL){
		tituloFormatado("TODOS OS CONTATOS");
		for(i = 0; i < *totalContatos; i++){
			imprimirContatoNaTela(contato, i, modoImpressao);
			printf("\n");
		}	
	}
		else if(modoImpressao == NOME){
			for(i = 0; i < *totalContatos; i++){
				imprimirContatoNaTela(contato, i, modoImpressao);
			}
		}
	}
}
//TITULO FORMATADO
void tituloFormatado(const char *texto){
	printf("***************************************\n");
	printf("\t %s\n", texto);
	printf("***************************************\n");
}
//FUN��O QUE LISTA CONTATOS INICIADOS COM DETERMINADA LETRA
int listarContatosPorLetra(tContato *contato, int *totalContatos){
	int i, contador = 0;
	char letra;
	tituloFormatado("LISTAR CONTATOS POR LETRA");
	printf("DIGITE UMA LETRA: ");
	scanf(" %c", &letra);
//	letra = toupper(letra);
	system("cls");
	lerTotalContatos("Total de Contatos.txt", totalContatos);
	contato = lerArquivoDeContatos(contato, "Contatos.txt", totalContatos);
	tituloFormatado("RESULTADO DA BUSCA");
	printf(" NOMES:\n\n");
	for(i=0; i<*totalContatos; i++){
		if(letra == contato[i].nome[0]){
			imprimirContatoNaTela(contato, i, NOME);
			contador++;
		}
	}
	printf("\n\nCONTATOS INICIADOS COM A LETRA (%C): %d\n", letra, contador);
	printf("\n");
}
//GRAVAR VETOR DE CONTATOS NO ARQUIVO
void gravarVetorDeContatoNoArquivo(tContato *contato, int *totalContatos, const char *nomeArquivo){
	FILE *f;
	int i;
	f = fopen(nomeArquivo, "w");
	testaAberturaDoArquivo(f, nomeArquivo);
	for(i=0; i<*totalContatos; i++){
		fprintf(f, "%s\n", contato[i].nome);
		fprintf(f, "%s\n", contato[i].email);
		fprintf(f, "%s\n", contato[i].telefone);
		fprintf(f, "%s\n", contato[i].nascimento);
		fprintf(f, "\n");
	}
	fclose(f);
//	*totalContatos += 1;
}
//FAZER PESQUISA
void fazerPesquisaPorNome(tContato *contato, int *totalContatos){
	contato = lerArquivoDeContatos(contato, "Contatos.txt", totalContatos);
	int i, j;
	char nome[100];
	printf("Informe um nome de Contato: ");
	scanf(" %[^\n]s", nome);
	i = pesquisarContatoPeloNome(contato, totalContatos, nome);
	if(i < 0){
		tituloFormatado("RESULTADO DA BUSCA");
		printf("N�O H� CONTATO CADASTRADO COM O NOME: \"%s\"\n\n", nome);
	}
	else{
		tituloFormatado("RESULTADO DA BUSCA");
		imprimirContatoNaTela(contato, i, FULL);
		printf("\n");
	}
}
//FUN��O QUE RECEBE UM CONTATO E EDITA SUAS INFORMA��ES
int editarContato(tContato *contato, int indice, int *totalContatos){
	if(indice < 0){
		printf("CONTATO N�O ENCONTRADO\n\n");
		return 0;
		
	}
	tContato novoContato, auxiliarDeTroca;
	tituloFormatado("DADOS ATUAIS DO CONTATO");
	imprimirContatoNaTela(contato, indice, FULL);////////////////////////////////////////
	printf("\n\nDIGITE AS NOVAS INFORMA��ES DO CONTATO:\n\n");
	printf("Nome: ");
	scanf(" %[^\n]s", novoContato.nome);
	printf("Email: ");
	scanf(" %[^\n]s", novoContato.email);
	printf("Telefone: ");
	scanf(" %[^\n]s", novoContato.telefone);
	printf("Nascimento: ");
	scanf(" %[^\n]s", novoContato.nascimento);
	auxiliarDeTroca = contato[indice];
	contato[indice] = novoContato;
	//perguntar se deseja gravar no arquivo
	char resposta;
	do{
		printf("DESEJA GRAVAR ALTERA��ES NO ARQUIVO?\n\n");
		scanf(" %c", &resposta);
		resposta = toupper(resposta);
		if(resposta == 'S'){
			//gravar vetor de contatos no arquivo na forma de "w" e informar da conclus�o para o usu�rio
			gravarVetorDeContatoNoArquivo(contato, totalContatos, "Contatos.txt");
			break;
		}  
		else if(resposta == 'N'){
			printf("AS ALTERA��ES N�O SER�O GRAVADAS NO ARQUIVO\n\n");
			contato[indice] = auxiliarDeTroca;
			break;
		}
	}while(resposta != 'S' && resposta != 'N');


}
//CAPTURAR NOME DE CONTATO
void *capturarNomeParaPesquisa(char *nome){
	printf("Informe um nome de Contato: ");
	scanf(" %[^\n]s", nome);
	return nome;
}
//FUN��O QUE PESQUISA UM CONTATO PELO NOME APROXIMADO
int pesquisarContatoPeloNomeAproximado(tContato *contato, int *totalContatos){
	int i, j = 0;
	char nome[100];
	puts("Nome a ser pesquisado: ");
	scanf(" %[^\n]s", nome);
	lerTotalContatos("Total de Contatos.txt", totalContatos);
	contato = lerArquivoDeContatos(contato, "Contatos.txt", totalContatos);
	tituloFormatado("RESULTADO DA PESQUISA");
	printf("Busca por: \"%s\"\n\n", nome);
	for(i = 0; i < *totalContatos; i++){
		if(strnicmp(nome, contato[i].nome, strlen(nome)) == 0){
			j = 1;
			imprimirContatoNaTela(contato, i, FULL);
			printf("\n");
		}
	}
	if(j == 0){
		printf("N�O H� CONTATOS COM NOME INICIADO COM: \" %s\"\n", nome);
	}
}


