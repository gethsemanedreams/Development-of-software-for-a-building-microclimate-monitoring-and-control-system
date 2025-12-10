// Простое Java-консольное приложение, которое запускает собранный C#-exe
// и пробрасывает его вывод в консоль Java.
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws Exception {
        // Относительный путь к собранному C#-exe относительно папки JavaWrapper.
        // Перед запуском Java-кода нужно выполнить dotnet publish для проекта MonitoringSystem.Cli.
        String exePath = "E:\\ДЗ\\Программирование\\Sem_3\\Lab_04\\Lab04\\MonitoringSystem.Cli\\bin\\Release\\net8.0\\MonitoringSystem.Cli.exe";

        ProcessBuilder pb = new ProcessBuilder(exePath);
        pb.redirectErrorStream(true);
        Process process = pb.start();

        System.out.println("=== Запуск C# мониторинга из Java ===");

        try (BufferedReader reader =
                     new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }

        int exitCode = process.waitFor();
        System.out.println("=== C# завершился с кодом " + exitCode + " ===");
    }
}
