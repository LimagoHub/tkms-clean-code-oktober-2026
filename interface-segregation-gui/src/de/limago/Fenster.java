package de.limago;


import java.awt.*;
import java.awt.event.*;

public class Fenster extends Frame  {


    public Fenster()  {

        setSize(300, 300);



        addWindowListener(new MyWindowListener());
        Button button = new Button("Drück mich");
        button.addActionListener(new MyActionListener());
        add(button);


    }



    public static void main(String[] args) {

        new Fenster().setVisible(true);
    }

    private void beenden() {
        dispose();
    }

    private void ausgabe() {
        System.out.println("Button wurde gedrückt");
    }


    private class MyActionListener implements ActionListener {

        @Override
        public void actionPerformed(final ActionEvent e) {
            ausgabe();
        }
    }

    private class MyWindowListener extends WindowAdapter {

        @Override
        public void windowClosing(final WindowEvent e) {
            beenden();
        }
    }
}
