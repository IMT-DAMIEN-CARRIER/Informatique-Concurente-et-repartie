 
public class PC_Producteur extends Thread
 {
  private PC_Tampon tampon;
  private String    chaineAEnvoyer;
  
  public PC_Producteur ( PC_Tampon _tampon         ,
                         String    _chaineAEnvoyer )
   {
    tampon         = _tampon;
    chaineAEnvoyer = _chaineAEnvoyer;
   }
   
  public void run ()
   {
    for (int i=0; i< chaineAEnvoyer.length(); i++)
     {
      tampon.placer (chaineAEnvoyer.charAt (i) );
     }
     
    tampon.placer ( '\0');
    
     
    System.out.println ("Le producteur a envoye : " + chaineAEnvoyer );
   }

 }
