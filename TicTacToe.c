#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>
 

#define N 3
void inicio(void);
int tipo_de_jogo(void);
short tabuleiro[N][N]={ }, jog, n=1, primeiro=0,tipo_jog;
struct JOGADOR *bastur=NULL,*jogador_n1,*jogador_n2;
char jog1[10],jog2[10];
time_t start, stop;

  struct JOGADOR{

     short numero;
     char nome[20];
     int board[3][3];
     int record;
     struct JOGADOR *next;
   };


void info(void);
int estado_inicial(int *tipo_jog);  
void mostra_tabul(void);
    void numeros(int n);
    void linha(int n, int d);
    char conv(short int peca);
void jogada(int tipo);
void jogada_Humano(int jog);
void executa_movimento(int xi, int yi, int jog);
int movimento_valido(int xi, int yi, int jog);
void jogada_PC(int jog);
int avalia_tabul(int jog);
void reiniciar(void);
//funcoes struct
struct JOGADOR *Ler(void);
void Showlist(struct JOGADOR *prim);
struct JOGADOR *PROCURA(int numero);
struct JOGADOR *NOVO_JOG(struct JOGADOR *prim);
int GUARDAR_FICHEIRO(struct JOGADOR *lista);
void Showlist2(struct JOGADOR *prim);

int main(void){
  int fim=-1, i, j, tipo, ti, aux,vez=0, term=0;
  char venc, recebe[10];

//inicio();

bastur=Ler();
tipo = tipo_de_jogo();
      
 while (term==0){
     time(&start);
  do {
  	 
  	 if (jog==1) strcpy(recebe,jog1);
  	 else strcpy(recebe,jog2);
     
	 system("cls");
     printf("JOGADA No: %d Jogador: %s \n", n,recebe);
     mostra_tabul();            
     jogada(tipo);             
     fim = fim_jogo(n);
     if (jog==1) jog = 2; else jog = 1; 
     n++;
  } while(fim==-1);  
   time(&stop);
  mostra_tabul();
   printf("Tempo do Jogo %.0f Segundos \n", difftime(stop, start));
      switch(fim){
      	case 0: printf("EMPATE ENTRE %s & %s \n\n\n", jog1,jog2);break;
  	    case 1: printf("VITORIA\n %s VENCEU \n\n\n", jog1);break;
     	case 2: printf("VITORIA\n %s VENCEU \n\n\n", jog2);break;
      }
   if(fim==1&&(tipo==2||tipo==3)&&jogador_n1->record>difftime(stop, start))
    jogador_n1->record=difftime(stop, start),printf("Novo record para o jogador %s: %.0f segundos \n",jogador_n1->nome,difftime(stop, start));
    
    else if(fim==2&&(tipo==2||tipo==4)&&jogador_n2->record>difftime(stop, start))
    jogador_n2->record=difftime(stop, start),printf("Novo record para o jogador %s: %.0f segundos \n",jogador_n2->nome,difftime(stop, start));
    
   printf("JOGAR DE NOVO: 1\nSAIR: O\n\n\n");
   scanf("%d",&aux);
   if(aux==0) {
   	 GUARDAR_FICHEIRO(bastur);
	return;	
   }
   else{
     reiniciar();
     
           if(fim==1 || fim==0) jog=1;
      else if(fim==2 && tipo==2) jog=2; 
      else if(fim==2 && tipo==3) jog=1,tipo=4;
      else if(fim==2 && tipo==4) jog=1,tipo=3;
   }
  }
 
  system("PAUSE");
  return 0;
}


void inicio(void){
 printf("\n\n\n");
 printf("             UNIVERSIDADE DO MINHO - ESCOLA DE ENGENHARIA \n\n");
  sleep(1);
 printf("               AEQUITETURA E TECNOLOGIA DE COMPUTADORES \n\n");
  sleep(1);
 printf("            ENGENHARIA ELETRONICA INDUSTRIAL E COMPUTADOES \n");
  sleep(0);
 printf("                                2 ANO  \n\n");
  sleep(1);
 printf("                DOCENTE: AGOSTINHO GIL TEIXEIRA LOPES  \n\n");
  sleep(1);
 printf("                             TICK TACK TOE \n\n");
  sleep(1);
 printf("                       AILTON & ELADIO & ANGELO  \n");
 sleep(4);
 system ("cls");	
	
}

