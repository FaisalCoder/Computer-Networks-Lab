
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
public class EmployeeCLI {

    Scanner scanner;
    EmployeeI employeeI;

    public EmployeeCLI() throws NotBoundException, MalformedURLException, RemoteException {
        scanner = new Scanner(System.in);
        employeeI = (EmployeeI) Naming.lookup("rmi://localhost:5000/employee");
    }

    public void menu() throws IOException, ClassNotFoundException {
        System.out.println("1. Add Account");
        System.out.println("2. Delete Account");
        System.out.println("3. Update Account");
        System.out.print("Enter choice: ");
        int choice = scanner.nextInt();
        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                deleteAccount();
                break;
            case 3:
                updateAccount();
                break;
            default:
                System.out.println("Invalid Choice!");
                break;
        }
        System.out.println();
    }

    public void addAccount() throws IOException {
        System.out.print("Enter name: ");
        scanner.nextLine();
        String name = scanner.nextLine();
        System.out.print("Enter address: ");
        String address = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.next();
        int id = employeeI.add(name, address, password);
        System.out.println("Employee with id [" + id + "] added");
    }

    public void deleteAccount() throws IOException, ClassNotFoundException {
        System.out.println("Enter id: ");
        int id = scanner.nextInt();
        employeeI.delete(id);
    }

    public void updateAccount() throws IOException, ClassNotFoundException {
        System.out.print("Enter id: ");
        int id = scanner.nextInt();
        System.out.println("1. Update name");
        System.out.println("2. Update address");
        System.out.println("3. Update password");
        System.out.print("Enter choice: ");
        int choice = scanner.nextInt();
        scanner.nextLine();
        switch (choice) {
            case 1:
                System.out.print("Enter new name: ");
                String newName = scanner.nextLine();
                employeeI.updateName(id, newName);
                break;
            case 2:
                System.out.print("Enter new address: ");
                String newAddress = scanner.nextLine();
                employeeI.updateAddress(id, newAddress);
                break;
            case 3:
                System.out.print("Enter new password: ");
                String newPassword = scanner.nextLine();
                employeeI.updatePassword(id, newPassword);
                break;
            default:
                System.out.println("Invalid choice");
        }
    }

    public static void main(String[] args) throws NotBoundException, MalformedURLException, RemoteException, IOException, ClassNotFoundException {
        EmployeeCLI employeeCLI = new EmployeeCLI();
        while (true) {
            employeeCLI.menu();
        }
    }
}
