package com.tp3;

public class PC_Tampon
{
    private char tableau [];
    private int taille;
    private int index;

    public PC_Tampon (int size)
    {
        this.taille  = size;
        this.index   = 0;
        this.tableau = new char [taille];
    }

    public boolean estVide ()
    {
        return (index == 0);
    }

    public boolean estPlein ()
    {
        return (index == taille);
    }

    public synchronized char retirer ()
    {
        try {
            while (estVide()) {
                System.out.println ("Consommateur endormi");
                wait();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        char c = tableau[0];

        for (int i=0; i<taille-1; i++) {
            tableau [i] = tableau [i+1];
        }

        index--;

        notifyAll();

        System.out.println ("On retire " + c );

        return c;
    }

    public synchronized void placer (char c)
    {
        try {
            while (estPlein()) {
                System.out.println("Producteur endormi");
                wait();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        tableau[index++] = c;

        System.out.println ("On place " + c );

        notifyAll();
    }
}
