public class PC_Main
 {
  public static void main ( String args [] )
   {
    if ( args.length != 2 )
          {
           System.err.println ("Usage : java PC_Main taille Chaine"); 
          }
     else {
           PC_Tampon       tampon       = new PC_Tampon       ( Integer.parseInt (args [0]) );
           PC_Consommateur consommateur = new PC_Consommateur ( tampon );
           PC_Producteur   producteur   = new PC_Producteur   ( tampon , args [1] );
           
           consommateur.start ();
           producteur.start ();
           
           try
            {
             consommateur.join ();
             producteur.join ();
            }
           catch ( InterruptedException ex )
            {
             System.err.println ("Probleme avec le join");
            }
          }
   }
 }
 
