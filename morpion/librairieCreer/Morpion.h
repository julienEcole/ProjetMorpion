#ifndef MORPION_H
#define MORPION_H

class Morpion{
	private :
		char morpion[3][3];
		char rond, croix, vide, pion;
		int scoreRond, scoreCroix;

	public :
		Morpion();
		char Pion(); // debut accesseur
		char Rond();
		char Croix();
		char Vide();
		int ScoreRond();
		int ScoreCroix();   //fin accesseur
		void InitialiserGrille();
		void AfficherGrille();
		bool GrilleComplete();
		bool EnregistrerCoup(int ligne,int colone,char pion);
		char VerifierGain();
		void SimulerGrille();
		void TracerMorpionBMP();
};

#endif