void info(void){

int aux;
printf("\nINFORMACAO DOS JOGADORES: 1\nVOLTAR AO MENU: 0\n");
scanf("%d",&aux);
system ("cls");
if(aux==1)Showlist2(bastur);	
scanf("%d",&aux);	
}

//pede ao utilizador para escolher o tipo de jogo pretendido
int tipo_de_jogo(void){
  	
 int a=1 ,aux;
 char valor[10], recebe[10];
 while(a==1){
 
 printf(" TICK TACK TOE \n\n");
 printf("UM JOGADOR: 1\nDOIS JOGADORES: 2 \n\n");
 printf("INFORMACAO: 3\n\n");
 scanf("%s",&valor);
 tipo_jog=atoi(valor);
if(tipo_jog==3)info();
 if(tipo_jog!=1 && tipo_jog!=2)a=1;
 else a=0;
 system ("cls");
 }
   
  jog = estado_inicial(&tipo_jog);
  primeiro = jog;
  
  
  return tipo_jog;	
}

// funcao que reinicia o jogo, colocando o tabuleiro incicial a 0
void reiniciar(void){
	int i, j;
for(i=0; i<N; i++){
    for(j=0; j<N; j++) {
       tabuleiro[i][j] = 0;
    }
}
 n=1;		
}

// funcao que pede ao utilizador para escolher os nomes dos jogadores 
//ou criar um novo jogador, e escolher o primeiro jogador a jogar
int estado_inicial(int *tipo_jog){

 int i,j, aux3,flag=0;
  
for(i=0; i<N; i++){
    for(j=0; j<N; j++) {
       tabuleiro[i][j] = 0;
    }
}
	
if(*tipo_jog==2){
printf("ESCOLHA O PRIMEIRO JOGADOR \n");
Showlist(bastur);
printf("NOVO JOGADOR: 0\n"); 
scanf("%d",&aux3);
if(aux3!=0)jogador_n1=PROCURA(aux3);
else jogador_n1=NOVO_JOG(bastur);
Showlist(bastur);
printf("ESCOLHA O SEGUNDO JOGADOR \n");
printf("NOVO JOGADOR: 0\n"); 
scanf("%d",&aux3);
if(aux3!=0)jogador_n2=PROCURA(aux3);
else jogador_n2=NOVO_JOG(bastur);
strcpy(jog1,jogador_n1->nome);
strcpy(jog2,jogador_n2->nome);
for(i=0; i<N; i++){
    for(j=0; j<N; j++) {
       if(jogador_n1->board[i][j] != 0)flag=1; 
    }
}
if(flag==1){
printf("O Jogador %s tem um jogo Guardado:\nContinuar: 1\nNovo Jogo: 2",jogador_n1->nome);
scanf("%d",&aux3);
if(aux3==1)	{
	for(i=0; i<N; i++){
       for(j=0; j<N; j++) {
          tabuleiro[i][j] =jogador_n1->board[i][j];
		  jogador_n1->board[i][j]=0;  
      }
   }
}
}
return 1;
}


else if(*tipo_jog==1){
printf("ESCOLHA O PRIMEIRO JOGADOR \n");
Showlist(bastur);
printf("\nNOVO JOGADOR: 0\n"); 
scanf("%d",&aux3);
if(aux3!=0)jogador_n1=PROCURA(aux3);
else{
   jogador_n1=NOVO_JOG(bastur);
    
    for(i=0; i<N; i++){
       for(j=0; j<N; j++) {
           if(jogador_n1->board[i][j] != 0)flag=1; 
      }
   }
}
   if(flag==1){
   printf("O Jogador %s tem um jogo Guardado:\nContinuar: 1\nNovo Jogo: 2",jogador_n1->nome);
   scanf("%d",&aux3);
   if(aux3==1)	{
	 for(i=0; i<N; i++){
        for(j=0; j<N; j++) {
          tabuleiro[i][j] =jogador_n1->board[i][j];
		  jogador_n1->board[i][j]=0;  
      }
   }
  }

	
}
 system ("cls");
 
printf("PRIMEIRO JOGADOR:\nHUMANO: 1\nPC: 2\n");
scanf("%d",&aux3);
if(aux3==1)*tipo_jog=3, strcpy(jog1,jogador_n1->nome), strcpy(jog2,"PC");
else *tipo_jog=4,strcpy(jog2,jogador_n1->nome), strcpy(jog1,"PC");

return 1;
} 
}


