
import java.io.IOException;
import java.rmi.Remote;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author srgf-Ranjith
 */
public interface EmployeeI extends Remote{
       public int add(String name, String address, String password) throws IOException;

    public void delete(int id) throws IOException, ClassNotFoundException;

    public void updateName(int id, String newName) throws IOException, ClassNotFoundException;

    public void updateAddress(int id, String newAddress) throws IOException, ClassNotFoundException ;

    public void updatePassword(int id, String newPassword) throws IOException, ClassNotFoundException ;
}
