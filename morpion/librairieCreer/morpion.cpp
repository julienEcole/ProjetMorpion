#include "Morpion.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "SNImage.h"
using namespace std;


Morpion::Morpion(){
	croix = 'X';
	vide = ' ';
    rond = 'O';
	pion = croix;
	scoreRond = 0;
	scoreCroix = 0;
}

char Morpion::Pion(){return pion;}
char Morpion::Croix(){return croix ;}
char Morpion::Vide(){return vide;}
char Morpion::Rond(){return rond;}
int Morpion::ScoreCroix(){return scoreCroix;}
int Morpion::ScoreRond(){return scoreRond;}

void Morpion::InitialiserGrille(){   //perso j'aurais int?grer ?a au constructeur mais bon c'est vrai qu'on l'utiliseras entre 2 manches
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			morpion[i][j] = vide;
		}
	}
}

bool Morpion::EnregistrerCoup(int ligne,int collone, char pion){
	if(ligne < 3&& ligne >= 0 && collone < 3 && collone >= 0 && morpion[ligne][collone] == vide){
		morpion[ligne][collone] = pion;
		if(pion == croix){           //on change le pion une fois le mouvement fait
			this->pion = rond;
		}
		else{
			this->pion = croix;
		}
		return true;
	}
	return false;
}

void Morpion::AfficherGrille(){                 //TODO utiliser l'image obtenu plutot que console, un mystere encore non r?solu
	cout << "  0   1   2\n";
	char separation[15] =  "-----------   ";
	for (int i = 0; i < 3; i++) {
		cout << i << " " << morpion[i][0] << " | " << morpion[i][1] << " | " << morpion[i][2] << '\n';
		if(i == 0){
			cout << separation << rond << " :   " << scoreRond << '\n';
		}
		else if( i == 1){
			cout << separation << croix << " :   " << scoreCroix << '\n';
		}
	}
}

void Morpion::SimulerGrille(){
	int alignement=0;
	for(char pion=rond; pion<=croix; pion+=(croix-rond)){
		for(int alignement=0;alignement<8;alignement++){
			InitialiserGrille();
		//lignes :
			if(alignement<3)
			{ for(int j=0;j<3;j++) morpion[alignement][j]=pion;}
		//colonnes :
		else
			if(alignement<6){
				for(int i=0;i<3;i++) morpion[i][alignement-3]=pion;
			}
		//diagonales
		else
			if(alignement==6){
				for(int i=0;i<3;i++) morpion[i][i]=pion;
			}
		else
			if(alignement==7){
				for(int i=0;i<3;i++) morpion[i][2-i]=pion;
			}
		AfficherGrille();
		cout<<"Gain : "<<VerifierGain()<<endl;
		}
	}
}



bool Morpion::GrilleComplete(){
    bool result = true;
	int i = 0,j = 0;
	while (result && i < 3){
		result = result && (morpion[i][j] != vide);
		if (j >= 2){
		   j = 0;
		   i++;
		}
		else{
			j++;
        }
	}
	return result;
}

char Morpion::VerifierGain(){
	char actual;
	for(int i = 0; i < 3; i++){
		actual = morpion[i][0];
		if(morpion[i][1] == morpion[i][2] && morpion[i][1] == actual && actual != vide){
			if(actual == croix){
				scoreCroix++;
			}
			else{
				scoreRond++;
            }
			return actual;
		}
        actual = morpion[0][i];
		if(morpion[1][i] == morpion[2][i] && morpion[1][i] == actual && actual != vide){
			if(actual == croix){
				scoreCroix++;
			}
			else{
				scoreRond++;
			}
			return actual;
		}

	}

												// pour les diagonales pasa la peine de boucle, sinon il aurait sufft de faire [x][y] et [2-x][y] x = 0 et x++
	 if((morpion[0][0] == morpion[1][1]&& morpion[0][0] == morpion[2][2]) || (morpion[2][0] == morpion[1][1] && morpion[2][0] == morpion[0][2])){
		if(morpion[1][1] == croix){
			scoreCroix++;
		}
		else if(morpion[1][1] == rond){
			scoreRond++;
        }
		return morpion[1][1];  					//est la m?me pour tous les cas et si vide cela ne change par resultat final
	 }
	 return vide;
}

void Morpion::TracerMorpionBMP(){        		//doit encore tracer les traits de s?parations
	SNImage img;
    img.Charger("morpion.bmp");
	Coordonnee debut,fin;
	Pixel couleur;
    couleur.rouge=0;
	couleur.bleu=0;
	couleur.vert=0;
	for(int i=0;i<4;i++){            			//vider l'ancienne image pour avoir que du blanc
		debut.ligne=200*(i%2+1)*(i<2);
		debut.colonne=200*(i%2+1)*(i>1);
		img.Colorier(debut,599*(i<2)+1,599*(i>1)+1,couleur);
	}
	for(int i = 0;i < 3; i++){
		for(int j = 0;j < 3; j++){
												//j'ai un doute quand au trac? de la verticale, je me demande si je tracee pas aussi les s?parations. je n'y croix plus trop finalement
			if(morpion[i][j] == croix){     	//on doit tracer une croix a i j;
				couleur.rouge=0;            	//on met la couleur des croix
				couleur.bleu=255;
				couleur.vert=0;
				debut.ligne=200*i+10;
				debut.colonne=200*j+10;
				fin.ligne=200*i+190;;
				fin.colonne=200*j+190;
				img.TracerDiagonale(debut,fin,1,couleur);
                debut.ligne=200*i+10;
                debut.colonne=200*j+190;
                fin.ligne=200*i+190;
                fin.colonne=200*j+10;
				img.TracerDiagonale(debut,fin,1,couleur);
			}
			else if(morpion[i][j] == rond){
				debut.ligne=200*i+10;           //on place le d?but du cerclle au bon endroit
				debut.colonne=200*j+190;  		//on doit tracer on rond
				couleur.rouge=255;           	//on met la couleur rouge des rond
				couleur.bleu=0;
				couleur.vert=0;
				img.TracerCercle(debut,90,1,couleur); 	//enfin on trace le cercle
			}									//le cas ouon ne doit rien tracer incremente juste juste j
		}
	}

    couleur.rouge=0;            	//on met la couleur des croix
	couleur.bleu=255;
	couleur.vert=0;
	//mettre le for pour tracer les s?parations
	for (int i = 0; i < 3; i++) {

		debut.ligne=200*i+10;
		debut.colonne=10;
		fin.ligne=200*i+10;;
		fin.colonne=610;
		img.TracerDiagonale(debut,fin,1,couleur);

		debut.ligne=10;
		debut.colonne=200*i+10;
		fin.ligne=610;
		fin.colonne=200*i+10;
		img.TracerDiagonale(debut,fin,1,couleur);
	}

	img.Sauvegarder("grillemorpion.bmp");		//a la fin ne pas oublier sauvegarder l'image

}
