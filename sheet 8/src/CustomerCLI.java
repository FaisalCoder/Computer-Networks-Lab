
import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author srgf-Ranjith
 */
public class CustomerCLI {

    public static void main(String[] args) throws NotBoundException, MalformedURLException, RemoteException, IOException, ClassNotFoundException {
        CustomerI customer = (CustomerI) Naming.lookup("rmi://localhost:5000/customer");
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Enter id: ");
            int id = scanner.nextInt();
            Account account = customer.find(id);
            System.out.println(account);
            System.out.println();
        }
    }
}
