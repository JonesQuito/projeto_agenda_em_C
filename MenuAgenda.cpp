#include <stdio.h>

//FUNÇÃO QUE EXIBE UM MENU PARA O USUÁRIO DA AGENDA. ESSA FUNÇÃO CAPTURA O VALOR DIGITADO PELO USUÁIO E RTORNA U
int menu(){
	int opcao;
	printf("***************************************\n");
	printf("\t AGENDA ELETRONICA 2016\n");
	printf("\t AUTOR:   Jones Quito\n");
	printf("***************************************\n");
	printf("ESCOLHA UMA DAS OPï¿½ï¿½ES A SEGUIR:\n\n");
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

int main(void){
	menu();
}

