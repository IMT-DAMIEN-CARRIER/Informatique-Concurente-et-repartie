public class Tampon 
 {
  private int tableau [];
  private int taille;
  private int index;

  public Tampon (int size) 
   {
    this.taille  = size; 
    this.index   = 0;
    this.tableau = new int [taille];
   }

  public boolean estVide ()  { return (index == 0);    }
  public boolean estPlein () { return (index == taille); }

  public synchronized int retirer () 
   {
    try 
     { 
      while (estVide()) 
       {
        System.out.println ("Consommateur endormi");
        wait();
       }
     }
    catch (InterruptedException e) 
     {
      e.printStackTrace();
     }

    int val = tableau[--index];
    notifyAll();
    return val;
   }

    public synchronized void placer (int value) 
   {
    try 
     { 
      while (estPlein()) 
       {
        System.out.println("Producteur endormi");
        wait();
       }
     } 
    catch (InterruptedException e) 
     {
      e.printStackTrace();
     }

    tableau[index++] = value;
    notifyAll();
   }
 }
