
import java.io.IOException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author srgf-Ranjith
 */
public class Customer extends UnicastRemoteObject implements CustomerI{

    public Customer() throws RemoteException {

    }

    public Account find(int id) throws IOException, ClassNotFoundException {
        return Account.find(id);
    }
}