//funcao que desenha o tabuleiro do jogo em modo texto 
void mostra_tabul(void){
	int i,j;
    numeros(N);
    printf("\n %c",201); linha(N,203); printf("%c\n",187);
    for(i=0; i<N; i++) {
         printf("%c",i+49);    
         for(j=0; j<N; j++)
              printf("%c %c ", 186, conv (tabuleiro[i][j]));  
         printf("%c%c\n ",186,i+49);
         if (i<N-1) {printf("%c",204), linha(N, 206); printf("%c\n", 185);}
    }
    printf("%c",200), linha(N, 202); printf("%c\n", 188);
    numeros(N);
    printf("\n\n");
}   
     
// Função para imprimir os numeros assima do tabuleiro do jogo
void numeros(int n) {
	int i;
  printf("  "); 
  for(i=1; i<=n; i++)
      printf("%2d  ",i);   
} 
// Função para fazer uma linha 
 void linha(int n, int d) {
 		int i;
       for(i=0; i<n; i++) {
      printf("%c%c%c",205,205,205);  
      if(i!=n-1) printf("%c",d );   
   }    
} 

//funcao que converte os numeros guardados na matriz nos caracteres X e O depenendo do jogador (ex X = 1)
char conv(short auxiliar){
   if (auxiliar==1) return 'X';    
   else if (auxiliar==2) return 'O';    
   else return ' ';    
} 

// funcao que escolhe o tipo do jogo, existem tres tipos diferentes, humano/humano, pc/humano e Humano/pc
void jogada(int tipo){
   if (tipo==2) jogada_Humano(jog); 
      
   else if (tipo==3) {
	   if (n % 2 == 1) jogada_Humano(jog); else jogada_PC(jog);
   }
   else if (tipo==4) {
	   if (n % 2 == 1) jogada_PC(jog) ;  else jogada_Humano(jog);
  } 
} 

//funcao que pede ao utilizador que escolha uma posicao da matriz, verifica se jogar nessa posicao e valida
// se for valida executa a jogada, se nao pede de novo a posicao e diz qual o erro da jogada anterior
void jogada_Humano(int jog){
  char  xi[5], yi[5];  
  int pos_x, pos_y;
    do {
       	 printf("JOGAR PARA:\n ");
         scanf("%s%*c%s", xi,yi); 
         pos_x=atoi(xi);
		 pos_y=atoi(yi); 
		 pos_x--;pos_y--;      
          if(movimento_valido(pos_x,pos_y,jog)!=0) {   
		      switch (movimento_valido(pos_x,pos_y,jog)){
              case 1: printf(" COORDENADAS FORA DO TABULEIRO,tente novamente.\n\n "); break;
              case 2: printf(" MOVIMENTO INVALIDO, lugar oucupado, tente novamente.\n\n"); break;
              }
          }
    } while (movimento_valido(pos_x,pos_y,jog)!=0);  
    executa_movimento(pos_x,pos_y,jog); 
}  


