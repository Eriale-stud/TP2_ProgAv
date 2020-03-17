#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000


// création d'un tableau d'entier aléatoire
void genTab (int * tab,int n){
  int i;
  if (n != 0){
    srand(time(0));
    for (i=0;i<n;i++){
      tab[i] = 1 + rand()%(MAX);
    }
  }
}

//Affichage du Tab
void afftab(int* tab, int n){
  int i;
  printf("%d", tab[0]);
  for (i=1; i<n; i++){
    printf(" - %d", tab[i]);
  }
  printf("\n");
}

void copytab(int * tab, int * tabbis, int n){ //set up le malloc de tabbis et le remplir de 0 a n des valeur de tab
  int i;
  /*tabbis = calloc(n, sizeof(int));*/
  for(i=0;i<=n-1;i++){
    tabbis[i] = tab[i];  
  }
}
//Liberation mémoire
void freetab(int * tab, int n){
  if (n != 0){
    free(tab);
  }
}

//Ecriture dans un fichier
 void Ecritfiche(float f){
  FILE* fichier = NULL;
  fichier = fopen("test.txt", "a+");

  if (fichier != NULL){
    fprintf(fichier,"%f\n",f);
  }
  fclose(fichier);
}

//tri a bulle
void triBulles(int * tab, int n){
  if(n > 1){
    int i;
    int temp;
    for(i=0;i<=n-1;i++){
      if(tab[i] > tab[i+1]){
        temp = tab[i];
        tab[i] = tab[i+1];
        tab[i+1] = temp;
      }
    }
    triBulles(tab,n-1);
  }
}

//tri selection
void selection (int * tab, int n){
  int i;
  int j;
  int max;
  int temp;
  i = n - 1;

  while (i>0){
    max = 0;
    for(j=0;j<=i;j++){
      if (tab[j] > tab[max]){
        max = j;
      }
    }
    temp = tab[max];
    tab[max] = tab[i];
    tab[i] = temp;
    i = i - 1;
  }
}

int partitionner(int * Tab, int deb, int fin);

// tri rapide
void trier(int* Tab, int deb, int fin){
  if (deb < fin){
    int pivot = partitionner(Tab, deb, fin);

    trier(Tab, deb, pivot-1);
    trier(Tab, pivot+1, fin);
  }
}
int partitionner(int * Tab, int deb, int fin){
  int i, j, temp;
  j = deb;

  for (i=deb; i<=fin; i++){
    if (Tab[i] < Tab[j]){
      if (i != j+1){
        temp = Tab[j+1];
        Tab[j+1] = Tab[i];
        Tab[i] = temp;
      }
      temp = Tab[j];
      Tab[j] = Tab[j+1];
      Tab[j+1] = temp;
      j = j + 1;
    }
  }
  return (j);
}


//tri fusion
void Fusion(int * tab,int deb, int mid, int fin){
 int* temp = calloc(fin+1, sizeof(int));
  int j, k;
  int i = 0;
  int i1 = deb;
  int i2 = mid + 1;

  while ((i1 <= mid)&&(i2 <= fin)) {
    if (tab[i1] < tab[i2]) {
      temp[i] = tab[i1];
      i1 = i1 + 1;
    }
    else {
      temp[i] = tab[i2];
      i2 = i2 + 1;
    }
    i = i + 1;
  }

  if (i1 < mid+1) {
    for (j=i1 ; j<=mid; j++) {
      temp[i] = tab[j];
      i = i + 1;
    }
  }
  else {
    if (i2 < fin+1) {
      for (j=i2; j<=fin; j++) {
        temp[i] = tab[j];
          i = i + 1;
      }
    }
  }

  k = 0;
  for (i=deb; i<=fin; i++) {
    tab[i] = temp[k];
    k = k + 1;
  }

    freetab(temp, fin+1);
}
void mergeSort(int * tab, int i, int j){
  if (i < j) {
      mergeSort(tab, i, (i+j)/2);
      mergeSort(tab, (i+j)/2+1, j);
      Fusion(tab, i, (i+j)/2, j);
  }
}
void triFusion(int * tab, int n){
    mergeSort(tab, 0, n-1);
}

