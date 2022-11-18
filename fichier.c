#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nmax 10
struct maillon_ligne
{
	int pix;
	struct maillon_ligne * suiv;
};

typedef struct maillon_ligne * ptr_ligne;

typedef ptr_ligne T_image[nmax];


struct couple
{
	int val,nb;
};

struct maillon_ligne_compressee
{
	struct couple pix;
	struct maillon_ligne_compressee * suiv;
};

typedef struct maillon_ligne_compressee * ptr_ligne_compressee;

typedef ptr_ligne_compressee T_image_compressee[nmax];

T_image im,ima;
int nbligne;
T_image_compressee imc;
ptr_ligne_compressee ligne;


void ajout (int e, ptr_ligne *L)
{
	ptr_ligne p;
	p = malloc(sizeof(struct maillon_ligne));
	p->pix=e;
	p->suiv=*L;
	*L=p;
}

void ajouter (struct couple c, ptr_ligne_compressee *L)
{
	ptr_ligne_compressee p;
	p = malloc(sizeof(struct maillon_ligne_compressee));
	p->pix=c;
	p->suiv=*L;
	*L=p;
}

void afficheLigne(ptr_ligne L)
{
	while (L!=NULL)
		{
		printf("%d ",L->pix);
		L=L->suiv;
		}
	printf("\n");
}

void afficheLigneCompressee(ptr_ligne_compressee L)
{
	while (L!=NULL)
		{
		printf("(%d,%d) ",(L->pix).val,(L->pix).nb);
		L=L->suiv;
		}
	printf("\n");
}


void creer_image (T_image *im, int * nbligne)
{
	FILE *fp;
	int x,i;
	  if ((fp = fopen("image.txt", "r")) == NULL){
	    fprintf(stderr, "Cannot open image.txt\n");
	    exit(1);
	  }
	fscanf(fp,"%d",&(*nbligne));    
  for(i=0;i<*nbligne;i++)
		(*im)[i]=NULL;
  i=0;
  while (i != *nbligne)
  {
		do
			{
				fscanf(fp,"%i ",&x);
				if (x != -1)
					ajout(x,&(*im)[i]);
			}
		while (x != -1);
		i++;
	}
  fclose(fp);
}


void affiche(T_image im, int nbligne)
{
	ptr_ligne p;
	int i;
  for(i=0;i<nbligne;i++)
		{
      p=im[i];
      while (p != NULL)
				{
          printf("%d ",p->pix);
          p=p->suiv;
        }
        printf("\n");
    }
}

void affichecompressee (T_image_compressee im,int nbligne)
{
	ptr_ligne_compressee p;
	int i;
  for(i=0;i<nbligne;i++)
    {
      p=im[i];
      while(p != NULL)
        {
          printf("(%d,%d)",p->pix.val,p->pix.nb);
          p=p->suiv;
        }
        printf("\n");;
    }
}


void compresse_ligne(ptr_ligne L, ptr_ligne_compressee * C)
{
    struct couple e;
    e.val=L->pix;
    e.nb=1;
    L=L->suiv;
    while (L!=NULL)
	{
        if(L->pix==e.val){
              ++e.nb;
        }else{
            ajouter(e,C);
            e.val=L->pix;
            e.nb=1;
        }
        L=L->suiv;
	}
    ajouter(e,C);
    

}

void compresse_image(T_image IM,int n,T_image_compressee IC)
{
  int i=0;
  while(i<n)
  {
    compresse_ligne(IM[i],&IC[i]);
    ++i;
  }

}

void decompresse_ligne(ptr_ligne_compressee LC, ptr_ligne * L)
{
	while (LC != NULL)
	{
		struct couple e = LC->pix;

		for (int i = 1; i <= e.nb; ++i)
      ajout(e.val,L);
		
		LC = LC->suiv;
	}
}

void decompresse_image(T_image_compressee IC,int n,T_image IM)
{
  int i=0;
  while(i<n)
  {
    decompresse_ligne(IC[i],&IM[i]);
    ++i;
  }

}


int main()
{
  
  creer_image(&im,&nbligne);
	printf("Image saisie\n\n");
	affiche(im,nbligne);

	//compresse_ligne(im[0],&imc[0]);
  //printf("\nLigne 1 compressee\n");
	//afficheLigneCompressee(imc[0]);

  compresse_image(im,nbligne,imc);
	printf("\nImage compressee\n\n");
  affichecompressee(imc,nbligne);
  
  //decompresse_ligne(imc[0],&(ima[0]));
  //printf("\nLigne 1 decompressee\n");
  //affiche(ima,1);

  decompresse_image(imc,nbligne,ima);
  printf("\nImage decompressee\n\n");
  affiche(ima,nbligne);

  printf("\n");

	return 0;
}





