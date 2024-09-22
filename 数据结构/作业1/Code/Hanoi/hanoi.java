import java.util.Scanner;

public class hanoi {
    public static void main (String[] args) {
        ZYJ game = new ZYJ();
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        game.solveHanoi(n, 'A', 'C', 'B');
        scanner.close();
    }
}

class ZYJ {
    int steps = 0;

    public void solveHanoi(int n, char from, char to, char by) {
        if (n == 1) {
            System.out.println("step " + (++steps) + ", plate " + n + ": " + from + "->" + to);
        } else {
            solveHanoi(n - 1, from, by, to);
            System.out.println("step " + (++steps) + ", plate " + n + ": " + from + "->" + to);
            solveHanoi(n - 1, by, to, from);
        }
    }
}