int main(){
  int n = 10; //taille du tableau
  clock_t start,end; //initialisation horloge
  int deb, fin;
  int k;
  /*printf("Quel algorithme de tri voulez vous utiliser  ?\n\n");
  printf("Tri rapide (1)\nTri selection (2)\nTri fusion (3)\nTri a bulle (4)\n \n");
  printf("Je voudrai utiliser le tri numero : ");
  scanf("%d",&k);
  printf("\n");*/
  int * tabOrigine = calloc(1000000, sizeof(int));
  int * tab;
  int * tab1;
  int * tab2;
  int * tab3;
  printf("It is OK !");

  while(n < 100000){

    k = 1;

    // tri rapide
    if (k == 1 && n <= 500000){
      deb = 0;
      fin = n-1;
      int * tab = calloc(n, sizeof(int));
      copytab(tabOrigine,tab,n);
      genTab(tab, n);
      start = clock();
      trier(tab,deb,fin);
      end = clock();
      printf("\n\nTRI RAPIDE\n");
      printf("        La taille du tableau est : %d\n\n",n);
      printf("        Le temps d'execution du tri rapide est    :    %f\n\n", (float)(end-start)/CLOCKS_PER_SEC);
      float f = (float)(end-start)/CLOCKS_PER_SEC;
      afftab(tab,n);
      //Ecritfiche(f);
      freetab(tab,n);
      k++;
    }

    //tri selection
    if (k == 2){
      int * tab1 = calloc(n,sizeof(int));
      copytab(tabOrigine,tab1,n);
      genTab(tab1,n);
      start = clock();
      selection(tab1,n);
      end = clock();
      printf("\n\nTRI SELECTION\n");
      printf("        La taille du tableau est : %d\n\n",n);
      printf("        Le temps d'execution du tri selection est    :    %f\n\n",(float)(end-start)/CLOCKS_PER_SEC);
      float f = (float)(end-start)/CLOCKS_PER_SEC;
      afftab(tab1,n);
      //Ecritfiche(f);
      freetab(tab1,n);
      k++;
    }

    //tri fusion
    if (k == 3 && n <= 500000){
      int * tab2 = calloc(n,sizeof(int));
      copytab(tabOrigine,tab2,n);
      genTab(tab2,n);
      start = clock();
      triFusion(tab2,n);
      end = clock();
      printf("\n\nTRI FUSION\n");
      printf("        La taille du tableau est : %d\n\n",n);
      printf("        Le temps d'execution du tri fusion est     :     %f\n\n",(float)(end-start)/CLOCKS_PER_SEC);
      float f = (float)(end-start)/CLOCKS_PER_SEC;
      //Ecritfiche(f);
      afftab(tab2,n);
      freetab(tab2,n);
      k++;
    }

    //tri a bulle
    if (k == 4){
      int * tab3 = calloc(n,sizeof(int));
      copytab(tabOrigine,tab3,n);
      genTab(tab3,n);
      start = clock ();
      triBulles(tab3,n);
      end = clock();
      printf("\n\nTRI A BULLE\n");
      printf("        La taille du tableau est : %d\n\n",n);
      printf("        Le temps d'execution du tri a bulle est   :   %f\n\n",(float)(end-start)/CLOCKS_PER_SEC);
      float f = (float)(end-start)/CLOCKS_PER_SEC;
      //Ecritfiche(f);
      afftab(tab3,n);
      freetab(tab3,n);
    }
    if (n < 100000){
      //n = n *10 ;
      n++;
    }
    else{
      n = n + 50000;
    }
  }
  freetab(tabOrigine,n);
  return 0;
}