// funcao que para todas as posicoes da matriz aonde a jogada é valida executa a jogada
// depois avalia a jogada feita com uma funcao que retorna um valor maior quanto melhor for a jogada
//depois desfaz a jogada e joga na posicao seguinte, e no final de jogar em todas as posicoes possiveis
// verifica qual a jogada aonde o avalia é maximo, e executa essa jogada 
void jogada_PC(int jog){
int i, j, bi, bj, av, maxav=-1000;
for(i=0; i<N; i++){     //para todas as posicoes da matriz 
  for(j=0; j<N; j++) {   //
    if (tabuleiro[i][j]==0){ 
          if (movimento_valido(i,j,jog)==0) {// uma posicao vazia onde a jogada é valida 
             tabuleiro[i][j]=jog;	//executa a jogada
              av = avalia_tabul(jog);
              if (av > maxav)  maxav = av, bi=i, bj=j;  // avalia o tabuleiro se av for maior que o anterior guarda as posicoes em bi,bj,bk,bl
              tabuleiro[i][j]=0;	 //desfaz jogada
          }
        }
      } 
    } 
  executa_movimento(bi,bj,jog); 
} 

//funcao que executa o movimento, colocando na matriz do jogo o valor dependendo do jogador
void executa_movimento(int xi, int yi, int jog){
	
      tabuleiro[xi][yi] = jog;
       
  }
// fucao que verifica se o movimento é válido, se for retorna 0, se nao, retorna um valor dependendo 
//do tipo de erro (ex: retorna 1 quando a posicao está fora do tabuleiro do jogo
int movimento_valido(int xi, int yi, int jog){
	
  	if(xi>=3||xi<0||yi>=3||yi<0) return 1;
  	if(tabuleiro[xi][yi]!=0) return 2;
    return 0;        
}
 
// funcao que verifica se algum dos jogadores conseguiran ganhar o jogo, ou se todas as posicoes da matriz estao oucupadas
// se o jogo ainda nao terminar retorna -1, se o jogador 1 vencer retorna 1 ou 2 se o jogador 2 vencer, ou retorna 0 no caso de empate
 int fim_jogo(int n){
 	
  int i=0,j;
  
 for(i=0; i<N; i++){
       if(tabuleiro[i][0]==tabuleiro[i][1] && tabuleiro[i][0]==tabuleiro[i][2]  && tabuleiro[i][0]!=0) return tabuleiro[i][0];
 }

 for(i=0;i<N; i++) { 
       if(tabuleiro[0][i]==tabuleiro[1][i] && tabuleiro[0][i]==tabuleiro[2][i] && tabuleiro[0][i]!=0) return tabuleiro[0][i];  
  }
                                           
       if(tabuleiro[0][0]!=0 && tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][2]) return tabuleiro[0][0]; 
         
       if(tabuleiro[0][2]!=0 && tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][0]) return tabuleiro[0][2];  


  	     if(n==10) return 0;
   		
                                               
    return -1;      
  } 
  
// funcao auxiliar para a jogada pc inteligente onde quanto mais perto da vitoria estiver um jogador maior será o seu avalia

  int avalia(int jog)
{
    int i=0,j=0;
    int av = 0;
    if (fim_jogo(n) == jog) av+=1000;
	
    if(n==1) { if (tabuleiro[1][1]==jog)av+=10000;}
    if(tabuleiro[1][1]==jog) { if (tabuleiro[0][0]==jog||tabuleiro[2][0]==jog||tabuleiro[0][2]==jog||tabuleiro[2][2]==jog)av+=100;} 
    if(n==2) { 
       if(tabuleiro[1][1]==0) { if (tabuleiro[1][1]==jog)av+=1000;} 
	   if(tabuleiro[1][1]!=jog) { if (tabuleiro[0][0]==jog||tabuleiro[2][0]==jog||tabuleiro[0][2]==jog||tabuleiro[2][2]==jog)av+=100;} 
	} 
for(i=0;i<N; i++) { 
        if(tabuleiro[i][0]==tabuleiro[i][1] && tabuleiro[i][0]!=0  && tabuleiro[i][2]==jog) av+=250;
   else if(tabuleiro[i][0]==tabuleiro[i][2] && tabuleiro[i][0]!=0  && tabuleiro[i][1]==jog) av+=250;
   else if(tabuleiro[i][1]==tabuleiro[i][2] && tabuleiro[i][1]!=0  && tabuleiro[i][0]==jog) av+=250;
}
for(j=0;j<N; j++) { 
        if(tabuleiro[0][j]==tabuleiro[1][j] && tabuleiro[0][j]!=0  && tabuleiro[2][j]==jog) av+=250;
   else if(tabuleiro[0][j]==tabuleiro[2][j] && tabuleiro[0][j]!=0  && tabuleiro[1][j]==jog) av+=250;
   else if(tabuleiro[1][j]==tabuleiro[2][j] && tabuleiro[1][j]!=0  && tabuleiro[0][j]==jog) av+=250;
}

        if(tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[0][0]!=0  && tabuleiro[2][2]==jog) av+=250;
   else if(tabuleiro[1][1]==tabuleiro[2][2] && tabuleiro[1][1]!=0  && tabuleiro[0][0]==jog) av+=250;
   else if(tabuleiro[0][0]==tabuleiro[2][2] && tabuleiro[0][0]!=0  && tabuleiro[1][1]==jog) av+=250; 
    
   else if(tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[0][2]!=0  && tabuleiro[2][0]==jog) av+=250;
   else if(tabuleiro[1][1]==tabuleiro[2][0] && tabuleiro[1][1]!=0  && tabuleiro[0][2]==jog) av+=250;
   else if(tabuleiro[0][2]==tabuleiro[2][0] && tabuleiro[0][2]!=0  && tabuleiro[1][1]==jog) av+=250;  

     return av;    
}  
  
