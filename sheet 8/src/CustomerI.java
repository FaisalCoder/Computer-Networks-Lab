
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
public interface CustomerI extends Remote {

    public Account find(int id) throws IOException, ClassNotFoundException;
}
