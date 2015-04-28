
import java.io.IOException;
import java.net.ServerSocket;
import javax.net.ssl.SSLServerSocket;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author srgf-Ranjith
 */
public class Q4Server {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException, InterruptedException {
        ServerSocket serverSocket = new ServerSocket(8000);
        System.out.println("Server started");
        serverSocket.accept();
        Thread.sleep(600000);
    }
    
}