// essa funcao usamos a mesma que no jogo que fizemos no 1º ano
// ela avalia o jogo para os dois jogadores e faz com que o pc faça a melhor jogada possivel
int avalia_tabul(int jog)
{
    int a1, a2;
    a1 = avalia(1);
    a2 = avalia(2);
    if (jog==1) return 2*a1-3*a2; else return 2*a2-3*a1;  
}
   

// funcao que lê o ficheiro com os dados dos jogadores para a memoria

struct JOGADOR *Ler(void){
int i,j;
struct JOGADOR *lista = NULL; // variável que representa a lista ligada
struct JOGADOR *novo; // variável que representa um novo elemento
struct JOGADOR *fim;
FILE *ficheiro;
    int numeros; // numeros é do tipo int, senão ao fazer scanf %d dá erro da stack
    char aux[20];
    char sep[20];
    int vec[3][3];
    int records; // records é do tipo int, senão ao fazer scanf %d dá erroda stack
    int valor;

//abrir o ficheiro de dados
    ficheiro = fopen("estado33.txt", "r");
if (ficheiro == NULL) { // necessitas de testar se o ficheiro abriu com sucesso
printf("Erro: o ficheiro não existe!\n"); // mostras a mensagem de erro
return NULL;
}

while(!feof(ficheiro)){

valor = fscanf(ficheiro,"%d-%d-%[^:]s",&numeros,&records,&aux);
if (valor != 3) { // verifica se consegui ler as 3 variáveis
printf("Erro: ficheiro mal formatado1!\n");
fclose(ficheiro); // em caso de erro, necessitas de fechar o ficheiro
return NULL;
}
// como em cima leste até aparecer o caracter ':', tens que o ler agora para o sep
if (fscanf(ficheiro, "%s", sep) != 1) { // verifica se conseguiu ler o caracter ':'
printf("Erro: ficheiro mal formatado!\n");
fclose(ficheiro);
return NULL;
}

for (i=0;i<N;i++){
for (j=0;j<N;j++) {
if (fscanf(ficheiro,"%d", &vec[i][j]) != 1) { // verifica se conseguiuler cada um dos elementos do vector
printf("Erro: ficheiro mal formatado!\n");
fclose(ficheiro);
return NULL;
}
}
}

// não necessitas de criar o jogador no if e no else,
// basta criar apenas num único sítio, senão duplicas o código
novo =(struct JOGADOR*)malloc (1*sizeof(struct JOGADOR));
novo->numero=numeros;
strcpy(novo->nome,aux);
novo->record=records;
for (i=0;i<N;i++){
for (j=0;j<N;j++){
novo->board[i][j] = vec[i][j];
}
  }
novo->next=NULL;

// se a lista estiver vazia
if(lista==NULL){
lista=novo;
fim=novo;
} 
else {
fim->next = novo;
fim = novo;
}
}
    fclose(ficheiro);
    return(lista);
}
     
