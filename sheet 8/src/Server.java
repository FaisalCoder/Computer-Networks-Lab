
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author srgf-Ranjith
 */
public class Server {

    public static void main(String[] args) throws RemoteException, MalformedURLException {
        Employee employee = new Employee();
        Naming.rebind("rmi://localhost:5000/employee", employee);
        Customer customer = new Customer();
        Naming.rebind("rmi://localhost:5000/customer", customer);
    }
}
