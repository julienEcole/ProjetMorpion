#include <stdio.h>
#include <iostream>
#include <string.h>
#include <conio.h>
#include "librairieCreer/Morpion.h"


using namespace std;
char reponse='N', pionVictorieux=' ';
bool nouveau=true, coupValide;


int main(){
	Morpion monMorpion;
	int ligne,colonne;
	do{
		if(nouveau){
			monMorpion.InitialiserGrille();
			nouveau=false;
		}
		monMorpion.AfficherGrille();
		do{
			cout << "Indiquer la case (ex : 0 1) pour les " << monMorpion.Pion() << " : ";
			cin >> colonne>>ligne;
			//coupValide=monMorpion.EnregistrerCoup(ligne,colonne,monMorpion.Pion());  //je ne trouve pas le pb emppechant de retenir le changement du pion; trouv� rajouter this devant pion
		}while(!monMorpion.EnregistrerCoup(ligne,colonne,monMorpion.Pion()));
		pionVictorieux=monMorpion.VerifierGain();
		if(monMorpion.GrilleComplete()||pionVictorieux!=' '){
			monMorpion.AfficherGrille();
			if(pionVictorieux != monMorpion.Vide()){cout << "Victoire des " << pionVictorieux << endl;}
			else cout << "Partie nulle" << endl;
			cout << "Nouvelle partie O/N ? ";         //avant cette ligne les methodes sont a changer
			cin >> reponse;
			nouveau=true;
			clrscr();
		}
	}while(reponse=='O' || reponse =='o' || !nouveau);
}