// funçao que recebe uma lista, e imprime o numero/nome/pontuacao dos jogadores que estao guardados na base de dados do jogo
void Showlist(struct JOGADOR *prim){
  int i,j;
        if(prim==NULL){
                printf("A Lista esta vazia!\n");
                return;
        }
        else {
              printf("NUMERO :        NOME:   MELHOR TEMPO/s\n\n");
                while(prim!=NULL){
                     printf("%4d  -  %12s  -  %4d\n",prim->numero,prim->nome,prim->record);
                     prim=prim->next;
                }
        }
}
struct JOGADOR *PROCURA(int numero){
struct JOGADOR *prim;
prim=bastur;
  int i,j;
        if(prim==NULL){
                printf("A Lista esta vazia!\n");
                return;
        }
        else {

                while(prim!=NULL){
                       if(prim->numero==numero) return (prim);
					   else prim=prim->next;
                }
        }
}

// funcao que cria um novo jogador
struct JOGADOR *NOVO_JOG(struct JOGADOR *prim){
  int i,j,aux=2;
  struct JOGADOR *novo,*fim;
  novo=(struct JOGADOR*)malloc (1*sizeof(struct JOGADOR));
  char nome_s[40];
  fim=prim;
       
                system ("cls");
                printf("Nome do Jogador\n");
                scanf("%s",&nome_s);
                novo->numero=aux;
                strcpy(novo->nome,nome_s);
                novo->record=200;
                for (i=0;i<N;i++){
                    for (j=0;j<N;j++){
                       novo->board[i][j]=0;                      
			        }
		       }printf("\n");
		       
		        
			if(prim==NULL){
                printf("A Lista esta vazia!\n");
                novo->next=NULL;
		        fim=novo;
            }
        
        else {
                while(fim->next!=NULL){
                   fim=fim->next;aux++;
		        }
		        novo->next=NULL;
		        fim->next=novo;
		}
               return (novo);
        
}
// funcao que no final do jogo guarda d novo todos os dados que estao na memoria para o ficheiro
int GUARDAR_FICHEIRO(struct JOGADOR *lista){
int i,j;
FILE* ficheiro;
ficheiro = fopen("estado33.txt", "w");
if (ficheiro == NULL) { // necessitas de testar se o ficheiro abriu com sucesso
printf("Erro: o ficheiro não existe!\n"); // mostras a mensagem de erro

}
fprintf(ficheiro,"%d-%d-%s:\n",lista->numero,lista->record,lista->nome);
   for (i=0;i<N;i++){
      for (j=0;j<N;j++){
          fprintf(ficheiro,"%d ",lista->board[i][j]);
     }
  }
  lista=lista->next;
  
while(lista!=NULL){
fprintf(ficheiro,"\n%d-%d-%s:\n",lista->numero,lista->record,lista->nome);
   for (i=0;i<N;i++){
      for (j=0;j<N;j++){
		 fprintf(ficheiro," %d",lista->board[i][j]);
     }
  }
  lista=lista->next;
}
    fclose(ficheiro);
}

// apresenta no ecran todos os dados de todos os jogadores que estao no ficheiro
void Showlist2(struct JOGADOR *prim){
  int i,j;
        if(prim==NULL){
                printf("A Lista esta vazia!\n");
                return;
        }
        else {
        
                while(prim!=NULL){
                     printf("JOGADODOR NUMERO: %4d\nNOME: %8s\nMELHOR TEMPO: %4d SEGUNDOS\n",prim->numero,prim->nome,prim->record);
                     printf("ESTADO DO JOGO\n");
                      for (i=0;i<N;i++){
                          for (j=0;j<N;j++){
                             printf(" %d ",prim->board[i][j]);
                         }
					  printf("\n");
                     }                     
                    prim=prim->next;
                     printf("\n\n");
                }
        }
}
