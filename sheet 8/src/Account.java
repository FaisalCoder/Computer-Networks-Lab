
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
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
public class Account implements Serializable {

    private int id;
    private String name;
    private String address;
    private String password;

    public Account(String name, String address, String password) throws IOException {
        this.name = name;
        this.address = address;
        this.password = password;
        id = getNewId();
    }

    public static Account find(int id) throws IOException, ClassNotFoundException {
        ObjectInputStream objectInputStream = new ObjectInputStream(new FileInputStream("db\\" + id + ".txt"));
        Account account = (Account) objectInputStream.readObject();
        objectInputStream.close();
        return account;
    }

    public void persist() throws FileNotFoundException, IOException {
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(new FileOutputStream("db\\" + id + ".txt"));
        objectOutputStream.writeObject(this);
        objectOutputStream.close();
    }

    public void delete() {
        File file = new File("db\\" + id + ".txt");
        if (file.exists()) {
            file.delete();
        }
    }

    public static synchronized int getNewId() throws FileNotFoundException, IOException {
        File file = new File("db\\seq.txt");
        Scanner scanner = new Scanner(file);
        int id = scanner.nextInt();
        scanner.close();
        FileWriter fileWriter = new FileWriter(file);
        fileWriter.write((id + 1) + "");
        fileWriter.close();
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String toString() {
        return "Id: " + id + "\n"
                + "Name: " + name + "\n"
                + "Password: " + password;
    }
}
