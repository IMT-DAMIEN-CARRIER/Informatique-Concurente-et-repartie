import javax.swing.*;

public class Fenetre extends JFrame
 {
  public Fenetre ()
   {
    super ("Horloge");

    setResizable (true);    
    setBounds (700, 300, 400, 200);
    setVisible (true);
    setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
    setContentPane ( new Horloge());
   }
   
  public static void main (String args[]) 
   {
    new Fenetre ();
   }
 }
