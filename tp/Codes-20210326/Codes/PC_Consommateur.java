 
 
public class PC_Consommateur extends Thread
 {
  private PC_Tampon tampon;
  private String    chaineRecue;
  
  public PC_Consommateur ( PC_Tampon _tampon )
   {
    tampon      = _tampon;
    chaineRecue = new String ();
   }
   
  public void run ()
   {
    char c;

    do
     {
      c = tampon.retirer ();

      if ( c != '\0' )
       {
        chaineRecue += c;
       }
     }
     while ( c != '\0' );
     
    System.out.println ("Le consommateur a recu : " + chaineRecue );
   }
 }
