
import java.io.IOException;
import java.io.Serializable;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author srgf-Ranjith
 */
public class Employee implements EmployeeI, Serializable {

    @Override
    public int add(String name, String address, String password) throws IOException {
        Account account = new Account(name, address, password);
        account.persist();
        return account.getId();
    }

    @Override
    public void delete(int id) throws IOException, ClassNotFoundException {
        Account.find(id).delete();
    }

    @Override
    public void updateName(int id, String newName) throws IOException, ClassNotFoundException {
        Account account = Account.find(id);
        account.setName(newName);
        account.persist();
    }

    @Override
    public void updateAddress(int id, String newAddress) throws IOException, ClassNotFoundException {
        Account account = Account.find(id);
        account.setAddress(newAddress);
        account.persist();
    }

    @Override
    public void updatePassword(int id, String newPassword) throws IOException, ClassNotFoundException {
        Account account = Account.find(id);
        account.setPassword(newPassword);
        account.persist();
    }
}
