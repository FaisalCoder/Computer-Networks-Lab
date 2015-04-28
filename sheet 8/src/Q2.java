
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author srgf-Ranjith
 */
public class Q2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        InetAddress inetAddress = InetAddress.getLocalHost();        
        System.out.println("Host and IP Address: "+inetAddress.toString());
    }

}
