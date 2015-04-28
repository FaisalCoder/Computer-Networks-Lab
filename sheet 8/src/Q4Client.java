
import java.io.IOException;
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
public class Q4Client {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        
        Socket socket = new Socket("127.0.0.1", 8000);
        String remoteAddress = socket.getRemoteSocketAddress().toString();
        System.out.println("Remote Address: "+remoteAddress);
        String localAddress = socket.getLocalSocketAddress().toString();
        System.out.println("Local Address: "+localAddress);
    }
    
}
